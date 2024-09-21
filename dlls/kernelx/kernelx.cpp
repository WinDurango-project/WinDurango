// ReSharper disable CppInconsistentNaming
// ReSharper disable CppParameterMayBeConst
// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement
// ReSharper disable CppClangTidyHicppMultiwayPathsCovered
// ReSharper disable CppClangTidyClangDiagnosticInconsistentDllimport
#include "pch.h"
#include <winternl.h>
#include "XPEB.h"

NtAllocateVirtualMemory_t NtAllocateVirtualMemory;
NtFreeVirtualMemory_t NtFreeVirtualMemory;
#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
#endif
//Ignoring this as for now (just hope it's not being used and it's not useful.)
__int64 NlsUpdateLocale_X() {
    return 0();
}

void WakeByAddressSingle_X(PVOID Address) {
    WakeByAddressSingle(Address);
}

void WakeByAddressAll_X(PVOID Address) {
    WakeByAddressAll(Address);
}

BOOL __stdcall WaitOnAddress_X(volatile void* Address, PVOID CompareAddress, SIZE_T AddressSize, DWORD dwMilliseconds)
{
    return WaitOnAddress(Address, CompareAddress, AddressSize, dwMilliseconds);
}

bool ToolingMemoryStatus_X(__int64 a1)
{
    int v3; // eax
    __int64 SystemInformation[4]; // [rsp+20h] [rbp-38h] BYREF

    if (*(DWORD*)a1 != 40)
    {
        SetLastError(0x57u);
        return false;
    }
    v3 = NtQuerySystemInformation((SYSTEM_INFORMATION_CLASS)(0x96 | 0x80), SystemInformation, 0x20u, 0i64);
    if (v3 < 0)
    {
        SetLastError(v3);
        return false;
    }
    *(DWORD*)(a1 + 8) = SystemInformation[0];
    *(DWORD*)(a1 + 16) = SystemInformation[1];
    *(DWORD*)(a1 + 24) = SystemInformation[2];
    *(DWORD*)(a1 + 32) = SystemInformation[3];
    return true;
}

bool TitleMemoryStatus_X(__int64 a1)
{
    int v3; // eax
    __int64 v4; // rcx
    __int64 v5; // rax
    __int64 v6; // rax
    __int64 v7; // rcx
    __int64 v8; // rax
    __int64 ProcessInformation[10]; // [rsp+30h] [rbp-68h] BYREF

    if (*(DWORD*)a1 != 80)
    {
        SetLastError(0x57u);
        return false;
    }
    v3 = NtQueryInformationProcess(
        (HANDLE)0xFFFFFFFFFFFFFFFFi64,
        (PROCESSINFOCLASS)(0x3A | 0x3A),
        ProcessInformation,
        0x48u,
        0i64);
    if (v3 < 0)
    {
        SetLastError(v3);
        return false;
    }
    v4 = ProcessInformation[2];
    v5 = ProcessInformation[0];
    *(DWORD*)(a1 + 8) = ProcessInformation[0];
    *(DWORD*)(a1 + 16) = v5 - ProcessInformation[1];
    v6 = ProcessInformation[4] - v4;
    *(DWORD*)(a1 + 24) = v4;
    v7 = ProcessInformation[5];
    *(DWORD*)(a1 + 40) = v6;
    *(DWORD*)(a1 + 32) = ProcessInformation[3];
    v8 = ProcessInformation[6] - v7;
    *(DWORD*)(a1 + 48) = v7;
    *(DWORD*)(a1 + 56) = v8;
    *(DWORD*)(a1 + 64) = ProcessInformation[7];
    *(DWORD*)(a1 + 72) = ProcessInformation[8];
    return true;
}

// We ignore setting this as we actually don't care about this.
bool SetThreadpoolAffinityMask_X()
{
    return true;
}

__int64 SetThreadName_X(HANDLE ThreadHandle, const WCHAR* a2)
{
    int v3; // eax
    _UNICODE_STRING DestinationString; // [rsp+20h] [rbp-18h] BYREF

    RtlInitUnicodeString(&DestinationString, a2);
    v3 = NtSetInformationThread(ThreadHandle, ThreadNameInformation, &DestinationString, 0x10u);
    if (v3 >= 0)
        return 1i64;
    return 0i64;
}

