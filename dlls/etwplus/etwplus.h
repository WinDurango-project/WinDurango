// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the ETWPLUS_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// ETWPLUS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ETWPLUS_EXPORTS
#define ETWPLUS_API __declspec(dllexport)
#else
#define ETWPLUS_API __declspec(dllimport)
#endif

// This class is exported from the dll
class ETWPLUS_API Cetwplus {
public:
	Cetwplus(void);
	// TODO: add your methods here.
};

extern ETWPLUS_API int netwplus;

ETWPLUS_API int fnetwplus(void);
