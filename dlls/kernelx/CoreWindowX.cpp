// ReSharper disable CppInconsistentNaming
// ReSharper disable CppFunctionResultShouldBeUsed
// ReSharper disable CppParameterMayBeConst
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

void CoreWindowX::Activate()
{
	m_coreWindow->Activate();
}

void CoreWindowX::Close()
{
	m_coreWindow->Close();
}

CoreVirtualKeyStates CoreWindowX::GetAsyncKeyState(VirtualKey key)
{
	//return ICoreWindowX::GetAsyncKeyState(key);

	return CoreVirtualKeyStates_None;
}

CoreVirtualKeyStates CoreWindowX::GetKeyState(VirtualKey key)
{
	//return ICoreWindowX::GetKeyState(key);

	return CoreVirtualKeyStates_None;
}

int32_t CoreWindowX::get_Bounds(Rect* rect)
{
	return m_coreWindow->get_Bounds(rect);
}

int32_t CoreWindowX::get_Dispatcher(CoreDispatcher** dispatcher)
{
	//return ICoreWindowX::get_Dispatcher(dispatcher);
	return 0;
}

int32_t CoreWindowX::get_IsInputEnabled(boolean* value)
{
	return m_coreWindow->get_IsInputEnabled(value);
}

int32_t CoreWindowX::set_IsInputEnabled(boolean value)
{
	//return ICoreWindowX::set_IsInputEnabled(value);

	return 0;
}

int32_t CoreWindowX::get_Visible(boolean* value)
{
	return m_coreWindow->get_Visible(value);
}

int32_t CoreWindowX::_abi_Activate()
{
	return m_coreWindow->Activate();
}

int32_t CoreWindowX::_abi_Close()
{
	return m_coreWindow->Close();
}

int32_t CoreWindowX::get_AsyncKeyState(VirtualKey key, CoreVirtualKeyStates* value)
{
	return m_coreWindow->GetAsyncKeyState(key, value);
}

int32_t CoreWindowX::get_KeyState(VirtualKey key, CoreVirtualKeyStates* value)
{
	return m_coreWindow->GetKeyState(key, value);
}

int32_t CoreWindowX::add_Activated(ITypedEventHandler<CoreWindow*, WindowActivatedEventArgs*>* handler,
	EventRegistrationToken* token)
{
	return m_coreWindow->add_Activated(handler, token);
}

int32_t CoreWindowX::remove_Activated(EventRegistrationToken token)
{
	return m_coreWindow->remove_Activated(token);
}

int32_t CoreWindowX::add_CharacterRecieved(ITypedEventHandler<CoreWindow*, CharacterReceivedEventArgs*>* handler,
	EventRegistrationToken* token)
{
	return m_coreWindow->add_CharacterReceived(handler, token);
}

int32_t CoreWindowX::remove_CharacterRecieved(EventRegistrationToken token)
{
	return m_coreWindow->remove_CharacterReceived(token);
}

int32_t CoreWindowX::add_Closed(ITypedEventHandler<CoreWindow*, CoreWindowEventArgs*>* handler,
	EventRegistrationToken* token)
{
	return m_coreWindow->add_Closed(handler, token);
}

int32_t CoreWindowX::remove_Closed(EventRegistrationToken token)
{
	return m_coreWindow->remove_Closed(token);
}

int32_t CoreWindowX::add_InputEnabled(ITypedEventHandler<CoreWindow*, InputEnabledEventArgs*>* handler,
	EventRegistrationToken* token)
{
	return m_coreWindow->add_InputEnabled(handler, token);
}

int32_t CoreWindowX::remove_InputEnabled(EventRegistrationToken token)
{
	return m_coreWindow->remove_InputEnabled(token);
}

int32_t CoreWindowX::add_KeyDown(ITypedEventHandler<CoreWindow*, KeyEventArgs*>* handler, EventRegistrationToken* token)
{
	return m_coreWindow->add_KeyDown(handler, token);
}

int32_t CoreWindowX::remove_KeyDown(EventRegistrationToken token)
{
	return m_coreWindow->remove_KeyDown(token);
}

int32_t CoreWindowX::add_KeyUp(ITypedEventHandler<CoreWindow*, KeyEventArgs*>* handler, EventRegistrationToken* token)
{
	return m_coreWindow->add_KeyUp(handler, token);
}

int32_t CoreWindowX::remove_KeyUp(EventRegistrationToken token)
{
	return m_coreWindow->remove_KeyUp(token);
}

int32_t CoreWindowX::add_PointerMoved(ITypedEventHandler<CoreWindow*, PointerEventArgs*>* handler,
	EventRegistrationToken* token)
{
	return m_coreWindow->add_PointerMoved(handler, token);
}

int32_t CoreWindowX::remove_PointerMoved(EventRegistrationToken token)
{
	return m_coreWindow->remove_PointerMoved(token);
}

int32_t CoreWindowX::add_PointerEntered(ITypedEventHandler<CoreWindow*, PointerEventArgs*>* handler,
	EventRegistrationToken* token)
{
	return m_coreWindow->add_PointerEntered(handler, token);
}

int32_t CoreWindowX::remove_PointerEntered(EventRegistrationToken token)
{
	return m_coreWindow->remove_PointerCaptureLost(token);
}

int32_t CoreWindowX::add_PointerExited(ITypedEventHandler<CoreWindow*, PointerEventArgs*>* handler,
	EventRegistrationToken* token)
{
	return m_coreWindow->add_PointerExited(handler, token);
}

int32_t CoreWindowX::remove_PointerExited(EventRegistrationToken token)
{
	return m_coreWindow->remove_PointerExited(token);
}

int32_t CoreWindowX::add_SizeChanged(ITypedEventHandler<CoreWindow*, WindowSizeChangedEventArgs*>* handler,
	EventRegistrationToken* token)
{
	return m_coreWindow->add_SizeChanged(handler, token);
}

int32_t CoreWindowX::remove_SizeChanged(EventRegistrationToken token)
{
	return m_coreWindow->remove_SizeChanged(token);
}

int32_t CoreWindowX::add_VisibilityChanged(ITypedEventHandler<CoreWindow*, VisibilityChangedEventArgs*>* handler,
	EventRegistrationToken* token)
{
	return m_coreWindow->add_VisibilityChanged(handler, token);
}

int32_t CoreWindowX::remove_VisibilityChanged(EventRegistrationToken token)
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