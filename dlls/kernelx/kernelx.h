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

// THE VALUES FOR NAMES ARE GUESSED, BUT NAMES ARE CORRECT (THAT HOW ENUM SHOULD LOOK LIKE)
enum CONSOLE_TYPE {
	CONSOLE_TYPE_XBOX_ONE = 1,
	CONSOLE_TYPE_XBOX_ONE_S = 2,
	CONSOLE_TYPE_XBOX_ONE_X = 3,
	CONSOLE_TYPE_XBOX_ONE_X_DEVKIT = 4
};

__int64 sub_18001BB8C();

NTSTATUS sub_18001BCA0(HINSTANCE hInstance, DWORD forwardReason, LPVOID lpvReserved);