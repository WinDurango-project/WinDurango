// ReSharper disable CppInconsistentNaming
// ReSharper disable CppParameterMayBeConst
// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement
// ReSharper disable CppClangTidyHicppMultiwayPathsCovered
// ReSharper disable CppClangTidyClangDiagnosticInconsistentDllimport
#include "pch.h"
#include "framework.h"
#include "kernelx.h"
#include <cstdint>

NtAllocateVirtualMemory_t NtAllocateVirtualMemory;
NtFreeVirtualMemory_t NtFreeVirtualMemory;

void EnterCriticalSection_X(LPCRITICAL_SECTION lpCriticalSection)
{
	EnterCriticalSection(lpCriticalSection);
}

HANDLE GetProcessHeap_X()
{
	return GetProcessHeap();
}

uint32_t dword_180021AA0[16];
uint32_t dword_180021A60[16];
int64_t qword_18002C7E0[34];
HANDLE HeapHandle;


bool XMemFreeDefault_X(PVOID P, unsigned __int64 a2) {
    if (!P) return FALSE;

    uint64_t v3 = a2 >> 29;
    uint32_t v2 = static_cast<uint32_t>(a2);

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


PVOID XMemAllocDefault_X(uint64_t size, uint64_t flags) {
    if (size == 0) return nullptr;

    int64_t v8;
    uint32_t v7 = dword_180021A60[(flags >> 29) & 0xF];
    if (v7 == 0 || (flags & 0x1F000000) > 0x4000000 || (flags & 0xC000) != 0) {
        if (v7 == 0x400000) {
            v8 = 33;
        }
        else {
            uint64_t v9 = (flags >> 24) & 0x1F;
            if (v9 > 0x10 || size > 0x20000) {
                v8 = 33;
            }
            else if (v9 > 0xC || size > 0xF00) {
                v8 = (flags >> 29) & 0xF | 0x10;
            }
            else {
                v8 = 32;
            }
        }
    }
    else {
        v8 = 32;
    }

    if (v8 == 32) {
        return nullptr;
    }

    if (v8 == 33) {
        uint32_t AllocationType = 1073754112;
        if ((flags & 0x1F000000) == 285212672) {
            AllocationType = -1073729536;
        }
        else if ((flags >> 14) & 0xFFFF == 1) {
            AllocationType = 1610625024;
        }
        else if ((flags >> 14) & 0xFFFF == 2) {
            AllocationType = -1073729536;
        }

        uint32_t Protect = dword_180021AA0[(flags >> 29) & 0xF];
        if (AllocationType & (1 << 22)) {
            AllocationType &= 0xFFBFFFFF;
            if ((flags & 0xC000) == 0) {
                AllocationType |= 0x20000000;
            }
        }

        void* baseAddress = nullptr;
        SIZE_T regionSize = size;
        if (NtAllocateVirtualMemory(
            INVALID_HANDLE_VALUE,
            &baseAddress,
            0,
            &regionSize,
            AllocationType,
            Protect) >= 0) {
            return baseAddress;
        }
        return nullptr;
    }

    HeapHandle = HeapCreate(v8, 0, 0);
    if (HeapHandle) {
        return HeapAlloc(HeapHandle, 0, size);
    }
    return nullptr;
}

PVOID XMemAlloc_X(ULONG64 a1, __int64 a2)
{
    return XMemAllocDefault_X(a1, a2);
}

//TODO
// I can't find any Kernel32 equivalent
BOOL AllocateTitlePhysicalPages_X()
{
    return 1;
}

BOOL Beep_X(DWORD dwFreq, DWORD dwDuration)
{
    return Beep(dwFreq, dwDuration);
}

BOOL BindIoCompletionCallback_X(HANDLE FileHandle, LPOVERLAPPED_COMPLETION_ROUTINE Function, ULONG Flags)
{
    return BindIoCompletionCallback(FileHandle, Function, Flags);
}

BOOL CallbackMayRunLong_X(PTP_CALLBACK_INSTANCE pci)
{
    return CallbackMayRunLong(pci);
}

BOOL CancelIoEx_X(HANDLE hFile, LPOVERLAPPED lpOverlapped)
{
    return CancelIoEx(hFile, lpOverlapped);
}

BOOL CancelSynchronousIo_X(HANDLE hThread)
{
    return CancelSynchronousIo(hThread);
}

BOOL CancelWaitableTimer_X(HANDLE hTimer)
{
    return CancelWaitableTimer(hTimer);
}

LONG CompareFileTime_X(const FILETIME* lpFileTime1, const FILETIME* lpFileTime2)
{
    return CompareFileTime(lpFileTime1, lpFileTime2);
}

int CompareStringEx_X(LPCWSTR lpLocaleName, DWORD dwCmpFlags, LPCWSTR lpString1, int cchCount1, LPCWSTR lpString2, int cchCount2, LPNLSVERSIONINFO lpVersionInformation, LPVOID lpReserved, LPARAM lParam)
{
    return CompareStringEx(lpLocaleName, dwCmpFlags, lpString1, cchCount1, lpString2, cchCount2, lpVersionInformation, lpReserved, lParam);
}

int CompareStringOrdinal_X(LPCWCH lpString1, int cchCount1, LPCWCH lpString2, int cchCount2, BOOL bIgnoreCase)
{
    return CompareStringOrdinal(lpString1, cchCount1, lpString2, cchCount2, bIgnoreCase);
}

int CompareStringW_X(LCID Locale, DWORD dwCmpFlags, PCNZWCH lpString1, int cchCount1, PCNZWCH lpString2, int cchCount2)
{
    return CompareStringW(Locale, dwCmpFlags, lpString1, cchCount1, lpString2, cchCount2);
}

BOOL ConnectNamedPipe_X(HANDLE hNamedPipe, LPOVERLAPPED lpOverlapped)
{
    return ConnectNamedPipe(hNamedPipe, lpOverlapped);
}

BOOL ConvertFiberToThread_X()
{
    return ConvertFiberToThread();
}

LPVOID ConvertThreadToFiberEx_X(LPVOID lpParameter, DWORD dwFlags)
{
    return ConvertThreadToFiberEx(lpParameter, dwFlags);
}

LPVOID ConvertThreadToFiber_X(LPVOID lpParameter)
{
    return ConvertThreadToFiber(lpParameter);
}

BOOL CopyContext_X(PCONTEXT Destination, DWORD ContextFlags, PCONTEXT Source)
{
    return CopyContext(Destination, ContextFlags, Source);
}

HRESULT CopyFile2_X(PCWSTR pwszExistingFileName, PCWSTR pwszNewFileName, COPYFILE2_EXTENDED_PARAMETERS* pExtendedParameters)
{
    return CopyFile2(pwszExistingFileName, pwszNewFileName, pExtendedParameters);
}

BOOL CreateDirectoryA_X(LPCSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
    return CreateDirectoryA(lpPathName, lpSecurityAttributes);
}

HANDLE CreateEventA_X(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCSTR lpName)
{
    return CreateEventA( lpEventAttributes, bManualReset, bInitialState, lpName);
}

HANDLE CreateEventExA_X(LPSECURITY_ATTRIBUTES lpEventAttributes, LPCSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess)
{
    return CreateEventExA(lpEventAttributes, lpName, dwFlags, dwDesiredAccess);
}

LPVOID CreateFiberEx_X(SIZE_T dwStackCommitSize, SIZE_T dwStackReserveSize, DWORD dwFlags, LPFIBER_START_ROUTINE lpStartAddress, LPVOID lpParameter)
{
    return CreateFiberEx(dwStackCommitSize, dwStackReserveSize, dwFlags, lpStartAddress, lpParameter);
}

LPVOID CreateFiber_X(SIZE_T dwStackSize, LPFIBER_START_ROUTINE lpStartAddress, LPVOID lpParameter)
{
    return CreateFiber(dwStackSize, lpStartAddress, lpParameter);
}

//TODO
// strange lol
void CreateFile2_X()
{
    //return CreateFile2();
}

HANDLE CreateFileA_X(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
    return CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}


HANDLE CreateFileMappingW_X(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCWSTR lpName)
{
    return CreateFileMappingW(hFile, lpFileMappingAttributes, flProtect, dwMaximumSizeHigh, dwMaximumSizeLow, lpName);
}

HANDLE CreateIoCompletionPort_X(HANDLE FileHandle, HANDLE ExistingCompletionPort, ULONG_PTR CompletionKey, DWORD NumberOfConcurrentThreads)
{
    return CreateIoCompletionPort(FileHandle, ExistingCompletionPort, CompletionKey, NumberOfConcurrentThreads);
}

HANDLE CreateMutexA_X(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName)
{
    return CreateMutexA(lpMutexAttributes, bInitialOwner, lpName);
}

HANDLE CreateMutexExA_X(LPSECURITY_ATTRIBUTES lpMutexAttributes, LPCSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess)
{
    return CreateMutexExA(lpMutexAttributes, lpName, dwFlags, dwDesiredAccess);
}

HANDLE CreateMutexExW_X(LPSECURITY_ATTRIBUTES lpMutexAttributes, LPCWSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess)
{
    return CreateMutexExW(lpMutexAttributes, lpName, dwFlags, dwDesiredAccess);
}

HANDLE CreateMutexW_X(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCWSTR lpName)
{
    return CreateMutexW(lpMutexAttributes, bInitialOwner, lpName);
}

HANDLE CreateNamedPipeW_X(LPCWSTR lpName, DWORD dwOpenMode, DWORD dwPipeMode, DWORD nMaxInstances, DWORD nOutBufferSize, DWORD nInBufferSize, DWORD nDefaultTimeOut, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
    return CreateNamedPipeW(lpName, dwOpenMode, dwPipeMode, nMaxInstances, nOutBufferSize, nInBufferSize, nDefaultTimeOut, lpSecurityAttributes);
}

BOOL CreatePipe_X(PHANDLE hReadPipe, PHANDLE hWritePipe, LPSECURITY_ATTRIBUTES lpPipeAttributes, DWORD nSize)
{
    return CreatePipe(hReadPipe, hWritePipe, lpPipeAttributes, nSize);
}

BOOL CreateProcessA_X(LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)
{
    return CreateProcessA(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
}

BOOL CreateProcessW_X(LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)
{
    return CreateProcessW(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
}

HANDLE CreateRemoteThread_X(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId)
{
    return CreateRemoteThread(hProcess, lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
}

HANDLE CreateSemaphoreA_X(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, LONG lInitialCount, LONG lMaximumCount, LPCSTR lpName)
{
    return CreateSemaphoreA(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName);
}

HANDLE CreateSemaphoreExA_X(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, LONG lInitialCount, LONG lMaximumCount, LPCSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess)
{
    return CreateSemaphoreExA(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName, dwFlags, dwDesiredAccess);
}

HANDLE CreateSemaphoreExW_X(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, LONG lInitialCount, LONG lMaximumCount, LPCWSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess)
{
    return CreateSemaphoreExW(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName, dwFlags, dwDesiredAccess);
}

HANDLE CreateSemaphoreW_X(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, LONG lInitialCount, LONG lMaximumCount, LPCWSTR lpName)
{
    return CreateSemaphoreW(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName);
}

PTP_CLEANUP_GROUP CreateThreadpoolCleanupGroup_X()
{
    return CreateThreadpoolCleanupGroup();
}

PTP_IO CreateThreadpoolIo_X(HANDLE fl, PTP_WIN32_IO_CALLBACK pfnio, PVOID pv, PTP_CALLBACK_ENVIRON pcbe)
{
    return CreateThreadpoolIo(fl, pfnio, pv, pcbe);
}

PTP_TIMER CreateThreadpoolTimer_X(PTP_TIMER_CALLBACK pfnti, PVOID pv, PTP_CALLBACK_ENVIRON pcbe)
{
    return CreateThreadpoolTimer(pfnti, pv, pcbe);
}

PTP_WAIT CreateThreadpoolWait_X(PTP_WAIT_CALLBACK pfnwa, PVOID pv, PTP_CALLBACK_ENVIRON pcbe)
{
    return CreateThreadpoolWait(pfnwa, pv, pcbe);
}

PTP_WORK CreateThreadpoolWork_X(PTP_WORK_CALLBACK pfnwk, PVOID pv, PTP_CALLBACK_ENVIRON pcbe)
{
    return CreateThreadpoolWork(pfnwk, pv, pcbe);
}

PTP_POOL CreateThreadpool_X(PVOID reserved)
{
    return CreateThreadpool(reserved);
}

HANDLE CreateWaitableTimerA_X(LPSECURITY_ATTRIBUTES lpTimerAttributes, BOOL bManualReset, LPCSTR lpTimerName)
{
    return CreateWaitableTimerA(lpTimerAttributes, bManualReset, lpTimerName);
}

HANDLE CreateWaitableTimerExA_X(LPSECURITY_ATTRIBUTES lpTimerAttributes, LPCSTR lpTimerName, DWORD dwFlags, DWORD dwDesiredAccess)
{
    return CreateWaitableTimerExA_X(lpTimerAttributes, lpTimerName, dwFlags, dwDesiredAccess);
}

HANDLE CreateWaitableTimerExW_X(LPSECURITY_ATTRIBUTES lpTimerAttributes, LPCWSTR lpTimerName, DWORD dwFlags, DWORD dwDesiredAccess)
{
    return CreateWaitableTimerExW(lpTimerAttributes, lpTimerName, dwFlags, dwDesiredAccess);
}

HANDLE CreateWaitableTimerW_X(LPSECURITY_ATTRIBUTES lpTimerAttributes, BOOL bManualReset, LPCWSTR lpTimerName)
{
    return CreateWaitableTimerW_X(lpTimerAttributes, bManualReset, lpTimerName);
}

void DeleteFiber_X(LPVOID lpFiber)
{
    DeleteFiber(lpFiber);
}

BOOL DeleteFileA_X(LPCSTR lpFileName)
{
    return DeleteFileA(lpFileName);
}

BOOL DisconnectNamedPipe_X(HANDLE hNamedPipe)
{
    return DisconnectNamedPipe(hNamedPipe);
}

BOOL DuplicateHandle_X(HANDLE hSourceProcessHandle,HANDLE hSourceHandle, HANDLE hTargetProcessHandle, LPHANDLE lpTargetHandle, DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwOptions)
{
    return DuplicateHandle(hSourceProcessHandle, hSourceHandle, hTargetProcessHandle, lpTargetHandle, dwDesiredAccess, bInheritHandle, dwOptions);
}

BOOL EnterSynchronizationBarrier_X(LPSYNCHRONIZATION_BARRIER lpBarrier, DWORD dwFlags)
{
    return EnterSynchronizationBarrier(lpBarrier, dwFlags);
}

BOOL EnumSystemLocalesA_X(LOCALE_ENUMPROCA lpLocaleEnumProc, DWORD dwFlags)
{
    return EnumSystemLocalesA(lpLocaleEnumProc, dwFlags);
}

BOOL EnumSystemLocalesEx_X(LOCALE_ENUMPROCEX lpLocaleEnumProcEx, DWORD dwFlags, LPARAM lParam, LPVOID lpReserved)
{
    return EnumSystemLocalesEx(lpLocaleEnumProcEx, dwFlags, lParam, lpReserved);
}

BOOL EnumSystemLocalesW_X(LOCALE_ENUMPROCW lpLocaleEnumProc, DWORD dwFlags)
{
    return EnumSystemLocalesW(lpLocaleEnumProc, dwFlags);
}

BOOL InitializeCriticalSectionEx_X(LPCRITICAL_SECTION lpCriticalSection, DWORD dwSpinCount, DWORD Flags)
{
    return InitializeCriticalSectionEx(lpCriticalSection, dwSpinCount, Flags);
}

LPTOP_LEVEL_EXCEPTION_FILTER SetUnhandledExceptionFilter_X(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)
{
    return SetUnhandledExceptionFilter(lpTopLevelExceptionFilter);
}

BOOL TerminateProcess_X(HANDLE hProcess, UINT uExitCode)
{
    return TerminateProcess(hProcess, uExitCode);
}

HANDLE GetCurrentProcess_X()
{
    return GetCurrentProcess();
}

LONG UnhandledExceptionFilter_X(_EXCEPTION_POINTERS* ExceptionInfo)
{
    return UnhandledExceptionFilter(ExceptionInfo);
}

DWORD GetTickCount_X()
{
    return GetTickCount();
}

void RtlCaptureContext_X(PCONTEXT ContextRecord)
{
    return RtlCaptureContext(ContextRecord);
}

PRUNTIME_FUNCTION RtlLookupFunctionEntry_X(DWORD64 ControlPc, PDWORD64 ImageBase, PUNWIND_HISTORY_TABLE HistoryTable)
{
    return RtlLookupFunctionEntry(ControlPc, ImageBase, HistoryTable);
}

void RtlUnwindEx_X(PVOID TargetFrame, PVOID TargetIp, PEXCEPTION_RECORD ExceptionRecord, PVOID ReturnValue, PCONTEXT ContextRecord, PUNWIND_HISTORY_TABLE HistoryTable)
{
    RtlUnwindEx(TargetFrame, TargetIp, ExceptionRecord, ReturnValue, ContextRecord, HistoryTable);
}

BOOL DeviceIoControl_X(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped)
{
    return DeviceIoControl(hDevice, dwIoControlCode, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, lpBytesReturned, lpOverlapped);
}

HMODULE LoadLibraryExW_X(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)
{
    return LoadLibraryExW(lpLibFileName, hFile, dwFlags);
}

DWORD GetProcessId_X(HANDLE Process)
{
    return GetProcessId(Process);
}

void GetSystemTimeAsFileTime_X(LPFILETIME lpSystemTimeAsFileTime)
{
    return GetSystemTimeAsFileTime(lpSystemTimeAsFileTime);
}

DWORD WaitForSingleObjectEx_X(HANDLE hHandle, DWORD dwMilliseconds, BOOL bAlertable)
{
    return WaitForSingleObjectEx(hHandle, dwMilliseconds, bAlertable);
}

void GetStartupInfoW_X(LPSTARTUPINFOW lpStartupInfo)
{
    GetStartupInfoW(lpStartupInfo);
}

HMODULE GetModuleHandleW_X(LPCWSTR lpModuleName)
{
    return GetModuleHandleW(lpModuleName);
}

HMODULE GetModuleHandleA_X(LPCSTR lpModuleName)
{
    return GetModuleHandleA(lpModuleName);
}

void GetLocalTime_X(LPSYSTEMTIME lpSystemTime)
{
    GetLocalTime(lpSystemTime);
}

DWORD GetLastError_X()
{
    return GetLastError();
}

BOOL GetFileSizeEx_X(HANDLE hFile, PLARGE_INTEGER lpFileSize)
{
    return GetFileSizeEx(hFile, lpFileSize);
}

DWORD GetFileAttributesW_X(LPCWSTR lpFileName)
{
    return GetFileAttributesW(lpFileName);
}

BOOL GetFileAttributesExW_X(LPCWSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation)
{
    return GetFileAttributesExW(lpFileName, fInfoLevelId, lpFileInformation);
}

BOOL GetExitCodeThread_X(HANDLE hThread, LPDWORD lpExitCode)
{
    return GetExitCodeThread(hThread, lpExitCode);
}

HANDLE GetCurrentThread_X()
{
    return GetCurrentThread();
}

DWORD GetCurrentThreadId_X()
{
    return GetCurrentThreadId();
}

DWORD GetCurrentProcessId_X()
{
    return GetCurrentProcessId();
}

BOOL FindNextFileW_X(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData)
{
    return FindNextFileW(hFindFile, lpFindFileData);
}

HANDLE FindFirstFileW_X(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData)
{
    return FindFirstFileW(lpFileName, lpFindFileData);
}

BOOL FindClose_X(HANDLE hFindFile)
{
    return FindClose(hFindFile);
}

BOOL FileTimeToSystemTime_X(FILETIME* lpFileTime, LPSYSTEMTIME lpSystemTime)
{
    return FileTimeToSystemTime(lpFileTime, lpSystemTime);
}

void ExitProcess_X(UINT uExitCode)
{
    ExitProcess(uExitCode);
}

BOOL DeleteFileW_X(LPCWSTR lpFileName)
{
    return DeleteFileW(lpFileName);
}

BOOL DeleteSynchronizationBarrier_X(LPSYNCHRONIZATION_BARRIER lpBarrier)
{
	return DeleteSynchronizationBarrier(lpBarrier);
}

void DebugBreak_X()
{
    return DebugBreak();
}

HANDLE CreateThread_X(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId)
{
    return CreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
}

HANDLE CreateFileW_X(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
    return CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

HANDLE CreateEventW_X(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCWSTR lpName)
{
    return CreateEventW(lpEventAttributes, bManualReset, bInitialState, lpName);
}

HANDLE CreateEventExW_X(LPSECURITY_ATTRIBUTES lpEventAttributes, LPCWSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess)
{
    return CreateEventExW(lpEventAttributes, lpName, dwFlags, dwDesiredAccess);
}

BOOL CreateDirectoryW_X(LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
    return CreateDirectoryW(lpPathName, lpSecurityAttributes);
}

BOOL CloseHandle_X(HANDLE hObject)
{
    return CloseHandle(hObject);
}

BOOL VirtualFree_X(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType)
{
    //Get rid of Warnings i guess TODO
    //if (dwFreeType == 0) return;
    return VirtualFree(lpAddress, dwSize, dwFreeType);
}

BOOL TlsSetValue_X(DWORD dwTlsIndex, LPVOID lpTlsValue)
{
    return TlsSetValue(dwTlsIndex, lpTlsValue);
}

LPVOID VirtualAlloc_X(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect)
{
    return VirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
}


BOOL WriteFile_X(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
{
    return WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}

DWORD WaitForSingleObject_X(HANDLE hHandle, DWORD dwMilliseconds)
{
    return WaitForSingleObject(hHandle, dwMilliseconds);
}

DWORD WaitForMultipleObjects_X(DWORD nCount, HANDLE* lpHandles, BOOL bWaitAll, DWORD dwMilliseconds)
{
    return WaitForMultipleObjects(nCount, lpHandles, bWaitAll, dwMilliseconds);
}

LPVOID TlsGetValue_X(DWORD dwTlsIndex)
{
    return TlsGetValue(dwTlsIndex);
}

DWORD TlsAlloc_X()
{
    return TlsAlloc();
}

BOOL SystemTimeToFileTime_X(SYSTEMTIME* lpSystemTime, LPFILETIME lpFileTime)
{
    return SystemTimeToFileTime(lpSystemTime, lpFileTime);
}

void Sleep_X(DWORD dwMilliseconds)
{
    return Sleep(dwMilliseconds);
}

BOOL SetThreadPriority_X(HANDLE hThread, int nPriority)
{
    return SetThreadPriority(hThread, nPriority);
}

DWORD_PTR SetThreadAffinityMask_X(HANDLE hThread, DWORD_PTR dwThreadAffinityMask)
{
    return SetThreadAffinityMask(hThread, dwThreadAffinityMask);
}

DWORD SetFilePointer_X(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod)
{
    return SetFilePointer(hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod);
}

DWORD ResumeThread_X(HANDLE hThread)
{
    return ResumeThread(hThread);
}

BOOL ResetEvent_X(HANDLE hEvent)
{
    return ResetEvent(hEvent);
}

BOOL ReadFile_X(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped)
{
    return ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}

void RaiseException_X(DWORD dwExceptionCode, DWORD dwExceptionFlags, DWORD nNumberOfArguments, ULONG_PTR* lpArguments)
{
    return RaiseException(dwExceptionCode, dwExceptionFlags, nNumberOfArguments, lpArguments);
}

BOOL QueryPerformanceFrequency_X(LARGE_INTEGER* lpFrequency)
{
    return QueryPerformanceFrequency(lpFrequency);
}

BOOL QueryPerformanceCounter_X(LARGE_INTEGER* lpPerformanceCount)
{
    return QueryPerformanceCounter(lpPerformanceCount);
}

void OutputDebugStringA_X(LPCSTR lpOutputString)
{
    OutputDebugStringA(lpOutputString);
}

void OutputDebugStringW_X(LPCWSTR lpOutputString)
{
    OutputDebugStringW(lpOutputString);
}

int MultiByteToWideChar_X(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar)
{
    return MultiByteToWideChar(CodePage, dwFlags, lpMultiByteStr, cbMultiByte, lpWideCharStr, cchWideChar);
}

BOOL IsProcessorFeaturePresent_X(DWORD ProcessorFeature)
{
    return IsProcessorFeaturePresent(ProcessorFeature);
}

BOOL IsDebuggerPresent_X()
{
    return IsDebuggerPresent();
}

BOOL InitializeCriticalSectionAndSpinCount_X(LPCRITICAL_SECTION lpCriticalSection, DWORD dwSpinCount)
{
    return InitializeCriticalSectionAndSpinCount(lpCriticalSection, dwSpinCount);
}

GEOID GetUserGeoID_X(GEOCLASS GeoClass)
{
    return GetUserGeoID(GeoClass);
}

int GetUserDefaultLocaleName_X(LPWSTR lpLocaleName, int cchLocaleName)
{
    return GetUserDefaultLocaleName(lpLocaleName, cchLocaleName);
}

BOOL SetEvent_X(HANDLE hEvent)
{
    return SetEvent(hEvent);
}

BOOL PeekNamedPipe_X(HANDLE hNamedPipe, LPVOID lpBuffer, DWORD nBufferSize, LPDWORD lpBytesRead, LPDWORD lpTotalBytesAvail, LPDWORD lpBytesLeftThisMessage)
{
    return PeekNamedPipe(hNamedPipe, lpBuffer, nBufferSize, lpBytesRead, lpTotalBytesAvail, lpBytesLeftThisMessage);
}

BOOL DisableThreadLibraryCalls_X(HMODULE hLibModule)
{
    return DisableThreadLibraryCalls(hLibModule);
}

BOOL HeapFree_X(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem)
{
    return HeapFree(hHeap, dwFlags, lpMem);
}

void GetSystemTime_X(LPSYSTEMTIME lpSystemTime)
{
    GetSystemTime(lpSystemTime);
}


__int64 GetConsoleType_X()
{
    //STUB
    return 1;
    /*unsigned int v5; // ecx

    _RAX = 1073741837LL;
    __asm { cpuid }
    v5 = WORD1(_RCX);
    if (v5 >= 0x32)
    {
        switch (v5)
        {
        case '@':
            return 2LL;
        case 'P':
            return 3LL;
        case 'X':
            return 4LL;
        }
    }
    return 1LL;*/
}


// !!!!!
/*/ Should be in ntdll.dll reimplementation, right now i'm just testing things with DLLMain entryPoint
PVOID RtlSetUnhandledExceptionFilter(PVOID ExceptionFilter)
{
	return EncodePointer(ExceptionFilter);
}*/







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
    return 0;//TODO
}

INT16 sub_18001D768()
{
    return 0;//TODO
}

int sub_18001D96C(int v2, unsigned short* codePageData, unsigned int p, bool t,long l)
{
    return 0;//TODO
}

__int64 sub_18001BB8C()
{
    // I know this should be done inside dllmain.cpp entrypoint but this is litreally the same (as this is called always at attachment
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
BOOL WriteConsoleW_X(HANDLE hConsoleOutput, const void* lpBuffer, DWORD nNumberOfCharsToWrite, LPDWORD lpNumberOfCharsWritten, LPVOID lpReserved)
{
    return WriteConsoleW(hConsoleOutput, lpBuffer, nNumberOfCharsToWrite, lpNumberOfCharsWritten, lpReserved);
}

BOOL GetDiskFreeSpaceExW_X(LPCWSTR lpDirectoryName, PULARGE_INTEGER lpFreeBytesAvailableToCaller, PULARGE_INTEGER lpTotalNumberOfBytes, PULARGE_INTEGER lpTotalNumberOfFreeBytes)
{
    return GetDiskFreeSpaceExW(lpDirectoryName,lpFreeBytesAvailableToCaller, lpTotalNumberOfBytes, lpTotalNumberOfFreeBytes);
}
UINT GetDriveTypeW_X(LPCWSTR lpRootPathName)
{
    return GetDriveTypeW(lpRootPathName);
}
FARPROC GetProcAddress_X(HMODULE hModule, LPCSTR lpProcName)
{
    return GetProcAddress(hModule, lpProcName);
}
BOOL FreeLibrary_X(HMODULE hLibModule)
{
    return FreeLibrary(hLibModule);
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