#pragma once
#include "ICoreApplicationResourceAvailabilityX.h"

class CoreApplicationResourceAvailabilityX : public ICoreApplicationResourceAvailabilityX
{
public:
	virtual INT32 _abi_get_ResourceAvailability(ResourceAvailability* resourceAvailability) override;
	virtual INT32 _abi_add_ResourceAvailabilityChanged(__FIEventHandler_1_IInspectable* handler, EventRegistrationToken* token) override;
	virtual INT32 _abi_remove_ResourceAvailabilityChanged(EventRegistrationToken token) override;
};