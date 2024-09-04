#pragma once

#include "framework.h"

// EXE EXPORTS
extern "C" void AcquireSRWLockExclusive_X(PSRWLOCK SRWLock);

extern "C" void AcquireSRWLockShared_X(PSRWLOCK SRWLock);

extern "C" void EnterCriticalSection_X(LPCRITICAL_SECTION lpCriticalSection);

extern "C" HANDLE GetProcessHeap_X();

// TODO: Need to figure out this function.
extern "C" PVOID XMemAllocDefault_X(ULONG_PTR a1, UINT64 a2);

extern "C" PVOID XMemAlloc_X(SIZE_T dwSize, ULONGLONG dwAttributes);

// EXE EXPORTS END


PVOID RtlSetUnhandledExceptionFilter(PVOID ExceptionFilter);

__int64 sub_18001BB8C();

NTSTATUS sub_18001BCA0(HINSTANCE hInstance, DWORD forwardReason, LPVOID lpvReserved);