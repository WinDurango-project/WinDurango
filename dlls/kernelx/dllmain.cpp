// ReSharper disable CppInconsistentNaming
// ReSharper disable CppParameterMayBeConst
// ReSharper disable CppClangTidyClangDiagnosticMicrosoftCast
// ReSharper disable CppClangTidyClangDiagnosticUndefinedReinterpretCast
// ReSharper disable CppClangTidyClangDiagnosticShadow
// ReSharper disable CppClangTidyClangDiagnosticCastFunctionTypeStrict
#include "pch.h"

typedef HRESULT (WINAPI *GetActivationFactory)(HSTRING classId, IActivationFactory** factory);

HRESULT(WINAPI* TrueRoGetActivationFactory)(HSTRING classId, REFIID iid, void** factory) = RoGetActivationFactory;

HRESULT WINAPI RoGetActivationFactory_Hook(HSTRING classId, REFIID iid, void** factory)
{
	auto hr = TrueRoGetActivationFactory(classId, iid, factory);

	const std::wstring message = std::wstring(L"classId: ") + WindowsGetStringRawBuffer(classId, nullptr);

    if (FAILED(hr))
    {
		MessageBox(nullptr, message.c_str(), L"RoGetActivationFactory Failed", MB_OK);

        auto library = LoadLibraryW(L"winrt_x.dll");

		GetActivationFactory pGetActivationFactory = reinterpret_cast<GetActivationFactory>(GetProcAddress(
			(HMODULE)library, "GetActivationFactory_X"));

        Microsoft::WRL::ComPtr<IActivationFactory> _factory{};

        auto b = _factory.GetAddressOf();

        hr = pGetActivationFactory(classId, _factory.GetAddressOf());
    }
    else
    {
		MessageBox(nullptr, message.c_str(), L"RoGetActivationFactory Success", MB_OK);
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
