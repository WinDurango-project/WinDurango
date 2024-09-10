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

    MessageBox(nullptr, message.c_str(), L"RoGetActivationFactory Success", MB_OK);

    if (FAILED(hr))
    {
		MessageBox(nullptr, message.c_str(), L"RoGetActivationFactory Failed", MB_OK);

		const auto pGetActivationFactory = reinterpret_cast<GetActivationFactory>(
            GetProcAddress(
                GetModuleHandle(
                    TEXT("winrt_x.dll")), "GetActivationFactory_X"));

        Microsoft::WRL::ComPtr<IActivationFactory> _factory{};

        auto b = _factory.GetAddressOf();

        hr = pGetActivationFactory(classId, _factory.GetAddressOf());
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
