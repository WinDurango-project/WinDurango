// xg_x.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "xg_x.h"


// This is an example of an exported variable
XGX_API int nxgx=0;

// This is an example of an exported function.
XGX_API int fnxgx(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
Cxgx::Cxgx()
{
    return;
}
