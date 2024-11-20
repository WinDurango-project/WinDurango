#pragma once
#include "ICoreApplicationX.h"

class CoreApplicationWrapperX : public ICoreApplicationX
{
public:
	CoreApplicationWrapperX(winrt::Windows::ApplicationModel::Core::CoreApplication* application)
	{
		m_applicationCore = reinterpret_cast<winrt::Windows::ApplicationModel::Core::CoreApplication*>(application);
		m_IapplicationCore = reinterpret_cast<ABI::Windows::ApplicationModel::Core::ICoreApplication*>(application);
		m_IapplicationCoreView = reinterpret_cast<ABI::Windows::ApplicationModel::Core::ICoreApplicationView*>(application);
		m_applicationCoreView = reinterpret_cast<ABI::Windows::ApplicationModel::Core::CoreApplicationView*>(application);
		m_applicationCoreExit = reinterpret_cast<ABI::Windows::ApplicationModel::Core::ICoreApplicationExit*>(application);
		m_coreWindow = reinterpret_cast<ABI::Windows::UI::Core::ICoreWindow*>(application);
		m_IFrameworkView = reinterpret_cast<ABI::Windows::ApplicationModel::Core::IFrameworkView*>(application);
		m_IFrameworkViewSource = reinterpret_cast<ABI::Windows::ApplicationModel::Core::IFrameworkViewSource*>(application);
	}

	CoreApplicationWrapperX(ComPtr<IActivationFactory> realFactory)
		: m_realFactory(realFactory)
	{}
public:
	HRESULT ActivateInstance(IInspectable** instance) override;
	HRESULT GetIids(ULONG* iidCount, IID** iids) override;
	HRESULT GetRuntimeClassName(HSTRING* className) override;
	HRESULT GetTrustLevel(TrustLevel* trustLevel) override;
	INT32 _abi_add_Resuming(__FIEventHandler_1_IInspectable* handler, EventRegistrationToken* token) override;
	INT32 _abi_remove_Resuming(EventRegistrationToken token) override;
	INT32 _abi_add_Suspending(__FIEventHandler_1_Windows__CApplicationModel__CSuspendingEventArgs* handler, EventRegistrationToken* token) override;
	INT32 _abi_remove_Suspending(EventRegistrationToken token) override;
	HRESULT _abi_get_ResourceAvailability(ResourceAvailability* resourceAvailability) override;
	INT32 _abi_get_ResourceAvailability() override;
	HRESULT _abi_add_ResourceAvailabilityChanged(winrt::Windows::Foundation::EventHandler<IInspectable>* handler, EventRegistrationToken* token) override;
	HRESULT _abi_remove_ResourceAvailabilityChanged(EventRegistrationToken token) override;
	INT32 _abi_get_CoreWindow(ABI::Windows::UI::Core::ICoreWindow**) override;
	INT32 _abi_add_Activated(__FITypedEventHandler_2_Windows__CApplicationModel__CCore__CCoreApplicationView_Windows__CApplicationModel__CActivation__CIActivatedEventArgs* handler, EventRegistrationToken* token) override;
	INT32 _abi_remove_Activated(EventRegistrationToken token) override;
	INT32 _abi_Exit() override;
	INT32 _abi_add_Exiting(__FIEventHandler_1_IInspectable* handler, EventRegistrationToken* token) override;
	INT32 _abi_remove_Exiting(EventRegistrationToken token) override;
	INT32 _abi_RunWithActivationFactories(ABI::Windows::Foundation::IGetActivationFactory* activationFactoryCallback) override;
	INT32 _abi_GetCurrentView(ABI::Windows::ApplicationModel::Core::ICoreApplicationView** value) override;
	INT32 _abi_Run(ABI::Windows::ApplicationModel::Core::IFrameworkViewSource* viewSource) override;
	INT32 Run(ABI::Windows::ApplicationModel::Core::IFrameworkViewSource* viewSource) override;
	INT32 _abi_get_Id(HSTRING* value) override;
	INT32 _abi_get_Properties(ABI::Windows::Foundation::Collections::IPropertySet** value) override;
	INT32 _abi_Initialize(ABI::Windows::ApplicationModel::Core::ICoreApplicationView* application) override;
	INT32 _abi_SetWindow(ICoreWindow* window) override;
	INT32 _abi_Load(HSTRING string) override;
	INT32 __abi_Run() override;
	INT32 _abi_Uninitialize() override;
	INT32 _abi_CreateView(ABI::Windows::ApplicationModel::Core::IFrameworkView** view) override;

	HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
	ULONG AddRef() override;
	ULONG Release() override;

private:
	long m_refCount = 1;
	ComPtr<IActivationFactory> m_realFactory;

	winrt::Windows::ApplicationModel::Core::CoreApplication* m_applicationCore;
	ABI::Windows::ApplicationModel::Core::ICoreApplication* m_IapplicationCore;
	ABI::Windows::ApplicationModel::Core::ICoreApplicationView* m_IapplicationCoreView;
	ABI::Windows::ApplicationModel::Core::CoreApplicationView* m_applicationCoreView;
	ABI::Windows::ApplicationModel::Core::ICoreApplicationExit* m_applicationCoreExit;
	ABI::Windows::UI::Core::ICoreWindow* m_coreWindow;
	ABI::Windows::ApplicationModel::Core::IFrameworkView* m_IFrameworkView;
	ABI::Windows::ApplicationModel::Core::IFrameworkViewSource* m_IFrameworkViewSource;

};