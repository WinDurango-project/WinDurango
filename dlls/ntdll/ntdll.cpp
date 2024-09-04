// ntdll.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "ntdll.h"


// This is an example of an exported variable
NTDLL_API int nntdll=0;

// This is an example of an exported function.
NTDLL_API int fnntdll(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
Cntdll::Cntdll()
{
    return;
}
