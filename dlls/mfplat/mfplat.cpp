// mfplat.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "mfplat.h"

__int64 __fastcall MFCreateDxvaSampleRendererX_X(__int64 a, __int64 b, __int64 c)
{
	return 0;
}

__int64 MFResetDXGIDeviceManagerX_X() { return 0; }

HRESULT MFCreateDXGIDeviceManager_X(UINT* resetToken, /*IMFDXGIDeviceManager*/PVOID64 ppDeviceManager)
{
	return 0;
}
HRESULT MFCreateAttributes_X(/*IMFAttributes*/PVOID64** ppMFAttributes, UINT32 cInitialSize)
{
	return 0;
}
HRESULT MFCreateMediaType_X(/*IMFMediaType*/PVOID64** ppMFType)
{
	return 0;
}
HRESULT MFStartup_X(ULONG Version, DWORD dwFlags)
{
	return 0;
}