unsigned __int64 QueryProcessorSchedulingStatistics_X(unsigned __int64* a1)
{
    unsigned __int64 result = 0;
    LARGE_INTEGER frequency = { 0 };
    LARGE_INTEGER counter = { 0 };

    // Query the performance frequency and counter
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&counter);

    // Set a1[2] based on the performance counter and frequency
    a1[2] = counter.QuadPart / (frequency.QuadPart / 10000000);

    // Use the CPUID instruction
    int cpuInfo[4] = { 0 }; // {EAX, EBX, ECX, EDX}
    __cpuid(cpuInfo, 0);  // This gets the highest function supported by CPUID

    // Combine RBX and RAX as a 64-bit value and store in *a1
    a1[0] = __ull_rshift(cpuInfo[1], cpuInfo[0]);  // EBX (RBX), EAX (RAX)

    // Combine RDX and RCX as a 64-bit value and store in a1[1]
    result = __ull_rshift(cpuInfo[3], cpuInfo[2]); // EDX (RDX), ECX (RCX)
    a1[1] = result;

    return result;
}

bool JobTitleMemoryStatus_X(void* a1, __int64 a2)
{
    int v4; // eax
    __int64 v5; // rcx
    __int64 v6; // rax
    __int64 v7; // rax
    __int64 v8; // rcx
    __int64 v9; // rax
    __int64 JobInformation[10]; // [rsp+30h] [rbp-68h] BYREF

    if (*(DWORD*)a2 != 80)
    {
        SetLastError(0x57u);
        return false;
    }
    v4 = QueryInformationJobObject(a1, (JOBOBJECTINFOCLASS)(JobObjectGroupInformation | 0x10), JobInformation, 0x48u, 0i64);
    if (v4 < 0)
    {
        SetLastError(v4);
        return false;
    }
    v5 = JobInformation[2];
    v6 = JobInformation[0];
    *(DWORD*)(a2 + 8) = JobInformation[0];
    *(DWORD*)(a2 + 16) = v6 - JobInformation[1];
    v7 = JobInformation[4] - v5;
    *(DWORD*)(a2 + 24) = v5;
    v8 = JobInformation[5];
    *(DWORD*)(a2 + 40) = v7;
    *(DWORD*)(a2 + 32) = JobInformation[3];
    v9 = JobInformation[6] - v8;
    *(DWORD*)(a2 + 48) = v8;
    *(DWORD*)(a2 + 56) = v9;
    *(DWORD*)(a2 + 64) = JobInformation[7];
    *(DWORD*)(a2 + 72) = JobInformation[8];
    return true;
}

__int64 GetThreadName_X(HANDLE ThreadHandle, void* a2, unsigned __int64 a3, unsigned __int64* a4)
{
    NTSTATUS v8; // ecx
    const void** v10; // rbp
    ULONG v11; // ebx
    unsigned __int64 v12; // rsi
    NTSTATUS v13; // eax
    int v14; // edi
    ULONG ReturnLength; // [rsp+78h] [rbp+20h] BYREF

    if (!a4)
    {
        v8 = -1073741811;
    LABEL_3:
        SetLastError(v8);
        return 0i64;
    }
    v10 = 0i64;
    v11 = 144;
    v12 = 0i64;
    while (1)
    {
        if (v10)
            HeapFree(GetProcessHeap(), 0, v10);
        v10 = (const void**)HeapAlloc(GetProcessHeap(), 0, v11);
        if (!v10)
        {
            v14 = -1073741801;
            goto LABEL_18;
        }
        v13 = NtQueryInformationThread(ThreadHandle, ThreadNameInformation, v10, v11, &ReturnLength);
        v14 = v13;
        if (v13 != -1073741820 && v13 != -1073741789 && v13 != -2147483643)
            break;
        v11 = ReturnLength;
    }
    if (v13 >= 0)
    {
        v12 = (unsigned __int64)*(unsigned __int16*)v10 >> 1;
        if (a2 && v12 < a3)
        {
            memcpy(a2, v10[1], 2 * v12);
            *((WORD*)a2 + v12) = 0;
        }
        else
        {
            ++v12;
            v14 = -1073741789;
        }
    }
LABEL_18:
    *a4 = v12;
    HeapFree(GetProcessHeap(), 0, v10);
    if (v14 < 0)
    {
        v8 = v14;
        goto LABEL_3;
    }
    return 1i64;
}

