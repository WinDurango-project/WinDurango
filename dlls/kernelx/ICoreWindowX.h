// ReSharper disable CppPolymorphicClassWithNonVirtualPublicDestructor
// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyClangDiagnosticNonVirtualDtor
// ReSharper disable IdentifierTypo
// ReSharper disable CppClangTidyClangDiagnosticHeaderHygiene
#pragma once
#include <inspectable.h>
#include <windows.foundation.h>
#include <windows.ui.core.h>
#include <windows.system.h>

using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Core;
using namespace ABI::Windows::System;

class ICoreWindowX : public IInspectable
{
public:
	virtual INT32 _abi_get_Bounds(Rect* rect);
	virtual INT32 _abi_get_Dispatcher(ICoreDispatcher** dispatcher);
	virtual INT32 _abi_get_IsInputEnabled(boolean* value);
	virtual INT32 _abi_set_IsInputEnabled(boolean value);
	virtual INT32 _abi_get_Visible(boolean* value);
	virtual INT32 _abi_Activate();
	virtual INT32 _abi_Close();
	virtual INT32 _abi_get_AsyncKeyState(VirtualKey key, CoreVirtualKeyStates* value);
	virtual INT32 _abi_get_KeyState(VirtualKey key, CoreVirtualKeyStates* value);
	virtual INT32 _abi_add_Activated(ITypedEventHandler<CoreWindow*, WindowActivatedEventArgs*>* handler, EventRegistrationToken* token);
	virtual INT32 _abi_remove_Activated(EventRegistrationToken token);
	virtual INT32 _abi_add_CharacterRecieved(ITypedEventHandler<CoreWindow*, CharacterReceivedEventArgs*>* handler, EventRegistrationToken* token);
	virtual INT32 _abi_remove_CharacterRecieved(EventRegistrationToken token);
	virtual INT32 _abi_add_Closed(ITypedEventHandler<CoreWindow*, CoreWindowEventArgs*>* handler, EventRegistrationToken* token);
	virtual INT32 _abi_remove_Closed(EventRegistrationToken token);
	virtual INT32 _abi_add_InputEnabled(ITypedEventHandler<CoreWindow*, InputEnabledEventArgs*>* handler, EventRegistrationToken* token);
	virtual INT32 _abi_remove_InputEnabled(EventRegistrationToken token);
	virtual INT32 _abi_add_KeyDown(ITypedEventHandler<CoreWindow*, KeyEventArgs*>* handler, EventRegistrationToken* token);
	virtual INT32 _abi_remove_KeyDown(EventRegistrationToken token);
	virtual INT32 _abi_add_KeyUp(ITypedEventHandler<CoreWindow*, KeyEventArgs*>* handler, EventRegistrationToken* token);
	virtual INT32 _abi_remove_KeyUp(EventRegistrationToken token);
	virtual INT32 _abi_add_PointerMoved(ITypedEventHandler<CoreWindow*, PointerEventArgs*>* handler, EventRegistrationToken* token);
	virtual INT32 _abi_remove_PointerMoved(EventRegistrationToken token);
	virtual INT32 _abi_add_PointerEntered(ITypedEventHandler<CoreWindow*, PointerEventArgs*>* handler, EventRegistrationToken* token);
	virtual INT32 _abi_remove_PointerEntered(EventRegistrationToken token);
	virtual INT32 _abi_add_PointerExited(ITypedEventHandler<CoreWindow*, PointerEventArgs*>* handler, EventRegistrationToken* token);
	virtual INT32 _abi_remove_PointerExited(EventRegistrationToken token);
	virtual INT32 _abi_add_SizeChanged(ITypedEventHandler<CoreWindow*, WindowSizeChangedEventArgs*>* handler, EventRegistrationToken* token);
	virtual INT32 _abi_remove_SizeChanged(EventRegistrationToken token);
	virtual INT32 _abi_add_VisibilityChanged(ITypedEventHandler<CoreWindow*, VisibilityChangedEventArgs*>* handler, EventRegistrationToken* token);
	virtual INT32 _abi_remove_VisibilityChanged(EventRegistrationToken token);

	HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
	ULONG AddRef() override;
	ULONG Release() override;
};