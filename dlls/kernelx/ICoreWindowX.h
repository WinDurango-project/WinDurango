#pragma once
#include <windows.foundation.h>
#include <windows.ui.core.h>
#include <windows.system.h>
#include <wrl.h>

using namespace Microsoft::WRL;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Core;
using namespace ABI::Windows::System;

MIDL_INTERFACE("79b9d5f2-879e-4b89-b798-79e47598030c")
ICoreWindowX : public IInspectable
{
public:
	virtual HRESULT QueryInterface(const IID & riid, void** ppvObject) override = 0;
	virtual ULONG AddRef() override = 0;
	virtual ULONG Release() override = 0;

	virtual INT32 _abi_get_Bounds(Rect* rect) = 0;
	virtual INT32 _abi_get_Dispatcher(ICoreDispatcher** dispatcher) = 0;
	virtual INT32 _abi_get_IsInputEnabled(boolean* value) = 0;
	virtual INT32 _abi_set_IsInputEnabled(boolean value) = 0;
	virtual INT32 _abi_get_Visible(boolean* value) = 0;
	virtual INT32 _abi_Activate() = 0;
	virtual INT32 _abi_Close() = 0;
	virtual INT32 _abi_get_AsyncKeyState(VirtualKey key, CoreVirtualKeyStates* value) = 0;
	virtual INT32 _abi_get_KeyState(VirtualKey key, CoreVirtualKeyStates* value) = 0;
	virtual INT32 _abi_add_Activated(ITypedEventHandler<CoreWindow*, WindowActivatedEventArgs*>* handler, EventRegistrationToken* token) = 0;
	virtual INT32 _abi_remove_Activated(EventRegistrationToken token) = 0;
	virtual INT32 _abi_add_CharacterReceived(ITypedEventHandler<CoreWindow*, CharacterReceivedEventArgs*>* handler, EventRegistrationToken* token) = 0;
	virtual INT32 _abi_remove_CharacterReceived(EventRegistrationToken token) = 0;
	virtual INT32 _abi_add_Closed(ITypedEventHandler<CoreWindow*, CoreWindowEventArgs*>* handler, EventRegistrationToken* token) = 0;
	virtual INT32 _abi_remove_Closed(EventRegistrationToken token) = 0;
	virtual INT32 _abi_add_InputEnabled(ITypedEventHandler<CoreWindow*, InputEnabledEventArgs*>* handler, EventRegistrationToken* token) = 0;
	virtual INT32 _abi_remove_InputEnabled(EventRegistrationToken token) = 0;
	virtual INT32 _abi_add_KeyDown(ITypedEventHandler<CoreWindow*, KeyEventArgs*>* handler, EventRegistrationToken* token) = 0;
	virtual INT32 _abi_remove_KeyDown(EventRegistrationToken token) = 0;
	virtual INT32 _abi_add_KeyUp(ITypedEventHandler<CoreWindow*, KeyEventArgs*>* handler, EventRegistrationToken* token) = 0;
	virtual INT32 _abi_remove_KeyUp(EventRegistrationToken token) = 0;
	virtual INT32 _abi_add_PointerMoved(ITypedEventHandler<CoreWindow*, PointerEventArgs*>* handler, EventRegistrationToken* token) = 0;
	virtual INT32 _abi_remove_PointerMoved(EventRegistrationToken token) = 0;
	virtual INT32 _abi_add_PointerEntered(ITypedEventHandler<CoreWindow*, PointerEventArgs*>* handler, EventRegistrationToken* token) = 0;
	virtual INT32 _abi_remove_PointerEntered(EventRegistrationToken token) = 0;
	virtual INT32 _abi_add_PointerExited(ITypedEventHandler<CoreWindow*, PointerEventArgs*>* handler, EventRegistrationToken* token) = 0;
	virtual INT32 _abi_remove_PointerExited(EventRegistrationToken token) = 0;
	virtual INT32 _abi_add_SizeChanged(ITypedEventHandler<CoreWindow*, WindowSizeChangedEventArgs*>* handler, EventRegistrationToken* token) = 0;
	virtual INT32 _abi_remove_SizeChanged(EventRegistrationToken token) = 0;
	virtual INT32 _abi_add_VisibilityChanged(ITypedEventHandler<CoreWindow*, VisibilityChangedEventArgs*>* handler, EventRegistrationToken* token) = 0;
	virtual INT32 _abi_remove_VisibilityChanged(EventRegistrationToken token) = 0;
};