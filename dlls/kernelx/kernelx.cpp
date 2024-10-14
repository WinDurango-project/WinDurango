#include "pch.h"

NtAllocateVirtualMemory_t NtAllocateVirtualMemory;
NtFreeVirtualMemory_t NtFreeVirtualMemory;

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


CONSOLE_TYPE GetConsoleType_X() {
    return CONSOLE_TYPE::CONSOLE_TYPE_XBOX_ONE_X_DEVKIT;
}

uint32_t dword_180021AA0[16];
uint32_t dword_180021A60[16];
int64_t qword_18002C7E0[34];
HANDLE HeapHandle;


void XMemFreeDefault_X(PVOID pADDRESS, uint64_t dwAllocAttributes) {

    uint64_t v3 = dwAllocAttributes >> 29;
    uint32_t v2 = static_cast<uint32_t>(dwAllocAttributes);

    // Check if RtlFreeHeap can be used
    if (!dword_180021A60[v3 & 0xF] && (v2 & 0x1F000000) <= 0x4000000 && (v2 & 0xC000) == 0) {
        HeapFree(HeapHandle, 0, pADDRESS);
    }

    uint64_t v6 = v3 & 0xF;
    int64_t v7 = qword_18002C7E0[v6];

    // Check if the memory can be freed using sub_18000EA08
    if (!v7 || !*reinterpret_cast<uint64_t*>(v7 + 48) ||
        *reinterpret_cast<uint64_t*>(v7 + 48) > reinterpret_cast<uint64_t>(pADDRESS) ||
        *reinterpret_cast<uint64_t*>(v7 + 56) < reinterpret_cast<uint64_t>(pADDRESS)) {

        v7 = qword_18002C7E0[static_cast<unsigned int>(v6 + 16)];
        if (!v7 || !*reinterpret_cast<uint64_t*>(v7 + 48) ||
            *reinterpret_cast<uint64_t*>(v7 + 48) > reinterpret_cast<uint64_t>(pADDRESS) ||
            *reinterpret_cast<uint64_t*>(v7 + 56) < reinterpret_cast<uint64_t>(pADDRESS)) {
            v7 = 0;
        }
    }

    if (v7) {
        //Bored to implement
        //return sub_18000EA08() ? TRUE : FALSE;
    }

    SIZE_T RegionSize = 0;
    // Attempt to free virtual memory
    NtFreeVirtualMemory(
        reinterpret_cast<HANDLE>(0xFFFFFFFFFFFFFFFF),
        &pADDRESS,
        &RegionSize,
        MEM_RELEASE
    );
}

void XMemFree_X(PVOID pADDRESS, uint64_t dwAllocAttributes) {
    XMemFreeDefault_X(pADDRESS, dwAllocAttributes);
}

// Define PVOID for non-Windows environments if needed
#ifndef _WINDEF_
typedef void* PVOID;
#endif

PVOID XMemAllocDefault_X(SIZE_T dwSize, uint64_t flags) {
    PVOID ptr = nullptr;
    // Example flag usage: we assume if the highest bit of flags is set, we zero the memory.
    bool shouldZeroMemory = (flags & (1ULL << 63)) != 0;

    // Allocate memory
    ptr = malloc(dwSize);

    // Optionally zero out the memory if the flag is set
    if (ptr && shouldZeroMemory) {
        memset(ptr, 0, dwSize);
    }

    return ptr;
}

PVOID XMemAlloc_X(SIZE_T dwSize, uint64_t flags) {
    return XMemAllocDefault_X(dwSize, flags);
}

static decltype(&XMemAlloc_X) XMemAllocRoutine_X;
static decltype(&XMemFree_X) XMemFreeRoutine_X;
static CRITICAL_SECTION XMemSetAllocationHooksLock_X;

void XMemSetAllocationHooks_X(decltype(&XMemAlloc_X) Alloc, decltype(&XMemFree_X) Free)
{
    EnterCriticalSection(&XMemSetAllocationHooksLock_X);

    if (Alloc) {
        XMemAllocRoutine_X = Alloc;
        XMemFreeRoutine_X = Free;
    }
    else {
        XMemAllocRoutine_X = &XMemAllocDefault_X;
        XMemFreeRoutine_X = &XMemFreeDefault_X;
    }

    LeaveCriticalSection(&XMemSetAllocationHooksLock_X);

}
// TODO
// absolutely temporary implementation I just want to make it work
// sub_18001BCA0 
char* qword_18002B880;
char* qword_18002B890;
HANDLE qword_18002B820;
HANDLE qword_18002B830;
HANDLE qword_18002B818;
HANDLE qword_18002B850;
HANDLE qword_18002B858;
HANDLE qword_18002B888;
HANDLE P;
char* dword_18002B84C;

//sub_18001BB8C
int dword_18002BF68;


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

int sub_18001D96C(int v2, unsigned short* codePageData, unsigned int p, bool t, long l)
{
    //TODO
    return 0;
}

