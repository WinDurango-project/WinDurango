// ReSharper disable CppInconsistentNaming
// ReSharper disable CppParameterMayBeConst
// ReSharper disable CppClangTidyClangDiagnosticMicrosoftCast
// ReSharper disable CppClangTidyClangDiagnosticUndefinedReinterpretCast
#include "pch.h"

typedef HRESULT (WINAPI* FuncRoGetActivationFactory)(HSTRING, REFIID, void**);

FuncRoGetActivationFactory pRoGetActivationFactory = RoGetActivationFactory;

HRESULT WINAPI RoGetActivationFactory_Hook(HSTRING classId, REFIID iid, void** factory)
{
    const wchar_t* classIdStr = WindowsGetStringRawBuffer(classId, nullptr);

    if (wcscmp(classIdStr, L"Windows.ApplicationModel.Core.CoreApplication") == 0) 
    {
		MessageBox(nullptr, L"RoGetActivationFactory", L"classId: Windows.ApplicationModel.Core.CoreApplication", MB_OK);
    }

    return S_OK;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID reserved)
{    
    if (DetourIsHelperProcess()) return TRUE;

    if (dwReason == DLL_PROCESS_ATTACH) 
    {
        DetourRestoreAfterWith();

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());

        DetourAttach(&reinterpret_cast<PVOID&>(pRoGetActivationFactory), RoGetActivationFactory_Hook);

        DetourTransactionCommit();
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
        
        DetourDetach(&reinterpret_cast<PVOID&>(pRoGetActivationFactory), RoGetActivationFactory_Hook);

        DetourTransactionCommit();
    }

    return TRUE;
}
