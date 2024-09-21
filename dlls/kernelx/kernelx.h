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

// Deleted that extern "C" stuff as I don't think it's needed, if it's needed someone added it pls

__int64 ConfigureLocaleSettings();

NTSTATUS CleanupResources(HINSTANCE hInstance, DWORD forwardReason, LPVOID lpvReserved);