#define H_API extern "C" __declspec( dllexport )

H_API HRESULT(__stdcall* MFCreateDXGIDeviceManager)(UINT* resetToken, /*IMFDXGIDeviceManager*/PVOID64 ppDeviceManager);
H_API __int64(__fastcall* MFCreateDxvaSampleRendererX)(__int64 a, __int64 b, __int64 c);
H_API __int64 (*MFResetDXGIDeviceManagerX)();
H_API HRESULT(__stdcall* MFCreateAttributes)(/*IMFAttributes*/PVOID64** ppMFAttributes, UINT32 cInitialSize);
H_API HRESULT(__stdcall* MFCreateMediaType)(/*IMFMediaType*/PVOID64** ppMFType);
H_API HRESULT(__stdcall* MFStartup)(ULONG Version, DWORD dwFlags);
