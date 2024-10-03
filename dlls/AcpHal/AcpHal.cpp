#include "pch.h"
#include "AcpHal.h"
#include <stdlib.h>

struct IAcpHal;

HRESULT AcpHalAllocateShapeContexts_X(__int64 a1) {
    return 0;
}

HRESULT AcpHalCreate_X(IAcpHal* a1) {
    return 0;
}

HRESULT AcpHalReleaseShapeContexts_X() {
    return 0;
}

HRESULT ApuAlloc_X(void* ptr, void* a2, size_t size, UINT32 alignment) {
    ptr = malloc(size);
    return 0;
}

HRESULT ApuCreateHeap_X(size_t initialSize, size_t maximumSize) {
    // Don't think we need that as this is for chaning memory pool iirc...
    return 0;
}

HRESULT ApuFree_X(void* ptr) {
    free(ptr);
    return 0;
}

HRESULT ApuHeapGetState_X(ApuHeapState* a1, int type) {
    return 0;
}

HRESULT ApuIsVirtualAddressValid_X(unsigned __int64 a1, unsigned int a2) {
    return 0;
}

HRESULT ApuMapApuAddress_X(unsigned int a1) {
    return 0;
}

HRESULT ApuMapVirtualAddress_X(unsigned __int64 a1) {
    return 0;
}
