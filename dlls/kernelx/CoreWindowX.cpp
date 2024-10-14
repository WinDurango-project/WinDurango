#include "pch.h"
#include "CoreWindowX.h"

HRESULT CoreWindowX::GetIids(ULONG* iidCount, IID** iids)
{
	return m_coreWindow->GetIids(iidCount, iids);
}

HRESULT CoreWindowX::GetRuntimeClassName(HSTRING* className)
{
	return m_coreWindow->GetRuntimeClassName(className);
}

HRESULT CoreWindowX::GetTrustLevel(TrustLevel* trustLevel)
{
	return m_coreWindow->GetTrustLevel(trustLevel);
}

INT32 CoreWindowX::_abi_get_Bounds(Rect* rect)
{
	return m_coreWindow->get_Bounds(rect);
}

INT32 CoreWindowX::_abi_get_Dispatcher(ICoreDispatcher** dispatcher)
{
	return m_coreWindow->get_Dispatcher(dispatcher);
}

INT32 CoreWindowX::_abi_get_IsInputEnabled(boolean* value)
{
	return m_coreWindow->get_IsInputEnabled(value);
}

INT32 CoreWindowX::_abi_set_IsInputEnabled(boolean value)
{
	return m_coreWindow->put_IsInputEnabled(value);
}

INT32 CoreWindowX::_abi_get_Visible(boolean* value)
{
	return m_coreWindow->get_Visible(value);
}

INT32 CoreWindowX::_abi_Activate()
{
	return m_coreWindow->Activate();
}

INT32 CoreWindowX::_abi_Close()
{
	return m_coreWindow->Close();
}

INT32 CoreWindowX::_abi_get_AsyncKeyState(VirtualKey key, CoreVirtualKeyStates* value)
{
	return m_coreWindow->GetAsyncKeyState(key, value);
}

INT32 CoreWindowX::_abi_get_KeyState(VirtualKey key, CoreVirtualKeyStates* value)
{
	return m_coreWindow->GetKeyState(key, value);
}

INT32 CoreWindowX::_abi_add_Activated(ITypedEventHandler<CoreWindow*, WindowActivatedEventArgs*>* handler,
	EventRegistrationToken* token)
{
	return m_coreWindow->add_Activated(handler, token);
}

INT32 CoreWindowX::_abi_remove_Activated(EventRegistrationToken token)
{
	return m_coreWindow->remove_Activated(token);
}

INT32 CoreWindowX::_abi_add_CharacterReceived(ITypedEventHandler<CoreWindow*, CharacterReceivedEventArgs*>* handler,
	EventRegistrationToken* token)
{
	return m_coreWindow->add_CharacterReceived(handler, token);
}

INT32 CoreWindowX::_abi_remove_CharacterReceived(EventRegistrationToken token)
{
	return m_coreWindow->remove_CharacterReceived(token);
}

INT32 CoreWindowX::_abi_add_Closed(ITypedEventHandler<CoreWindow*, CoreWindowEventArgs*>* handler,
	EventRegistrationToken* token)
{
	return m_coreWindow->add_Closed(handler, token);
}

INT32 CoreWindowX::_abi_remove_Closed(EventRegistrationToken token)
{
	return m_coreWindow->remove_Closed(token);
}

INT32 CoreWindowX::_abi_add_InputEnabled(ITypedEventHandler<CoreWindow*, InputEnabledEventArgs*>* handler,
	EventRegistrationToken* token)
{
	return m_coreWindow->add_InputEnabled(handler, token);
}

INT32 CoreWindowX::_abi_remove_InputEnabled(EventRegistrationToken token)
{
	return m_coreWindow->remove_InputEnabled(token);
}

INT32 CoreWindowX::_abi_add_KeyDown(ITypedEventHandler<CoreWindow*, KeyEventArgs*>* handler,
	EventRegistrationToken* token)
{
	return m_coreWindow->add_KeyDown(handler, token);
}

INT32 CoreWindowX::_abi_remove_KeyDown(EventRegistrationToken token)
{
	return m_coreWindow->remove_KeyDown(token);
}

INT32 CoreWindowX::_abi_add_KeyUp(ITypedEventHandler<CoreWindow*, KeyEventArgs*>* handler,
	EventRegistrationToken* token)
{
	return m_coreWindow->add_KeyUp(handler, token);
}

INT32 CoreWindowX::_abi_remove_KeyUp(EventRegistrationToken token)
{
	return m_coreWindow->remove_KeyUp(token);
}

INT32 CoreWindowX::_abi_add_PointerMoved(ITypedEventHandler<CoreWindow*, PointerEventArgs*>* handler,
	EventRegistrationToken* token)
{
	return m_coreWindow->add_PointerMoved(handler, token);
}

INT32 CoreWindowX::_abi_remove_PointerMoved(EventRegistrationToken token)
{
	return m_coreWindow->remove_PointerMoved(token);
}

INT32 CoreWindowX::_abi_add_PointerEntered(ITypedEventHandler<CoreWindow*, PointerEventArgs*>* handler,
	EventRegistrationToken* token)
{
	return m_coreWindow->add_PointerEntered(handler, token);
}

INT32 CoreWindowX::_abi_remove_PointerEntered(EventRegistrationToken token)
{
	return m_coreWindow->remove_PointerEntered(token);
}

INT32 CoreWindowX::_abi_add_PointerExited(ITypedEventHandler<CoreWindow*, PointerEventArgs*>* handler,
	EventRegistrationToken* token)
{
	return m_coreWindow->add_PointerExited(handler, token);
}

INT32 CoreWindowX::_abi_remove_PointerExited(EventRegistrationToken token)
{
	return m_coreWindow->remove_PointerExited(token);
}

INT32 CoreWindowX::_abi_add_SizeChanged(ITypedEventHandler<CoreWindow*, WindowSizeChangedEventArgs*>* handler,
	EventRegistrationToken* token)
{
	return m_coreWindow->add_SizeChanged(handler, token);
}

INT32 CoreWindowX::_abi_remove_SizeChanged(EventRegistrationToken token)
{
	return m_coreWindow->remove_SizeChanged(token);
}

INT32 CoreWindowX::_abi_add_VisibilityChanged(ITypedEventHandler<CoreWindow*, VisibilityChangedEventArgs*>* handler,
	EventRegistrationToken* token)
{
	return m_coreWindow->add_VisibilityChanged(handler, token);
}

INT32 CoreWindowX::_abi_remove_VisibilityChanged(EventRegistrationToken token)
{
	return m_coreWindow->remove_VisibilityChanged(token);
}

HRESULT CoreWindowX::QueryInterface(const IID& riid, void** ppvObject)
{
	return m_coreWindow->QueryInterface(riid, ppvObject);
}

ULONG CoreWindowX::AddRef()
{
	return m_coreWindow->AddRef();
}

ULONG CoreWindowX::Release()
{
	return m_coreWindow->Release();
}