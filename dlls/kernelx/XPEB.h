#pragma once
#include <WTypesbase.h>
#include <winternl.h>
// XPEB.h
#ifndef XPEB_H
#define XPEB_H
#define NtCurrentPeb() (reinterpret_cast<struct _XPEB*>(__readgsqword(0x60)))
#define RtlAcquireSRWLockExclusive AcquireSRWLockExclusive
#define RtlReleaseSRWLockExclusive ReleaseSRWLockExclusive
#define _DWORD DWORD
#define SECURITY_KERNEL
typedef PSRWLOCK _QWORD;
struct _XPEB {
    // Offsets: 0x0000 - 0x0007
    BYTE InheritedAddressSpace;
    BYTE ReadImageFileExecOptions;
    BYTE BeingDebugged;
    BYTE Reserved1[1]; // Padding

    // Offsets: 0x0008 - 0x000F
    PVOID Mutant; // Offset for Mutant

    // Offsets: 0x0010 - 0x0017
    PVOID ImageBaseAddress; // Offset for ImageBaseAddress

    // Offsets: 0x0018 - 0x001F
    PVOID Ldr; // Offset for Ldr

    // Offsets: 0x0020 - 0x0027
    PVOID ProcessParameters; // Offset for ProcessParameters

    // Offsets: 0x0028 - 0x002F
    PVOID SubSystemData; // Offset for SubSystemData

    // Offsets: 0x0030 - 0x0037
    PVOID ProcessHeap; // Offset for ProcessHeap

    // Offsets: 0x0038 - 0x003F
    PVOID FastPebLock; // Offset for FastPebLock

    // Offsets: 0x0040 - 0x0047
    PVOID AltThunkSListPtr; // Offset for AltThunkSListPtr

    // Offsets: 0x0048 - 0x004F
    PVOID IFEOKey; // Offset for IFEOKey

    // Offsets: 0x0050 - 0x0057
    BYTE Reserved2[4]; // Padding

    // Offsets: 0x0058 - 0x005F
    BYTE Reserved3[8]; // Padding

    // Offsets: 0x0060 - 0x0063
    ULONG SystemReserved;

    // Offsets: 0x0064 - 0x0067
    ULONG SpareUlong;

    // Offsets: 0x0068 - 0x006F
    PVOID FreeList; // Offset for FreeList

    // Offsets: 0x0070 - 0x0073
    ULONG TlsExpansionCounter;

    // Offsets: 0x0074 - 0x0077
    BYTE Reserved4[4]; // Padding

    // Offsets: 0x0078 - 0x007F
    PVOID TlsBitmap; // Offset for TlsBitmap

    // Offsets: 0x0080 - 0x0087
    ULONG TlsBitmapBits[2]; // Array of 2 ULONGs

    // Offsets: 0x0088 - 0x008F
    PVOID ReadOnlySharedMemoryBase; // Offset for ReadOnlySharedMemoryBase

    // Offsets: 0x0090 - 0x0097
    PVOID HotpatchInformation; // Offset for HotpatchInformation

    // Offsets: 0x0098 - 0x009F
    PVOID ReadOnlyStaticServerData; // Offset for ReadOnlyStaticServerData

    // Offsets: 0x00A0 - 0x00A7
    PVOID AnsiCodePageData; // Offset for AnsiCodePageData

    // Offsets: 0x00A8 - 0x00AF
    PVOID OemCodePageData; // Offset for OemCodePageData

    // Offsets: 0x00B0 - 0x00B7
    PVOID UnicodeCaseTableData; // Offset for UnicodeCaseTableData

    // Offsets: 0x00B8 - 0x00BB
    ULONG NumberOfProcessors;

    // Offsets: 0x00BC - 0x00BF
    ULONG NtGlobalFlag;

    // Offsets: 0x00C0 - 0x00C7
    LARGE_INTEGER CriticalSectionTimeout;

    // Offsets: 0x00C8 - 0x00CF
    SIZE_T HeapSegmentReserve;

    // Offsets: 0x00D0 - 0x00D7
    SIZE_T HeapSegmentCommit;

    // Offsets: 0x00D8 - 0x00DF
    SIZE_T HeapDeCommitTotalFreeThreshold;

    // Offsets: 0x00E0 - 0x00E7
    SIZE_T HeapDeCommitFreeBlockThreshold;

    // Offsets: 0x00E8 - 0x00EB
    ULONG NumberOfHeaps;

    // Offsets: 0x00EC - 0x00EF
    ULONG MaximumNumberOfHeaps;

