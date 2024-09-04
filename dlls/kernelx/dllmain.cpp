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

/*
NTSYSAPI VOID RtlCaptureContext_X(PCONTEXT ContextRecord)
{

}
*/

// dwSize - size of allocated memory block that was requested.
// dwAttributes - allocated memory block attributes.
//
// returns a pointer allocated memory block.

/*
ULONGLONG __fastcall XMemAlloc(ULONG64 a1, __int64 a2)
{
	ULONGLONG v4; // rbx
	_EVENT_TRACE_HEADER TraceHeader; // [rsp+20h] [rbp-48h] BYREF
	__int64 v7; // [rsp+50h] [rbp-18h]

	v4 = off_18002B1B8();
	if (MEMORY[0x7FFE0390] && v4)
	{
		*(&TraceHeader.GuidPtr + 1) = v4;
		TraceHeader.Class.Version = 3104;
		TraceHeader.ProcessorTime = a1;
		v7 = a2;
		NtTraceEvent(MEMORY[0x7FFE0390], 0x10402u, 0x18u, &TraceHeader);
	}
	return v4;
}
*/

PVOID XMemAlloc_X(SIZE_T dwSize, ULONGLONG dwAttributes)
{
	return VirtualAlloc(nullptr, dwSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
}