void GetSystemOSVersion_X(uint8_t* buffer) {
    if (!buffer) return;

    int cpuInfo[4] = { -1 };

    // Execute CPUID with EAX = 1
    __cpuid(cpuInfo, 1);

    int eax = cpuInfo[0];
    int ebx = cpuInfo[1];
    int edx = cpuInfo[3];

    // Store parts of the results in the buffer
    buffer[0] = (uint8_t)(ebx & 0xFF);              // Lowest 8 bits of EBX
    buffer[1] = (uint8_t)((eax >> 24) & 0xFF);      // Highest 8 bits of EAX

    *(uint16_t*)(buffer + 2) = (uint16_t)((eax >> 16) & 0xFFFF); // Second 16 bits of EAX (High 16 bits of lower 32 bits)
    *(uint16_t*)(buffer + 4) = (uint16_t)(edx & 0xFFFF);         // Low 16 bits of EDX
}


__int64 GetConsoleType_X() {
    return 4;
}

uint32_t dword_180021AA0[16];
uint32_t dword_180021A60[16];
int64_t qword_18002C7E0[34];
HANDLE HeapHandle;


bool XMemFreeDefault_X(PVOID P, unsigned __int64 a2) {
    if (!P) return FALSE;

    uint64_t v3 = a2 >> 29;
    uint32_t v2 = static_cast<uint32_t>(a2);

    // Check if RtlFreeHeap can be used
    if (!dword_180021A60[v3 & 0xF] && (v2 & 0x1F000000) <= 0x4000000 && (v2 & 0xC000) == 0) {
        return HeapFree(HeapHandle, 0, P) ? TRUE : FALSE;
    }

    uint64_t v6 = v3 & 0xF;
    int64_t v7 = qword_18002C7E0[v6];

    // Check if the memory can be freed using sub_18000EA08
    if (!v7 || !*reinterpret_cast<uint64_t*>(v7 + 48) ||
        *reinterpret_cast<uint64_t*>(v7 + 48) > reinterpret_cast<uint64_t>(P) ||
        *reinterpret_cast<uint64_t*>(v7 + 56) < reinterpret_cast<uint64_t>(P)) {

        v7 = qword_18002C7E0[static_cast<unsigned int>(v6 + 16)];
        if (!v7 || !*reinterpret_cast<uint64_t*>(v7 + 48) ||
            *reinterpret_cast<uint64_t*>(v7 + 48) > reinterpret_cast<uint64_t>(P) ||
            *reinterpret_cast<uint64_t*>(v7 + 56) < reinterpret_cast<uint64_t>(P)) {
            v7 = 0;
        }
    }

    if (v7) {
        //Bored to implement
        //return sub_18000EA08() ? TRUE : FALSE;
    }

    SIZE_T RegionSize = 0;
    // Attempt to free virtual memory
    return NtFreeVirtualMemory(
        reinterpret_cast<HANDLE>(0xFFFFFFFFFFFFFFFF),
        &P,
        &RegionSize,
        MEM_RELEASE
    ) >= 0 ? TRUE : FALSE;
}

__int64 XMemFree_X(PVOID P, __int64 a2) {
    return XMemFreeDefault_X(P, a2);
}

// Define PVOID for non-Windows environments if needed
#ifndef _WINDEF_
typedef void* PVOID;
#endif

PVOID XMemAllocDefault_X(uint64_t size, uint64_t flags) {
    PVOID ptr = nullptr;
    // Example flag usage: we assume if the highest bit of flags is set, we zero the memory.
    bool shouldZeroMemory = (flags & (1ULL << 63)) != 0;

    // Allocate memory
    ptr = malloc(size);

    // Optionally zero out the memory if the flag is set
    if (ptr && shouldZeroMemory) {
        memset(ptr, 0, size);
    }

    return ptr;
}

