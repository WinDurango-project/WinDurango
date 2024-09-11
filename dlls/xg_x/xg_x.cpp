#include "pch.h"
#include "framework.h"
#include "d3dkmddi.h"

//xg stands for "Xbox Graphics".

PHYSICAL_ADDRESS d3d_addr_pipes(PHYSICAL_ADDRESS* pipe)
{

	BOOL CreatePipe(
		          PHANDLE               hReadPipe,
		          PHANDLE               hWritePipe,
		 LPSECURITY_ATTRIBUTES lpPipeAttributes,
		         DWORD                 nSize
	);

	//doesn't need to return something since the CreatePipe() already returns a value.
}

PHYSICAL_ADDRESS d3d_addr_banks(PHYSICAL_ADDRESS BaseAddress)
{
	
	DXGKDDI_CREATEALLOCATION DxgkddiCreateallocation;

	NTSTATUS DxgkddiCreateallocation(
		     IN_CONST_HANDLE hAdapter,
		 INOUT_PDXGKARG_CREATEALLOCATION pCreateAllocation
	);

	typedef struct _DXGK_SEGMENTDESCRIPTOR {
		PHYSICAL_ADDRESS  BaseAddress;
		PHYSICAL_ADDRESS  CpuTranslatedAddress;
		SIZE_T            Size;
		UINT              NbOfBanks;
		SIZE_T* pBankRangeTable;
		SIZE_T            CommitLimit;
		DXGK_SEGMENTFLAGS Flags;
	} DXGK_SEGMENTDESCRIPTOR;

	_DXGK_SEGMENTDESCRIPTOR segmentDescriptor;
	segmentDescriptor.BaseAddress = BaseAddress;
	
	return segmentDescriptor.BaseAddress;

}

