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

void AcquireSRWLockExclusive_X(PSRWLOCK SRWLock)
{
	AcquireSRWLockExclusive(SRWLock);
}

void AcquireSRWLockShared_X(PSRWLOCK SRWLock)
{
	AcquireSRWLockShared(SRWLock);
}

void EnterCriticalSection_X(LPCRITICAL_SECTION lpCriticalSection)
{
	EnterCriticalSection(lpCriticalSection);
}

HANDLE GetProcessHeap_X()
{
	return GetProcessHeap();
}

// TODO: Need to figure out this function.
PVOID XMemAllocDefault_X(ULONG_PTR a1, UINT64 a2)
{
	return nullptr;
}


PVOID XMemAlloc_X(SIZE_T dwSize, ULONGLONG dwAttributes)
{
	return XMemAllocDefault_X(dwSize, dwAttributes);
}