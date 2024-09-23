// ReSharper disable CppInconsistentNaming
// ReSharper disable CppParameterMayBeConst
// ReSharper disable CppClangTidyClangDiagnosticMicrosoftCast
// ReSharper disable CppClangTidyClangDiagnosticUndefinedReinterpretCast
// ReSharper disable CppClangTidyClangDiagnosticShadow
// ReSharper disable CppClangTidyClangDiagnosticCastFunctionTypeStrict
#include "pch.h"

HMODULE hModule;
SYSTEM_BASIC_INFORMATION systemBasicInfo;

HRESULT(WINAPI* pRoGetActivationFactory)(HSTRING classId, REFIID iid, void** factory) = RoGetActivationFactory;

typedef HRESULT(__fastcall* FuncDllGetActivationFactory)(void*, void**);

FuncDllGetActivationFactory pDllGetActivationFactory;

void debug_printf(const char *format, ...) {
    char buffer[1024];  // Temporary buffer to hold the formatted string
    va_list args;
    
    // Start handling the variable argument list
    va_start(args, format);

    // Format the input string and store it in the buffer
    vsnprintf(buffer, sizeof(buffer), format, args);

    // End argument handling
    va_end(args);

    // Send the formatted string to the debugger
    OutputDebugStringA(buffer);
}

HRESULT WINAPI RoGetActivationFactory_Hook(HSTRING classId, REFIID iid, void** factory)
{
    const wchar_t* classIdStr = WindowsGetStringRawBuffer(classId, nullptr);
    int result = pRoGetActivationFactory(classId, iid, factory);

    // Failed, redirect to our winrt component
    if (result < 0) {
        debug_printf("[DEBUG] Forwarding activationFactory of %ls to our dll!", classIdStr);
        
		// Checks if we initialized pointer to our DllGetActivationFactory
        if (!pDllGetActivationFactory) {
	        const HMODULE winrtLib = LoadLibraryA("winrt_x.dll");

            debug_printf("[DEBUG] winrtLib: %i\n", winrtLib);
            
			if (!winrtLib)
                return result;

            pDllGetActivationFactory = reinterpret_cast<FuncDllGetActivationFactory>(GetProcAddress(winrtLib, "DllGetActivationFactory"));
            
			debug_printf("[DEBUG] pDllGetActivationFactory: %i\n", pDllGetActivationFactory);

            if (!pDllGetActivationFactory)
                return result;
        }

        result = pDllGetActivationFactory(classId, factory);
        
        if (result < 0)
            return result;

        return result;
    }

    return result;
}

LPTOP_LEVEL_EXCEPTION_FILTER RtlSetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)
{
	return SetUnhandledExceptionFilter(lpTopLevelExceptionFilter);
}

// 100% the same as the original code besides the added detour code - VodkaDoc
BOOL __stdcall DllEntryPoint(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpReserved)
{
	BOOL isInit = FALSE;
	ANSI_STRING DestinationString;

	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DetourRestoreAfterWith();
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&reinterpret_cast<PVOID&>(pRoGetActivationFactory), RoGetActivationFactory_Hook);
		DetourTransactionCommit();

		if (NtQuerySystemInformation(SystemBasicInformation, &systemBasicInfo, 0x40u, nullptr) >= 0)
		{
			const auto peb = NtCurrentPeb();
			const auto processParams = static_cast<RTL_USER_PROCESS_PARAMETERS*>(peb->ProcessParameters); // Cast ProcessParameters
			
			if (RtlUnicodeStringToAnsiString(&DestinationString, &processParams->CommandLine, 1u) < 0)
			{
				DestinationString.Length = 0i64;
				DestinationString.Buffer = nullptr;
			}

			RtlSetUnhandledExceptionFilter(UnhandledExceptionFilter);
		}
		else
			isInit = FALSE;


		hModule = hInstance;

		// ConfigureLocaleSettings(); Incomplete
	}
	else
	{
		isInit = true;
		if (!fdwReason == DLL_PROCESS_DETACH)
		{
			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());
			DetourDetach(&reinterpret_cast<PVOID&>(pRoGetActivationFactory), RoGetActivationFactory_Hook);
			DetourTransactionCommit();
			
			// CleanupResources(hInstance, fdwReason, lpReserved); Incomplete
		}
	}

	return isInit;
}