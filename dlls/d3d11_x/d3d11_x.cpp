// d3d11_x.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "d3d11_x.h"


// This is an example of an exported variable
D3D11X_API int nd3d11x=0;

// This is an example of an exported function.
D3D11X_API int fnd3d11x(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
Cd3d11x::Cd3d11x()
{
    return;
}
