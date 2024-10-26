#include "pch.h"
#include "CoreApplicationX.h"

HRESULT CoreApplicationX::GetIids(ULONG* iidCount, IID** iids)
{
	return m_coreWindow->GetIids(iidCount, iids);
}

HRESULT CoreApplicationX::GetRuntimeClassName(HSTRING* className)
{
	return m_coreWindow->GetRuntimeClassName(className);
}

HRESULT CoreApplicationX::GetTrustLevel(TrustLevel* trustLevel)
{
	return m_coreWindow->GetTrustLevel(trustLevel);
}

INT32 CoreApplicationX::_abi_add_Resuming(__FIEventHandler_1_IInspectable* handler, EventRegistrationToken* token)
{
	return m_IapplicationCore->add_Resuming(handler, token);
}

INT32 CoreApplicationX::_abi_remove_Resuming(EventRegistrationToken token)
{
	return m_IapplicationCore->remove_Resuming(token);
}

INT32 CoreApplicationX::_abi_add_Suspending(__FIEventHandler_1_Windows__CApplicationModel__CSuspendingEventArgs* handler, EventRegistrationToken* token)
{
	return m_IapplicationCore->add_Suspending(handler, token);
}

INT32 CoreApplicationX::_abi_remove_Suspending(EventRegistrationToken token)
{
	return m_IapplicationCore->remove_Suspending(token);
}

INT32 CoreApplicationX::_abi_get_ResourceAvailability(ResourceAvailability* resourceAvailability)
{
	// TODO: Stubbed for now.
	*resourceAvailability = ResourceAvailability_Full;

	return S_OK;
}

INT32 CoreApplicationX::_abi_get_ResourceAvailability()
{
	return S_OK;
}

INT32 CoreApplicationX::_abi_add_ResourceAvailabilityChanged(winrt::Windows::Foundation::EventHandler<IInspectable>* handler, EventRegistrationToken* token)
{
	//Stubbed at this moment.
	return 0;
}

INT32 CoreApplicationX::_abi_remove_ResourceAvailabilityChanged(EventRegistrationToken token)
{
	//Stubbed at this moment.
	return 0;
}

INT32 CoreApplicationX::_abi_get_CoreWindow(ABI::Windows::UI::Core::ICoreWindow** Window)
{
	return m_IapplicationCoreView->get_CoreWindow(Window);
}

INT32 CoreApplicationX::_abi_add_Activated(__FITypedEventHandler_2_Windows__CApplicationModel__CCore__CCoreApplicationView_Windows__CApplicationModel__CActivation__CIActivatedEventArgs* handler, EventRegistrationToken* token)
{
	return m_IapplicationCoreView->add_Activated(handler, token);
}

INT32 CoreApplicationX::_abi_remove_Activated(EventRegistrationToken token)
{
	return m_IapplicationCoreView->remove_Activated(token);
}

INT32 CoreApplicationX::_abi_Exit()
{
	return m_applicationCoreExit->Exit();
}

INT32 CoreApplicationX::_abi_add_Exiting(__FIEventHandler_1_IInspectable* handler, EventRegistrationToken* token)
{
	return m_applicationCoreExit->add_Exiting(handler, token);
}

INT32 CoreApplicationX::_abi_remove_Exiting(EventRegistrationToken token)
{
	return m_applicationCoreExit->remove_Exiting(token);
}

INT32 CoreApplicationX::_abi_RunWithActivationFactories(ABI::Windows::Foundation::IGetActivationFactory* activationFactoryCallback)
{
	return m_IapplicationCore->RunWithActivationFactories(activationFactoryCallback);
}

INT32 CoreApplicationX::_abi_GetCurrentView(ABI::Windows::ApplicationModel::Core::ICoreApplicationView** value)
{
	return m_IapplicationCore->GetCurrentView(value);
}

INT32 CoreApplicationX::_abi_Run(ABI::Windows::ApplicationModel::Core::IFrameworkViewSource* viewSource)
{
	return m_IapplicationCore->Run(viewSource);
}

INT32 CoreApplicationX::Run(ABI::Windows::ApplicationModel::Core::IFrameworkViewSource* viewSource)
{
	return m_IapplicationCore->Run(viewSource);
}

INT32 CoreApplicationX::_abi_get_Id(HSTRING* value)
{
	return m_IapplicationCore->get_Id(value);
}

INT32 CoreApplicationX::_abi_get_Properties(ABI::Windows::Foundation::Collections::IPropertySet** value)
{
	return m_IapplicationCore->get_Properties(value);
}

INT32 CoreApplicationX::_abi_Initialize(ABI::Windows::ApplicationModel::Core::ICoreApplicationView* application)
{
	return m_IFrameworkView->Initialize(application);
}

INT32 CoreApplicationX::_abi_SetWindow(ICoreWindow* window)
{
	return m_IFrameworkView->SetWindow(window);
}

INT32 CoreApplicationX::_abi_Load(HSTRING string)
{
	return m_IFrameworkView->Load(string);
}

INT32 CoreApplicationX::__abi_Run()
{
	return m_IFrameworkView->Run();
}

INT32 CoreApplicationX::_abi_Uninitialize()
{
	return m_IFrameworkView->Uninitialize();
}

INT32 CoreApplicationX::_abi_CreateView(ABI::Windows::ApplicationModel::Core::IFrameworkView** view)
{
	return m_IFrameworkViewSource->CreateView(view);
}

HRESULT CoreApplicationX::QueryInterface(const IID& riid, void** ppvObject)
{
	return m_coreWindow->QueryInterface(riid, ppvObject);
}

ULONG CoreApplicationX::AddRef()
{
	return m_coreWindow->AddRef();
}

ULONG CoreApplicationX::Release()
{
	return m_coreWindow->Release();
}