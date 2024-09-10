// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the WINRTX_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// WINRTX_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef WINRTX_EXPORTS
#define WINRTX_API __declspec(dllexport)
#else
#define WINRTX_API __declspec(dllimport)
#endif

// This class is exported from the dll
class WINRTX_API Cwinrtx {
public:
	Cwinrtx(void);
	// TODO: add your methods here.
};

extern WINRTX_API int nwinrtx;

WINRTX_API int fnwinrtx(void);
