#pragma once

#include "framework.h"

// EXE EXPORTS
extern "C"
{
	void AcquireSRWLockExclusive_X(PSRWLOCK SRWLock);

	void AcquireSRWLockShared_X(PSRWLOCK SRWLock);

	void EnterCriticalSection_X(LPCRITICAL_SECTION lpCriticalSection);

	HANDLE GetProcessHeap_X();

	BOOL __stdcall GetDiskFreeSpaceExW_X(LPCWSTR lpDirectoryName, PULARGE_INTEGER lpFreeBytesAvailableToCaller, PULARGE_INTEGER lpTotalNumberOfBytes, PULARGE_INTEGER lpTotalNumberOfFreeBytes);

	FARPROC __stdcall GetProcAddress_X(HMODULE hModule, LPCSTR lpProcName);
	// TODO: Need to figure out this function.
	PVOID XMemAllocDefault_X(ULONG_PTR a1, UINT64 a2);

	PVOID XMemAlloc_X(SIZE_T dwSize, ULONGLONG dwAttributes);

  	BOOL XMemFree_X(PVOID P, UINT64 a2);

	BOOL __stdcall WriteConsoleW_X(HANDLE hConsoleOutput, const void* lpBuffer, DWORD nNumberOfCharsToWrite, LPDWORD lpNumberOfCharsWritten, LPVOID lpReserved);

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

  	BOOL XMemFreeDefault_X(PVOID P, UINT64 a2);

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

	void GetStartupInfoW_X(LPSTARTUPINFOW lpStartupInfo);

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
