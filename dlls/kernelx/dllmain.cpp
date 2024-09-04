// ReSharper disable CppInconsistentNaming
// ReSharper disable CppParameterMayBeConst
// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement
// ReSharper disable CppClangTidyHicppMultiwayPathsCovered
// ReSharper disable CppClangTidyClangDiagnosticInconsistentDllimport
#include "pch.h"
#include "kernelx.h"



ANSI_STRING* DestinationString;
SYSTEM_BASIC_INFORMATION* System_Info;

HINSTANCE hModule;



BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD forwardReason, LPVOID lpvReserved)
{

    

    BOOL v4;
	switch (forwardReason)
	{
	case DLL_PROCESS_ATTACH:

        if (NtQuerySystemInformation(SystemBasicInformation, &System_Info, 0x40u, 0LL) >= 0)
        {
            v4 = true;
            if (RtlUnicodeStringToAnsiString(DestinationString OUT, &NtCurrentTeb()->ProcessEnvironmentBlock->ProcessParameters->CommandLine, true) < 0)
            {
                DestinationString->Length = 0LL;
                DestinationString->Buffer = 0LL;
            }
            RtlSetUnhandledExceptionFilter(UnhandledExceptionFilter);
        }
        else
        {
            v4 = 0;
        }
        hModule = hInstance;
        sub_18001BB8C();
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
        v4 = 1;
        sub_18001BCA0(hInstance, forwardReason, lpvReserved);
		break;
	}

	return TRUE;

    /*BOOL v4; // ebx

    if (fdwReason == 1)
    {
        if (NtQuerySystemInformation(SystemBasicInformation, &unk_18002C900, 0x40u, 0LL) >= 0)
        {
            v4 = 1;
            if (RtlUnicodeStringToAnsiString(&DestinationString, &NtCurrentPeb()->ProcessParameters->CommandLine, 1u) < 0)
            {
                *(_QWORD*)&DestinationString.Length = 0LL;
                DestinationString.Buffer = 0LL;
            }
            RtlSetUnhandledExceptionFilter((PRTLP_UNHANDLED_EXCEPTION_FILTER)UnhandledExceptionFilter);
        }
        else
        {
            v4 = 0;
        }
        hModule = hinstDLL;
        sub_18001BB8C();
    }
    else
    {
        v4 = 1;
        if (!fdwReason)
            sub_18001BCA0(hinstDLL, fdwReason, lpReserved);
    }
    return v4;*/
}


