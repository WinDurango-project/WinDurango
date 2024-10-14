// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClassCanBeFinal
// ReSharper disable CppPolymorphicClassWithNonVirtualPublicDestructor
// ReSharper disable CppClangTidyClangDiagnosticNonVirtualDtor
#pragma once
#include "ICoreApplicationX.h"


class CoreApplicationX : public ICoreApplicationX
{
public:
	CoreApplicationX(winrt::Windows::ApplicationModel::Core::CoreApplication* application)
	{
		m_applicationCore = reinterpret_cast<winrt::Windows::ApplicationModel::Core::CoreApplication*>(application);
		m_IapplicationCore = reinterpret_cast<ABI::Windows::ApplicationModel::Core::ICoreApplication*>(application);
		m_coreWindow = reinterpret_cast<ABI::Windows::UI::Core::ICoreWindow*>(application);
	}

public:
	HRESULT GetIids(ULONG* iidCount, IID** iids) override;
	HRESULT GetRuntimeClassName(HSTRING* className) override;
	HRESULT GetTrustLevel(TrustLevel* trustLevel) override;
	INT32 _abi_add_Resuming(__FIEventHandler_1_IInspectable* handler, EventRegistrationToken* token) override;
	INT32 _abi_remove_Resuming(EventRegistrationToken token) override;
	INT32 _abi_add_Suspending(__FIEventHandler_1_Windows__CApplicationModel__CSuspendingEventArgs* handler, EventRegistrationToken* token) override;
	INT32 _abi_remove_Suspending(EventRegistrationToken token) override;
	INT32 _abi_get_ResourceAvailability() override;
	INT32 _abi_add_ResourceAvailabilityChanged(winrt::Windows::Foundation::EventHandler<IInspectable>* handler, EventRegistrationToken* token) override;
	INT32 _abi_remove_ResourceAvailabilityChanged(EventRegistrationToken token) override;

	INT32 _abi_RunWithActivationFactories(ABI::Windows::Foundation::IGetActivationFactory* activationFactoryCallback) override;
	INT32 _abi_GetCurrentView(ABI::Windows::ApplicationModel::Core::ICoreApplicationView** value) override;
	INT32 _abi_Run(ABI::Windows::ApplicationModel::Core::IFrameworkViewSource* viewSource) override;
	INT32 Run(ABI::Windows::ApplicationModel::Core::IFrameworkViewSource* viewSource) override;
	INT32 _abi_get_Id(HSTRING* value) override;
	INT32 _abi_get_Properties(ABI::Windows::Foundation::Collections::IPropertySet** value) override;

	HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
	ULONG AddRef() override;
	ULONG Release() override;

private:
	winrt::Windows::ApplicationModel::Core::CoreApplication* m_applicationCore;
	ABI::Windows::ApplicationModel::Core::ICoreApplication* m_IapplicationCore;
	ABI::Windows::UI::Core::ICoreWindow* m_coreWindow;

};