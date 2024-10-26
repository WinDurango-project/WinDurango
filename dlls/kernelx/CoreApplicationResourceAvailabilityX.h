#pragma once
#include "ICoreApplicationResourceAvailabilityX.h"

class CoreApplicationResourceAvailabilityX : public ICoreApplicationResourceAvailabilityX
{
public:
	virtual HRESULT _abi_get_ResourceAvailability(ResourceAvailability* resourceAvailability) override;
	virtual HRESULT _abi_add_ResourceAvailabilityChanged(__FIEventHandler_1_IInspectable* handler, EventRegistrationToken* token) override;
	virtual HRESULT _abi_remove_ResourceAvailabilityChanged(EventRegistrationToken token) override;
};