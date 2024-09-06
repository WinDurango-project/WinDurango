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

void GetCurrentPackageInfo_X() { }

void GetCurrentPackagePath_X() { }

void GetCurrentXboxLiveInfo_X() { }

void GetCurrentXboxLiveTitleId_X() { }

void GetPackageFamilyName_X() { }

void GetPackageFullName_X() { }

LONG GetPackageId_X(HANDLE hProcess, UINT32 *bufferLength, BYTE *buffer) { return 0; }

void GetPackagePath_X() { }

void GetPackageXboxLiveInfo_X() { }

void GetPackagesByPackageFamily_X() { }

void GetProcessXboxLiveInfo_X() { }

void GetXboxLiveTitleId_X() { }

void PsmBlockAppStateChangeCompletion_X() { }

void PsmRegisterAppStateChangeNotification_X() { }

void PsmShutdownApplication_X() { }

void PsmUnblockAppStateChangeCompletion_X() { }

void PsmUnregisterAppStateChangeNotification_X() { }

void PsmWaitForAppResume_X() { }