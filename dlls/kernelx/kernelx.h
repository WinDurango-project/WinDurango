#pragma once

#include "framework.h"

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

// EXE EXPORTS
extern "C"
{

	BOOL AllocateTitlePhysicalPages_X();

	BOOL Beep_X(DWORD dwFreq, DWORD dwDuration);

	BOOL BindIoCompletionCallback_X(HANDLE FileHandle, LPOVERLAPPED_COMPLETION_ROUTINE Function, ULONG Flags);

	BOOL CallbackMayRunLong_X(PTP_CALLBACK_INSTANCE pci);

	BOOL CancelIoEx_X(HANDLE hFile, LPOVERLAPPED lpOverlapped);

	BOOL CancelSynchronousIo_X(HANDLE hThread);

	BOOL CancelWaitableTimer_X(HANDLE hTimer);

	LONG CompareFileTime_X(const FILETIME* lpFileTime1, const FILETIME* lpFileTime2);

	int CompareStringEx_X(LPCWSTR lpLocaleName, DWORD dwCmpFlags, LPCWSTR lpString1, int cchCount1, LPCWSTR lpString2, int cchCount2, LPNLSVERSIONINFO lpVersionInformation, LPVOID lpReserved, LPARAM lParam);

	int CompareStringOrdinal_X(LPCWCH lpString1, int cchCount1, LPCWCH lpString2, int cchCount2, BOOL bIgnoreCase);

	int CompareStringW_X(LCID Locale, DWORD dwCmpFlags, PCNZWCH lpString1, int cchCount1, PCNZWCH lpString2, int cchCount2);

	BOOL ConnectNamedPipe_X(HANDLE hNamedPipe, LPOVERLAPPED lpOverlapped);

	BOOL ConvertFiberToThread_X();

	LPVOID ConvertThreadToFiberEx_X(LPVOID lpParameter, DWORD dwFlags);

	LPVOID ConvertThreadToFiber_X(LPVOID lpParameter);

	BOOL CopyContext_X(PCONTEXT Destination, DWORD ContextFlags, PCONTEXT Source);

	HRESULT CopyFile2_X(PCWSTR pwszExistingFileName, PCWSTR pwszNewFileName, COPYFILE2_EXTENDED_PARAMETERS* pExtendedParameters);

	BOOL CreateDirectoryA_X(LPCSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);

	HANDLE CreateEventA_X(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCSTR lpName);

	HANDLE CreateEventExA_X(LPSECURITY_ATTRIBUTES lpEventAttributes, LPCSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess);

	LPVOID CreateFiberEx_X(SIZE_T dwStackCommitSize, SIZE_T dwStackReserveSize, DWORD dwFlags, LPFIBER_START_ROUTINE lpStartAddress, LPVOID lpParameter);

	LPVOID CreateFiber_X(SIZE_T dwStackSize, LPFIBER_START_ROUTINE lpStartAddress, LPVOID lpParameter);

	void CreateFile2_X();

	HANDLE CreateFileA_X(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);

	HANDLE CreateFileMappingW_X(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCWSTR lpName);

	HANDLE CreateIoCompletionPort_X(HANDLE FileHandle, HANDLE ExistingCompletionPort, ULONG_PTR CompletionKey, DWORD NumberOfConcurrentThreads);

	HANDLE CreateMutexA_X(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName);

	HANDLE CreateMutexExA_X(LPSECURITY_ATTRIBUTES lpMutexAttributes, LPCSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess);

	HANDLE CreateMutexExW_X(LPSECURITY_ATTRIBUTES lpMutexAttributes, LPCWSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess);

	HANDLE CreateMutexW_X(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCWSTR lpName);

	HANDLE CreateNamedPipeW_X(LPCWSTR lpName, DWORD dwOpenMode, DWORD dwPipeMode, DWORD nMaxInstances, DWORD nOutBufferSize, DWORD nInBufferSize, DWORD nDefaultTimeOut, LPSECURITY_ATTRIBUTES lpSecurityAttributes);

	BOOL CreatePipe_X(PHANDLE hReadPipe, PHANDLE hWritePipe, LPSECURITY_ATTRIBUTES lpPipeAttributes, DWORD nSize);

	BOOL CreateProcessA_X(LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation);

	BOOL CreateProcessW_X(LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation);

	HANDLE CreateRemoteThread_X(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);

	HANDLE CreateSemaphoreA_X(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, LONG lInitialCount, LONG lMaximumCount, LPCSTR lpName);

	HANDLE CreateSemaphoreExA_X(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, LONG lInitialCount, LONG lMaximumCount, LPCSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess);

	HANDLE CreateSemaphoreExW_X(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, LONG lInitialCount, LONG lMaximumCount, LPCWSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess);

	HANDLE CreateSemaphoreW_X(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, LONG lInitialCount, LONG lMaximumCount, LPCWSTR lpName);

	PTP_CLEANUP_GROUP CreateThreadpoolCleanupGroup_X();

	PTP_IO CreateThreadpoolIo_X(HANDLE fl, PTP_WIN32_IO_CALLBACK pfnio, PVOID pv, PTP_CALLBACK_ENVIRON pcbe);

	PTP_TIMER CreateThreadpoolTimer_X(PTP_TIMER_CALLBACK pfnti, PVOID pv, PTP_CALLBACK_ENVIRON pcbe);

	PTP_WAIT CreateThreadpoolWait_X(PTP_WAIT_CALLBACK pfnwa, PVOID pv, PTP_CALLBACK_ENVIRON pcbe);

	PTP_WORK CreateThreadpoolWork_X(PTP_WORK_CALLBACK pfnwk, PVOID pv, PTP_CALLBACK_ENVIRON pcbe);

	PTP_POOL CreateThreadpool_X(PVOID reserved);

	HANDLE CreateWaitableTimerA_X(LPSECURITY_ATTRIBUTES lpTimerAttributes, BOOL bManualReset, LPCSTR lpTimerName);

	HANDLE CreateWaitableTimerExA_X(LPSECURITY_ATTRIBUTES lpTimerAttributes, LPCSTR lpTimerName, DWORD dwFlags, DWORD dwDesiredAccess);

	HANDLE CreateWaitableTimerExW_X(LPSECURITY_ATTRIBUTES lpTimerAttributes, LPCWSTR lpTimerName, DWORD dwFlags, DWORD dwDesiredAccess);

	HANDLE CreateWaitableTimerW_X(LPSECURITY_ATTRIBUTES lpTimerAttributes, BOOL bManualReset, LPCWSTR lpTimerName);

	void DeleteFiber_X(LPVOID lpFiber);

	BOOL DeleteFileA_X(LPCSTR lpFileName);

	BOOL DisconnectNamedPipe_X(HANDLE hNamedPipe);

	BOOL DuplicateHandle_X(HANDLE hSourceProcessHandle, HANDLE hSourceHandle, HANDLE hTargetProcessHandle, LPHANDLE lpTargetHandle, DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwOptions);

	BOOL EnterSynchronizationBarrier_X(LPSYNCHRONIZATION_BARRIER lpBarrier, DWORD dwFlags);

	BOOL EnumSystemLocalesA_X(LOCALE_ENUMPROCA lpLocaleEnumProc, DWORD dwFlags);

	BOOL EnumSystemLocalesEx_X(LOCALE_ENUMPROCEX lpLocaleEnumProcEx, DWORD dwFlags, LPARAM lParam, LPVOID lpReserved);

	BOOL EnumSystemLocalesW_X(LOCALE_ENUMPROCW lpLocaleEnumProc, DWORD dwFlags);

	void EnterCriticalSection_X(LPCRITICAL_SECTION lpCriticalSection);

	HANDLE GetProcessHeap_X();

	BOOL GetDiskFreeSpaceExW_X(LPCWSTR lpDirectoryName, PULARGE_INTEGER lpFreeBytesAvailableToCaller, PULARGE_INTEGER lpTotalNumberOfBytes, PULARGE_INTEGER lpTotalNumberOfFreeBytes);

	FARPROC GetProcAddress_X(HMODULE hModule, LPCSTR lpProcName);
	// TODO: Need to figure out this function.
	PVOID XMemAllocDefault_X(ULONG_PTR a1, UINT64 a2);

	PVOID XMemAlloc_X(SIZE_T dwSize, ULONGLONG dwAttributes);

  	BOOL XMemFree_X(PVOID P, UINT64 a2);

	BOOL WriteConsoleW_X(HANDLE hConsoleOutput, const void* lpBuffer, DWORD nNumberOfCharsToWrite, LPDWORD lpNumberOfCharsWritten, LPVOID lpReserved);

  	LPTOP_LEVEL_EXCEPTION_FILTER SetUnhandledExceptionFilter_X(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter);

	BOOL TerminateProcess_X(HANDLE hProcess, UINT uExitCode);

	HANDLE GetCurrentProcess_X();

	LONG UnhandledExceptionFilter_X(_EXCEPTION_POINTERS* ExceptionInfo);

	DWORD GetTickCount_X();

	void RtlCaptureContext_X(PCONTEXT ContextRecord);

	PRUNTIME_FUNCTION RtlLookupFunctionEntry_X(DWORD64 ControlPc, PDWORD64 ImageBase, PUNWIND_HISTORY_TABLE HistoryTable);

  	void RtlUnwindEx_X(PVOID TargetFrame, PVOID TargetIp, PEXCEPTION_RECORD ExceptionRecord, PVOID ReturnValue, PCONTEXT ContextRecord, PUNWIND_HISTORY_TABLE HistoryTable);

  	BOOL DeviceIoControl_X(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped);

  	HMODULE LoadLibraryExW_X(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags);

  	DWORD GetProcessId_X(HANDLE Process);

	void GetSystemTimeAsFileTime_X(LPFILETIME lpSystemTimeAsFileTime);

	DWORD WaitForSingleObjectEx_X(HANDLE hHandle, DWORD dwMilliseconds, BOOL bAlertable);

	void GetStartupInfoW_X(LPSTARTUPINFOW lpStartupInfo);

	BOOL VirtualFree_X(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType);

	BOOL TlsSetValue_X(DWORD dwTlsIndex, LPVOID lpTlsValue);

	LPVOID VirtualAlloc_X(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);

	bool XMemFreeDefault_X(PVOID P, unsigned __int64 a2);

	BOOL WriteFile_X(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);

	DWORD WaitForSingleObject_X(HANDLE hHandle, DWORD dwMilliseconds);

	DWORD WaitForMultipleObjects_X(DWORD nCount, HANDLE* lpHandles, BOOL bWaitAll, DWORD dwMilliseconds);

	LPVOID  TlsGetValue_X(DWORD dwTlsIndex);

	DWORD TlsAlloc_X();

	BOOL  SystemTimeToFileTime_X(SYSTEMTIME* lpSystemTime, LPFILETIME lpFileTime);

	void Sleep_X(DWORD dwMilliseconds);

	BOOL SetThreadPriority_X(HANDLE hThread, int nPriority);

	DWORD_PTR SetThreadAffinityMask_X(HANDLE hThread, DWORD_PTR dwThreadAffinityMask);

	DWORD SetFilePointer_X(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);

	DWORD ResumeThread_X(HANDLE hThread);

	BOOL ResetEvent_X(HANDLE hEvent);

	BOOL ReadFile_X(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);

	void RaiseException_X(DWORD dwExceptionCode, DWORD dwExceptionFlags, DWORD nNumberOfArguments, ULONG_PTR* lpArguments);

	BOOL QueryPerformanceFrequency_X(LARGE_INTEGER* lpFrequency);

	BOOL QueryPerformanceCounter_X(LARGE_INTEGER* lpPerformanceCount);

  	void OutputDebugStringA_X(LPCSTR lpOutputString);

  	void OutputDebugStringW_X(LPCWSTR lpOutputString);

	int MultiByteToWideChar_X(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);

	BOOL IsProcessorFeaturePresent_X(DWORD ProcessorFeature);

	BOOL IsDebuggerPresent_X();

	BOOL InitializeCriticalSectionAndSpinCount_X(LPCRITICAL_SECTION lpCriticalSection, DWORD dwSpinCount);

 	BOOL InitializeCriticalSectionEx_X(LPCRITICAL_SECTION lpCriticalSection, DWORD dwSpinCount, DWORD Flags);

  	GEOID GetUserGeoID_X(GEOCLASS GeoClass);

	int GetUserDefaultLocaleName_X(LPWSTR lpLocaleName, int cchLocaleName);

	void GetSystemTime_X(LPSYSTEMTIME lpSystemTime);

	HMODULE GetModuleHandleW_X(LPCWSTR lpModuleName);

  	HMODULE GetModuleHandleA_X(LPCSTR lpModuleName);

  	void GetLocalTime_X(LPSYSTEMTIME lpSystemTime);

	DWORD GetLastError_X();

	BOOL GetFileSizeEx_X(HANDLE hFile, PLARGE_INTEGER lpFileSize);

	DWORD GetFileAttributesW_X(LPCWSTR lpFileName);

	BOOL GetFileAttributesExW_X(LPCWSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation);

	BOOL GetExitCodeThread_X(HANDLE hThread, LPDWORD lpExitCode);

	HANDLE GetCurrentThread_X();

	DWORD GetCurrentThreadId_X();

	DWORD GetCurrentProcessId_X();

	BOOL FindNextFileW_X(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData);

	HANDLE FindFirstFileW_X(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData);

	BOOL FindClose_X(HANDLE hFindFile);

	BOOL FileTimeToSystemTime_X(FILETIME* lpFileTime, LPSYSTEMTIME lpSystemTime);

	void ExitProcess_X(UINT uExitCode);

	BOOL DeleteFileW_X(LPCWSTR lpFileName);

	BOOL DeleteSynchronizationBarrier_X(LPSYNCHRONIZATION_BARRIER lpBarrier);

	void DebugBreak_X();

  	BOOL SetEvent_X(HANDLE hEvent);

  	HANDLE CreateThread_X(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);

	HANDLE CreateFileW_X(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);

	HANDLE CreateEventW_X(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCWSTR lpName);

	HANDLE CreateEventExW_X(LPSECURITY_ATTRIBUTES lpEventAttributes, LPCWSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess);

	BOOL CreateDirectoryW_X(LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);

	BOOL CloseHandle_X(HANDLE hObject);

  	BOOL DisableThreadLibraryCalls_X(HMODULE hLibModule);

  	BOOL HeapFree_X(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem);

  	BOOL PeekNamedPipe_X(HANDLE hNamedPipe, LPVOID lpBuffer, DWORD nBufferSize, LPDWORD lpBytesRead, LPDWORD lpTotalBytesAvail, LPDWORD lpBytesLeftThisMessage);

  	__int64 GetConsoleType_X();

	//BOOL TerminateProcess(HANDLE hProcess, UINT uExitCode);
}
// EXE EXPORTS END


//PVOID RtlSetUnhandledExceptionFilter(PVOID ExceptionFilter);

//DLLMain entrypoint matching test
__int64 sub_18001BB8C();
NTSTATUS sub_18001BCA0(HINSTANCE hInstance, DWORD forwardReason, LPVOID lpvReserved);
