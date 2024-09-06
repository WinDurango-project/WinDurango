#include "pch.h"
#include "kernelx.h"
#include <cstdlib>

ANSI_STRING* DestinationString;
SYSTEM_BASIC_INFORMATION* System_Info;

HINSTANCE hModule;

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD forwardReason, LPVOID lpvReserved)
{
    BOOL result = TRUE; // Default to TRUE for all cases
    switch (forwardReason)
    {
    case DLL_PROCESS_ATTACH:
        // Allocate and initialize the global pointers
        DestinationString = (ANSI_STRING*)malloc(sizeof(ANSI_STRING));
        if (!DestinationString) {
            return FALSE; // Fail if memory allocation fails
        }
        System_Info = (SYSTEM_BASIC_INFORMATION*)malloc(sizeof(SYSTEM_BASIC_INFORMATION));
        if (!System_Info) {
            free(DestinationString); // Clean up previously allocated memory
            return FALSE;
        }

        if (NtQuerySystemInformation(SystemBasicInformation, System_Info, sizeof(SYSTEM_BASIC_INFORMATION), NULL) < 0) {
            free(DestinationString); // Clean up
            free(System_Info);
            return FALSE; // Fail if system info can't be obtained
        }

        DestinationString->Buffer = (char*)malloc(1024); // Allocate buffer for ANSI string
        if (!DestinationString->Buffer) {
            free(DestinationString); // Clean up
            free(System_Info);
            return FALSE;
        }
        DestinationString->Length = 0;
        DestinationString->MaximumLength = 1024;

        if (RtlUnicodeStringToAnsiString(DestinationString, &NtCurrentTeb()->ProcessEnvironmentBlock->ProcessParameters->CommandLine, FALSE) < 0) {
            free(DestinationString->Buffer); // Clean up
            free(DestinationString);
            free(System_Info);
            return FALSE;
        }

        // Set exception handler
        SetUnhandledExceptionFilter(UnhandledExceptionFilter);
        hModule = hInstance;
        sub_18001BB8C();
        break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        // Perform cleanup on process detach
        if (forwardReason == DLL_PROCESS_DETACH) {
            if (DestinationString) {
                if (DestinationString->Buffer)
                    free(DestinationString->Buffer);
                free(DestinationString);
            }
            if (System_Info) {
                free(System_Info);
            }
        }
        result = sub_18001BCA0(hInstance, forwardReason, lpvReserved);
        break;
    }

    return result;
}