    // Offsets: 0x00F0 - 0x00F7
    PVOID ProcessHeaps; // Offset for ProcessHeaps

    // Offsets: 0x00F8 - 0x00FF
    PVOID GdiSharedHandleTable; // Offset for GdiSharedHandleTable

    // Offsets: 0x0100 - 0x0107
    PVOID ProcessStarterHelper; // Offset for ProcessStarterHelper

    // Offsets: 0x0108 - 0x010B
    ULONG GdiDCAttributeList;

    // Offsets: 0x010C - 0x010F
    BYTE Reserved5[4]; // Padding

    // Offsets: 0x0110 - 0x0117
    PVOID LoaderLock; // Offset for LoaderLock

    // Offsets: 0x0118 - 0x011B
    ULONG OSMajorVersion;

    // Offsets: 0x011C - 0x011F
    ULONG OSMinorVersion;

    // Offsets: 0x0120 - 0x0121
    USHORT OSBuildNumber;

    // Offsets: 0x0122 - 0x0123
    USHORT OSCSDVersion;

    // Offsets: 0x0124 - 0x0127
    ULONG OSPlatformId;

    // Offsets: 0x0128 - 0x012B
    ULONG ImageSubsystem;

    // Offsets: 0x012C - 0x012F
    ULONG ImageSubsystemMajorVersion;

    // Offsets: 0x0130 - 0x0133
    ULONG ImageSubsystemMinorVersion;

    // Offsets: 0x0134 - 0x0137
    BYTE Reserved6[4]; // Padding

    // Offsets: 0x0138 - 0x013F
    SIZE_T ImageProcessAffinityMask;

    // Offsets: 0x0140 - 0x022F
    ULONG GdiHandleBuffer[60];

    // Offsets: 0x0230 - 0x0237
    PVOID PostProcessInitRoutine; // Offset for PostProcessInitRoutine

    // Offsets: 0x0238 - 0x023F
    PVOID TlsExpansionBitmap; // Offset for TlsExpansionBitmap

    // Offsets: 0x0240 - 0x02BF
    ULONG TlsExpansionBitmapBits[32]; // Array of 32 ULONGs

    // Offsets: 0x02C0 - 0x02C3
    ULONG SessionId;

    // Offsets: 0x02C4 - 0x02C7
    BYTE Reserved7[4]; // Padding

    // Offsets: 0x02C8 - 0x02CF
    ULARGE_INTEGER AppCompatFlags;

    // Offsets: 0x02D0 - 0x02D7
    ULARGE_INTEGER AppCompatFlagsUser;

    // Offsets: 0x02D8 - 0x02DF
    PVOID pShimData; // Offset for pShimData

    // Offsets: 0x02E0 - 0x02E7
    PVOID AppCompatInfo; // Offset for AppCompatInfo

    // Offsets: 0x02E8 - 0x02F7
    UNICODE_STRING CSDVersion;

    // Offsets: 0x02F8 - 0x02FF
    PVOID ActivationContextData; // Offset for ActivationContextData

    // Offsets: 0x0300 - 0x0307
    PVOID ProcessAssemblyStorageMap; // Offset for ProcessAssemblyStorageMap

    // Offsets: 0x0308 - 0x030F
    PVOID SystemDefaultActivationContextData; // Offset for SystemDefaultActivationContextData

    // Offsets: 0x0310 - 0x0317
    PVOID SystemAssemblyStorageMap; // Offset for SystemAssemblyStorageMap

    // Offsets: 0x0318 - 0x031F
    SIZE_T MinimumStackCommit;

    // Offsets: 0x0320 - 0x0327
    PVOID FlsCallback; // Offset for FlsCallback

    // Offsets: 0x0328 - 0x0337
    LIST_ENTRY FlsListHead;

    // Offsets: 0x0338 - 0x033F
    PVOID FlsBitmap; // Offset for FlsBitmap

    // Offsets: 0x0340 - 0x034F
    ULONG FlsBitmapBits[4]; // Array of 4 ULONGs

    // Offsets: 0x0350 - 0x0353
    ULONG FlsHighIndex;

    // Offsets: 0x0354 - 0x0357
    BYTE Reserved8[4]; // Padding

    // Offsets: 0x0358 - 0x035F
    PVOID WerRegistrationData; // Offset for WerRegistrationData

    // Offsets: 0x0360 - 0x0367
    PVOID WerShipAssertPtr; // Offset for WerShipAssertPtr
};

#endif