PVOID XMemAlloc_X(uint64_t size, uint64_t flags) {
    return XMemAllocDefault_X(size, flags);
}


// TODO
// absolutely temporary implementation I just want to make it work
// sub_18001BCA0 
PVOID globalDataBlock;
PVOID localeDataHeap;
HANDLE qword_18002B820;
HANDLE qword_18002B830;
HANDLE qword_18002B818;
HANDLE qword_18002B850;
HANDLE qword_18002B858;
PVOID baseBufferMemory;
HANDLE P;
char* dword_18002B84C;

//sub_18001BB8C

int sub_18001D528()
{
    //TODO
    return 0;
}

INT16 sub_18001D768()
{
    //TODO
    return 0;
}

int sub_18001D96C(int v2, PVOID codePageData, unsigned int p, bool t, long l)
{
    //TODO
    return 0;
}
    // I know it should look better if it was initalized at dllmain.cpp but then I can't fix some idiotic errors
    //HMODULE ntdll = LoadLibraryA("ntdll.dll");
    //if (ntdll) {
    //    NtAllocateVirtualMemory =
    //        (NtAllocateVirtualMemory_t)GetProcAddress(ntdll, "NtAllocateVirtualMemory");
    //    NtFreeVirtualMemory =
    //        (NtFreeVirtualMemory_t)GetProcAddress(ntdll, "NtFreeVirtualMemory");

    //    FreeLibrary(ntdll);
    //}

BOOL isLocaleConfigInitialized;

__int64 AllocateLocaleHeapMemory()
{
    //memset(&globalDataBlock, 0, 0xD8ui64);
    //baseBufferMemory = RtlAllocateHeap(NtCurrentPeb()->ProcessHeap, 8u, 0x400ui64);
    //if (!baseBufferMemory)
    //    return 14i64;
    //localeDataHeap = RtlAllocateHeap(NtCurrentPeb()->ProcessHeap, 8u, 0x400ui64);
    //if (!localeDataHeap)
    //{
    //    if (baseBufferMemory)
    //        RtlFreeHeap(NtCurrentPeb()->ProcessHeap, 0, baseBufferMemory);
    //    return 14i64;
    //}
    return 0i64;
}

int dword_18002BF68;
_QWORD unk_18002B838;
__int64 qword_18002B828;
__int64 qword_18002B980;
__int64 qword_18002B990;
__int16 word_18002BF64;
HANDLE Event;
__int64 __fastcall sub_18001EB38(unsigned int a1, __int64 a2 = 0)
{
    return 0;
}
__int64 __fastcall MapLocaleFileAndInitializeData(unsigned int* a1 = 0)
{
    return 0;
}
__int64 ConfigureLocaleSettings()
{
    unsigned int localeHeapMemory;      // LocaleHeapMemory -> localeHeapMemory
    PVOID ansiCodePageData;             // AnsiCodePageData -> ansiCodePageData
    int ansiCodePage;                   // v2 -> ansiCodePage
    PVOID localeDataPointer;            // v3 -> localeDataPointer
    HMODULE libraryHandle;              // v4 -> libraryHandle

    localeHeapMemory = 0;

    // Check if locale configuration is already initialized
    if (!isLocaleConfigInitialized)
    {
        // Try to allocate memory for locale data
        localeHeapMemory = AllocateLocaleHeapMemory();

        if (!localeHeapMemory)
        {
            // If allocation fails, attempt to map the locale file and initialize data
            localeHeapMemory = ((__int64 (*)(void))MapLocaleFileAndInitializeData)();

            if (!localeHeapMemory)
            {
                // Retrieve AnsiCodePage data from PEB
                ansiCodePageData = NtCurrentPeb()->AnsiCodePageData;
                ansiCodePage = *((unsigned __int16*)ansiCodePageData + 1);

                // Store AnsiCodePage value in a global variable
                dword_18002BF68 = ansiCodePage;

                // Call a subroutine with various locale parameters
                localeHeapMemory = sub_18001D96C(ansiCodePage,
                    (PVOID)(DWORD)ansiCodePageData,
                    (unsigned int)&P, 0, 0i64);

                // If no memory is allocated, set up synchronization and locale data
                if (!localeHeapMemory)
                {
                    // Acquire exclusive lock for synchronization
                    RtlAcquireSRWLockExclusive((PSRWLOCK)&unk_18002B838);

                    // Attempt to initialize locale data
                    qword_18002B828 = sub_18001EB38(127i64);

                    if (qword_18002B828)
                    {
                        // Release lock after initialization
                        RtlReleaseSRWLockExclusive((PSRWLOCK)&unk_18002B838);

                        qword_18002B990 = 0i64;
                        qword_18002B980 = 0i64;
                        word_18002BF64 = 1;
                        Event = 0i64;
                        isLocaleConfigInitialized = 1;
                    }
                    else
                    {
                        // Release lock if initialization fails
                        RtlReleaseSRWLockExclusive((PSRWLOCK)&unk_18002B838);

                        // Cleanup in case of failure
                        localeDataPointer = P;
                        libraryHandle = (HMODULE) * ((_QWORD*)P + 8);

                        // Free the loaded library if it exists
                        if (libraryHandle)
                            FreeLibrary(libraryHandle);

                        // Free heap memory allocated for locale data
                        RtlFreeHeap(NtCurrentPeb()->ProcessHeap, 0, localeDataPointer);
                        P = 0i64;

                        // Return error code 87 (ERROR_INVALID_PARAMETER)
                        return 87;
                    }
                }
            }
        }
    }

    return localeHeapMemory;
}



