#pragma once
#include <winrt/Windows.ApplicationModel.h>

#include "CoreApplicationX.h"

class CCoreApplicationResourceAvailabilityX : public ICoreApplicationResourceAvailabilityX
{
	LONG m_RefCount = 1;

public:
	IFACEMETHOD(QueryInterface)(REFIID iid, void** ppv)
	{
		if (ppv == nullptr) return E_POINTER;

		if (iid == __uuidof(IUnknown) || iid == __uuidof(IInspectable) || iid == __uuidof(ICoreApplicationResourceAvailabilityX))
		{
			this->AddRef();

			*ppv = this;
			
			return S_OK;
		}

		*ppv = nullptr;

		return E_NOINTERFACE;
	}

	IFACEMETHOD_(ULONG, AddRef)()
	{
		return InterlockedIncrement(&this->m_RefCount);
	}

	IFACEMETHOD_(ULONG, Release)()
	{
		const auto refCount = InterlockedDecrement(&this->m_RefCount);

		if (refCount == 0) delete this;

		return refCount;
	}

	IFACEMETHOD(_abi_get_ResourceAvailability)(ResourceAvailability *value)
	{
		if (value == nullptr) return E_POINTER;

		*value = ResourceAvailability_Full;

		return S_OK();
	}

	IFACEMETHOD(_abi_add_ResourceAvailabilityChanged)(__FIEventHandler_1_IInspectable  *handler, EventRegistrationToken *token)
	{
		if (token == nullptr) return E_POINTER;

		*token = {};

		return S_OK();
	}

	IFACEMETHOD(_abi_remove_ResourceAvailabilityChanged)(EventRegistrationToken token)
	{
		return S_OK();
	}

	IFACEMETHOD(GetIids)(ULONG* iidCount, IID** iids)
	{
		// TODO: Implement this method.
		return S_OK();
	}

	IFACEMETHOD(GetRuntimeClassName)(HSTRING* className)
	{		
		if (className == nullptr) return E_POINTER;

		HSTRING _className = nullptr;

		WindowsCreateString(L"Windows.Core.CCoreApplicationResourceAvailability", 39, &_className);

		*className = _className;

		return S_OK();
	}

	IFACEMETHOD(GetTrustLevel)(TrustLevel* trustLevel)
	{
		*trustLevel = FullTrust;

		return S_OK();
	}
};

inline bool IsClassName(HSTRING classId, const char* classIdName)
{
	const wchar_t* classIdString = WindowsGetStringRawBuffer(classId, nullptr);
	std::wstring classIdWString(classIdString);
	const std::string classIdStringUTF8(classIdWString.begin( ), classIdWString.end( ));

	return (classIdStringUTF8 == classIdName);
}

typedef HRESULT(*DllGetForCurrentThreadFunc) (ICoreWindowStatic*, CoreWindow**);
typedef HRESULT(*DllGetForCurrentThreadFunc_App) (ICoreApplication*, winrt::Windows::ApplicationModel::Core::CoreApplication**);
typedef HRESULT(*CoreApplicationFactory_QueryInterface) (IUnknown* pFactory, REFIID iid, void** ppv);
typedef HRESULT(*DllGetActivationFactoryFunc) (HSTRING, IActivationFactory**);

DllGetForCurrentThreadFunc pDllGetForCurrentThread = nullptr;
DllGetForCurrentThreadFunc_App pDllGetForCurrentThread_App = nullptr;
CoreApplicationFactory_QueryInterface pCoreApplicationFactory_QueryInterface = nullptr;
DllGetActivationFactoryFunc pDllGetActivationFactory = nullptr;

HRESULT(STDMETHODCALLTYPE* TrueGetForCurrentThread)(ICoreWindowStatic* staticWindow, CoreWindow** window);
HRESULT(STDMETHODCALLTYPE* TrueGetForCurrentThread_App)(ICoreApplication* application, winrt::Windows::ApplicationModel::Core::CoreApplication** Application);
HRESULT(STDMETHODCALLTYPE* TrueCoreApplicationFactory_QueryInterface)(IUnknown* factory, REFIID iid, void** ppv);
HRESULT(WINAPI* TrueRoGetActivationFactory)(HSTRING classId, REFIID iid, void** factory) = RoGetActivationFactory;

