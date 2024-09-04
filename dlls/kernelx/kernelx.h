#pragma once

#include "framework.h"
// EXE EXPORTS
#define KernalX __declspec( dllexport )
KernalX void AcquireSRWLockExclusive_X(PSRWLOCK SRWLock);

KernalX void AcquireSRWLockShared_X(PSRWLOCK SRWLock);

KernalX void EnterCriticalSection_X(LPCRITICAL_SECTION lpCriticalSection);

KernalX HANDLE GetProcessHeap_X();

// TODO: Need to figure out this function.
KernalX PVOID XMemAllocDefault_X(ULONG_PTR a1, UINT64 a2);


KernalX PVOID XMemAlloc_X(SIZE_T dwSize, ULONGLONG dwAttributes);

PVOID RtlSetUnhandledExceptionFilter(PVOID ExceptionFilter);

__int64 sub_18001BB8C();

char sub_18001BCA0(HINSTANCE hInstance, DWORD forwardReason, LPVOID lpvReserved);