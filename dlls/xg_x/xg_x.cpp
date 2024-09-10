#include "pch.h"
#include "framework.h"
#include "d3dkmddi.h"

//xg stands for "Xbox Graphics".

_int64 d3d_addr_pipes(_int64* pipe)
{

	BOOL CreatePipe(
		          PHANDLE               hReadPipe,
		          PHANDLE               hWritePipe,
		 LPSECURITY_ATTRIBUTES lpPipeAttributes,
		         DWORD                 nSize
	);

	//doesn't need to return something since the CreatePipe() already returns a value.
}

_int64 d3d_addr_banks()
{
	typedef struct _DXGK_SEGMENTDESCRIPTOR {
		PHYSICAL_ADDRESS  BaseAddress;
		PHYSICAL_ADDRESS  CpuTranslatedAddress;
		SIZE_T            Size;
		UINT              NbOfBanks;
		SIZE_T*			pBankRangeTable;
		SIZE_T            CommitLimit;
		DXGK_SEGMENTFLAGS Flags;
	} DXGK_SEGMENTDESCRIPTOR;

	DXGKDDI_CREATEALLOCATION DxgkddiCreateallocation;

	NTSTATUS DxgkddiCreateallocation(
		     IN_CONST_HANDLE hAdapter,
		 INOUT_PDXGKARG_CREATEALLOCATION pCreateAllocation
	);
	
}

