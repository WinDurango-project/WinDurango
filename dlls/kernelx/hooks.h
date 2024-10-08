// ReSharper disable CppInconsistentNaming
// ReSharper disable CppParameterMayBeConst
// ReSharper disable CppClangTidyClangDiagnosticMicrosoftCast
// ReSharper disable CppClangTidyClangDiagnosticUndefinedReinterpretCast
// ReSharper disable CppClangTidyClangDiagnosticShadow
// ReSharper disable CppClangTidyClangDiagnosticCastFunctionTypeStrict
// ReSharper disable CppFunctionalStyleCast
// ReSharper disable CppClangTidyClangDiagnosticCastAlign
// ReSharper disable CppClangTidyClangDiagnosticCastQual
// ReSharper disable CppZeroConstantCanBeReplacedWithNullptr
#pragma once

inline bool IsClassName(HSTRING classId, const char* classIdName)
{
	const wchar_t* classIdString = WindowsGetStringRawBuffer(classId, nullptr);
	std::wstring classIdWString(classIdString);
	const std::string classIdStringUTF8(classIdWString.begin(), classIdWString.end());

	return (classIdStringUTF8 == classIdName);
}

typedef HRESULT(*DllGetActivationFactoryFunc) (HSTRING, IActivationFactory**);
typedef HRESULT(*DllGetForCurrentThreadFunc) (CoreWindow**);

DllGetActivationFactoryFunc pDllGetActivationFactory = nullptr;
DllGetForCurrentThreadFunc pDllGetForCurrentThread = nullptr;

HRESULT(STDMETHODCALLTYPE* TrueGetForCurrentThread)(CoreWindow** window);
HRESULT(WINAPI* TrueRoGetActivationFactory)(HSTRING classId, REFIID iid, void** factory) = RoGetActivationFactory;

void* GetForCurrentThread = nullptr;

inline HRESULT STDMETHODCALLTYPE GetForCurrentThread_Hook(CoreWindow** window)
{
	return S_OK;
}

inline HRESULT WINAPI RoGetActivationFactory_Hook(HSTRING classId, REFIID iid, void** factory)
{
	auto hr = TrueRoGetActivationFactory(classId, iid, factory);

	if (FAILED(hr))
	{
		auto library = LoadPackagedLibrary(L"winrt_x.dll", 0);

		if (!library) library = LoadLibraryW(L"winrt_x.dll");

		if (!library) return hr;

		pDllGetActivationFactory = reinterpret_cast<DllGetActivationFactoryFunc>
			(GetProcAddress(library, "DllGetActivationFactory"));

		if (!pDllGetActivationFactory)
			return hr;

		ComPtr<IActivationFactory> _factory;


		if (IsClassName(classId, "Windows.UI.Core.CoreWindow"))
		{
			ComPtr<ICoreWindowStatic> coreWindowStatic;

			hr = RoGetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Core_CoreWindow).Get(), IID_PPV_ARGS(&coreWindowStatic));

			GetForCurrentThread = (*reinterpret_cast<void***>(coreWindowStatic.Get()))[6];

			DetourAttach(&GetForCurrentThread, GetForCurrentThread_Hook);
		}
		else
		{
			hr = pDllGetActivationFactory(classId, _factory.GetAddressOf());
		}

		if (FAILED(hr)) return hr;

		return _factory.CopyTo(iid, factory);
	}

	return hr;
}