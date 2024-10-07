// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClassCanBeFinal
#pragma once
#include "ICoreWindowX.h"

#include <windows.ui.core.h>

class CoreWindowX : public ICoreWindowX
{
	Microsoft::WRL::ComPtr<ICoreWindow> m_coreWindow;

public:
	HRESULT GetIids(ULONG* iidCount, IID** iids) override;
	HRESULT GetRuntimeClassName(HSTRING* className) override;
	HRESULT GetTrustLevel(TrustLevel* trustLevel) override;
	void Activate() override;
	void Close() override;
	CoreVirtualKeyStates GetAsyncKeyState(VirtualKey key) override;
	CoreVirtualKeyStates GetKeyState(VirtualKey key) override;
	int32_t get_Bounds(Rect* rect) override;
	int32_t get_Dispatcher(CoreDispatcher** dispatcher) override;
	int32_t get_IsInputEnabled(boolean* value) override;
	int32_t set_IsInputEnabled(boolean value) override;
	int32_t get_Visible(boolean* value) override;
	int32_t _abi_Activate() override;
	int32_t _abi_Close() override;
	int32_t get_AsyncKeyState(VirtualKey key, CoreVirtualKeyStates* value) override;
	int32_t get_KeyState(VirtualKey key, CoreVirtualKeyStates* value) override;
	int32_t add_Activated(ITypedEventHandler<CoreWindow*, WindowActivatedEventArgs*>* handler,
		EventRegistrationToken* token) override;
	int32_t remove_Activated(EventRegistrationToken token) override;
	int32_t add_CharacterRecieved(ITypedEventHandler<CoreWindow*, CharacterReceivedEventArgs*>* handler,
		EventRegistrationToken* token) override;
	int32_t remove_CharacterRecieved(EventRegistrationToken token) override;
	int32_t add_Closed(ITypedEventHandler<CoreWindow*, CoreWindowEventArgs*>* handler,
		EventRegistrationToken* token) override;
	int32_t remove_Closed(EventRegistrationToken token) override;
	int32_t add_InputEnabled(ITypedEventHandler<CoreWindow*, InputEnabledEventArgs*>* handler,
		EventRegistrationToken* token) override;
	int32_t remove_InputEnabled(EventRegistrationToken token) override;
	int32_t add_KeyDown(ITypedEventHandler<CoreWindow*, KeyEventArgs*>* handler,
		EventRegistrationToken* token) override;
	int32_t remove_KeyDown(EventRegistrationToken token) override;
	int32_t add_KeyUp(ITypedEventHandler<CoreWindow*, KeyEventArgs*>* handler, EventRegistrationToken* token) override;
	int32_t remove_KeyUp(EventRegistrationToken token) override;
	int32_t add_PointerMoved(ITypedEventHandler<CoreWindow*, PointerEventArgs*>* handler,
		EventRegistrationToken* token) override;
	int32_t remove_PointerMoved(EventRegistrationToken token) override;
	int32_t add_PointerEntered(ITypedEventHandler<CoreWindow*, PointerEventArgs*>* handler,
		EventRegistrationToken* token) override;
	int32_t remove_PointerEntered(EventRegistrationToken token) override;
	int32_t add_PointerExited(ITypedEventHandler<CoreWindow*, PointerEventArgs*>* handler,
		EventRegistrationToken* token) override;
	int32_t remove_PointerExited(EventRegistrationToken token) override;
	int32_t add_SizeChanged(ITypedEventHandler<CoreWindow*, WindowSizeChangedEventArgs*>* handler,
		EventRegistrationToken* token) override;
	int32_t remove_SizeChanged(EventRegistrationToken token) override;
	int32_t add_VisibilityChanged(ITypedEventHandler<CoreWindow*, VisibilityChangedEventArgs*>* handler,
		EventRegistrationToken* token) override;
	int32_t remove_VisibilityChanged(EventRegistrationToken token) override;
	HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
	ULONG AddRef() override;
	ULONG Release() override;
};