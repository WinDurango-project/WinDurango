// ReSharper disable CppInconsistentNaming
// ReSharper disable CppParameterMayBeConst
// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement
// ReSharper disable CppClangTidyHicppMultiwayPathsCovered
// ReSharper disable CppClangTidyClangDiagnosticInconsistentDllimport
#include "pch.h"
#include "framework.h"
#include "kernelx.h"




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



// !!!!!
// Should be in ntdll.dll reimplementation, right now i'm just testing things with DLLMain entryPoint
PVOID RtlSetUnhandledExceptionFilter(PVOID ExceptionFilter)
{
	return EncodePointer(ExceptionFilter);
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
}

INT16 sub_18001D768()
{
    //TODO
}

int sub_18001D96C(int v2, unsigned short* codePageData, unsigned int p, bool t,long l)
{
    //TODO
}

__int64 sub_18001BB8C()
{
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