// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the APPMODEL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// APPMODEL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef APPMODEL_EXPORTS
#define APPMODEL_API __declspec(dllexport)
#else
#define APPMODEL_API __declspec(dllimport)
#endif

// This class is exported from the dll
class APPMODEL_API Cappmodel {
public:
	Cappmodel(void);
	// TODO: add your methods here.
};

extern APPMODEL_API int nappmodel;

APPMODEL_API int fnappmodel(void);
