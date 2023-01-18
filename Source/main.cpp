// ReSharper disable CppInconsistentNaming
// NOLINT(performance-no-int-to-ptr)
#include <cstdio>
#include <tchar.h>

#include <Windows.h>

typedef struct BASE_RELOCATION_ENTRY
{
	WORD Offset : 12;
	WORD Type : 4;
} BASE_RELOCATION_ENTRY;

#define RELOC_32BIT_FIELD 3

BYTE* MapFileToMemory(const LPCSTR filename, LONGLONG &fileLength)
{
	FILE* filePtr = fopen(filename, "rb");

	fseek(filePtr, 0, SEEK_END);

	fileLength = ftell(filePtr);

	rewind(filePtr);

	const auto buffer = static_cast<BYTE*>(malloc((fileLength + 1) * sizeof(char)));

	fread(buffer, fileLength, 1, filePtr);
	fclose(filePtr);

	return buffer;
}

BYTE* GetNtHeaders(BYTE* peBuffer)
{
	if (peBuffer == nullptr) 
		return nullptr;

	const auto imageDosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(peBuffer);

	if (imageDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		return nullptr;

	constexpr LONG kMaxOffset = 1024;

	const LONG peOffset = imageDosHeader->e_lfanew;

	if (peOffset > kMaxOffset) return nullptr;

	const auto imageNtHeaders32 = reinterpret_cast<IMAGE_NT_HEADERS32*>(peBuffer + peOffset);

	if (imageNtHeaders32->Signature != IMAGE_NT_SIGNATURE) return nullptr;

	return reinterpret_cast<BYTE*>(imageNtHeaders32);
}

IMAGE_DATA_DIRECTORY* GetPeDir(const PVOID peBuffer, const size_t dirId)
{
	if (dirId >= IMAGE_NUMBEROF_DIRECTORY_ENTRIES) return nullptr;

	const auto ntHeaders = GetNtHeaders(static_cast<BYTE*>(peBuffer));

	if (ntHeaders == nullptr) return nullptr;

	const auto ntHeader = reinterpret_cast<IMAGE_NT_HEADERS*>(ntHeaders);

	IMAGE_DATA_DIRECTORY* peDir = &(ntHeader->OptionalHeader.DataDirectory[dirId]);

	if (peDir->VirtualAddress == NULL)
		return nullptr;

	return peDir;
}

BOOL FixImportAddressTable(const PVOID modulePtr)
{
	printf("[+] Fix Import Address Table\n");

	const IMAGE_DATA_DIRECTORY* importsDir = GetPeDir(modulePtr, IMAGE_DIRECTORY_ENTRY_IMPORT);

	if (importsDir == nullptr) return FALSE;

	const size_t maxSize = importsDir->Size;
	const size_t impAddress = importsDir->VirtualAddress;

	IMAGE_IMPORT_DESCRIPTOR* lib_desc = nullptr;

	for (size_t parsedSize = 0; parsedSize < maxSize; parsedSize += sizeof(IMAGE_IMPORT_DESCRIPTOR)) {
		lib_desc = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(impAddress + parsedSize + reinterpret_cast<ULONG_PTR>(modulePtr));

		if (lib_desc->OriginalFirstThunk == NULL && lib_desc->FirstThunk == NULL) break;

		const auto libName = reinterpret_cast<LPSTR>(reinterpret_cast<ULONGLONG>(modulePtr) + lib_desc->Name);

		// TODO: Replace any Xbox specific libraries with their Windows counterparts.

		printf("    [+] Import DLL: %s\n", libName);

		size_t callVia = lib_desc->FirstThunk;
		size_t thunkAddress = lib_desc->OriginalFirstThunk;

		if (thunkAddress == NULL) thunkAddress = lib_desc->FirstThunk;

		size_t offsetField = 0;
		size_t offsetThunk = 0;

		while (true)
		{
			
		}
	}

	return FALSE;
}

BOOL ApplyRelocation(const ULONGLONG newBase, const ULONGLONG oldBase, PVOID modulePtr, const SIZE_T moduleSize)
{
	const IMAGE_DATA_DIRECTORY* relocDir = GetPeDir(modulePtr, IMAGE_DIRECTORY_ENTRY_BASERELOC);

	/* Cannot relocate - application have no relocation table */
	if (relocDir == nullptr) 
		return FALSE;

	const size_t maxSize = relocDir->Size;
	const size_t relocAddress = relocDir->VirtualAddress;
	IMAGE_BASE_RELOCATION* reloc = nullptr;

	size_t parsedSize = 0;

	for (; parsedSize < maxSize; parsedSize += reloc->SizeOfBlock) {
		reloc = reinterpret_cast<IMAGE_BASE_RELOCATION*>(relocAddress + parsedSize + reinterpret_cast<size_t>(modulePtr));

		if (reloc->VirtualAddress == NULL || reloc->SizeOfBlock == 0)
			break;

		const size_t entriesNum = (reloc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(BASE_RELOCATION_ENTRY);
		const size_t page = reloc->VirtualAddress;

		auto entry = reinterpret_cast<BASE_RELOCATION_ENTRY*>(reinterpret_cast<size_t>(reloc) + sizeof(IMAGE_BASE_RELOCATION));

		for (size_t i = 0; i < entriesNum; i++) {
			const size_t offset = entry->Offset;
			const size_t type = entry->Type;
			const size_t relocField = page + offset;

			if (entry == nullptr || type == 0)
				break;
			if (type != RELOC_32BIT_FIELD) {
				printf("    [!] Not supported relocations format at %d: %d\n", static_cast<int>(i), static_cast<int>(type));

				return FALSE;
			}
			if (relocField >= moduleSize) {
				printf("    [-] Out of Bound Field: %llu\n", relocField);

				return FALSE;
			}

			const auto relocateAddress = reinterpret_cast<size_t*>(reinterpret_cast<size_t>(modulePtr) + relocField);

			printf("    [V] Apply Relocation Field at %llu\n", *relocateAddress);

			(*relocateAddress) = ((*relocateAddress) - oldBase + newBase);

			entry = reinterpret_cast<BASE_RELOCATION_ENTRY*>(reinterpret_cast<size_t>(entry) + sizeof(BASE_RELOCATION_ENTRY));
		}
	}
	return (parsedSize != 0);

	return FALSE;
}

BOOL PELoader(const char* exePath)
{
	LONGLONG file_size = -1;

	BYTE* data = MapFileToMemory(exePath, file_size);

	BYTE* pImageBase = nullptr;
	LPVOID preferAddress = nullptr;

	const auto ntHeader = reinterpret_cast<IMAGE_NT_HEADERS*>(GetNtHeaders(data));

	if (!ntHeader)
	{
		printf("[+] File %p isn't a PE file.", exePath);

		return FALSE;
	}

	const auto relocDir = GetPeDir(data, IMAGE_DIRECTORY_ENTRY_BASERELOC);

	preferAddress = reinterpret_cast<LPVOID>(ntHeader->OptionalHeader.ImageBase);

	printf("[+] Executable File Prefer Image Base at %p\n", preferAddress);

	const HMODULE dll = LoadLibraryA("ntdll.dll");

	reinterpret_cast<int(__stdcall*)(HANDLE, PVOID)>(GetProcAddress(dll, "NtUnmapViewOfSection"))(reinterpret_cast<HANDLE>(-1), reinterpret_cast<LPVOID>(ntHeader->OptionalHeader.ImageBase));

	pImageBase = static_cast<BYTE*>(VirtualAlloc(preferAddress, ntHeader->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));

	if (!pImageBase && !relocDir)
	{
		printf("[-] Allocate Image Base At %p Failure.\n", preferAddress);
		return FALSE;
	}

	if (!pImageBase && relocDir)
	{
		printf("[+] Try to Allocate Memory for New Image Base\n");
		pImageBase = static_cast<BYTE*>(VirtualAlloc(nullptr, ntHeader->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE,PAGE_EXECUTE_READWRITE));

		if (!pImageBase)
		{
			printf("[-] Allocate Memory For Image Base Failure.\n");
			return FALSE;
		}
	}

	puts("[+] Mapping Section ...");
	ntHeader->OptionalHeader.ImageBase = reinterpret_cast<size_t>(pImageBase);
	memcpy(pImageBase, data, ntHeader->OptionalHeader.SizeOfHeaders);

	const auto SectionHeaderArr = reinterpret_cast<IMAGE_SECTION_HEADER*>
		(reinterpret_cast<size_t>(ntHeader) + sizeof(IMAGE_NT_HEADERS));

	for (int i = 0; i < ntHeader->FileHeader.NumberOfSections; i++)
	{
		printf("    [+] Mapping Section %s\n", SectionHeaderArr[i].Name);
		memcpy
		(
			reinterpret_cast<LPVOID>(reinterpret_cast<size_t>(pImageBase) 
				+ SectionHeaderArr[i].VirtualAddress),
			reinterpret_cast<LPVOID>(reinterpret_cast<size_t>(data) 
				+ SectionHeaderArr[i].PointerToRawData),
			SectionHeaderArr[i].SizeOfRawData
		);
	}


	// masqueradeCmdline(cmdline);
	// fixIAT(pImageBase);

	if (pImageBase != preferAddress)
		if (ApplyRelocation(reinterpret_cast<size_t>(pImageBase), reinterpret_cast<size_t>(preferAddress),
			pImageBase, 
			ntHeader->OptionalHeader.SizeOfImage))
			puts("[+] Relocation Fixed.");

	size_t returnAddress = reinterpret_cast<size_t>(pImageBase)+ntHeader->OptionalHeader.AddressOfEntryPoint;

	printf("Run Exe Module: %p\n", exePath);


	// return reinterpret_cast<void(*)()>(returnAddress)();

	return FALSE;
}

int main(const int argc, char** argv)
{
	if (argc != 2) {
		printf("Usage: xbonemu [exePath]\n");

		return FALSE;
	}

	const char* exePath = argv[1];

	PELoader(exePath);

	return FALSE;
}