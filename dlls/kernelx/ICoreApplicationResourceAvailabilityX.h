#pragma once
#include <winrt/Windows.ApplicationModel.h>
#include <windows.ui.core.h>

using namespace ABI::Windows::ApplicationModel;
using namespace ABI::Windows::ApplicationModel::Activation;
using namespace ABI::Windows::ApplicationModel::Core;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::System;

enum ResourceAvailability
{
	ResourceAvailability_Full,
	ResourceAvailability_Constrained,
	ResourceAvailability_FullWithExtendedSystemReserve,
};

MIDL_INTERFACE("9FF3799E-6E83-468C-A5B0-501CE6BB0FA1")
ICoreApplicationResourceAvailabilityX : public IInspectable
{
public:
	STDMETHOD(_abi_get_ResourceAvailability)(ResourceAvailability *) PURE;
	STDMETHOD(_abi_add_ResourceAvailabilityChanged)(winrt::Windows::Foundation::EventHandler<IInspectable>* handler, EventRegistrationToken* token) PURE;
	STDMETHOD(_abi_remove_ResourceAvailabilityChanged)(EventRegistrationToken) PURE;
};