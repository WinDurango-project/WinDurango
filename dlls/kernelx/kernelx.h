#pragma once

#include "framework.h"

// EXE EXPORTS
extern "C" void AcquireSRWLockExclusive_X(PSRWLOCK SRWLock);

extern "C" void AcquireSRWLockShared_X(PSRWLOCK SRWLock);

extern "C" void EnterCriticalSection_X(LPCRITICAL_SECTION lpCriticalSection);

extern "C" HANDLE GetProcessHeap_X();

// TODO: Need to figure out this function.
extern "C" PVOID XMemAllocDefault_X(ULONG_PTR a1, UINT64 a2);

extern "C" PVOID XMemAlloc_X(SIZE_T dwSize, ULONGLONG dwAttributes);

extern "C" BOOL XMemFree_X(PVOID P, unsigned __int64 a2);

extern "C" LPTOP_LEVEL_EXCEPTION_FILTER SetUnhandledExceptionFilter_X(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter);

extern "C" BOOL TerminateProcess_X(HANDLE hProcess, UINT uExitCode);

extern "C" HANDLE GetCurrentProcess_X();

extern "C" LONG UnhandledExceptionFilter_X(_EXCEPTION_POINTERS* ExceptionInfo);

extern "C" DWORD GetTickCount_X();

extern "C" void RtlCaptureContext_X(PCONTEXT ContextRecord);

extern "C" PRUNTIME_FUNCTION RtlLookupFunctionEntry_X(DWORD64 ControlPc, PDWORD64 ImageBase, PUNWIND_HISTORY_TABLE HistoryTable);

extern "C" DWORD GetProcessId_X(HANDLE Process);

extern "C" void GetSystemTimeAsFileTime_X(LPFILETIME lpSystemTimeAsFileTime);

extern "C" DWORD WaitForSingleObjectEx_X(HANDLE hHandle, DWORD dwMilliseconds, BOOL bAlertable);

extern "C" void GetStartupInfoW_X(LPSTARTUPINFOW lpStartupInfo);

extern "C" BOOL VirtualFree_X(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType);

extern "C" BOOL TlsSetValue_X(DWORD dwTlsIndex, LPVOID lpTlsValue);

extern "C" LPVOID VirtualAlloc_X(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);

extern "C" BOOL XMemFreeDefault_X(PVOID P, unsigned __int64 a2);

extern "C" BOOL WriteFile_X(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);

extern "C" DWORD WaitForSingleObject_X(HANDLE hHandle, DWORD dwMilliseconds);

extern "C" DWORD WaitForMultipleObjects_X(DWORD nCount, HANDLE* lpHandles, BOOL bWaitAll, DWORD dwMilliseconds);

extern "C" LPVOID  TlsGetValue_X(DWORD dwTlsIndex);

extern "C" DWORD TlsAlloc_X();

extern "C" BOOL  SystemTimeToFileTime_X(SYSTEMTIME* lpSystemTime, LPFILETIME lpFileTime);

extern "C" void Sleep_X(DWORD dwMilliseconds);

extern "C" BOOL SetThreadPriority_X(HANDLE hThread, int nPriority);

extern "C" DWORD_PTR SetThreadAffinityMask_X(HANDLE hThread, DWORD_PTR dwThreadAffinityMask);

extern "C" DWORD SetFilePointer_X(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);

extern "C" DWORD ResumeThread_X(HANDLE hThread);

extern "C" BOOL ResetEvent_X(HANDLE hEvent);

extern "C" BOOL ReadFile_X(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);

extern "C" void RaiseException_X(DWORD dwExceptionCode, DWORD dwExceptionFlags, DWORD nNumberOfArguments, ULONG_PTR* lpArguments);

extern "C" BOOL QueryPerformanceFrequency_X(LARGE_INTEGER* lpFrequency);

extern "C" BOOL QueryPerformanceCounter_X(LARGE_INTEGER* lpPerformanceCount);

extern "C" void OutputDebugStringW_X(LPCWSTR lpOutputString);

extern "C" int MultiByteToWideChar_X(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);

extern "C" BOOL IsProcessorFeaturePresent_X(DWORD ProcessorFeature);

extern "C" BOOL IsDebuggerPresent_X();

extern "C" BOOL InitializeCriticalSectionAndSpinCount_X(LPCRITICAL_SECTION lpCriticalSection, DWORD dwSpinCount);

extern "C" GEOID GetUserGeoID_X(GEOCLASS GeoClass);

extern "C" int GetUserDefaultLocaleName_X(LPWSTR lpLocaleName, int cchLocaleName);

extern "C" void GetSystemTime_X(LPSYSTEMTIME lpSystemTime);

extern "C" void GetStartupInfoW_X(LPSTARTUPINFOW lpStartupInfo);

extern "C" HMODULE GetModuleHandleW_X(LPCWSTR lpModuleName);

extern "C" void GetLocalTime_X(LPSYSTEMTIME lpSystemTime);

extern "C" DWORD GetLastError_X();

extern "C" BOOL GetFileSizeEx_X(HANDLE hFile, PLARGE_INTEGER lpFileSize);

extern "C" DWORD GetFileAttributesW_X(LPCWSTR lpFileName);

extern "C" BOOL GetFileAttributesExW_X(LPCWSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation);

extern "C" BOOL GetExitCodeThread_X(HANDLE hThread, LPDWORD lpExitCode);

extern "C" HANDLE GetCurrentThread_X();

extern "C" DWORD GetCurrentThreadId_X();

extern "C" DWORD GetCurrentProcessId_X();

extern "C" BOOL FindNextFileW_X(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData);

extern "C" HANDLE FindFirstFileW_X(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData);

extern "C" BOOL FindClose_X(HANDLE hFindFile);

extern "C" BOOL FileTimeToSystemTime_X(FILETIME* lpFileTime, LPSYSTEMTIME lpSystemTime);

extern "C" void ExitProcess_X(UINT uExitCode);

extern "C" BOOL DeleteFileW_X(LPCWSTR lpFileName);

extern "C" void DebugBreak_X();

extern "C" HANDLE CreateThread_X(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);

extern "C" HANDLE CreateFileW_X(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);

extern "C" HANDLE CreateEventW_X(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCWSTR lpName);

extern "C" HANDLE CreateEventExW_X(LPSECURITY_ATTRIBUTES lpEventAttributes, LPCWSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess);

extern "C" BOOL CreateDirectoryW_X(LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);

extern "C" BOOL CloseHandle_X(HANDLE hObject);

extern "C" __int64 GetConsoleType_X();


//extern "C" BOOL TerminateProcess(HANDLE hProcess, UINT uExitCode);
// EXE EXPORTS END


PVOID RtlSetUnhandledExceptionFilter(PVOID ExceptionFilter);

__int64 sub_18001BB8C();

NTSTATUS sub_18001BCA0(HINSTANCE hInstance, DWORD forwardReason, LPVOID lpvReserved);