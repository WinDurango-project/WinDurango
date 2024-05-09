#include "pch.h"

#include <assert.h>
#include <psapi.h>
#include <stdio.h>
#include <windows.h>

typedef UINT(__cdecl* XBOX_ENTRYPOINT)(HINSTANCE, HINSTANCE, LPCWSTR, int);
void XboxEntrypointWrapper();

XBOX_ENTRYPOINT Entrypoint;

static void XboxEntrypointWrapper()
{
	STARTUPINFOW startupInfo;
	LPCWSTR  commandLine;
	BOOL bQuoted;
	UINT result;
	int nCmdShow;

	GetStartupInfo(&startupInfo);

	commandLine = GetCommandLineW();

	bQuoted = FALSE;

	while (*commandLine)
	{
		if (*commandLine == '"')
			bQuoted = !bQuoted;

		if (bQuoted == FALSE)
		{
			if (iswspace(*commandLine))
			{
				while (iswspace(*commandLine)) commandLine++;

				break;
			}
		}

		commandLine++;
	}

	// TODO: wcedcl handles the nCmdShow stuff here, not sure how that works so I'm just going to skip that for now.
	// TODO: wcedcl uses repair codes stuff here not sure how that works so I'm just going to skip that for now.

	result = Entrypoint(GetModuleHandleW(NULL), NULL, commandLine, nCmdShow);

	ExitProcess(result);
}

static BOOL PatchEntrypoint()
{
	MODULEINFO moduleInfo;
	HMODULE hModule;
	PIMAGE_DOS_HEADER dosHeader;
	DWORD dwOld;
	MEMORY_BASIC_INFORMATION mbi;
	XBOX_ENTRYPOINT entrypoint;

	hModule = GetModuleHandleA(NULL);
	dosHeader = (PIMAGE_DOS_HEADER)hModule;

	if (GetModuleInformation(GetCurrentProcess(), hModule, &moduleInfo, sizeof(moduleInfo)) == 0)
		return FALSE;

	entrypoint = (XBOX_ENTRYPOINT)moduleInfo.EntryPoint;

	VirtualQuery(entrypoint, &mbi, sizeof(mbi));

	mbi.Protect &= ~(PAGE_READONLY | PAGE_EXECUTE_READ);
	mbi.Protect |= PAGE_EXECUTE_READWRITE;

	if (VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &dwOld) == FALSE)
		return FALSE;

	Entrypoint = entrypoint;

	// TODO: wcedcl uses repair codes stuff here not sure how that works so I'm just going to skip that for now.

	return TRUE;
}

BOOL __stdcall DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if (MessageBoxExW(NULL, L"Attach a debugger now?", L"Xbox Compatibility Layer", MB_YESNO | MB_ICONQUESTION, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)) == IDYES)
		{
			WCHAR VSJitDebugger[MAX_PATH], CmdLineBuf[256], SystemDirectory[MAX_PATH];

			PROCESS_INFORMATION Info = { };
			STARTUPINFO StartupInfo = { };

			GetSystemDirectoryW(SystemDirectory, MAX_PATH);

			swprintf_s(VSJitDebugger, MAX_PATH, L"%s\\vsjitdebugger.exe", SystemDirectory);
			swprintf_s(CmdLineBuf, 256, L"%s -p %d", VSJitDebugger, GetCurrentProcessId());

			StartupInfo.wShowWindow = SW_SHOW;

			assert(CreateProcess(VSJitDebugger, CmdLineBuf, NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &Info));

			WaitForSingleObject(Info.hProcess, -1);

			CloseHandle(Info.hProcess);
			CloseHandle(Info.hThread);
		}

		PatchEntrypoint();

		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}