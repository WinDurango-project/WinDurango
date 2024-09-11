// ReSharper disable CppInconsistentNaming
#include "pch.h"

HRESULT GetActivationFactory_X(HSTRING classId, IActivationFactory** factory)
{
	switch (classId) 
	{
	case "Windows.Xbox.Achievements.AchievementNotifier":
	default:
		break;
	}

	return S_OK;
}
