// ReSharper disable CppInconsistentNaming
#include "pch.h"

#include <string>
#include <WinString.h>

#include "Windows.Xbox/Windows.Xbox.Achievement.AchievementNotifier.h"

HRESULT GetActivationFactory_X(HSTRING classId, IActivationFactory** factory)
{
	const std::wstring classIdStr = WindowsGetStringRawBuffer(classId, nullptr);

	if (wcscmp(classIdStr.c_str(), L"Windows.Xbox.Achievement.AchievementNotifier") == 0)
	{
		Windows::Xbox::Achievements::IXboxAchievementNotifier* pXboxAchievementNotifier = nullptr;


		HSTRING hStrRuntimeClass = nullptr;
		HSTRING_HEADER hStrHeader = { nullptr };


		// TODO: Not sure if we need this.
		auto hr = RoInitialize(RO_INIT_SINGLETHREADED);

		if (hr != S_OK())
			return hr;

		hr = WindowsCreateStringReference(
			Windows::Xbox::Achievements::RuntimeClass_XboxAchievementNotifier, 
			static_cast<UINT32>(wcslen(Windows::Xbox::Achievements::RuntimeClass_XboxAchievementNotifier)), 
			&hStrHeader, 
			&hStrRuntimeClass);

		if (hr != S_OK())
			return hr;

		hr = RoGetActivationFactory(hStrRuntimeClass, Windows::Xbox::Achievements::IID_IXboxAchievementNotifier, reinterpret_cast<void**>(&pXboxAchievementNotifier));
	}

	return S_OK;
}
