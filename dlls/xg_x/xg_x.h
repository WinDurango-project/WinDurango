// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the XGX_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// XGX_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef XGX_EXPORTS
#define XGX_API __declspec(dllexport)
#else
#define XGX_API __declspec(dllimport)
#endif

// This class is exported from the dll
class XGX_API Cxgx {
public:
	Cxgx(void);
	// TODO: add your methods here.
};

extern XGX_API int nxgx;

XGX_API int fnxgx(void);
