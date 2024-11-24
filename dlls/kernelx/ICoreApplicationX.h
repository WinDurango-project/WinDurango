#pragma once
#include <winrt/Windows.ApplicationModel.h>
#include <windows.ui.core.h>

#include "ICoreApplicationResourceAvailabilityX.h"

using namespace ABI::Windows::ApplicationModel;
using namespace ABI::Windows::ApplicationModel::Activation;
using namespace ABI::Windows::ApplicationModel::Core;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::System;

MIDL_INTERFACE("0aacf7a4-5e1d-49df-8034-fb6a68bc5ed1")
ICoreApplicationX : public IInspectable
{
public:
	virtual HRESULT QueryInterface(const IID & riid, void** ppvObject) override = 0;
	virtual ULONG AddRef() override = 0;
	virtual ULONG Release() override = 0;


	virtual INT32 _abi_get_Id(HSTRING* value) = 0;
	virtual INT32 _abi_add_Suspending(__FIEventHandler_1_Windows__CApplicationModel__CSuspendingEventArgs* handler, EventRegistrationToken* token) = 0;
	virtual INT32 _abi_remove_Suspending(EventRegistrationToken token) = 0;
	virtual INT32 _abi_add_Resuming(__FIEventHandler_1_IInspectable* handler, EventRegistrationToken* token) = 0;
	virtual INT32 _abi_remove_Resuming(EventRegistrationToken token) = 0;
	virtual INT32 _abi_get_Properties(ABI::Windows::Foundation::Collections::IPropertySet** value) = 0;
	virtual INT32 _abi_GetCurrentView(ABI::Windows::ApplicationModel::Core::ICoreApplicationView** value) = 0;
	virtual INT32 _abi_Run(ABI::Windows::ApplicationModel::Core::IFrameworkViewSource* viewSource) = 0;
	//virtual INT32 _abi_RunWithActivationFactories(ABI::Windows::Foundation::IGetActivationFactory* activationFactoryCallback) = 0;

};