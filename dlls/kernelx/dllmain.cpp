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
            //Probably have to change this to SetUnhandledExceptionFilter
            SetUnhandledExceptionFilter(UnhandledExceptionFilter);
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
}


