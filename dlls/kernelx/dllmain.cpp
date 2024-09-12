// ReSharper disable CppInconsistentNaming
// ReSharper disable CppParameterMayBeConst
// ReSharper disable CppClangTidyClangDiagnosticMicrosoftCast
// ReSharper disable CppClangTidyClangDiagnosticUndefinedReinterpretCast
// ReSharper disable CppClangTidyClangDiagnosticShadow
// ReSharper disable CppClangTidyClangDiagnosticCastFunctionTypeStrict
#include "pch.h"


typedef HRESULT(*DllGetActivationFactoryFunc) (HSTRING, IActivationFactory**);

DllGetActivationFactoryFunc pDllGetActivationFactory = nullptr;


HRESULT(WINAPI* TrueRoGetActivationFactory)(HSTRING classId, REFIID iid, void** factory) = RoGetActivationFactory;

HRESULT WINAPI RoGetActivationFactory_Hook(HSTRING classId, REFIID iid, void** factory)
{
	auto hr = TrueRoGetActivationFactory(classId, iid, factory);

	const std::wstring message = std::wstring(L"classId: ") + 
		WindowsGetStringRawBuffer(classId, nullptr);

	if (FAILED(hr))
	{
		Microsoft::WRL::ComPtr<IActivationFactory> _factory{};

		auto library = LoadPackagedLibrary(L"winrt_x.dll", 0);

		if (!library)
			library = LoadLibraryW(L"winrt_x.dll");

		auto error = GetLastError();

		if (library) 
		{
			pDllGetActivationFactory = reinterpret_cast<DllGetActivationFactoryFunc>(GetProcAddress(library, "DllGetActivationFactory"));

			if (pDllGetActivationFactory)
				hr = pDllGetActivationFactory(classId, _factory.GetAddressOf());
		}
	}

	return hr;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID reserved)
{    
	if (DetourIsHelperProcess()) return TRUE;

	if (dwReason == DLL_PROCESS_ATTACH) 
	{
		DetourRestoreAfterWith();
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&reinterpret_cast<PVOID&>(TrueRoGetActivationFactory), RoGetActivationFactory_Hook);
		DetourTransactionCommit();
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&reinterpret_cast<PVOID&>(TrueRoGetActivationFactory), RoGetActivationFactory_Hook);
		DetourTransactionCommit();
	}

	return TRUE;
}
