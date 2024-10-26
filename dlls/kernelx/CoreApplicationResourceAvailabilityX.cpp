#include "pch.h"
#include "CoreApplicationResourceAvailabilityX.h"

HRESULT CoreApplicationResourceAvailabilityX::_abi_get_ResourceAvailability(ResourceAvailability* resourceAvailability)
{
	*resourceAvailability = ResourceAvailability_Full;

	return S_OK;
}

HRESULT CoreApplicationResourceAvailabilityX::_abi_add_ResourceAvailabilityChanged(__FIEventHandler_1_IInspectable* handler, EventRegistrationToken* token)
{
	return S_OK;
}

HRESULT CoreApplicationResourceAvailabilityX::_abi_remove_ResourceAvailabilityChanged(EventRegistrationToken token)
{
	return S_OK;
}