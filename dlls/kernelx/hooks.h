#pragma once
#include <winrt/Windows.ApplicationModel.h>

#include "CoreApplicationWrapperX.h"

/* This function is used to compare the class name of the classId with the classIdName. */
inline bool IsClassName(HSTRING classId, const char* classIdName)
{
	const wchar_t* classIdString = WindowsGetStringRawBuffer(classId, nullptr);
	std::wstring classIdWString(classIdString);
	const std::string classIdStringUTF8(classIdWString.begin( ), classIdWString.end( ));

	return (classIdStringUTF8 == classIdName);
}

/* Function pointers for the DllGetForCurrentThread */
typedef HRESULT(*DllGetForCurrentThreadFunc) (ICoreWindowStatic*, CoreWindow**);
/* Function pointers for the DllGetForCurrentThread */
typedef HRESULT(*DllGetForCurrentThreadFunc_App) (ICoreApplication*, winrt::Windows::ApplicationModel::Core::CoreApplication**);
/* Function pointers for the CoreApplicationFactory's QueryInterface */
typedef HRESULT(*CoreApplicationFactory_QueryInterface) (IUnknown* pFactory, REFIID iid, void** ppv);
/* Function pointers for the DllGetActivationFactory */
typedef HRESULT(*DllGetActivationFactoryFunc) (HSTRING, IActivationFactory**);

/* Function pointers for the DllGetForCurrentThread */
DllGetForCurrentThreadFunc pDllGetForCurrentThread = nullptr;
/* Function pointers for the DllGetForCurrentThread */
DllGetForCurrentThreadFunc_App pDllGetForCurrentThread_App = nullptr;
/* Function pointers for the DllGetActivationFactory */
DllGetActivationFactoryFunc pDllGetActivationFactory = nullptr;

/* Function pointers for the DllGetForCurrentThread */
HRESULT(STDMETHODCALLTYPE* TrueGetForCurrentThread)(ICoreWindowStatic* staticWindow, CoreWindow** window);
/* Function pointers for the DllGetForCurrentThread */
HRESULT(STDMETHODCALLTYPE* TrueGetForCurrentThread_App)(ICoreApplication* application, winrt::Windows::ApplicationModel::Core::CoreApplication** Application);
/* Function pointers for the WinRT RoGetActivationFactory function. */
HRESULT(WINAPI* TrueRoGetActivationFactory)(HSTRING classId, REFIID iid, void** factory) = RoGetActivationFactory;

/* Hook for ICoreWindowStatic's GetCurrentThread function. */
inline HRESULT STDMETHODCALLTYPE GetForCurrentThread_Hook(ICoreWindowStatic* paramThis, CoreWindow** window)
{
	// ReSharper disable once CppLocalVariableMayBeConst
	HRESULT hr = TrueGetForCurrentThread(paramThis, window);

	//*reinterpret_cast<void**>(window) = new CoreWindowX(*window);
	auto p = *reinterpret_cast<void**>(window);

	p = new CoreWindowX(*window);

	return hr;
}

/* Hook for CoreApplication's GetForCurrentThread function. */
inline HRESULT STDMETHODCALLTYPE GetForCurrentThreadCoreApplication_Hook(ICoreApplication* paramThis, winrt::Windows::ApplicationModel::Core::CoreApplication** Application)
{
	wprintf(L"SAsa");
	// ReSharper disable once CppLocalVariableMayBeConst
	HRESULT hrApp = TrueGetForCurrentThread_App(paramThis, Application);

	auto pApp = *reinterpret_cast<void**>(Application);

	//pApp = new CoreApplicationWrapperX(*Application);

	return hrApp;
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


		//ComPtr<ICoreApplicationX> wrappedFactory = Make<ICoreApplicationX>(realFactory.Get());
		ComPtr<CoreApplicationWrapperX> wrappedFactory = Make<CoreApplicationWrapperX>(realFactory);

		return wrappedFactory.CopyTo(iid, factory);
	}
	else if (IsClassName(classId, "Windows.UI.Core.CoreWindow"))
	{
		/*ComPtr<ICoreWindowStatic> coreWindowStatic;

		hr = RoGetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Core_CoreWindow).Get(), IID_PPV_ARGS(&coreWindowStatic));

		*reinterpret_cast<void**>(&TrueGetForCurrentThread) = (*reinterpret_cast<void***>(coreWindowStatic.Get()))[6];

		DetourAttach(&TrueGetForCurrentThread, GetForCurrentThread_Hook);*/
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