// ReSharper disable CppInconsistentNaming
// ReSharper disable CppParameterMayBeConst
// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement
// ReSharper disable CppClangTidyHicppMultiwayPathsCovered
// ReSharper disable CppClangTidyClangDiagnosticInconsistentDllimport
#include "pch.h"
#include "framework.h"

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD forwardReason, LPVOID lpvReserved)
{
	switch (forwardReason)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}

// TODO: I'm not sure what the return type or parameters are for this function.
void TpSetPoolAffinityMask_X()
{
	// TODO: This needs an implementation.
}