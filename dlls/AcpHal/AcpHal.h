#pragma once
#include <inttypes.h>

struct ApuHeapState {
/* 0x0000 */ public: uint32_t bytesFree;
/* 0x0004 */ public: uint32_t bytesAllocated;
/* 0x0008 */ public: uint32_t bytesLost;
/* 0x000c */ public: uint32_t maximumBlockSizeAvailable;
/* 0x0010 */ public: uint32_t allocationCount;
};