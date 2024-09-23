#pragma once

typedef NTSTATUS(NTAPI* NtAllocateVirtualMemory_t)(
	HANDLE ProcessHandle,
	PVOID* BaseAddress,
	ULONG_PTR ZeroBits,
	PSIZE_T RegionSize,
	ULONG AllocationType,
	ULONG Protect
	);

typedef NTSTATUS(NTAPI* NtFreeVirtualMemory_t)(
	HANDLE ProcessHandle,
	PVOID* BaseAddress,
	PSIZE_T RegionSize,
	ULONG FreeType
	);

__int64 sub_18001BB8C();

NTSTATUS sub_18001BCA0(HINSTANCE hInstance, DWORD forwardReason, LPVOID lpvReserved);