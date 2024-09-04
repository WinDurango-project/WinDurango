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


/*
__int64 __fastcall TpSetPoolAffinityMask(__int64 a1, __int64 a2)
{
  __int64 result; // rax
  __int64 v5; // rax
  _BYTE v6[16]; // [rsp+30h] [rbp-38h] BYREF
  __int64 v7; // [rsp+40h] [rbp-28h]

  if ( !a2 )
	return 3221225485LL;
  result = ZwQueryInformationProcess(-1LL, 0LL, v6, 48LL, 0LL);
  if ( (int)result >= 0 )
  {
	if ( (a2 & v7) != a2 )
	  return 3221225485LL;
	if ( a1 )
	{
	  _InterlockedExchange64((volatile __int64 *)(a1 + 456), a2);
	}
	else
	{
	  RtlAcquireSRWLockExclusive(&unk_18009DB38);
	  qword_18009DB28 = a2;
	  RtlReleaseSRWLockExclusive(&unk_18009DB38);
	  v5 = sub_18005E18C();
	  if ( v5 )
	  {
		TpSetPoolAffinityMask(v5, a2);
		sub_18005E0E8(&qword_18009DB30, &unk_18009DB38);
	  }
	}
	return 0LL;
  }
  return result;
}
*/

void TpSetPoolAffinityMask_X()
{
	// TODO: This needs an implementation.
}