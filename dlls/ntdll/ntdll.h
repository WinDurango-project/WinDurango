// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the NTDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// NTDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef NTDLL_EXPORTS
#define NTDLL_API __declspec(dllexport)
#else
#define NTDLL_API __declspec(dllimport)
#endif

// This class is exported from the dll
class NTDLL_API Cntdll {
public:
	Cntdll(void);
	// TODO: add your methods here.
};

extern NTDLL_API int nntdll;

NTDLL_API int fnntdll(void);
