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
	virtual ~ICoreWindowX() = default;
	virtual void Activate();
	virtual void Close();

	virtual CoreVirtualKeyStates GetAsyncKeyState(VirtualKey key);
	virtual CoreVirtualKeyStates GetKeyState(VirtualKey key);

	virtual int32_t get_Bounds(Rect* rect);
	virtual int32_t get_Dispatcher(CoreDispatcher** dispatcher);
	virtual int32_t get_IsInputEnabled(boolean* value);
	virtual int32_t set_IsInputEnabled(boolean value);
	virtual int32_t get_Visible(boolean* value);
	virtual int32_t _abi_Activate();
	virtual int32_t _abi_Close();
	virtual int32_t get_AsyncKeyState(VirtualKey key, CoreVirtualKeyStates* value);
	virtual int32_t get_KeyState(VirtualKey key, CoreVirtualKeyStates* value);
	virtual int32_t add_Activated(ITypedEventHandler<CoreWindow*, WindowActivatedEventArgs*>* handler, EventRegistrationToken* token);
	virtual int32_t remove_Activated(EventRegistrationToken token);
	virtual int32_t add_CharacterRecieved(ITypedEventHandler<CoreWindow*, CharacterReceivedEventArgs*>* handler, EventRegistrationToken* token);
	virtual int32_t remove_CharacterRecieved(EventRegistrationToken token);
	virtual int32_t add_Closed(ITypedEventHandler<CoreWindow*, CoreWindowEventArgs*>* handler, EventRegistrationToken* token);
	virtual int32_t remove_Closed(EventRegistrationToken token);
	virtual int32_t add_InputEnabled(ITypedEventHandler<CoreWindow*, InputEnabledEventArgs*>* handler, EventRegistrationToken* token);
	virtual int32_t remove_InputEnabled(EventRegistrationToken token);
	virtual int32_t add_KeyDown(ITypedEventHandler<CoreWindow*, KeyEventArgs*>* handler, EventRegistrationToken* token);
	virtual int32_t remove_KeyDown(EventRegistrationToken token);
	virtual int32_t add_KeyUp(ITypedEventHandler<CoreWindow*, KeyEventArgs*>* handler, EventRegistrationToken* token);
	virtual int32_t remove_KeyUp(EventRegistrationToken token);
	virtual int32_t add_PointerMoved(ITypedEventHandler<CoreWindow*, PointerEventArgs*>* handler, EventRegistrationToken* token);
	virtual int32_t remove_PointerMoved(EventRegistrationToken token);
	virtual int32_t add_PointerEntered(ITypedEventHandler<CoreWindow*, PointerEventArgs*>* handler, EventRegistrationToken* token);
	virtual int32_t remove_PointerEntered(EventRegistrationToken token);
	virtual int32_t add_PointerExited(ITypedEventHandler<CoreWindow*, PointerEventArgs*>* handler, EventRegistrationToken* token);
	virtual int32_t remove_PointerExited(EventRegistrationToken token);
	virtual int32_t add_SizeChanged(ITypedEventHandler<CoreWindow*, WindowSizeChangedEventArgs*>* handler, EventRegistrationToken* token);
	virtual int32_t remove_SizeChanged(EventRegistrationToken token);
	virtual int32_t add_VisibilityChanged(ITypedEventHandler<CoreWindow*, VisibilityChangedEventArgs*>* handler, EventRegistrationToken* token);
	virtual int32_t remove_VisibilityChanged(EventRegistrationToken token);

public:
	HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
	ULONG AddRef() override;
	ULONG Release() override;
};