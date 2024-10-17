#include "pch.h"
#include "CoreApplicationResourceAvailabilityX.h"

INT32 CoreApplicationResourceAvailabilityX::_abi_get_ResourceAvailability(ResourceAvailability* resourceAvailability)
{
	*resourceAvailability = Full;

	return S_OK;
}

INT32 CoreApplicationResourceAvailabilityX::_abi_add_ResourceAvailabilityChanged(__FIEventHandler_1_IInspectable* handler, EventRegistrationToken* token)
{
	return S_OK;
}

INT32 CoreApplicationResourceAvailabilityX::_abi_remove_ResourceAvailabilityChanged(EventRegistrationToken token)
{
	return S_OK;
}