/* Hook for ICoreWindowStatic's GetCurrentThread function. */
inline HRESULT STDMETHODCALLTYPE GetForCurrentThread_Hook(ICoreWindowStatic* paramThis, CoreWindow** window)
{
	// ReSharper disable once CppLocalVariableMayBeConst
	HRESULT hr = TrueGetForCurrentThread(paramThis, window);

	//*reinterpret_cast<void**>(window) = new CoreWindowX(*window);
	auto p = *reinterpret_cast<void**>(window);

	p = new CoreWindowX(*window);

	return hr;
}

/* Hook for CoreApplication's GetForCurrentThread function. */
inline HRESULT STDMETHODCALLTYPE GetForCurrentThreadCoreApplication_Hook(ICoreApplication* paramThis, winrt::Windows::ApplicationModel::Core::CoreApplication** Application)
{
	// ReSharper disable once CppLocalVariableMayBeConst
	HRESULT hrApp = TrueGetForCurrentThread_App(paramThis, Application);

	auto pApp = *reinterpret_cast<void**>(Application);

	pApp = new CoreApplicationX(*Application);

	return hrApp;
}

/* Hook for CoreApplicationFactory's QueryInterface function. */
inline HRESULT STDMETHODCALLTYPE CoreApplicationFactory_QueryInterface_Hook(IUnknown* pFactory, REFIID iid, void** ppv)
{
	if (ppv == nullptr)
		return E_POINTER;

	if (iid == __uuidof(ICoreApplicationResourceAvailabilityX))
	{
		*ppv = new CCoreApplicationResourceAvailabilityX;

		return S_OK();
	}

	return TrueCoreApplicationFactory_QueryInterface(pFactory, iid, ppv);
}

/* Hook for the WinRT RoGetActivationFactory function. */
inline HRESULT WINAPI RoGetActivationFactory_Hook(HSTRING classId, REFIID iid, void** factory)
{
	auto hr = TrueRoGetActivationFactory(classId, iid, factory);

	if (FAILED(hr))
	{
		auto library = LoadPackagedLibrary(L"winrt_x.dll", 0);

		if (!library) library = LoadLibraryW(L"winrt_x.dll");

		if (!library) return hr;

		pDllGetActivationFactory = reinterpret_cast<DllGetActivationFactoryFunc>
			(GetProcAddress(library, "DllGetActivationFactory"));

		if (!pDllGetActivationFactory)
			return hr;

		ComPtr<IActivationFactory> _factory;

		if (IsClassName(classId, "Windows.ApplicationModel.Core.ICoreApplicationResourceAvailability"))
		{
			// TODO: Implement this method.

			// TODO: Get the correct vtable index.
			*reinterpret_cast<void**>(&TrueCoreApplicationFactory_QueryInterface); // = (*reinterpret_cast<void***>(_factory.Get()))[0];

			DetourAttach(&TrueCoreApplicationFactory_QueryInterface, CoreApplicationFactory_QueryInterface_Hook);
		}
		else if (IsClassName(classId, "Windows.ApplicationModel.Core.CoreApplication"))
		{
			ComPtr<ICoreApplication> ICoreApplicationPtr;

			hr = RoGetActivationFactory(HStringReference(RuntimeClass_Windows_ApplicationModel_Core_CoreApplication).Get(), IID_PPV_ARGS(&ICoreApplicationPtr));

			*reinterpret_cast<void**>(&TrueGetForCurrentThread_App) = (*reinterpret_cast<void***>(ICoreApplicationPtr.Get()))[6];

			DetourAttach(&TrueGetForCurrentThread_App, GetForCurrentThreadCoreApplication_Hook);
		}
		else if (IsClassName(classId, "Windows.UI.Core.CoreWindow"))
		{
			ComPtr<ICoreWindowStatic> coreWindowStatic;

			hr = RoGetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Core_CoreWindow).Get(), IID_PPV_ARGS(&coreWindowStatic));

			*reinterpret_cast<void**>(&TrueGetForCurrentThread) = (*reinterpret_cast<void***>(coreWindowStatic.Get()))[6];

			DetourAttach(&TrueGetForCurrentThread, GetForCurrentThread_Hook);
		}
		else
		{
			hr = pDllGetActivationFactory(classId, _factory.GetAddressOf());
		}

		if (FAILED(hr)) return hr;

		return _factory.CopyTo(iid, factory);
	}

	return hr;
}