__int64 sub_18001BB8C()
{
    // I know it should look better if it was initalized at dllmain.cpp but then I can't fix some idiotic errors
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    if (ntdll) {
        NtAllocateVirtualMemory =
            (NtAllocateVirtualMemory_t)GetProcAddress(ntdll, "NtAllocateVirtualMemory");
        NtFreeVirtualMemory =
            (NtFreeVirtualMemory_t)GetProcAddress(ntdll, "NtFreeVirtualMemory");

        FreeLibrary(ntdll);
    }
    /*unsigned int v0; // ebx
    unsigned __int16* AnsiCodePageData; // rdx
    int v2; // ecx
    PVOID v3; // rbx
    HMODULE v4; // rcx

    v0 = 0;
    if (!dword_18002B84C)
    {

        v0 = sub_18001D528();
        if (!v0)
        {
            v0 = sub_18001D768();
            if (!v0)
            {
                // not sure
                AnsiCodePageData = (unsigned __int16*)NtCurrentTeb()->ProcessEnvironmentBlock->ProcessParameters;
                v2 = AnsiCodePageData[1];
                dword_18002BF68 = v2;
                v0 = sub_18001D96C(v2, AnsiCodePageData, (unsigned int)&P, 0, 0LL);
                if (!v0)
                {
                    RtlAcquireSRWLockExclusive(&unk_18002B838);
                    qword_18002B828 = sub_18001EB38(127LL);
                    if (qword_18002B828)
                    {
                        RtlReleaseSRWLockExclusive(&unk_18002B838);
                        qword_18002B990 = 0LL;
                        qword_18002B980 = 0LL;
                        word_18002BF64 = 1;
                        Event = 0LL;
                        dword_18002B84C = 1;
                    }
                    else
                    {
                        RtlReleaseSRWLockExclusive(&unk_18002B838);
                        v3 = P;
                        v4 = (HMODULE) * ((_QWORD*)P + 8);
                        if (v4)
                            FreeLibrary(v4);
                        RtlFreeHeap(NtCurrentPeb()->ProcessHeap, 0, v3);
                        P = 0LL;
                        return 87;
                    }
                }
            }
        }
    }
    return v0;*/
    return 0;
}


// absolutely temporary implementation I just want to make it work
// decompilation from ghidra (it looks horrible lol)
NTSTATUS sub_18001BCA0(HINSTANCE hInstance, DWORD forwardReason, LPVOID lpvReserved)
{
    char* v0; // rax
    __int64 v1; // rdi
    __int64 v2; // rsi
    char* v3; // rbx
    HMODULE v4; // rcx
    char* v5; // rbp
    char* v6; // rax
    __int64 v7; // rdi
    __int64 v8; // rsi
    char* v9; // r8
    char* v10; // rbx
    PVOID v11; // rbx
    HMODULE v12; // rcx
    NTSTATUS result; // al


    v0 = (char*)qword_18002B880;
    if (qword_18002B880)
    {
        v1 = 0LL;
        v2 = 197LL;
        do
        {
            v3 = *(char**)&v0[v1];
            if (v3)
            {
                do
                {
                    v4 = (HMODULE)v3[8];
                    v5 = (char*)v3[9];
                    if (v4)
                        FreeLibrary(v4);
                    HeapFree(GetProcessHeap(), 0, v3);
                    v3 = v5;
                } while (v5);
                v0 = (char*)qword_18002B880;
            }
            v1 += 8LL;
            --v2;
        } while (v2);
        if (v0)
            HeapFree(GetProcessHeap(), 0, qword_18002B880);
        qword_18002B880 = 0LL;
    }
    v6 = (char*)qword_18002B890;
    v7 = 0LL;
    v8 = 128LL;
    do
    {
        v9 = *(char**)&v6[v7];
        if (v9)
        {
            do
            {
                v10 = (char*)v9[10];
                HeapFree(GetProcessHeap(), 0, v9);
                v9 = v10;
            } while (v10);
            v6 = (char*)qword_18002B890;
        }
        v7 += 8LL;
        --v8;
    } while (v8);
    if (v6)
        HeapFree(GetProcessHeap(), 0, qword_18002B890);
    qword_18002B890 = 0LL;
    if (qword_18002B888)
        HeapFree(GetProcessHeap(), 0, qword_18002B888);
    // P ?!?
    v11 = P;
    qword_18002B888 = 0LL;
    v12 = (HMODULE) * ((char*)P + 8);
    if (v12)
        FreeLibrary(v12);
    result = HeapFree(GetProcessHeap(), 0, v11);
    P = 0LL;
    if (GetModuleHandle)
    {
        result = NtClose(GetModuleHandle);
    }
    if (qword_18002B820)
    {
        result = NtClose(qword_18002B820);
        qword_18002B820 = 0LL;
    }
    if (qword_18002B830)
    {
        result = NtClose(qword_18002B830);
        qword_18002B830 = 0LL;
    }
    if (qword_18002B818)
    {
        result = NtClose(qword_18002B818);
        qword_18002B818 = 0LL;
    }
    if (qword_18002B850)
    {
        result = NtClose(qword_18002B850);
        qword_18002B850 = 0LL;
    }
    if (qword_18002B858)
    {
        result = NtClose(qword_18002B858);
        qword_18002B858 = 0LL;
    }
    dword_18002B84C = 0;
    return result;
}