// absolutely temporary implementation I just want to make it work
// decompilation from ghidra (it looks horrible lol)
NTSTATUS CleanupResources(HINSTANCE hInstance, DWORD forwardReason, LPVOID lpvReserved)
{
    char* resourceArray1 = (char*)globalDataBlock;
    if (resourceArray1)
    {
        for (int i = 0; i < 197; ++i)
        {
            char* currentResource = *(char**)&resourceArray1[i * 8];
            while (currentResource)
            {
                HMODULE moduleHandle = (HMODULE)currentResource[8];
                char* nextResource = (char*)currentResource[9];

                if (moduleHandle)
                    FreeLibrary(moduleHandle);

                HeapFree(GetProcessHeap(), 0, currentResource);
                currentResource = nextResource;
            }
        }
        HeapFree(GetProcessHeap(), 0, globalDataBlock);
        globalDataBlock = 0LL;
    }

    char* resourceArray2 = (char*)localeDataHeap;
    if (resourceArray2)
    {
        for (int i = 0; i < 128; ++i)
        {
            char* currentResource = *(char**)&resourceArray2[i * 8];
            while (currentResource)
            {
                char* nextResource = (char*)currentResource[10];
                HeapFree(GetProcessHeap(), 0, currentResource);
                currentResource = nextResource;
            }
        }
        HeapFree(GetProcessHeap(), 0, localeDataHeap);
        localeDataHeap = 0LL;
    }

    if (baseBufferMemory)
    {
        HeapFree(GetProcessHeap(), 0, baseBufferMemory);
        baseBufferMemory = 0LL;
    }

    // Handle cleanup of 'P'
    PVOID pResource = P;
    if (pResource)
    {
        HMODULE moduleHandle = (HMODULE)((char*)P + 8);
        if (moduleHandle)
            FreeLibrary(moduleHandle);

        HeapFree(GetProcessHeap(), 0, pResource);
        P = 0LL;
    }

    // Close any open module handles
    if (GetModuleHandle)
        NtClose(GetModuleHandle);

    if (qword_18002B820)
    {
        NtClose(qword_18002B820);
        qword_18002B820 = 0LL;
    }

    if (qword_18002B830)
    {
        NtClose(qword_18002B830);
        qword_18002B830 = 0LL;
    }

    if (qword_18002B818)
    {
        NtClose(qword_18002B818);
        qword_18002B818 = 0LL;
    }

    if (qword_18002B850)
    {
        NtClose(qword_18002B850);
        qword_18002B850 = 0LL;
    }

    if (qword_18002B858)
    {
        NtClose(qword_18002B858);
        qword_18002B858 = 0LL;
    }

    dword_18002B84C = 0;
    return STATUS_SUCCESS;
}
