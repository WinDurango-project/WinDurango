#pragma once
#include <winrt/Windows.ApplicationModel.h>


#include "CoreApplicationWrapperX.h"


/* This function is used to compare the class name of the classId with the classIdName. */
inline bool IsClassName(HSTRING classId, const char* classIdName)
{
	const wchar_t* classIdString = WindowsGetStringRawBuffer(classId, nullptr);
	std::wstring classIdWString(classIdString);
	const std::string classIdStringUTF8(classIdWString.begin(), classIdWString.end());

	return (classIdStringUTF8 == classIdName);
}

/* Function pointers for the DllGetForCurrentThread */
typedef HRESULT(*DllGetForCurrentThreadFunc) (ICoreWindowStatic*, CoreWindow**);
/* Function pointers for the DllGetForCurrentThread */
DllGetForCurrentThreadFunc pDllGetForCurrentThread = nullptr;
/* Function pointers for the DllGetForCurrentThread */
HRESULT(STDMETHODCALLTYPE* TrueGetForCurrentThread)(ICoreWindowStatic* staticWindow, CoreWindow** window);
/* Function pointers for the DllGetActivationFactory */
typedef HRESULT(*DllGetActivationFactoryFunc) (HSTRING, IActivationFactory**);
/* Function pointers for the DllGetActivationFactory */
DllGetActivationFactoryFunc pDllGetActivationFactory = nullptr;
/* Function pointers for the WinRT RoGetActivationFactory function. */
HRESULT(WINAPI* TrueRoGetActivationFactory)(HSTRING classId, REFIID iid, void** factory) = RoGetActivationFactory;

// As Zombie suggested, this check if the function get called from a xbox dll or not
BOOL IsXboxModule(HMODULE module)
{
	// probably better to check for dlls in the game folder but idk this works i think
	wchar_t moduleFilePath[MAX_PATH];
	if (GetModuleFileNameW(module, moduleFilePath, MAX_PATH) > 0)
	{
		std::wstring moduleFileName(moduleFilePath);
		wprintf(L"%ls\n", moduleFileName.c_str());

		// Testing (i'll complete those)

		/*if (!(moduleFileName.find(L"CoreUIComponents") != std::wstring::npos)) // Example check for "Xbox" in the file name
		{
			return TRUE; // The caller is from an Xbox module
		}*/
	}

	return FALSE;
}


BOOL IsXboxAddress(PVOID Address)
{
	HMODULE Module;

	// Technically this should also use 'GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT'
	if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)Address, &Module))
		return FALSE;

	return IsXboxModule(Module);
}


// The hook function for GetForCurrentThread
HRESULT STDMETHODCALLTYPE GetForCurrentThread_Hook(ICoreWindowStatic* pThis, CoreWindow** ppWindow)
{
	HRESULT hr = TrueGetForCurrentThread(pThis, ppWindow);
	if (FAILED(hr))
	{
		return hr;
	}

	if (*ppWindow == NULL)
		return hr;

	// if GetForCurrentThread is called from xbox code we wrap it with the xbox ICoreWindow
	if (IsXboxAddress(_ReturnAddress()))
	{
		*reinterpret_cast<ICoreWindowX**>(ppWindow) = new CoreWindowWrapperX(*ppWindow);

		return S_OK;
	}

	return hr;
}


/* Hook for the WinRT RoGetActivationFactory function. */
inline HRESULT WINAPI RoGetActivationFactory_Hook(HSTRING classId, REFIID iid, void** factory)
{
	// Get the raw buffer from the HSTRING
	const wchar_t* rawString = WindowsGetStringRawBuffer(classId, nullptr);

	if (rawString) {
		// Print the string using wprintf
		wprintf(L"%ls\n", rawString);
	}
	auto hr = 0;

	if (IsClassName(classId, "Windows.ApplicationModel.Core.CoreApplication"))
	{
		ComPtr<IActivationFactory> realFactory;

		hr = TrueRoGetActivationFactory(HStringReference(RuntimeClass_Windows_ApplicationModel_Core_CoreApplication).Get(), IID_PPV_ARGS(&realFactory));

		if (FAILED(hr))
			return hr;

		ComPtr<CoreApplicationWrapperX> wrappedFactory = Make<CoreApplicationWrapperX>(realFactory);

		return wrappedFactory.CopyTo(iid, factory);
	}
	else if (IsClassName(classId, "Windows.UI.Core.CoreWindow"))
	{
		//
		// for now we just hook GetForCurrentThread to get the CoreWindow but i'll change it later to
		// wrap ICoreWindowStatic or as zombie said another thing that works is by hooking IFrameworkView::SetWindow
		// but for now this *should* work just fine -AleBlbl
		//
		ComPtr<ICoreWindowStatic> coreWindowStatic;
		hr = TrueRoGetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Core_CoreWindow).Get(), IID_PPV_ARGS(&coreWindowStatic));
		if (FAILED(hr)) {
			return hr;
		}

		if (!TrueGetForCurrentThread)
		{
			*reinterpret_cast<void**>(&TrueGetForCurrentThread) = (*reinterpret_cast<void***>(coreWindowStatic.Get()))[6];

			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());
			DetourAttach(&TrueGetForCurrentThread, GetForCurrentThread_Hook);
			DetourTransactionCommit();
		}

		return coreWindowStatic.CopyTo(iid, factory);
	}

	// After WinDurango overrides try to load the rest

	hr = TrueRoGetActivationFactory(classId, iid, factory);

	if (FAILED(hr))
	{
		if (!pDllGetActivationFactory)
		{
			auto library = LoadPackagedLibrary(L"winrt_x.dll", 0);

			if (!library) library = LoadLibraryW(L"winrt_x.dll");

			if (!library) return hr;

			pDllGetActivationFactory = reinterpret_cast<DllGetActivationFactoryFunc>
				(GetProcAddress(library, "DllGetActivationFactory"));

			if (!pDllGetActivationFactory)
				return hr;
		}


		// fallback
		ComPtr<IActivationFactory> fallbackFactory;
		hr = pDllGetActivationFactory(classId, fallbackFactory.GetAddressOf());

		if (FAILED(hr))
			return hr;

		return fallbackFactory.CopyTo(iid, factory);
	}

	return hr;
}