// ReSharper disable CppPolymorphicClassWithNonVirtualPublicDestructor
// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyClangDiagnosticNonVirtualDtor
// ReSharper disable IdentifierTypo
// ReSharper disable CppClangTidyClangDiagnosticHeaderHygiene
#include <winrt/windows.foundation.collections.h>
#include <winrt/Windows.ApplicationModel.h>
#include <windows.ui.core.h>


using namespace ABI::Windows::ApplicationModel::Activation;
using namespace ABI::Windows::ApplicationModel;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::ApplicationModel::Core;
using namespace ABI::Windows::System;

class ICoreApplicationX : public IInspectable
{
public:
	virtual INT32 _abi_add_Resuming(__FIEventHandler_1_IInspectable* handler, EventRegistrationToken* token) = 0;
	virtual INT32 _abi_remove_Resuming(EventRegistrationToken token) = 0;
	virtual INT32 _abi_add_Suspending(__FIEventHandler_1_Windows__CApplicationModel__CSuspendingEventArgs* handler, EventRegistrationToken* token) = 0;
	virtual INT32 _abi_remove_Suspending(EventRegistrationToken token) = 0;
	//virtual INT32 _abi_get_ResourceAvailability(Windows::ApplicationModel::Core::ResourceAvailability*) = 0;
	virtual INT32 _abi_get_ResourceAvailability() = 0;
	virtual INT32 _abi_add_ResourceAvailabilityChanged(winrt::Windows::Foundation::EventHandler<IInspectable>* handler, EventRegistrationToken* token) = 0;
	virtual INT32 _abi_remove_ResourceAvailabilityChanged(EventRegistrationToken token) = 0;
	virtual INT32 _abi_get_CoreWindow(ABI::Windows::UI::Core::ICoreWindow**) = 0;
	virtual INT32 _abi_add_Activated(__FITypedEventHandler_2_Windows__CApplicationModel__CCore__CCoreApplicationView_Windows__CApplicationModel__CActivation__CIActivatedEventArgs* handler, EventRegistrationToken* token) = 0;
	virtual INT32 _abi_remove_Activated(EventRegistrationToken token) = 0;
	virtual INT32 _abi_Exit() = 0;
	virtual INT32 _abi_add_Exiting(__FIEventHandler_1_IInspectable* handler, EventRegistrationToken* token) = 0;
	virtual INT32 _abi_remove_Exiting(EventRegistrationToken token) = 0;
	virtual INT32 _abi_RunWithActivationFactories(ABI::Windows::Foundation::IGetActivationFactory* activationFactoryCallback) = 0;
	virtual INT32 _abi_GetCurrentView(ABI::Windows::ApplicationModel::Core::ICoreApplicationView** value) = 0;
	virtual INT32 _abi_Run(ABI::Windows::ApplicationModel::Core::IFrameworkViewSource* viewSource) = 0;
	virtual INT32 Run(ABI::Windows::ApplicationModel::Core::IFrameworkViewSource* viewSource) = 0;
	virtual INT32 _abi_get_Id(HSTRING* value) = 0;
	virtual INT32 _abi_get_Properties(ABI::Windows::Foundation::Collections::IPropertySet** value) = 0;

	virtual HRESULT QueryInterface(const IID& riid, void** ppvObject) override = 0;
	virtual ULONG AddRef() override = 0;
	virtual ULONG Release() override = 0;

};