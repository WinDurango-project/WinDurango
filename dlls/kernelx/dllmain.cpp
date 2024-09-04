// ReSharper disable CppInconsistentNaming
// ReSharper disable CppParameterMayBeConst
// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement
// ReSharper disable CppClangTidyHicppMultiwayPathsCovered
// ReSharper disable CppClangTidyClangDiagnosticInconsistentDllimport
#include "pch.h"
#include "framework.h"

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD forwardReason, LPVOID lpvReserved)
{
	switch (forwardReason)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}

void AcquireSRWLockExclusive(PSRWLOCK SRWLock)
{
	
}

void AcquireSRWLockShared(PSRWLOCK SRWLock)
{

}

void EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
{

}

HANDLE GetProcessHeap()
{
	return nullptr;
}

NTSYSAPI VOID RtlCaptureContext(PCONTEXT ContextRecord)
{

}

// dwSize - size of allocated memory block that was requested.
// dwAttributes - allocated memory block attributes.
//
// returns a pointer allocated memory block.
PVOID XMemAlloc(SIZE_T dwSize, ULONGLONG dwAttributes)
{
	return nullptr;
}
