// ReSharper disable CppClangTidyClangDiagnosticLanguageExtensionToken
// ReSharper disable CppInconsistentNaming
#pragma once

#include <cstdint>
#include <roapi.h>
#include <eventtoken.h>
#include <winstring.h>
#include <ole2.h>

#include <inspectable.h>
#include <asyncinfo.h>
#include <EventToken.h>
#include <WindowsContracts.h>
#include <windows.foundation.h>
#include <windows.system.h>

#include "Windows.Xbox.h"
#include "Windows.Xbox.Shell.Social.h"
#include "Windows.Xbox.System.h"

namespace Windows {
	namespace Xbox {
		namespace Achievements {
			MIDL_INTERFACE("DE87AD07-75DC-4EEC-9226-5628E98B9914")
				IXboxAchievementNotifier : public IInspectable
			{
				// TODO: Maybe we generate these I'm an idiot so IDK.
			};

			constexpr PCWSTR RuntimeClass_XboxAchievementNotifier = L"Microsoft.Xbox.Achievement.AchievementNotifier";
			inline const __declspec(selectany) auto& IID_IXboxAchievementNotifier = __uuidof(IXboxAchievementNotifier);
		}
	}
}

