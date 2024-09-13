// ReSharper disable CppInconsistentNaming
#include "pch.h"
#include "Windows.Xbox.Achievements.AchievementNotifier.h"
#include "Windows.Xbox.Achievements.AchievementNotifier.g.cpp"

namespace winrt::Windows::Xbox::Achievements::implementation
{
	AchievementSource AchievementNotifier::GetTitleIdFilteredSource()
	{
		AchievementSource achievement_source(nullptr);

		return achievement_source;
	}

	AchievementSource AchievementNotifier::GetUnfilteredSource()
	{
		AchievementSource achievement_source(nullptr);

		return achievement_source;
	}
}
