// appmodel.cpp : Defines the exported functions for the DLL.
#include "pch.h"
#include "appmodel.h"

HRESULT CreateRandomAccessStreamOnFile_X(PCWSTR filePath, DWORD accessMode, REFIID riid, void **ppv) { return TRUE; }

HRESULT CreateRandomAccessStreamOverStream_X(
	// IStream      *stream,
	// BSOS_OPTIONS options,
	REFIID       riid,
	void         **ppv) 
{
	return TRUE;
}

void DllCanUnloadNow_X() { }

void DllGetActivationFactory_X() { }

void DllGetClassObject_X() { }

void GetApplicationUserModelId_X() { }

void GetApplicationXboxLiveInfo_X() { }

void GetCurrentApplicationUserModelId_X() { }

void GetCurrentPackageFamilyName_X() { }

void GetCurrentPackageFullName_X() { }

void GetCurrentPackageId_X() { }


void GetCurrentPackagePath_X() { }



void GetPackageFamilyName_X() { }

void GetPackagePath_X() { }

void GetPackageXboxLiveInfo_X() { }

void GetProcessXboxLiveInfo_X() { }

void GetXboxLiveTitleId_X() { }

void PsmBlockAppStateChangeCompletion_X() { }

void PsmRegisterAppStateChangeNotification_X() { }

void PsmShutdownApplication_X() { }

void PsmUnblockAppStateChangeCompletion_X() { }

void PsmWaitForAppResume_X() { }

LONG GetPackageId(HANDLE hProcess, UINT32* bufferLength, BYTE* buffer) { return 0; }

LONG GetPackageFullName_X(HANDLE hProcess, UINT32* packageFullNameLength, PWSTR packageFullName) { return 0; }

LONG GetCurrentPackageInfo_X(const UINT32 flags, UINT32* bufferLength, BYTE* buffer, UINT32* count) { return 0; }

LONG GetPackagesByPackageFamily_X(PCWSTR packageFamilyName, UINT32* count, PWSTR* packageFullNames, UINT32* bufferLength, WCHAR* buffer) { return 0; }

__int64 __fastcall GetCurrentXboxLiveTitleId_X(__int64 a) { return 0; }

__int64 __fastcall GetCurrentXboxLiveInfo_X(__int64 a, __int64 b, __int64 c) { return 0; }

__int64 __fastcall PsmUnregisterAppStateChangeNotification(__int64 notificationId, __int64 processId, __int64 additionalParam) { return 0; }