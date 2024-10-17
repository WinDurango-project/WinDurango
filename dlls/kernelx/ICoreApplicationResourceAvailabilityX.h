#pragma once
#include <winrt/Windows.ApplicationModel.h>
#include <windows.ui.core.h>

using namespace ABI::Windows::ApplicationModel;
using namespace ABI::Windows::ApplicationModel::Activation;
using namespace ABI::Windows::ApplicationModel::Core;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::System;

enum ResourceAvailability : INT32 {
	Full = 0x0000,
	Constrained = 0x0001,
	FullWithExtendedSystemReserve = 0x0002,
};

class ICoreApplicationResourceAvailabilityX : public IInspectable
{
public:
	virtual INT32 _abi_get_ResourceAvailability(ResourceAvailability* resourceAvailability) = 0;
	virtual INT32 _abi_add_ResourceAvailabilityChanged(__FIEventHandler_1_IInspectable* handler, EventRegistrationToken* token) = 0;
	virtual INT32 _abi_remove_ResourceAvailabilityChanged(EventRegistrationToken token) = 0;
};