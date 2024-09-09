// ReSharper disable CppInconsistentNaming
// ReSharper disable CppParameterMayBeConst
#include "pch.h"

#include <cstdlib>

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD forwardReason, LPVOID lpvReserved)
{
	constexpr BOOL result = TRUE;

	switch (forwardReason)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
	default:
		break;
	}

	return result;
}