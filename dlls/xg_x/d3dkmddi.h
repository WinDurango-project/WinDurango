/******************************Module*Header**********************************\
*
* Module Name: d3dkmddi.h
*
* Content: longhorn display driver kernel mode interfaces
*
* Copyright (c) 2003 Microsoft Corporation.  All rights reserved.
\*****************************************************************************/
#ifndef _D3DKMDDI_H_
#define _D3DKMDDI_H_

#include <d3dkmdt.h>

#ifndef DXGK_ALLOCATIONINFOFLAGS_EXT
#define DXGK_ALLOCATIONINFOFLAGS_EXT
#define DXGK_ALLOC_RESERVED0        Reserved0
#define DXGK_ALLOC_RESERVED1        Reserved1
#define DXGK_ALLOC_RESERVED2        Reserved2
#define DXGK_ALLOC_RESERVED3        Reserved3
#define DXGK_ALLOC_RESERVED4        Reserved4
#define DXGK_ALLOC_RESERVED5        Reserved5
#define DXGK_ALLOC_RESERVED6        Reserved6
#define DXGK_ALLOC_RESERVED7        Reserved7
#define DXGK_ALLOC_RESERVED8        Reserved8
#define DXGK_ALLOC_RESERVED9        Reserved9
#define DXGK_ALLOC_RESERVED10       Reserved10
#define DXGK_ALLOC_RESERVED11       Reserved11
#define DXGK_ALLOC_RESERVED12       Reserved12
#define DXGK_ALLOC_RESERVED13       Reserved13
#define DXGK_ALLOC_RESERVED14       Reserved14
#define DXGK_ALLOC_RESERVED15       Reserved15
#endif

#ifndef DXGK_DEVICEFLAGS_EXT
#define DXGK_DEVICEFLAGS_EXT
#define DXGK_DEVICE_RESERVED0       Reserved0
#endif

//
// Stable power states ETW defines
//
#define DXGK_KEYWORD_LOG_FLAGS_STABLE_POWER   0x1000
#define DXGK_KEYWORD_LOG_FLAGS_STABLE_POWER2  0x2000

#pragma warning(push)
#pragma warning(disable:4200) /* nonstandard extension used : zero-sized array in struct/union */
#pragma warning(disable:4201) // anonymous unions warning
#pragma warning(disable:4510 4512 4610 ) // cannot generate default constructor

typedef D3DDDI_SEGMENTPREFERENCE DXGK_SEGMENTPREFERENCE;

typedef struct _DXGK_SEGMENTBANKPREFERENCE
{
    union
    {
        struct
        {
            UINT Bank0          : 7;    // 0x0000007F
            UINT Direction0     : 1;    // 0x00000080
            UINT Bank1          : 7;    // 0x00007F00
            UINT Direction1     : 1;    // 0x00008000
            UINT Bank2          : 7;    // 0x007F0000
            UINT Direction2     : 1;    // 0x00800000
            UINT Bank3          : 7;    // 0x7F000000
            UINT Direction3     : 1;    // 0x80000000
        };
        UINT Value;
    };
} DXGK_SEGMENTBANKPREFERENCE;

typedef struct _DXGK_ALLOCATIONLIST
{
    HANDLE              hDeviceSpecificAllocation;
    struct
    {
        UINT            WriteOperation  : 1;    // 0x00000001
        UINT            SegmentId       : 5;    // 0x0000002E
        UINT            Reserved        : 26;   // 0xFFFFFFC0
    };
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
    union
    {
        PHYSICAL_ADDRESS    PhysicalAddress;
        D3DGPU_VIRTUAL_ADDRESS VirtualAddress;
    };
#else // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
    PHYSICAL_ADDRESS    PhysicalAddress;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
} DXGK_ALLOCATIONLIST;

//
// The below is to allow drivers to use the updated annotations if they wish,
// but not yet require all drivers to update their annotations.
//

#ifdef ENABLE_DXGK_SAL
#define _Function_class_DXGK_(param)    _Function_class_(param)
#else
#define _Function_class_DXGK_(param)
#endif



/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Define parameter types for SAL-annotated DDI parameters.  These are used by DDI function
//          name typedefs in dispmprt.h and d3dkmddi.h.  They are not needed in a driver's DDI function
//          definitions, and should not be used in driver code.
//
//  Naming convention: Concatenate all SAL annotations, an underscore, other modifiers
//                     such as CONST, and the type of the parameter, and use uppercase
//                     only.
//
typedef _In_          BOOLEAN               IN_BOOLEAN;
typedef _In_          UCHAR                 IN_UCHAR;
typedef _In_          DEVICE_POWER_STATE    IN_DEVICE_POWER_STATE;
typedef _In_    CONST HANDLE                IN_CONST_HANDLE;
typedef _Inout_       UINT*                 INOUT_PUINT;
typedef _Out_         UINT*                 OUT_PUINT;
typedef _In_          ULONG                 IN_ULONG;
typedef _Out_         PULONG                OUT_PULONG;
typedef _In_          POWER_ACTION          IN_POWER_ACTION;
typedef _In_          PVOID                 IN_PVOID;
typedef _In_    CONST PVOID                 IN_CONST_PVOID;
typedef _Outptr_      PVOID*                OUT_PPVOID;
typedef _In_    CONST SIZE_T                IN_CONST_SIZE_T;
typedef _Out_         SIZE_T*               OUT_PSIZE_T;
typedef _Out_         SIZE_T*   CONST       OUT_PSIZE_T_CONST;


typedef struct _DXGKARG_RENDER
{
    CONST VOID* CONST           pCommand;
    CONST UINT                  CommandLength;
    VOID*                       pDmaBuffer;
    UINT                        DmaSize;
    VOID*                       pDmaBufferPrivateData;
    UINT                        DmaBufferPrivateDataSize;
    DXGK_ALLOCATIONLIST*        pAllocationList;
    UINT                        AllocationListSize;
    D3DDDI_PATCHLOCATIONLIST*   pPatchLocationListIn;
    UINT                        PatchLocationListInSize;
    D3DDDI_PATCHLOCATIONLIST*   pPatchLocationListOut;
    UINT                        PatchLocationListOutSize;
    UINT                        MultipassOffset;
    UINT                        DmaBufferSegmentId;
    PHYSICAL_ADDRESS            DmaBufferPhysicalAddress;
} DXGKARG_RENDER;

typedef _Inout_ DXGKARG_RENDER*     INOUT_PDXGKARG_RENDER;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_RENDER)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_RENDER(
    IN_CONST_HANDLE         hContext,
    INOUT_PDXGKARG_RENDER   pRender
    );


#define DXGK_PRESENT_SOURCE_INDEX       1
#define DXGK_PRESENT_DESTINATION_INDEX  2
#define DXGK_PRESENT_MAX_INDEX          DXGK_PRESENT_DESTINATION_INDEX

typedef struct _DXGK_PRESENTFLAGS
{
    union
    {
        struct
        {
            UINT    Blt                     : 1;    // 0x00000001
            UINT    ColorFill               : 1;    // 0x00000002
            UINT    Flip                    : 1;    // 0x00000004
            UINT    FlipWithNoWait          : 1;    // 0x00000008
            UINT    SrcColorKey             : 1;    // 0x00000010
            UINT    DstColorKey             : 1;    // 0x00000020
            UINT    LinearToSrgb            : 1;    // 0x00000040
            UINT    Rotate                  : 1;    // 0x00000080
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
            UINT    FlipStereo              : 1;    // 0x00000100
            UINT    FlipStereoTemporaryMono : 1;    // 0x00000200   // Use the left image only when making a stereo frame
            UINT    FlipStereoPreferRight   : 1;    // 0x00000400   // Used when a stereo primary is cloned to a mono monitor. Cannot be used with FlipStereoTemporaryMono
            UINT    BltStereoUseRight       : 1;    // 0x00000800   // Used when presenting from a stereo back buffer to a mono surface. The right image must be used.
            UINT    FlipWithMultiPlaneOverlay : 1;  // 0x00001000
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
            UINT    RedirectedFlip          : 1;    // 0x00002000
            UINT    Reserved                :18;    // 0xFFFFC000
#else
            UINT    Reserved                :19;    // 0xFFFFE000
#endif // DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0
#else
            UINT    Reserved                :24;    // 0xFFFFFF00
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
        };
        UINT Value;
    };
} DXGK_PRESENTFLAGS;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN7)

typedef struct _DXGK_PRESENTALLOCATIONINFO
{
    HANDLE                   hDeviceSpecificAllocation;
    D3DGPU_VIRTUAL_ADDRESS   AllocationVirtualAddress;
    PHYSICAL_ADDRESS         PhysicalAddress;
    WORD                     SegmentId;
    WORD                     PhysicalAdapterIndex;
} DXGK_PRESENTALLOCATIONINFO;
#endif // DXGKDDI_INTERFACE_VERSION

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
typedef struct _DXGK_PRESENTMULTIPLANEOVERLAYLIST
{
    UINT                LayerIndex;
    BOOL                Enabled;

    HANDLE              hDeviceSpecificAllocation;
    struct
    {
        UINT            SegmentId       : 5;    // in: 0x0000001F
        UINT            Reserved        : 27;
    };
    PHYSICAL_ADDRESS    PhysicalAddress;
} DXGK_PRESENTMULTIPLANEOVERLAYLIST;

typedef struct _DXGK_PRESENTMULTIPLANEOVERLAYINFO
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID     VidPnSourceId;
    UINT                               PlaneListCount;
    DXGK_PRESENTMULTIPLANEOVERLAYLIST* pPlaneList;
} DXGK_PRESENTMULTIPLANEOVERLAYINFO;
#endif // DXGKDDI_INTERFACE_VERSION

typedef struct _DXGKARG_PRESENT
{
    VOID*                       pDmaBuffer;
    UINT                        DmaSize;
    VOID*                       pDmaBufferPrivateData;
    UINT                        DmaBufferPrivateDataSize;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN7)
    union
    {
        DXGK_ALLOCATIONLIST*        pAllocationList;
        DXGK_PRESENTALLOCATIONINFO* pAllocationInfo;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
        DXGK_PRESENTMULTIPLANEOVERLAYINFO* pPresentMultiPlaneOverlayInfo;
#endif // DXGKDDI_INTERFACE_VERSION
    };
    D3DDDI_PATCHLOCATIONLIST*   pPatchLocationListOut;     // Not used
    UINT                        PatchLocationListOutSize;  // Not used
#else
    DXGK_ALLOCATIONLIST*        pAllocationList;
    D3DDDI_PATCHLOCATIONLIST*   pPatchLocationListOut;
    UINT                        PatchLocationListOutSize;
#endif // DXGKDDI_INTERFACE_VERSION
    UINT                        MultipassOffset;
    UINT                        Color;
    RECT                        DstRect;
    RECT                        SrcRect;
    UINT                        SubRectCnt;
    CONST RECT*                 pDstSubRects;
    D3DDDI_FLIPINTERVAL_TYPE    FlipInterval;
    DXGK_PRESENTFLAGS           Flags;
    UINT                        DmaBufferSegmentId;
    PHYSICAL_ADDRESS            DmaBufferPhysicalAddress;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
    UINT                        Reserved;
#endif
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
    D3DGPU_VIRTUAL_ADDRESS      DmaBufferGpuVirtualAddress;
    UINT                        NumSrcAllocations;
    UINT                        NumDstAllocations;
    UINT                        PrivateDriverDataSize;
    _Field_size_bytes_(PrivateDriverDataSize)
    PVOID                       pPrivateDriverData;
#endif // DXGKDDI_INTERFACE_VERSION
} DXGKARG_PRESENT;

typedef _Inout_ DXGKARG_PRESENT*    INOUT_PDXGKARG_PRESENT;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_PRESENT)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_PRESENT(
    IN_CONST_HANDLE         hContext,
    INOUT_PDXGKARG_PRESENT  pPresent
    );

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
typedef struct _DXGK_MULTIPLANE_OVERLAY_FLAGS
{
    union
    {
        struct
        {
            UINT    VerticalFlip              : 1;    // 0x00000001
            UINT    HorizontalFlip            : 1;    // 0x00000002
            UINT    Reserved                  :30;    // 0xFFFFFFFC
        };
        UINT Value;
    };
} DXGK_MULTIPLANE_OVERLAY_FLAGS;

typedef struct _DXGK_MULTIPLANE_OVERLAY_BLEND
{
    union
    {
        struct
        {
            UINT    AlphaBlend     : 1;    // 0x00000001
            UINT    Reserved       :31;    // 0xFFFFFFFE
        };
        UINT Value;
    };
} DXGK_MULTIPLANE_OVERLAY_BLEND;

typedef struct _DXGK_MULTIPLANE_OVERLAY_YCbCr_FLAGS
{
    union
    {
        struct
        {
            UINT    NominalRange   : 1;    // 0x00000001
            UINT    Bt709          : 1;    // 0x00000002
            UINT    xvYCC          : 1;    // 0x00000004
            UINT    Reserved       : 29;   // 0xFFFFFFF8
        };
        UINT Value;
    };
} DXGK_MULTIPLANE_OVERLAY_YCbCr_FLAGS;

typedef enum _DXGK_MULTIPLANE_OVERLAY_VIDEO_FRAME_FORMAT
{
    DXGK_MULTIPLANE_OVERLAY_VIDEO_FRAME_FORMAT_PROGRESSIVE                   = 0,
    DXGK_MULTIPLANE_OVERLAY_VIDEO_FRAME_FORMAT_INTERLACED_TOP_FIELD_FIRST    = 1,
    DXGK_MULTIPLANE_OVERLAY_VIDEO_FRAME_FORMAT_INTERLACED_BOTTOM_FIELD_FIRST = 2,
} DXGK_MULTIPLANE_OVERLAY_VIDEO_FRAME_FORMAT;

typedef enum _DXGK_MULTIPLANE_OVERLAY_STEREO_FORMAT
{
    DXGK_MULTIPLANE_OVERLAY_STEREO_FORMAT_MONO               = 0,
    DXGK_MULTIPLANE_OVERLAY_STEREO_FORMAT_HORIZONTAL         = 1,
    DXGK_MULTIPLANE_OVERLAY_STEREO_FORMAT_VERTICAL           = 2,
    DXGK_MULTIPLANE_OVERLAY_STEREO_FORMAT_SEPARATE           = 3,
    DXGK_MULTIPLANE_OVERLAY_STEREO_FORMAT_MONO_OFFSET        = 4,
    DXGK_MULTIPLANE_OVERLAY_STEREO_FORMAT_ROW_INTERLEAVED    = 5,
    DXGK_MULTIPLANE_OVERLAY_STEREO_FORMAT_COLUMN_INTERLEAVED = 6,
    DXGK_MULTIPLANE_OVERLAY_STEREO_FORMAT_CHECKERBOARD       = 7,
} DXGK_MULTIPLANE_OVERLAY_STEREO_FORMAT;

typedef enum _DXGK_MULTIPLANE_OVERLAY_STEREO_FLIP_MODE
{
   DXGK_MULTIPLANE_OVERLAY_STEREO_FLIP_NONE   = 0,
   DXGK_MULTIPLANE_OVERLAY_STEREO_FLIP_FRAME0 = 1,
   DXGK_MULTIPLANE_OVERLAY_STEREO_FLIP_FRAME1 = 2,
} DXGK_MULTIPLANE_OVERLAY_STEREO_FLIP_MODE;

typedef enum _DXGK_MULTIPLANE_OVERLAY_STRETCH_QUALITY
{
    DXGK_MULTIPLANE_OVERLAY_STRETCH_QUALITY_BILINEAR        = 0x1,  // Bilinear
    DXGK_MULTIPLANE_OVERLAY_STRETCH_QUALITY_HIGH            = 0x2,  // Maximum
} DXGK_MULTIPLANE_OVERLAY_STRETCH_QUALITY;

typedef struct _DXGK_MULTIPLANE_OVERLAY_ATTRIBUTES
{
    DXGK_MULTIPLANE_OVERLAY_FLAGS                  Flags;
    RECT                                           SrcRect;
    RECT                                           DstRect;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
    RECT                                           ClipRect;
#endif
    D3DDDI_ROTATION                                Rotation;
    DXGK_MULTIPLANE_OVERLAY_BLEND                  Blend;
#if (DXGKDDI_INTERFACE_VERSION < DXGKDDI_INTERFACE_VERSION_WDDM1_3)
    UINT                                           NumFilters;
    void*                                          pFilters;
#endif
    DXGK_MULTIPLANE_OVERLAY_VIDEO_FRAME_FORMAT     VideoFrameFormat;
    DXGK_MULTIPLANE_OVERLAY_YCbCr_FLAGS            YCbCrFlags;
    DXGK_MULTIPLANE_OVERLAY_STEREO_FORMAT          StereoFormat;
    BOOL                                           StereoLeftViewFrame0;
    BOOL                                           StereoBaseViewFrame0;
    DXGK_MULTIPLANE_OVERLAY_STEREO_FLIP_MODE       StereoFlipMode;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
    DXGK_MULTIPLANE_OVERLAY_STRETCH_QUALITY        StretchQuality;
#endif
} DXGK_MULTIPLANE_OVERLAY_ATTRIBUTES;

typedef struct _DXGK_CHECK_MULTIPLANE_OVERLAY_SUPPORT_PLANE
{
    HANDLE                               hAllocation;
    D3DDDI_VIDEO_PRESENT_SOURCE_ID       VidPnSourceId;
    DXGK_MULTIPLANE_OVERLAY_ATTRIBUTES   PlaneAttributes;
} DXGK_CHECK_MULTIPLANE_OVERLAY_SUPPORT_PLANE;

typedef struct DXGK_CHECK_MULTIPLANE_OVERLAY_SUPPORT_RETURN_INFO
{
    union
    {
        struct
        {
            UINT    FailingPlane        : 4;   // The 0 based index of the first plane that could not be supported
            UINT    TryAgain            : 1;   // The configuration is not supported due to a transition condition, which should shortly go away
            UINT    Reserved            : 27;
        };
        UINT    Value;
    };
} DXGK_CHECK_MULTIPLANE_OVERLAY_SUPPORT_RETURN_INFO;

typedef struct _DXGK_MULTIPLANE_OVERLAY_PLANE
{
    UINT                                 LayerIndex;
    BOOL                                 Enabled;

    UINT                                 AllocationSegment;
    PHYSICAL_ADDRESS                     AllocationAddress;
    HANDLE                               hAllocation;
    DXGK_MULTIPLANE_OVERLAY_ATTRIBUTES   PlaneAttributes;
} DXGK_MULTIPLANE_OVERLAY_PLANE;
#endif // DXGKDDI_INTERFACE_VERSION

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
typedef struct _DXGK_MULTIPLANE_OVERLAY_ATTRIBUTES2
{
    DXGK_MULTIPLANE_OVERLAY_FLAGS                Flags;     // Specifies a combination of flip operations by Oring values in the DXGK_MULTIPLANE_OVERLAY_FLAGS enumeration.
    RECT                                         SrcRect;   // Specifies the source rectangle, of type RECT, relative to the source resource.
    RECT                                         DstRect;   // Specifies the destination rectangle, of type RECT, relative to the monitor resolution.
    RECT                                         ClipRect;  // Specifies any additional clipping, of type RECT, relative to the DstRect rectangle, 
                                                            // after the data has been stretched according to the values of SrcRect and DstRect.

                                                            // The driver and hardware can use the ClipRect member to apply a common stretch factor 
                                                            // as the clipping changes when an app occludes part of the DstRect destination rectangle.
    D3DDDI_ROTATION                              Rotation;  // Specifies the clockwise rotation of the overlay plane, given as a value from the D3DDDI_ROTATION enumeration.
    DXGK_MULTIPLANE_OVERLAY_BLEND                Blend;     // Specifies the blend mode that applies to this overlay plane and the plane beneath it, given as a value from the DXGK_MULTIPLANE_OVERLAY_BLEND enumeration.
    DXGK_MULTIPLANE_OVERLAY_VIDEO_FRAME_FORMAT   VideoFrameFormat;  // Specifies the overlay plane's video frame format, given as a value from the DXGK_MULTIPLANE_OVERLAY_VIDEO_FRAME_FORMAT enumeration.
    D3DDDI_COLOR_SPACE_TYPE                      ColorSpaceType;    // Specifies the colorspace configuration, given as a value from the D3DDDI_COLOR_SPACE_TYPE enumeration.
    DXGK_MULTIPLANE_OVERLAY_STEREO_FORMAT        StereoFormat;      // Specifies the overlay plane's video frame format, given as a value from the DXGK_MULTIPLANE_OVERLAY_STEREO_FORMAT enumeration.
    BOOL                                         StereoLeftViewFrame0;  // Reserved for system use. Must always be FALSE.
    BOOL                                         StereoBaseViewFrame0;  // Reserved for system use. Must always be FALSE.
    DXGK_MULTIPLANE_OVERLAY_STEREO_FLIP_MODE     StereoFlipMode;        // Specifies the overlay plane's stereo flip mode, given as a value from the DXGK_MULTIPLANE_OVERLAY_STEREO_FLIP_MODE enumeration.
    DXGK_MULTIPLANE_OVERLAY_STRETCH_QUALITY      StretchQuality;        // Specifies the overlay plane's stretch quality, given as a value from the DXGK_MULTIPLANE_OVERLAY_STRETCH_QUALITY enumeration.
    UINT                                         Reserved1;
} DXGK_MULTIPLANE_OVERLAY_ATTRIBUTES2;

// Describes the multi-plane overlay plane attributes, allocation, and VidPnSourceId.
typedef struct _DXGK_MULTIPLANE_OVERLAY_PLANE_WITH_SOURCE
{
    HANDLE                                  hAllocation;                 // A handle to the allocation.
    D3DDDI_VIDEO_PRESENT_SOURCE_ID          VidPnSourceId;               // The zero-based video present network (VidPN) source identification number 
                                                                         // of the input for which the support levels are queried.
    UINT                                    LayerIndex;
    DXGK_MULTIPLANE_OVERLAY_ATTRIBUTES2     PlaneAttributes;             // A DXGK_MULTIPLANE_OVERLAY_ATTRIBUTES1 structure that specifies overlay plane attributes.
} DXGK_MULTIPLANE_OVERLAY_PLANE_WITH_SOURCE;

typedef struct _DXGKARG_CHECKMULTIPLANEOVERLAYSUPPORT2
{
    UINT                                                PlaneCount;     // The number of planes to be enabled.
    DXGK_MULTIPLANE_OVERLAY_PLANE_WITH_SOURCE*          pPlanes;        // A pointer to a DXGK_MULTIPLANE_OVERLAY_PLANE_WITH_SOURCE 
                                                                        // structure that specifies support attributes that the hardware
                                                                        // provides for multi-plane overlays.
    BOOL                                                Supported;      // TRUE if the multi-plane overlay configuration can be supported, otherwise FALSE.
    DXGK_CHECK_MULTIPLANE_OVERLAY_SUPPORT_RETURN_INFO   ReturnInfo;     // Specifies additional information.
} DXGKARG_CHECKMULTIPLANEOVERLAYSUPPORT2;

typedef _Inout_ DXGKARG_CHECKMULTIPLANEOVERLAYSUPPORT2* IN_OUT_PDXGKARG_CHECKMULTIPLANEOVERLAYSUPPORT2;
#endif  // DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN7)

typedef enum _DXGK_GDIROP_BITBLT
{
    DXGK_GDIROP_INVALID     = 0,
    DXGK_GDIROP_SRCCOPY     = 1,            // Dst = Src
    DXGK_GDIROP_SRCINVERT   = 2,            // Dst = Dst ^ Src
    DXGK_GDIROP_SRCAND      = 3,            // Dst = Dst & Src
    DXGK_GDIROP_SRCOR       = 4,            // Dst = Dst | Src
    DXGK_GDIROP_ROP3        = 5,            // The high word contains the GDI Rop3 code
} DXGK_GDIROP_BITBLT;

typedef struct _DXGK_GDIARG_BITBLT
{
    RECT                SrcRect;                // Source rectangle
    RECT                DstRect;                // Destination rectangle
    UINT                SrcAllocationIndex;     // Index in the allocation list
    UINT                DstAllocationIndex;     // Index in the allocation list
    UINT                NumSubRects;            // Number of sub-rects in the destination space.
    RECT*               pSubRects;              // Pointer to sub-rects in the destination space
    WORD                Rop;                    // DXGK_GDIROP_BITBLT
    WORD                Rop3;                   // GDI Rop3 code when Rop == DXGK_GDIROP_ROP3
    UINT                SrcPitch;               // Source surface pitch (in bytes)
    UINT                DstPitch;               // Destination surface pitch (in bytes)
} DXGK_GDIARG_BITBLT;

typedef enum _DXGK_GDIROP_COLORFILL
{
    DXGK_GDIROPCF_INVALID   = 0,
    DXGK_GDIROPCF_PATCOPY   = 1,        // Dst = Color
    DXGK_GDIROPCF_PATINVERT = 2,        // Dst = Dst ^ Color
    DXGK_GDIROPCF_PDXN      = 3,        // Dst = ~(Color ^ Dst)
    DXGK_GDIROPCF_DSTINVERT = 4,        // Dst = ~Dst
    DXGK_GDIROPCF_PATAND    = 5,        // Dst = Dst & Color
    DXGK_GDIROPCF_PATOR     = 6,        // Dst = Dst | Color
    DXGK_GDIROPCF_ROP3      = 7,        // The high word contains the GDI Rop3 code
} DXGK_GDIROP_COLORFILL;

typedef struct _DXGK_GDIARG_STRETCHBLT
{
    RECT                SrcRect;                // Source rectangle
    RECT                DstRect;                // Destination rectangle
    UINT                DstAllocationIndex;     // Index in the allocation list
    UINT                SrcAllocationIndex;     // Index in the allocation list
    UINT                NumSubRects;            // Number of sub-rects in the destination space.
    RECT*               pSubRects;              // Pointer to sub-rects in the destination space
    union
    {
        struct
        {
            UINT        Mode    : 16;           // Stretch BLT mode (See MSDN DrvStrechBlt)
            UINT        MirrorX : 1;            // Do mirroring along X axes
            UINT        MirrorY : 1;            // Do mirroring along Y axes
        };
        UINT            Flags;
    };
    UINT                SrcPitch;               // Source surface pitch (in bytes)
} DXGK_GDIARG_STRETCHBLT;

typedef struct _DXGK_GDIARG_COLORFILL
{
    RECT                    DstRect;                // Destination rectangle
    UINT                    DstAllocationIndex;     // Index in the allocation list
    UINT                    NumSubRects;            // Number of sub-rects in the destination space
    RECT*                   pSubRects;              // Pointer to sub-rects in the destination space
    UINT                    Color;                  // Color in the format of the destination surface
    WORD                    Rop;                    // DXGK_GDIROP_COLORFILL
    WORD                    Rop3;                   // GDI Rop3 code when Rop == DXGK_GDIROP_ROP3
} DXGK_GDIARG_COLORFILL;

typedef struct _DXGK_GDIARG_ALPHABLEND
{
    RECT                SrcRect;                // Source rectangle
    RECT                DstRect;                // Destination rectangle
    UINT                SrcAllocationIndex;     // Index in the allocation list
    UINT                DstAllocationIndex;     // Index in the allocation list
    UINT                NumSubRects;            // Number of sub-rects in the destination space.
    RECT*               pSubRects;              // Pointer to sub-rects in the destination space
    BYTE                SourceConstantAlpha;
    BOOLEAN             SourceHasAlpha;
    UINT                SrcPitch;               // Source surface pitch (in bytes)
} DXGK_GDIARG_ALPHABLEND;

typedef struct _D3DKM_TRANSPARENTBLTFLAGS
{
    union
    {
        struct
        {
            UINT    HonorAlpha             : 1;
        };
        UINT        Value;
    };
} D3DKM_TRANSPARENTBLTFLAGS;

typedef struct _DXGK_GDIARG_TRANSPARENTBLT
{
    RECT                SrcRect;                // Source rectangle
    RECT                DstRect;                // Destination rectangle
    UINT                SrcAllocationIndex;     // Index in the allocation list
    UINT                DstAllocationIndex;     // Index in the allocation list
    UINT                Color;                  // Pixels with this color should not be copied to the destination.
    UINT                NumSubRects;            // Number of sub-rects in the destination space.
    RECT*               pSubRects;              // Pointer to sub-rects in the destination space
    D3DKM_TRANSPARENTBLTFLAGS Flags;
    UINT                SrcPitch;               // Source surface pitch (in bytes)
} DXGK_GDIARG_TRANSPARENTBLT;

#define D3DKM_INVALID_GAMMA_INDEX 0xFFFFFFFF

typedef struct _DXGK_GDIARG_CLEARTYPEBLEND
{
    RECT  DstRect;              // Destination rectangle
    UINT  TmpSurfAllocationIndex;
    UINT  GammaSurfAllocationIndex;
    UINT  AlphaSurfAllocationIndex;
    UINT  DstAllocationIndex;
    INT   DstToAlphaOffsetX;    // Used to transforms rectangles from the destination surface space to the alpha surface space.
    INT   DstToAlphaOffsetY;    // Used to transforms rectangles from the destination surface space to the alpha surface space.
    UINT  Color;                // Foreground color in a 32-bit surface format (gamma corrected)
    UINT  Gamma;                // Value to pick the gamma and inverse gamma tables
    UINT  NumSubRects;          // Number of sub-rects in the destination space.
    RECT* pSubRects;            // Pointer to sub-rects in the destination space
    UINT  AlphaSurfPitch;       // Alpha surface pitch (in bytes)
    UINT  Color2;               // Foreground color in a 32-bit surface format (not gamma corrected)
} DXGK_GDIARG_CLEARTYPEBLEND;

typedef enum _DXGK_RENDERKM_OPERATION
{
    DXGK_GDIOP_BITBLT           = 1,
    DXGK_GDIOP_COLORFILL        = 2,
    DXGK_GDIOP_ALPHABLEND       = 3,
    DXGK_GDIOP_STRETCHBLT       = 4,
    DXGK_GDIOP_ESCAPE           = 5,                // Driver ignores this command
    DXGK_GDIOP_TRANSPARENTBLT   = 6,
    DXGK_GDIOP_CLEARTYPEBLEND   = 7,
} DXGK_RENDERKM_OPERATION;

typedef struct _DXGK_RENDERKM_COMMAND
{
    DXGK_RENDERKM_OPERATION     OpCode;         // Command OpCode
    UINT                        CommandSize;    // Number of bytes to the next command from the start of DXGK_RENDERKM_COMMAND
    union
    {
        DXGK_GDIARG_BITBLT          BitBlt;
        DXGK_GDIARG_COLORFILL       ColorFill;
        DXGK_GDIARG_ALPHABLEND      AlphaBlend;
        DXGK_GDIARG_STRETCHBLT      StretchBlt;
        DXGK_GDIARG_TRANSPARENTBLT  TransparentBlt;
        DXGK_GDIARG_CLEARTYPEBLEND  ClearTypeBlend;
    } Command;
} DXGK_RENDERKM_COMMAND;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_RENDER)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_RENDERKM(
    IN_CONST_HANDLE             hContext,
    INOUT_PDXGKARG_RENDER       pRenderKmArgs
    );

#endif // DXGKDDI_INTERFACE_VERSION

typedef struct _DXGKARG_STOPCAPTURE
{
    HANDLE                      hAllocation;
} DXGKARG_STOPCAPTURE;

typedef _In_ CONST DXGKARG_STOPCAPTURE*     IN_CONST_PDXGKARG_STOPCAPTURE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_STOPCAPTURE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_STOPCAPTURE(
    IN_CONST_HANDLE                 hAdapter,
    IN_CONST_PDXGKARG_STOPCAPTURE   pStopCapture
    );

//
// Definitions for reporting the progress in the kernel mode display
// only device present.
//
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)

typedef enum _DXGK_PRESENT_DISPLAY_ONLY_PROGRESS_ID
{
    DXGK_PRESENT_DISPLAYONLY_PROGRESS_ID_COMPLETE  = 0,
    DXGK_PRESENT_DISPLAYONLY_PROGRESS_ID_FAILED    = 1,
} DXGK_PRESENT_DISPLAY_ONLY_PROGRESS_ID;

typedef struct _DXGKARGCB_PRESENT_DISPLAYONLY_PROGRESS
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID        VidPnSourceId;
    DXGK_PRESENT_DISPLAY_ONLY_PROGRESS_ID ProgressId;
} DXGKARGCB_PRESENT_DISPLAYONLY_PROGRESS;

typedef _In_ CONST DXGKARGCB_PRESENT_DISPLAYONLY_PROGRESS*  IN_CONST_PDXGKARGCB_PRESENT_DISPLAYONLY_PROGRESS;

#endif // DXGKDDI_INTERFACE_VERSION

//
// Definition for Scheduler Interrupt Event Type.
//
typedef enum _DXGK_INTERRUPT_TYPE
{
    DXGK_INTERRUPT_DMA_COMPLETED                = 1,
    DXGK_INTERRUPT_DMA_PREEMPTED                = 2,
    DXGK_INTERRUPT_CRTC_VSYNC                   = 3,
    DXGK_INTERRUPT_DMA_FAULTED                  = 4,

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    DXGK_INTERRUPT_DISPLAYONLY_VSYNC            = 5,
    DXGK_INTERRUPT_DISPLAYONLY_PRESENT_PROGRESS = 6,
    DXGK_INTERRUPT_CRTC_VSYNC_WITH_MULTIPLANE_OVERLAY = 7,
#endif // DXGKDDI_INTERFACE_VERSION

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
    DXGK_INTERRUPT_MICACAST_CHUNK_PROCESSING_COMPLETE = 8,
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
    DXGK_INTERRUPT_DMA_PAGE_FAULTED = 9,
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
    DXGK_INTERRUPT_CRTC_VSYNC_WITH_MULTIPLANE_OVERLAY2 = 10,
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
    DXGK_INTERRUPT_MONITORED_FENCE_SIGNALED = 11,
    DXGK_INTERRUPT_HWQUEUE_PAGE_FAULTED = 12,
    DXGK_INTERRUPT_HWCONTEXTLIST_SWITCH_COMPLETED = 13,
    DXGK_INTERRUPT_PERIODIC_MONITORED_FENCE_SIGNALED = 14,
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

} DXGK_INTERRUPT_TYPE;


#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
typedef struct _DXGK_MULTIPLANE_OVERLAY_VSYNC_INFO
{
    DWORD                                LayerIndex;
    BOOL                                 Enabled;
    PHYSICAL_ADDRESS                     PhysicalAddress;
    DXGK_MULTIPLANE_OVERLAY_ATTRIBUTES   PlaneAttributes;
} DXGK_MULTIPLANE_OVERLAY_VSYNC_INFO;
#endif // DXGKDDI_INTERFACE_VERSION

typedef struct _DXGKCB_NOTIFY_INTERRUPT_DATA_FLAGS
{
    union
    {
        struct
        {
            UINT            ValidPhysicalAdapterMask : 1; // 0x00000001
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
            UINT            HsyncFlipCompletion      : 1; // 0x00000002
            UINT            Reserved                 :30; // 0xFFFFFFFC
#else
            UINT            Reserved                 :31; // 0xFFFFFFFE
#endif
        };
        UINT                Value;
    };
} DXGKCB_NOTIFY_INTERRUPT_DATA_FLAGS;

typedef struct _DXGKCB_NOTIFY_MPO_VSYNC_FLAGS
{
    union
    {
        struct
        {
            UINT            PostPresentNeeded        : 1; // 0x00000001
            UINT            Reserved                 :31; // 0xFFFFFFFE
        };
        UINT                Value;
    };
} DXGKCB_NOTIFY_MPO_VSYNC_FLAGS;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
typedef struct _DXGK_MULTIPLANE_OVERLAY_VSYNC_INFO2
{
    DWORD                                LayerIndex;
    ULONGLONG                            PresentId;
	DXGKCB_NOTIFY_MPO_VSYNC_FLAGS        Flags;
} DXGK_MULTIPLANE_OVERLAY_VSYNC_INFO2;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)

typedef struct _DXGKARGCB_NOTIFY_INTERRUPT_DATA
{
    DXGK_INTERRUPT_TYPE  InterruptType;        // in: interrupt type
    union
    {
        struct
        {
            UINT             SubmissionFenceId;         // in: submission id of completed command.
            UINT             NodeOrdinal;               // in: Node ordinal of engine generating the notification.
            UINT             EngineOrdinal;             // in: Engine ordinal of engine generating the notification.
        } DmaCompleted;
        struct
        {
            UINT             PreemptionFenceId;    // in: submission id of preemption request.
            UINT             LastCompletedFenceId; // in: submission id of last completed command before preemption.
            UINT             NodeOrdinal;          // in: Node ordinal of engine generating the notification.
            UINT             EngineOrdinal;        // in: Engine ordinal of engine generating the notification.
        } DmaPreempted;
        struct
        {
            UINT             FaultedFenceId;       // in: submission id of faulted command.
            NTSTATUS         Status;               // in: status of fault
            UINT             NodeOrdinal;          // in: Node ordinal of engine generating the notification.
            UINT             EngineOrdinal;        // in: Engine ordinal of engine generating the notification.
        } DmaFaulted;
        struct
        {
            D3DDDI_VIDEO_PRESENT_TARGET_ID VidPnTargetId;       // in: VidPnTarget id (where vsync occurs).
            PHYSICAL_ADDRESS               PhysicalAddress;     // in: Physical Address of displaying buffer.
            UINT                           PhysicalAdapterMask; // in: Physical adapter mask (where vsync occurs).
                                                                //     (Must set Flags.ValidPhysicalAdapterMask as well)
        } CrtcVsync;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
        struct
        {
            D3DDDI_VIDEO_PRESENT_TARGET_ID VidPnTargetId;       // in: VidPnTarget id (where vsync occurs).
        } DisplayOnlyVsync;
        struct
        {
            D3DDDI_VIDEO_PRESENT_TARGET_ID     VidPnTargetId;
            UINT                               PhysicalAdapterMask;
            UINT                               MultiPlaneOverlayVsyncInfoCount;
            DXGK_MULTIPLANE_OVERLAY_VSYNC_INFO *pMultiPlaneOverlayVsyncInfo;
        } CrtcVsyncWithMultiPlaneOverlay;

        DXGKARGCB_PRESENT_DISPLAYONLY_PROGRESS DisplayOnlyPresentProgress;
#endif // DXGKDDI_INTERFACE_VERSION

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
        struct
        {
            D3DDDI_VIDEO_PRESENT_TARGET_ID VidPnTargetId;
            DXGK_MIRACAST_CHUNK_INFO       ChunkInfo;
            PVOID                          pPrivateDriverData;
            UINT                           PrivateDataDriverSize;
            NTSTATUS                       Status;
        } MiracastEncodeChunkCompleted;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
        struct
        {
            UINT                        FaultedFenceId;         // in: submission id of faulted command. If the faulted fence could not be determined reliably,
                                                                // PageFaultFlags should have DXGK_PAGE_FAULT_FENCE_INVALID flag set.
            UINT64                      FaultedPrimitiveAPISequenceNumber; // in: when per draw fence write is enabled, identifies the draw that caused the page fault, or DXGK_PRIMITIVE_API_SEQUENCE_NUMBER_UNKNOWN if such information is not available.           
            DXGK_RENDER_PIPELINE_STAGE  FaultedPipelineStage;   // in: render pipeline stage during which the fault was generated, or DXGK_RENDER_PIPELINE_STAGE_UNKNOWN if such information is not available.
            UINT                        FaultedBindTableEntry;  // in: a bind table index of a resource being accessed at the time of the fault, or DXGK_BIND_TABLE_ENTRY_UNKNOWN if such information is not available.
            DXGK_PAGE_FAULT_FLAGS       PageFaultFlags;         // in: flags specifying the nature of the page fault and recovery policy
            D3DGPU_VIRTUAL_ADDRESS      FaultedVirtualAddress;  // in: VA of fault, or 0 if the fault has another cause. In the latter case, FaultErrorCode field should be used to describe the GPU error.
            UINT                        NodeOrdinal;            // in: Node ordinal of engine generating the notification.
            UINT                        EngineOrdinal;          // in: Engine ordinal of engine generating the notification.
            UINT                        PageTableLevel;         // in: Described page table level which the faulting operation was attempted on.
            DXGK_FAULT_ERROR_CODE       FaultErrorCode;         // in: Structure that contains error code describing the fault.
            HANDLE                      FaultedProcessHandle;   // in: DXGK process handle of the process that generated page fault, or NULL if the faulted
                                                                // process could not be determined.
        } DmaPageFaulted;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
        struct
        {
            D3DDDI_VIDEO_PRESENT_TARGET_ID                VidPnTargetId;
            UINT                                          PhysicalAdapterMask;
            UINT                                          MultiPlaneOverlayVsyncInfoCount;
            _Field_size_(MultiPlaneOverlayVsyncInfoCount) DXGK_MULTIPLANE_OVERLAY_VSYNC_INFO2 *pMultiPlaneOverlayVsyncInfo;
            ULONGLONG                                     GpuFrequency;
            ULONGLONG                                     GpuClockCounter;
        } CrtcVsyncWithMultiPlaneOverlay2;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
        struct
        {
            UINT    NodeOrdinal;          // in: Node ordinal of engine generating the notification.
            UINT    EngineOrdinal;        // in: Engine ordinal of engine generating the notification.
        } MonitoredFenceSignaled;

        struct
        {
            UINT    NodeOrdinal;            // in: Node ordinal of engine generating the notification.
            UINT    EngineOrdinal;          // in: Engine ordinal of engine generating the notification.
            UINT64  ContextSwitchFence;     // in: Context switch fence used to perform this switch operation.
        } HwContextListSwitchCompleted;

        struct
        {
            UINT64                      FaultedFenceId;       // in: HW queue progress fence ID of the faulted command. If the faulted fence could not be determined reliably,
                                                              // PageFaultFlags should have DXGK_PAGE_FAULT_FENCE_INVALID flag set.
            D3DGPU_VIRTUAL_ADDRESS      FaultedVirtualAddress;  // in: VA of fault, or 0 if the fault has another cause. In the latter case, FaultErrorCode field should be used to describe the GPU error.
            UINT64                      FaultedPrimitiveAPISequenceNumber; // in: when per draw fence write is enabled, identifies the draw that caused the page fault, or DXGK_PRIMITIVE_API_SEQUENCE_NUMBER_UNKNOWN if such information is not available.           

            union
            {
                HANDLE                  FaultedHwQueue;         // in: when DXGK_PAGE_FAULT_FENCE_INVALID is not set,
                                                                // specifies the handle of the HW queue that generated the fault.
                HANDLE                  FaultedHwContext;       // in: when DXGK_PAGE_FAULT_FENCE_INVALID and DXGK_PAGE_FAULT_HW_CONTEXT_VALID are set,
                                                                // specifies the handle of the HW context that generated the fault.
                HANDLE                  FaultedProcessHandle;   // in: when DXGK_PAGE_FAULT_FENCE_INVALID and DXGK_PAGE_FAULT_PROCESS_HANDLE_VALID are set,
                                                                // specifies the handle of the process that generated the fault.
            };

            UINT                        NodeOrdinal;          // in: Node ordinal of engine generating the notification.
            UINT                        EngineOrdinal;        // in: Engine ordinal of engine generating the notification.

            DXGK_RENDER_PIPELINE_STAGE  FaultedPipelineStage;   // in: render pipeline stage during which the fault was generated, or DXGK_RENDER_PIPELINE_STAGE_UNKNOWN if such information is not available.
            UINT                        FaultedBindTableEntry;  // in: a bind table index of a resource being accessed at the time of the fault, or DXGK_BIND_TABLE_ENTRY_UNKNOWN if such information is not available.
            DXGK_PAGE_FAULT_FLAGS       PageFaultFlags;         // in: flags specifying the nature of the page fault and recovery policy
            UINT                        PageTableLevel;         // in: Described page table level which the faulting operation was attempted on.
            DXGK_FAULT_ERROR_CODE       FaultErrorCode;         // in: Structure that contains error code describing the fault.
        } HwQueuePageFaulted;

        struct
        {
            D3DDDI_VIDEO_PRESENT_TARGET_ID    VidPnTargetId;    // in: The display signaling the monitored fence.
            UINT                              NotificationID;   // in: The notification id as multiple can be attached to one VidPnSource.
        } PeriodicMonitoredFenceSignaled;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

        struct
        {
            UINT            Reserved[16];
        } Reserved;
    };
    DXGKCB_NOTIFY_INTERRUPT_DATA_FLAGS Flags;      // in: event flags
} DXGKARGCB_NOTIFY_INTERRUPT_DATA;

typedef _Inout_ DXGKARGCB_NOTIFY_INTERRUPT_DATA*     IN_CONST_PDXGKARGCB_NOTIFY_INTERRUPT_DATA;

// Device Driver Interface fence update at ISR.
//
typedef
    _Function_class_DXGK_(DXGKCB_NOTIFY_INTERRUPT)
    _IRQL_requires_(HIGH_LEVEL) // HIGH_LEVEL is best approximation of DIRQL
VOID (APIENTRY CALLBACK *DXGKCB_NOTIFY_INTERRUPT)(
    IN_CONST_HANDLE hAdapter, IN_CONST_PDXGKARGCB_NOTIFY_INTERRUPT_DATA
    );

// Device Driver Interface fence update at DPC.
//
typedef
    _Function_class_DXGK_(DXGKCB_NOTIFY_DPC)
    _IRQL_requires_(DISPATCH_LEVEL)
VOID
(APIENTRY CALLBACK *DXGKCB_NOTIFY_DPC)(
    IN_CONST_HANDLE hAdapter
    );

typedef struct _DXGK_OPENALLOCATIONINFO
{
    D3DKMT_HANDLE   hAllocation;                        // in: dxg assigned per Device handle
    VOID*           pPrivateDriverData;                 // in/out: Private data for each allocation allocated by the user mode driver
    UINT            PrivateDriverDataSize;              // in: Size of the private data
    HANDLE          hDeviceSpecificAllocation;          // out: driver set it
} DXGK_OPENALLOCATIONINFO;

typedef struct _DXGK_OPENALLOCATIONFLAGS
{
    union
    {
        struct
        {
            UINT    Create          : 1;    // 0x00000001       // Indicates that this allocation is being created, if not set then allocation is being opened
            UINT    ReadOnly        : 1;    // 0x00000002       // Indicates that this allocation is being opened read-only.
            UINT    Reserved        :30;    // 0xFFFFFFFC
        };
        UINT Value;
    };
} DXGK_OPENALLOCATIONFLAGS;

typedef struct _DXGKARG_OPENALLOCATION
{
    UINT                            NumAllocations;
    DXGK_OPENALLOCATIONINFO*        pOpenAllocation;
    VOID*                           pPrivateDriverData;
    UINT                            PrivateDriverSize;
    DXGK_OPENALLOCATIONFLAGS        Flags;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    UINT                            SubresourceIndex;
    // The following data is set by the driver for allocations which have all the following properties:
    // - shared;
    // - GDI compatible
    // - in the aperture segment
    // - linear
    // - the driver can texture from the allocation
    //
    SIZE_T                          SubresourceOffset;  // Out. Offset in bytes from the start of the allocation.
    UINT                            Pitch;              // Out. Pitch for allocations.
#endif
} DXGKARG_OPENALLOCATION;

typedef _In_ CONST DXGKARG_OPENALLOCATION*   IN_CONST_PDXGKARG_OPENALLOCATION;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_OPENALLOCATIONINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_OPENALLOCATIONINFO(
    IN_CONST_HANDLE                         hDevice,
    IN_CONST_PDXGKARG_OPENALLOCATION        pOpenAllocation
    );

typedef struct _DXGKARG_CLOSEALLOCATION
{
    UINT            NumAllocations;
    CONST HANDLE*   pOpenHandleList;    //in: hDeviceSpecificAllocation list
} DXGKARG_CLOSEALLOCATION;

typedef _In_    CONST DXGKARG_CLOSEALLOCATION*  IN_CONST_PDXGKARG_CLOSEALLOCATION;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_CLOSEALLOCATION)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_CLOSEALLOCATION(
    IN_CONST_HANDLE                     hDevice,
    IN_CONST_PDXGKARG_CLOSEALLOCATION   pCloseAllocation
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_DESTROYDEVICE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_DESTROYDEVICE(
    IN_CONST_HANDLE     hDevice
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_DESTROYCONTEXT)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_DESTROYCONTEXT(
    IN_CONST_HANDLE     hContext
    );

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_DESTROYHWCONTEXT)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_DESTROYHWCONTEXT(
    IN_CONST_HANDLE     hHwContext
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_DESTROYHWQUEUE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_DESTROYHWQUEUE(
    IN_CONST_HANDLE     hHwQueue
    );

#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

typedef _In_          D3DKMT_HANDLE             IN_D3DKMT_HANDLE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKCB_GETHANDLEPARENT)
    _IRQL_requires_(PASSIVE_LEVEL)
D3DKMT_HANDLE
(APIENTRY CALLBACK *DXGKCB_GETHANDLEPARENT)(IN_D3DKMT_HANDLE hAllocation);

typedef enum _DXGK_HANDLE_TYPE
{
    DXGK_HANDLE_ALLOCATION  = 1,
    DXGK_HANDLE_RESOURCE    = 2,
} DXGK_HANDLE_TYPE;

typedef struct _DXGKCB_GETHANDLEDATAFLAGS
{
    union
    {
        struct
        {
            UINT                DeviceSpecific  : 1;    // 0x00000001
            UINT                Reserved        :31;    // 0xFFFFFFFE
        };
        UINT Value;
    };
} DXGKCB_GETHANDLEDATAFLAGS;

typedef struct _DXGKARGCB_GETHANDLEDATA
{
    D3DKMT_HANDLE           hObject;
    DXGK_HANDLE_TYPE        Type;
    DXGKCB_GETHANDLEDATAFLAGS Flags;
} DXGKARGCB_GETHANDLEDATA;

typedef _In_    CONST DXGKARGCB_GETHANDLEDATA*  IN_CONST_PDXGKARGCB_GETHANDLEDATA;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKCB_GETHANDLEDATA)
    _IRQL_requires_(PASSIVE_LEVEL)
VOID*
(APIENTRY CALLBACK *DXGKCB_GETHANDLEDATA)(IN_CONST_PDXGKARGCB_GETHANDLEDATA);

typedef VOID * DXGKARG_RELEASE_HANDLE;
typedef DXGKARG_RELEASE_HANDLE * PDXGKARG_RELEASE_HANDLE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKCB_ACQUIREHANDLEDATA)
    _IRQL_requires_max_(APC_LEVEL)
VOID*
(APIENTRY CALLBACK *DXGKCB_ACQUIREHANDLEDATA)(IN_CONST_PDXGKARGCB_GETHANDLEDATA, _Out_ PDXGKARG_RELEASE_HANDLE);

typedef struct _DXGKARGCB_RELEASEHANDLEDATA
{
    DXGKARG_RELEASE_HANDLE  ReleaseHandle;
    DXGK_HANDLE_TYPE        Type;
} DXGKARGCB_RELEASEHANDLEDATA;

typedef _In_ CONST DXGKARGCB_RELEASEHANDLEDATA IN_CONST_DXGKARGCB_RELEASEHANDLEDATA;

typedef
    _Function_class_DXGK_(DXGKCB_RELEASEHANDLEDATA)
    _IRQL_requires_max_(APC_LEVEL)
VOID
(APIENTRY CALLBACK *DXGKCB_RELEASEHANDLEDATA)(IN_CONST_DXGKARGCB_RELEASEHANDLEDATA);

typedef struct _DXGKARGCB_ENUMHANDLECHILDREN
{
    D3DKMT_HANDLE   hObject;
    UINT            Index;
} DXGKARGCB_ENUMHANDLECHILDREN;

typedef _In_    CONST DXGKARGCB_ENUMHANDLECHILDREN*  IN_CONST_PDXGKARGCB_ENUMHANDLECHILDREN;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKCB_ENUMHANDLECHILDREN)
    _IRQL_requires_(PASSIVE_LEVEL)
D3DKMT_HANDLE
(APIENTRY CALLBACK *DXGKCB_ENUMHANDLECHILDREN)(IN_CONST_PDXGKARGCB_ENUMHANDLECHILDREN);

typedef struct _DXGKARGCB_GETCAPTUREADDRESS
{
    D3DKMT_HANDLE      hAllocation;          // in:  Allocation handle
    UINT               SegmentId;            // out: Segment ID of capture buffer
    PHYSICAL_ADDRESS   PhysicalAddress;      // out: Physical address of capture buffer
} DXGKARGCB_GETCAPTUREADDRESS;

typedef _Inout_  DXGKARGCB_GETCAPTUREADDRESS*  INOUT_PDXGKARGCB_GETCAPTUREADDRESS;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKCB_GETCAPTUREADDRESS)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY CALLBACK *DXGKCB_GETCAPTUREADDRESS)(INOUT_PDXGKARGCB_GETCAPTUREADDRESS);

typedef struct _DXGK_DEVICEINFOFLAGS
{
    union
    {
        struct
        {
            UINT    GuaranteedDmaBufferContract : 1;    // 0x00000001
            UINT    Reserved                    :31;    // 0xFFFFFFFE
        };
        UINT Value;
    };
 } DXGK_DEVICEINFOFLAGS;

typedef struct _DXGK_DEVICEINFO
{
    UINT        DmaBufferSize;
    UINT        DmaBufferSegmentSet;
    UINT        DmaBufferPrivateDataSize;
    UINT        AllocationListSize;
    UINT        PatchLocationListSize;
    DXGK_DEVICEINFOFLAGS Flags;
} DXGK_DEVICEINFO;

typedef struct _DXGK_CREATEDEVICEFLAGS
{
    union
    {
        struct
        {
            UINT    SystemDevice            :  1;  // 0x00000001
            UINT    GdiDevice               :  1;  // 0x00000002
            UINT    Reserved                : 29;  // 0x7FFFFFFC
            UINT    DXGK_DEVICE_RESERVED0   :  1;  // 0x80000000
        };
        UINT Value;
    };
} DXGK_CREATEDEVICEFLAGS;

typedef struct _DXGKARG_CREATEDEVICE
{
    HANDLE               hDevice;            // in:  Runtime handle/out: Driver handle
    union
    {
        DXGK_CREATEDEVICEFLAGS Flags;        // in:  device creation flags
        DXGK_DEVICEINFO*       pInfo;        // out: device info from driver (obsolate: backward compatibility only)
    };
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
    ULONG   Pasid;                          // in: the owner process PASID for SVM
    HANDLE  hKmdProcess;                    // in:  KMD driver process handle
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
} DXGKARG_CREATEDEVICE;

typedef _Inout_ DXGKARG_CREATEDEVICE*   INOUT_PDXGKARG_CREATEDEVICE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_CREATEDEVICE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_CREATEDEVICE(
    IN_CONST_HANDLE                 hAdapter,
    INOUT_PDXGKARG_CREATEDEVICE     pCreateDevice
    );

typedef struct _DXGK_CREATECONTEXTFLAGS
{
    union
    {
        struct
        {
            UINT    SystemContext           : 1;
            UINT    GdiContext              : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
            UINT    VirtualAddressing       : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
            UINT    SystemProtectedContext  : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)
            UINT    HwQueueSupported        : 1;
            UINT    Reserved                : 27;
#else  // ! DXGKDDI_INTERFACE_VERSION_WDDM2_3
            UINT    Reserved                : 28;
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_3
#else  // ! DXGKDDI_INTERFACE_VERSION_WDDM2_1
            UINT    Reserved                : 29;
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_1
#else  // ! DXGKDDI_INTERFACE_VERSION_WDDM2_0
            UINT    Reserved                : 30;
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_0
        };
        UINT Value;
    };
} DXGK_CREATECONTEXTFLAGS;

#define DXGK_ALLOCATION_LIST_SIZE_GDICONTEXT 256

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

typedef struct _DXGK_CONTEXTINFO_CAPS
{
    union
    {
        struct
        {
            UINT NoPatchingRequired     : 1;
            UINT DriverManagesResidency : 1;
            UINT UseIoMmu               : 1;
            UINT Reserved               : 29;
        };
        UINT Value;
    };
} DXGK_CONTEXTINFO_CAPS;

#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

typedef struct _DXGK_CONTEXTINFO
{
    UINT        DmaBufferSize;
    UINT        DmaBufferSegmentSet;
    UINT        DmaBufferPrivateDataSize;
    UINT        AllocationListSize;
    UINT        PatchLocationListSize;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN7)
    UINT        Reserved;
#endif // DXGKDDI_INTERFACE_VERSION
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
    DXGK_CONTEXTINFO_CAPS   Caps;                       // Describes optional features supported by the context
    ULONG                   PagingCompanionNodeId;      // Zero based node index to use with context paging operations
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
} DXGK_CONTEXTINFO;

typedef struct _DXGKARG_CREATECONTEXT
{
    HANDLE                  hContext;              // in:  Runtime handle/out: Driver handle
    UINT                    NodeOrdinal;           // in:  Node targetted for this context.
    UINT                    EngineAffinity;        // in:  Engine affinity.
    DXGK_CREATECONTEXTFLAGS Flags;                 // in:  Context creation flags.
    VOID*                   pPrivateDriverData;    // in:  Private driver data
    UINT                    PrivateDriverDataSize; // in:  Size of private driver data
    DXGK_CONTEXTINFO        ContextInfo;           // out: context info from driver
} DXGKARG_CREATECONTEXT;

typedef _Inout_ DXGKARG_CREATECONTEXT*   INOUT_PDXGKARG_CREATECONTEXT;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_CREATECONTEXT)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_CREATECONTEXT(
    IN_CONST_HANDLE                 hDevice,
    INOUT_PDXGKARG_CREATECONTEXT    pCreateContext
    );

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

typedef struct _DXGK_HWCONTEXT_CAPS
{
    union
    {
        struct
        {
            UINT UseIoMmu               : 1;
            UINT Reserved               : 31;
        };
        UINT Value;
    };
} DXGK_HWCONTEXT_CAPS;

typedef struct _DXGKARG_CREATEHWCONTEXT
{
    HANDLE                      hHwContext;            // in:  Runtime handle/out: Driver handle
    UINT                        NodeOrdinal;           // in:  Node targetted for this context.
    UINT                        EngineAffinity;        // in:  Engine affinity.
    D3DDDI_CREATEHWCONTEXTFLAGS Flags;                 // in:  Context creation flags.
    UINT                        PrivateDriverDataSize; // in:  Size of private driver data
    _Inout_
    _Field_size_bytes_         (PrivateDriverDataSize)
    VOID*                       pPrivateDriverData;    // in/out:  Private driver data
    DXGK_HWCONTEXT_CAPS         ContextCaps;           // out: context caps from driver
} DXGKARG_CREATEHWCONTEXT;

typedef _Inout_ DXGKARG_CREATEHWCONTEXT*   INOUT_PDXGKARG_CREATEHWCONTEXT;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_CREATEHWCONTEXT)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_CREATEHWCONTEXT(
    IN_CONST_HANDLE                 hDevice,
    INOUT_PDXGKARG_CREATEHWCONTEXT  pCreateContext
    );

typedef struct _DXGKARG_CREATEHWQUEUE
{
    HANDLE                      hHwQueue;              // in:  Runtime handle/out: Driver handle
    D3DDDI_CREATEHWQUEUEFLAGS   Flags;                 // in:  Queue creation flags.
    UINT                        PrivateDriverDataSize; // in:  Size of private driver data
    _Inout_
    _Field_size_bytes_         (PrivateDriverDataSize)
    VOID*                       pPrivateDriverData;    // in/out:  Private driver data
    D3DKMT_HANDLE               hHwQueueProgressFence; // in: Handle to the hardware queue progress fence object.
    VOID*                       HwQueueProgressFenceCPUVirtualAddress;  // in: Read-only mapping of the fence value for the CPU
    D3DGPU_VIRTUAL_ADDRESS      HwQueueProgressFenceGPUVirtualAddress;  // in: Read/write mapping of the fence value for the GPU
} DXGKARG_CREATEHWQUEUE;

typedef _Inout_ DXGKARG_CREATEHWQUEUE*   INOUT_PDXGKARG_CREATEHWQUEUE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_CREATEHWQUEUE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_CREATEHWQUEUE(
    IN_CONST_HANDLE                 hHwContext,
    INOUT_PDXGKARG_CREATEHWQUEUE    pCreateHwQueue
    );

#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

typedef _In_ CONST DXGKARG_SETPALETTE*      IN_CONST_PDXGKARG_SETPALETTE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_SETPALETTE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_SETPALETTE(
    IN_CONST_HANDLE                 hAdapter,
    IN_CONST_PDXGKARG_SETPALETTE    pSetPalette
    );

typedef struct _DXGK_POINTERFLAGS
{
    union
    {
        struct
        {
            UINT    Monochrome      : 1;    // 0x00000001
            UINT    Color           : 1;    // 0x00000002
            UINT    MaskedColor     : 1;    // 0x00000004
            UINT    Reserved        :29;    // 0xFFFFFFF8
        };
        UINT        Value;
    };
} DXGK_POINTERFLAGS;

typedef struct _DXGKARG_SETPOINTERSHAPE
{
    DXGK_POINTERFLAGS               Flags;
    UINT                            Width;
    UINT                            Height;
    UINT                            Pitch;
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;
    CONST VOID*                     pPixels;
    UINT                            XHot;
    UINT                            YHot;
} DXGKARG_SETPOINTERSHAPE;

//
//Flags specifies monochrome or color pointer or color pointer with alpha.
//
//Width is Width of the pointer in pixels.
//
//Height is Height of the pointer in scans.
//
//Pitch is Width of the pointer in bytes.
//
//VidPnSourceId is VidPN source ID of this adapter on which the pointer is being set.
//
//pPixels points to the start of color bitmap size of specified Width and Height
// in 32-bpp ARGB DIB format for non-monochrome pointers, or points to the start of
// monochrome bitmap size of specified Width and Height in 1-bpp DIB format AND mask
// followed by another 1-bpp DIB format XOR mask of the same size for monochrome pointers.
//
//XHot is column on which hot pixel is located from top left of pointer bitmap in pixels.
//
//YHot is row on which hot pixel is located from top left of pointer bitmap in pixels.
//

typedef _In_ CONST DXGKARG_SETPOINTERSHAPE*     IN_CONST_PDXGKARG_SETPOINTERSHAPE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_SETPOINTERSHAPE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_SETPOINTERSHAPE(
    IN_CONST_HANDLE                     hAdapter,
    IN_CONST_PDXGKARG_SETPOINTERSHAPE   pSetPointerShape
    );

typedef struct _DXGK_SETPOINTERPOSITIONFLAGS
{
    union
    {
        struct
        {
            UINT    Visible                 : 1;    // 0x00000001
            UINT    Procedural              : 1;    // 0x00000002
            UINT    Reserved                :30;    // 0xFFFFFFFC
        };
        UINT Value;
    };
} DXGK_SETPOINTERPOSITIONFLAGS;

typedef struct _DXGKARG_SETPOINTERPOSITION
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;
    INT                             X;
    INT                             Y;
    DXGK_SETPOINTERPOSITIONFLAGS    Flags;
} DXGKARG_SETPOINTERPOSITION;

//
//Visible indicates if the pointer should be visible or not.
//X and Y should be ignored by driver if FALSE.
//
//Output is output index of this adapter.
//
//X is Column on which the top left pixel of cursor image is located
//from the top left pixel of the VidPN source in pixels.
//
//Y is Row on which the top left pixel of cusor image is located from
//the top left pixel of the VidPN source in pixels.
//

typedef _In_ CONST DXGKARG_SETPOINTERPOSITION*      IN_CONST_PDXGKARG_SETPOINTERPOSITION;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_SETPOINTERPOSITION)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_SETPOINTERPOSITION(
    IN_CONST_HANDLE                         hAdapter,
    IN_CONST_PDXGKARG_SETPOINTERPOSITION    pSetPointerPosition
    );

typedef enum _DXGK_QUERYADAPTERINFOTYPE
{
    DXGKQAITYPE_UMDRIVERPRIVATE           = 0,
    DXGKQAITYPE_DRIVERCAPS                = 1,
    DXGKQAITYPE_QUERYSEGMENT              = 2,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN7)
    DXGKQAITYPE_RESERVED                  = 3, // _ADVSCH_
    DXGKQAITYPE_QUERYSEGMENT2             = 4, // _ADVSCH_
#endif // DXGKDDI_INTERFACE_VERSION_WIN7
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    DXGKQAITYPE_QUERYSEGMENT3             = 5,
    DXGKQAITYPE_NUMPOWERCOMPONENTS        = 6,
    DXGKQAITYPE_POWERCOMPONENTINFO        = 7,
    DXGKQAITYPE_PREFERREDGPUNODE          = 8,
#endif // DXGKDDI_INTERFACE_VERSION_WIN8
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
    DXGKQAITYPE_POWERCOMPONENTPSTATEINFO  = 9,
    DXGKQAITYPE_HISTORYBUFFERPRECISION    = 10,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM1_3
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
    DXGKQAITYPE_QUERYSEGMENT4             = 11,
    DXGKQAITYPE_SEGMENTMEMORYSTATE        = 12,
    DXGKQAITYPE_GPUMMUCAPS                = 13,
    DXGKQAITYPE_PAGETABLELEVELDESC        = 14,
    DXGKQAITYPE_PHYSICALADAPTERCAPS       = 15,
    DXGKQAITYPE_DISPLAY_DRIVERCAPS_EXTENSION    = 16,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_0
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
    DXGKQAITYPE_INTEGRATED_DISPLAY_DESCRIPTOR   = 17,
    DXGKQAITYPE_UEFIFRAMEBUFFERRANGES           = 18,
    DXGKQAITYPE_QUERYCOLORIMETRYOVERRIDES       = 19,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_2
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)
    DXGKQAITYPE_DISPLAYID_DESCRIPTOR   = 20,
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_3
} DXGK_QUERYADAPTERINFOTYPE;

typedef struct _DXGK_GAMMARAMPCAPS
{
    union
    {
        struct
        {
            UINT    Gamma_Rgb256x3x16  : 1;    // 0x00000001
            UINT    Reserved           :31;    // 0xFFFFFFFE
        };
        UINT        Value;
    };
} DXGK_GAMMARAMPCAPS;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

typedef struct _DXGK_COLORTRANSFORMCAPS
{
    union
    {
        struct
        {
            UINT    Gamma_Rgb256x3x16             : 1;    // 0x00000001
            UINT    Gamma_Dxgi1                   : 1;    // 0x00000002

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)

            UINT    Transform_3x4Matrix           : 1;    // 0x00000004
            UINT    Transform_3x4Matrix_WideColor : 1;    // 0x00000008
            UINT    Transform_3x4Matrix_HighColor : 1;    // 0x00000010
            UINT    Reserved                      :27;    // 0xFFFFFFE0

#else // DXGKDDI_INTERFACE_VERSION_WDDM2_3

            UINT    Reserved                      :30;    // 0xFFFFFFFC

#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_3
        };
        UINT        Value;
    };
} DXGK_COLORTRANSFORMCAPS;

#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_2


#define DXGK_TEXTURE_SIZE_SHIFT 11

typedef struct _DXGK_PRESENTATIONCAPS
{
    union
    {
        struct
        {
            UINT    NoScreenToScreenBlt             : 1;    // Driver does not support kernel mode Present within the same allocation
            UINT    NoOverlapScreenBlt              : 1;    // Driver does not support kernel mode Present within the same allocation with overlapped SrcRect and DstRect
            UINT    SupportKernelModeCommandBuffer  : 1;    // Driver supports RenderKm DDI
            UINT    NoSameBitmapAlphaBlend          : 1;    // Driver cannot support AlphaBlend when source and destination allocations are the same.
            UINT    NoSameBitmapStretchBlt          : 1;    // Driver cannot support StretchBlt when source and destination allocations are the same.
            UINT    NoSameBitmapTransparentBlt      : 1;    // Driver cannot support TransparentBlt when source and destination allocations are the same.
            UINT    NoSameBitmapOverlappedAlphaBlend: 1;    // Driver cannot support AlphaBlend when source and destination allocations are the same and
                                                            // source and destination rectangles overlap.
            UINT    NoSameBitmapOverlappedStretchBlt: 1;    // Driver cannot support StretchBlt when source and destination allocations are the same and
                                                            // source and destination rectangles overlap.
            UINT    DriverSupportsCddDwmInterop     : 1;    // Driver does not support hardware GDI acceleration, but supports Cdd-Dwm interop.
            UINT    Reserved0                       : 1;
            UINT    AlignmentShift                  : 4;    // Driver requires Blt surface pitch alignment to be (1 << AlignmentShift) bytes. Must be >= 2.
            UINT    MaxTextureWidthShift            : 3;    // Max supported texture width is 2 ^ (MaxTextureWidth + DXGK_TEXTURE_SIZE_SHIFT) texels
            UINT    MaxTextureHeightShift           : 3;    // Max supported texture height is 2 ^ (MaxTextureHeight + DXGK_TEXTURE_SIZE_SHIFT) texels
            UINT    SupportAllBltRops               : 1;    // Driver supports all GDI ROP3 operations in BitBlt and ColorFill
            UINT    SupportMirrorStretchBlt         : 1;    // Driver supports StretchBlt in mirror mode
            UINT    SupportMonoStretchBltModes      : 1;    // Driver supports BLACKONWHITE and WHITEONBLACK StretchBlt modes
            UINT    StagingRectStartPitchAligned    : 1;    // Driver requires the staging rect top/left point in the cpu visible surface to be pitch aligned (left = 0).
            UINT    NoSameBitmapBitBlt              : 1;    // Driver cannot support BitBlt when source and destination allocations are the same.
            UINT    NoSameBitmapOverlappedBitBlt    : 1;    // Driver cannot support BitBlt when source and destination allocations are the same and
                                                            // source and destination rectangles overlap.
            UINT    Reserved1                       : 1;
            UINT    NoTempSurfaceForClearTypeBlend  : 1;    // The driver does not need the temporary surface for ClearType blend
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
            UINT    SupportSoftwareDeviceBitmaps    : 1;    // Driver supports D3DKMDT_GDISURFACE_TEXTURE_CPUVISIBLE redirection bitmaps.
            UINT    NoCacheCoherentApertureMemory   : 1;    // Driver does not support cache coherent aperture memory.
            UINT    SupportLinearHeap               : 1;    // Driver supports linear heap allocation from staging surfaces.
            UINT    Reserved                        : 1;
#else
            UINT    Reserved                        : 4;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
        };
        UINT        Value;
    };
} DXGK_PRESENTATIONCAPS;

typedef struct _DXGK_FLIPCAPS
{
    union
    {
        struct
        {
            UINT    FlipOnVSyncWithNoWait : 1; // Support Flip on vsync via command buffer without wait.
            UINT    FlipOnVSyncMmIo       : 1; // Support Flip as mmio at vsync interrupt.
            UINT    FlipInterval          : 1; // Support FLIPINTERVAL_TWO, _THREE, _FOUR.
            UINT    FlipImmediateMmIo     : 1; // Support Flip as mmio immediate.
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
            UINT    FlipIndependent       : 1; // Support MMIO flip to redirected surfaces bypassing DMW Present.
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
            UINT    DdiPresentForIFlip    : 1; // Call DxgkDdiPresent when independent flip Present might be issued.
            UINT    FlipImmediateOnHSync  : 1; // Driver supports SetVidPnSourceAddress FlipImmediate flag with no tearing between HSync intervals.
            UINT    Reserved              :25;
#else
            UINT    Reserved              :27;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
#else
            UINT    Reserved              :28;
#endif // DXGKDDI_INTERFACE_VERSION
        };
        UINT        Value;
    };
} DXGK_FLIPCAPS;

typedef struct _DXGK_VIDSCHCAPS
{
    union
    {
        struct
        {
            UINT    MultiEngineAware       :1;
            UINT    VSyncPowerSaveAware    :1;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)

            UINT    PreemptionAware        :1;
            UINT    NoDmaPatching          :1;
            UINT    CancelCommandAware     :1;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

            UINT    No64BitAtomics         :1;
            UINT    LowIrqlPreemptCommand  :1;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)

            UINT    HwQueuePacketCap       :4;  // maximum number of DMA packets allowed to be queued to a node
            UINT    Reserved               :21;

#else

            UINT    Reserved               :25;

#endif // !(DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)

#else

            UINT    Reserved               :27;

#endif // !(DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

#else

            UINT    Reserved               :30;

#endif // !(DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
        };
        UINT        Value;
    };
} DXGK_VIDSCHCAPS;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

typedef enum _DXGK_PAGETABLEUPDATEMODE
{
   DXGK_PAGETABLEUPDATE_CPU_VIRTUAL,
   DXGK_PAGETABLEUPDATE_GPU_VIRTUAL,
   DXGK_PAGETABLEUPDATE_GPU_PHYSICAL,
} DXGK_PAGETABLEUPDATEMODE;

typedef struct _DXGK_PAGETABLEUPDATEADDRESS
{
    union
    {
        PVOID                   CpuVirtual;
        D3DGPU_PHYSICAL_ADDRESS GpuPhysical;
        D3DGPU_VIRTUAL_ADDRESS  GpuVirtual;
    };
} DXGK_PAGETABLEUPDATEADDRESS;

typedef struct _DXGK_PAGE_TABLE_LEVEL_DESC
{
    UINT    PageTableIndexBitCount;
    UINT    PageTableSegmentId;
    UINT    PagingProcessPageTableSegmentId;
    UINT    PageTableSizeInBytes;
    UINT    PageTableAlignmentInBytes;          // 0 means the page size of the memory segment
} DXGK_PAGE_TABLE_LEVEL_DESC;

typedef struct _DXGK_UPDATEPAGETABLEFLAGS
{
   UINT    Repeat          : 1;
   UINT    InitialUpdate   : 1;
   UINT    NotifyEviction  : 1;
   UINT    Use64KBPages    : 1;
   UINT    Reserved        : 28;
} DXGK_UPDATEPAGETABLEFLAGS;

typedef struct _DXGK_QUERYGPUMMUCAPSIN
{
    UINT  PhysicalAdapterIndex;
} DXGK_QUERYGPUMMUCAPSIN;

typedef struct _DXGK_QUERYPAGETABLELEVELDESCIN
{
    WORD  LevelIndex; 
    WORD  PhysicalAdapterIndex;
} DXGK_QUERYPAGETABLELEVELDESCIN;

typedef struct _DXGK_QUERYHISTORYBUFFERPRECISIONIN
{
    UINT  PhysicalAdapterIndex;
} DXGK_QUERYHISTORYBUFFERPRECISIONIN;

typedef struct _DXGK_GPUMMUCAPS
{
    union
    {
        struct
        {
            UINT ReadOnlyMemorySupported                : 1;
            UINT NoExecuteMemorySupported               : 1; 
            UINT ZeroInPteSupported                     : 1;
            UINT ExplicitPageTableInvalidation          : 1; 
            UINT CacheCoherentMemorySupported           : 1;    
            UINT PageTableUpdateRequireAddressSpaceIdle : 1;
            UINT LargePageSupported                     : 1;
            UINT DualPteSupported                       : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
            UINT AllowNonAlignedLargePageAddress        : 1;
            UINT SysMem64KBPageSupported                : 1;
            UINT Reserved                               : 22;
#else
            UINT Reserved                               : 24;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
        };
        UINT        Value;
    };
    DXGK_PAGETABLEUPDATEMODE    PageTableUpdateMode;
    UINT                        VirtualAddressBitCount;
    UINT                        LeafPageTableSizeFor64KPagesInBytes;
    UINT                        PageTableLevelCount;
    struct 
    {
        UINT SourcePageTableVaInTransfer  : 1;
        UINT Reserved                     : 31;
    } LegacyBehaviors;
} DXGK_GPUMMUCAPS;

typedef struct _DXGK_QUERYPHYSICALADAPTERCAPSIN
{
    UINT PhysicalAdapterIndex;
} DXGK_QUERYPHYSICALADAPTERCAPSIN;

typedef struct _DXGK_PHYSICALADAPTERFLAGS
{
   union
   {
      struct 
      {
         UINT IoMmuSupported                 : 1;
         UINT GpuMmuSupported                : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
         UINT MovePagingSupported            : 1;
         UINT VPRPagingContextRequired       : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
         UINT AllowHardwareProtectedNoVpr    : 1;
         UINT Reserved                       : 27;
#else
         UINT    Reserved                    : 28;
#endif
#else  // ! DXGKDDI_INTERFACE_VERSION_WDDM2_1
         UINT Reserved                       : 30;
#endif
      };
      UINT Value;
   };
} DXGK_PHYSICALADAPTERFLAGS;

typedef struct _DXGK_PHYSICALADAPTERCAPS
{
    WORD                        NumExecutionNodes;
    WORD                        PagingNodeIndex;
    HANDLE                      DxgkPhysicalAdapterHandle;
    DXGK_PHYSICALADAPTERFLAGS   Flags;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
    UINT                        VPRPagingNode;
#endif
} DXGK_PHYSICALADAPTERCAPS;

typedef struct _DXGK_CPUHOSTAPERTURE
{
    UINT64  PhysicalAddress;            // CPU physical address 
    UINT32  SizeInPages;                // Size in CPU host pages
} DXGK_CPUHOSTAPERTURE;

#endif // DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0

typedef struct _DXGK_VIDMMCAPS
{
    union
    {
        struct
        {
            UINT    OutOfOrderLock              : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN7)
            UINT    DedicatedPagingEngine       : 1; // _ADVSCH_
            UINT    PagingEngineCanSwizzle      : 1; // _ADVSCH_
            UINT    SectionBackedPrimary        : 1; // Create primaries using section without need for IO range
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
            UINT    CrossAdapterResource        : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
            UINT    VirtualAddressingSupported  : 1;
            UINT    GpuMmuSupported             : 1;  
            UINT    IoMmuSupported              : 1;  
            UINT    ReplicateGdiContent         : 1;  
            UINT    NonCpuVisiblePrimary        : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
            UINT    ParavirtualizationSupported : 1;
            UINT    Reserved                    : 21;
#else
            UINT    Reserved                    : 22;
#endif // DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2
#else  // ! DXGKDDI_INTERFACE_VERSION_WDDM2_0
            UINT    Reserved                    : 27;
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_0
#else  // ! DXGKDDI_INTERFACE_VERSION_WDDM1_3
            UINT    Reserved                    : 28;
#endif // DXGKDDI_INTERFACE_VERSION_WDDM1_3
#else  // ! DXGKDDI_INTERFACE_VERSION_WIN7
            UINT    Reserved                    : 31;
#endif // DXGKDDI_INTERFACE_VERSION_WIN7
        };
        UINT        Value;
    };
    UINT            PagingNode;
} DXGK_VIDMMCAPS;

#define DXGK_MAX_ASYMETRICAL_PROCESSING_NODES  64
typedef struct _DXGK_GPUENGINETOPOLOGY
{
    UINT NbAsymetricProcessingNodes;
    UINT Reserved[DXGK_MAX_ASYMETRICAL_PROCESSING_NODES];
} DXGK_GPUENGINETOPOLOGY;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN7)
typedef struct _DXGK_VIRTUALADDRESSCAPS_DEPRECATED // _ADVSCH_
{
    union
    {
        struct
        {
            UINT PrivilegedMemorySupported  : 1;
            UINT ReadOnlyMemorySupported    : 1;
            UINT Reserved                   : 30;
        };
        UINT        Value;
    };

    UINT VirtualAddressBitCount;
    UINT PageTableCoverageBitCount;

    UINT PageDirectoryEntrySize;

    UINT PageDirectorySegment;
    UINT PageTableSegment;

    UINT IdealGPUPageSize;
} DXGK_VIRTUALADDRESSCAPS_DEPRECATED;

typedef struct _DXGK_DMABUFFERCAPS_DEPRECATED // _ADVSCH_
{
    struct
    {
        UINT Size;
        UINT PrivateDriverDataSize;
        UINT SegmentId;
        UINT Reserved1;
        UINT Reserved[16];
    } PresentDmaBuffer;

    struct
    {
        UINT Size;
        UINT PrivateDriverDataSize;
        UINT SegmentId;
        UINT Reserved1;
        UINT Reserved[16];
    } PagingDmaBuffer;
} DXGK_DMABUFFERCAPS_DEPRECATED;

typedef enum _DXGK_WDDMVERSION // _ADVSCH_
{
     DXGKDDI_WDDMv1   = 0x1000,
     DXGKDDI_WDDMv1_2 = 0x1200,
     DXGKDDI_WDDMv1_3 = 0x1300,
     DXGKDDI_WDDMv2   = 0x2000,
     DXGKDDI_WDDMv2_1 = 0x2100,
     DXGKDDI_WDDMv2_2 = 0x2200,
     DXGKDDI_WDDMv2_3 = 0x2300,
} DXGK_WDDMVERSION;
#endif // DXGKDDI_INTERFACE_VERSION

typedef struct _DXGK_DRIVERCAPS
{
    PHYSICAL_ADDRESS        HighestAcceptableAddress;
    UINT                    MaxAllocationListSlotId;
    SIZE_T                  ApertureSegmentCommitLimit;
    UINT                    MaxPointerWidth;
    UINT                    MaxPointerHeight;
    DXGK_POINTERFLAGS       PointerCaps;
    UINT                    InterruptMessageNumber;
    UINT                    NumberOfSwizzlingRanges;
    UINT                    MaxOverlays;
    union
    {
        DXGK_GAMMARAMPCAPS      GammaRampCaps;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
        DXGK_COLORTRANSFORMCAPS ColorTransformCaps;
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_2
    };
    DXGK_PRESENTATIONCAPS   PresentationCaps;
    UINT                    MaxQueuedFlipOnVSync;
    DXGK_FLIPCAPS           FlipCaps;
    DXGK_VIDSCHCAPS         SchedulingCaps;
    DXGK_VIDMMCAPS          MemoryManagementCaps;
    DXGK_GPUENGINETOPOLOGY  GpuEngineTopology;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN7)
    DXGK_WDDMVERSION        WDDMVersion;        // _ADVSCH_
    DXGK_VIRTUALADDRESSCAPS_DEPRECATED Reserved;       // _ADVSCH_
    DXGK_DMABUFFERCAPS_DEPRECATED      Reserved1;      // _ADVSCH_
#endif // DXGKDDI_INTERFACE_VERSION
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    D3DKMDT_PREEMPTION_CAPS PreemptionCaps;
    BOOLEAN                 SupportNonVGA;
    BOOLEAN                 SupportSmoothRotation;
    BOOLEAN                 SupportPerEngineTDR;
    BOOLEAN                 SupportDirectFlip;
    BOOLEAN                 SupportMultiPlaneOverlay;
    BOOLEAN                 SupportRuntimePowerManagement;
    BOOLEAN                 SupportSurpriseRemovalInHibernation;
#endif // DXGKDDI_INTERFACE_VERSION
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
    BOOLEAN                 HybridDiscrete;
    UINT                    MaxOverlayPlanes;
#endif // DXGKDDI_INTERFACE_VERSION
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
    BOOLEAN                 HybridIntegrated;
    D3DGPU_VIRTUAL_ADDRESS  InternalGpuVirtualAddressRangeStart;
    D3DGPU_VIRTUAL_ADDRESS  InternalGpuVirtualAddressRangeEnd;
    BOOLEAN                 SupportSurpriseRemoval;
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_0
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
    BOOLEAN                 SupportMultiPlaneOverlayImmediateFlip;
    BOOLEAN                 CursorScaledWithMultiPlaneOverlayPlane0;
    BOOLEAN                 HybridAcpiChainingRequired;
    UINT                    MaxQueuedMultiPlaneOverlayFlipVSync;
#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_1


} DXGK_DRIVERCAPS;

// Segment Caps
typedef struct _DXGK_SEGMENTFLAGS
{
    union
    {
        struct
        {
            UINT    Aperture                          : 1;    // 0x00000001
            UINT    Agp                               : 1;    // 0x00000002
            UINT    CpuVisible                        : 1;    // 0x00000004
            UINT    UseBanking                        : 1;    // 0x00000008
            UINT    CacheCoherent                     : 1;    // 0x00000010
            UINT    PitchAlignment                    : 1;    // 0x00000020
            UINT    PopulatedFromSystemMemory         : 1;    // 0x00000040
            UINT    PreservedDuringStandby            : 1;    // 0x00000080
            UINT    PreservedDuringHibernate          : 1;    // 0x00000100
            UINT    PartiallyPreservedDuringHibernate : 1;    // 0x00000200
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
            UINT    DirectFlip                        : 1;    // 0x00000400
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
            UINT    Use64KBPages                      : 1;    // 0x00000800         // Defines if the segment is using 4GB or 64 KB pages 
            UINT    ReservedSysMem                    : 1;    // 0x00001000         // Reserved for system use
            UINT    SupportsCpuHostAperture           : 1;    // 0x00002000         // True if segment supports a CpuHostAperture
            UINT    SupportsCachedCpuHostAperture     : 1;    // 0x00004000         // True if segment supports cache coherent CpuHostAperture
            UINT    ApplicationTarget                 : 1;    // 0x00008000         // Deprecated, replaced by LocalBudgetGroup and NonLocalBudgetGroup flags.
            UINT    VprSupported                      : 1;    // 0x00010000         // Video Protected Region supported
            UINT    VprPreservedDuringStandby         : 1;    // 0x00020000         // Content of Video Protected Regions preserved during standby
            UINT    EncryptedPagingSupported          : 1;    // 0x00040000         // Hardware protected allocation are encripted during paging
            UINT    LocalBudgetGroup                  : 1;    // 0x00080000         // This segment counts against local memory segment budget group.
            UINT    NonLocalBudgetGroup               : 1;    // 0x00100000         // This segment counts against non-local memory segment budget group.
            UINT    Reserved                          :11;    // 0xFFE00000
#else
            UINT    Reserved                          :21;    // 0xFFFFF800
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
#else
            UINT    Reserved                          :22;    // 0xFFFFFC00
#endif
        };
        UINT        Value;
    };
} DXGK_SEGMENTFLAGS;

typedef struct _DXGK_SEGMENTDESCRIPTOR
{
    PHYSICAL_ADDRESS        BaseAddress;            // GPU logical base address for
                                                    // the segment.
    PHYSICAL_ADDRESS        CpuTranslatedAddress;   // CPU translated base address
                                                    // for the segment if CPU visible.
    SIZE_T                  Size;                   // Size of the segment.
    UINT                    NbOfBanks;              // Number of bank in the segment.
    SIZE_T*                 pBankRangeTable;        // Range delimiting each bank.
    SIZE_T                  CommitLimit;            // Maximum number of bytes that can be
                                                    // commited to this segment, apply to
                                                    // aperture segment only.
    DXGK_SEGMENTFLAGS       Flags;                  // Segment bit field flags
} DXGK_SEGMENTDESCRIPTOR;

typedef struct _DXGK_QUERYSEGMENTIN
{
    PHYSICAL_ADDRESS        AgpApertureBase;        // AGP aperture base address.
    LARGE_INTEGER           AgpApertureSize;        // Size of the available AGP aperture.
    DXGK_SEGMENTFLAGS       AgpFlags;               // Segment bit field flags
} DXGK_QUERYSEGMENTIN;

typedef struct _DXGK_QUERYSEGMENTOUT
{
    UINT                    NbSegment;              // Number of segment described.
    DXGK_SEGMENTDESCRIPTOR* pSegmentDescriptor;     // Buffer describing the segment.
    UINT                    PagingBufferSegmentId;  // SegmentId the paging buffer
                                                    // should be allocated from.
    UINT                    PagingBufferSize;       // Paging buffer size.
    UINT                    PagingBufferPrivateDataSize;
} DXGK_QUERYSEGMENTOUT;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN7)

//
// System Memory SegmentId define for WDDM v2
//
#define DXGK_SEGMENT_ID_INVALID           0
#define DXGK_SEGMENT_ID_SYSTEMMEMORY      31

//
// System Memory SegmentSet mask define for WDDM v2
//
#define DXGK_SEGMENT_SET_SYSTEMMEMORY     0x80000000

typedef struct _DXGK_SEGMENTFLAGS2
{
    union
    {
        struct
        {
            UINT    Aperture                    : 1;    // 0x00000001
            UINT    PopulatedFromSystemMemory   : 1;    // 0x00000002
            UINT    SystemMemoryReservedByBios  : 1;    // 0x00000004
            UINT    CpuVisible                  : 1;    // 0x00000008 // ADVSCH_M2 TEMPORARY
            UINT    Reserved                    :28;    // 0xFFFFFFF0
        };
        UINT        Value;
    };
} DXGK_SEGMENTFLAGS2;

typedef struct _DXGK_SEGMENTDESCRIPTOR2
{
    DXGK_SEGMENTFLAGS2       Flags;    // Segment bit field flags
    SIZE_T                   Size;     // Size of the segment.
    PMDL                     pMdl;     // Mdl for PopulatedFromSystemMemory segment
    PHYSICAL_ADDRESS         BaseAddress;          // ADVSCH_M2 TEMPORARY
    PHYSICAL_ADDRESS         CpuTranslatedAddress; // ADVSCH_M2 TEMPORARY
} DXGK_SEGMENTDESCRIPTOR2;

typedef struct _DXGK_QUERYSEGMENTOUT2
{
    UINT                     SegmentCount;       // Number of segment described.
    DXGK_SEGMENTDESCRIPTOR2* pSegmentDescriptor; // Buffer describing the segment.
} DXGK_QUERYSEGMENTOUT2;

#endif // DXGKDDI_INTERFACE_VERSION_WIN7

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
typedef struct _DXGK_SEGMENTDESCRIPTOR3
{
    DXGK_SEGMENTFLAGS       Flags;                  // Segment bit field flags
    PHYSICAL_ADDRESS        BaseAddress;            // GPU logical base address for
                                                    // the segment.
    PHYSICAL_ADDRESS        CpuTranslatedAddress;   // CPU translated base address
                                                    // for the segment if CPU visible.
    SIZE_T                  Size;                   // Size of the segment.
    UINT                    NbOfBanks;              // Number of bank in the segment.
    SIZE_T*                 pBankRangeTable;        // Range delimiting each bank.
    SIZE_T                  CommitLimit;            // Maximum number of bytes that can be
                                                    // commited to this segment, apply to
                                                    // aperture segment only.
    SIZE_T                  SystemMemoryEndAddress; // For segments that are partially composed
                                                    // of system memory, all allocations ending after
                                                    // this address are purged during hibernate.
    SIZE_T                  Reserved;
} DXGK_SEGMENTDESCRIPTOR3;

typedef struct _DXGK_QUERYSEGMENTOUT3
{
    UINT                     NbSegment;              // Number of segment described.
    DXGK_SEGMENTDESCRIPTOR3* pSegmentDescriptor;     // Buffer describing the segment.
    UINT                     PagingBufferSegmentId;  // SegmentId the paging buffer
                                                     // should be allocated from.
    UINT                     PagingBufferSize;       // Paging buffer size.
    UINT                     PagingBufferPrivateDataSize;
} DXGK_QUERYSEGMENTOUT3;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

typedef struct _DXGK_QUERYSEGMENTIN4
{
    UINT                    PhysicalAdapterIndex;   // Index of the physical adapter to query (engine ordinal index)
} DXGK_QUERYSEGMENTIN4;

typedef struct _DXGK_SEGMENTDESCRIPTOR4
{
    DXGK_SEGMENTFLAGS        Flags;                   // Segment bit field flags
    PHYSICAL_ADDRESS         BaseAddress;             // GPU logical base address for the segment.
    SIZE_T                   Size;                    // Size of the segment.
    SIZE_T                   CommitLimit;             // Maximum number of bytes that can be
                                                      // commited to this segment, apply to
                                                      // aperture segment only.
    SIZE_T                   SystemMemoryEndAddress;  // For segments that are partially composed
                                                      // of system memory, all allocations ending after
                                                      // this address are purged during hibernate.
    union
    {
        PHYSICAL_ADDRESS     CpuTranslatedAddress;    // If Flags.SupportsCpuHostAperture==FALSE and the
                                                      // segment is CPUVisible, this will be the
                                                      // CPU physical base address of the segment
        DXGK_CPUHOSTAPERTURE CpuHostAperture;         // If Flags.SupportsCpuHostAperture==TRUE this will
                                                      // have the CPU address and size of the
                                                      // CPUHostAperture
    };
    UINT                     NumInvalidMemoryRanges;  // Number of invalid memory ranges in the segment
    SIZE_T                   VprRangeStartOffset;     // Start offset of video protected region range in bytes
    SIZE_T                   VprRangeSize;            // Size of the video protected region range
    UINT                     VprAlignment;            // Alignment of video protected regions in bytes. Applies to size and start offset.
    UINT                     NumVprSupported;         // Number of supported video protected regions in the VPR range. Zero for infinite number.
    UINT                     VprReserveSize;          // Size of area in VPR to reserve for driver/hardware use.  Zero for no reserve.
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
    UINT                     NumUEFIFrameBufferRanges;// Number of UEFI frame buffer memory ranges in the segment.
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
} DXGK_SEGMENTDESCRIPTOR4;

typedef struct _DXGK_QUERYSEGMENTOUT4
{
    UINT    NbSegment;                      // Number of segment described.
    BYTE*   pSegmentDescriptor;             // An array of segment descriptors, where each element
                                            // is of 'SegmentDescriptorStride' in size.
    UINT    PagingBufferSegmentId;          // SegmentId the paging buffer
                                            // should be allocated from.
    UINT    PagingBufferSize;               // Paging buffer size.
    UINT    PagingBufferPrivateDataSize;
    SIZE_T  SegmentDescriptorStride;        // Size of each element in the 
                                            // pSegmentDescriptor array
} DXGK_QUERYSEGMENTOUT4;


typedef struct _DXGK_MEMORYRANGE
{
    UINT64  SegmentOffset;                  // Offset in bytes from the start of segment
    UINT64  SizeInBytes;                    // Size in bytes
} DXGK_MEMORYRANGE;

typedef struct _DXGK_QUERYSEGMENTMEMORYSTATE
{
    WORD                DriverSegmentId;        // [in] Driver segment Id.
    WORD                PhysicalAdapterIndex;   // [in] Physical adapter index in an LDA link
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
    union
    {
        UINT            NumInvalidMemoryRanges; // [in] Number of elements in the pMemoryRanges array used with DXGKQAITYPE_SEGMENTMEMORYSTATE.
        UINT            NumUEFIFrameBufferRanges;// [in] Number of elements in the pMemoryRanges array used with DXGKQAITYPE_UEFIFRAMEBUFFERRANGES.
    };
#else
    UINT                NumInvalidMemoryRanges; // [in] Number of elements in the pMemoryRanges array used with DXGKQAITYPE_SEGMENTMEMORYSTATE.
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
    DXGK_MEMORYRANGE*   pMemoryRanges;          // [out] Invalid memory ranges
} DXGK_QUERYSEGMENTMEMORYSTATE, DXGK_SEGMENTMEMORYSTATE;

typedef _In_ CONST DXGK_SEGMENTMEMORYSTATE* IN_CONST_PDXGK_SEGMENTMEMORYSTATE;

//
// Driver caps extension for WDDM2.0 or above drivers
//
typedef struct _DXGK_DISPLAY_DRIVERCAPS_EXTENSION
{
    union
    {
        struct
        {
            UINT    SecureDisplaySupport    : 1;    // 0x00000001
            UINT    VirtualModeSupport      : 1;    // 0x00000002
#if (DXGKDDI_INTERFACE_VERSION < DXGKDDI_INTERFACE_VERSION_WDDM2_1)
            UINT    Reserved                :29;    // 0x7FFFFFFC
            UINT    NonSpecificPrimarySupport : 1;  // 0x80000000 Do not use!
#else
            UINT    Reserved                :30;    // 0xFFFFFFFC
#endif
        };
        UINT        Value;
    };
} DXGK_DISPLAY_DRIVERCAPS_EXTENSION;

#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)


#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

#if defined(__cplusplus) && !defined(SORTPP_PASS)
typedef enum _DXGK_DISPLAYPANELORIENTATION : UINT
{
    DXGK_DPO_0      = 0,
    DXGK_DPO_90     = 1,
    DXGK_DPO_180    = 2,
    DXGK_DPO_270    = 3
} DXGK_DISPLAYPANELORIENTATION;
#else
typedef UINT DXGK_DISPLAYPANELORIENTATION;
#endif // defined(__cplusplus) && !defined(SORTPP_PASS)


#define DXGK_MAX_INTEGRATED_DISPLAYS 16

typedef union _DXGK_INTEGRATEDDISPLAYFLAGS
{
    struct
    {
        DXGK_DISPLAYPANELORIENTATION    UndockedOrientation         : 2;
        DXGK_DISPLAYPANELORIENTATION    DockedOrientation           : 2;
        UINT                            Reserved                    :28;
    };
    UINT Value;
} DXGK_INTEGRATEDDISPLAYFLAGS, *PDXGK_INTEGRATEDDISPLAYFLAGS;

typedef union _DXGK_STANDARD_COLORIMETRY_FLAGS
{
    struct
    {
        UINT    BT2020YCC   : 1;
        UINT    BT2020RGB   : 1;
        UINT    ST2084      : 1;
        UINT    Reserved    :29;
    };
    ULONG Value;
} DXGK_STANDARD_COLORIMETRY_FLAGS, *PDXGK_STANDARD_COLORIMETRY_FLAGS;

typedef struct _DXGK_COLORIMETRY
{
    // Color primaries
    D3DKMDT_2DOFFSET                    RedPoint;
    D3DKMDT_2DOFFSET                    GreenPoint;
    D3DKMDT_2DOFFSET                    BluePoint;
    D3DKMDT_2DOFFSET                    WhitePoint;

    // Luminance limits
    ULONG                               MinLuminance;
    ULONG                               MaxLuminance;
    ULONG                               MaxFullFrameLuminance;

    // Supported bit depths by wire format
    D3DKMDT_WIRE_FORMAT_AND_PREFERENCE  FormatBitDepths;

    // Standard colorimetry support flags
    DXGK_STANDARD_COLORIMETRY_FLAGS     StandardColorimetryFlags;
} DXGK_COLORIMETRY, *PDXGK_COLORIMETRY;

typedef struct _DXGK_QUERYINTEGRATEDDISPLAYOUT
{
    DXGK_INTEGRATEDDISPLAYFLAGS         Flags;

    D3DKMDT_VIDEO_SIGNAL_INFO           NativeTiming;

    DXGK_MONITORLINKINFO_CAPABILITIES   LinkCapabilities;

    DXGK_COLORIMETRY                    Colorimetry;

    DXGK_DISPLAY_TECHNOLOGY             DisplayTechnology;
    DXGK_DISPLAY_USAGE                  IntendedUsage;
    BYTE                                Instance;
    DXGK_DISPLAY_DESCRIPTOR_TYPE        DescriptorType;

    BYTE                                Descriptor[1];
} DXGK_QUERYINTEGRATEDDISPLAYOUT, *PDXGK_QUERYINTEGRATEDDISPLAYOUT;

typedef struct _DXGK_QAITARGETIN
{
    D3DDDI_VIDEO_PRESENT_TARGET_ID      TargetId;
} DXGK_QAITARGETIN;

typedef DXGK_QAITARGETIN DXGK_QUERYINTEGRATEDDISPLAYIN;
typedef DXGK_QAITARGETIN DXGK_QUERYCOLORIMETRYOVERRIDESIN;

#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_2

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)

typedef struct _DXGK_QUERYDISPLAYIDIN
{
    D3DDDI_VIDEO_PRESENT_TARGET_ID TargetId;
} DXGK_QUERYDISPLAYIDIN;

typedef struct _DXGK_QUERYDISPLAYIDOUT
{
    UINT Length;
    BYTE* pDescriptor;
} DXGK_QUERYDISPLAYIDOUT;

#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_3


//
// Defines for runtime power management
//

#define DXGK_FSTATE_UNKNOWN_POWER           0xFFFFFFFF
#define DXGK_FSTATE_UNKNOWN_TIME            0xFFFFFFFFFFFFFFFF
#define DXGK_MAX_F_STATES                   8
#define DXGK_POWER_COMPONENT_NAME_SIZE      40
#define DXGK_MAX_POWER_COMPONENT_PROVIDERS  16

//
// The folowing GUIDs are recommended to use in power control requests between miniport and PEP.
//

// {6131C9ED-B9EC-40B3-A5E2-C0613E437B7E}
DEFINE_GUID(GUID_DXGKDDI_POWER_VOLTAGE_UP,
0x6131c9ed, 0xb9ec, 0x40b3, 0xa5, 0xe2, 0xc0, 0x61, 0x3e, 0x43, 0x7b, 0x7e);

// {7F81CE3D-5989-4519-8394-B457F637BA39}
DEFINE_GUID(GUID_DXGKDDI_POWER_VOLTAGE_DOWN,
0x7f81ce3d, 0x5989, 0x4519, 0x83, 0x94, 0xb4, 0x57, 0xf6, 0x37, 0xba, 0x39);

// {78BA81DB-0F5C-45FD-8F03-C7B5CCD1E0DA}
// Could be used when miniport requests a change in voltage but it is not known in what direction
// it will be changed.
DEFINE_GUID(GUID_DXGKDDI_POWER_VOLTAGE,
0x78ba81db, 0xf5c, 0x45fd, 0x8f, 0x3, 0xc7, 0xb5, 0xcc, 0xd1, 0xe0, 0xda);

// {8C7FDE48-FF0B-48FF-936B-332ABB9BD3B3}
DEFINE_GUID(GUID_DXGKDDI_POWER_CLOCK_UP,
0x8c7fde48, 0xff0b, 0x48ff, 0x93, 0x6b, 0x33, 0x2a, 0xbb, 0x9b, 0xd3, 0xb3);

// {611114F3-CB1E-4D0C-8EE8-872E1FBDACEB}
DEFINE_GUID(GUID_DXGKDDI_POWER_CLOCK_DOWN,
0x611114f3, 0xcb1e, 0x4d0c, 0x8e, 0xe8, 0x87, 0x2e, 0x1f, 0xbd, 0xac, 0xeb);

// {51C6873B-1C29-4C45-8246-05E4D6D80D15}
// Could be used when miniport requests a change in clock but it is not known in what direction
// it will be changed.
DEFINE_GUID(GUID_DXGKDDI_POWER_CLOCK,
0x51c6873b, 0x1c29, 0x4c45, 0x82, 0x46, 0x5, 0xe4, 0xd6, 0xd8, 0xd, 0x15);

// {1995DCB1-986E-47BA-9A73-60AF5111938B}
DEFINE_GUID(GUID_DXGKDDI_POWER_BANDWIDTH_UP,
0x1995dcb1, 0x986e, 0x47ba, 0x9a, 0x73, 0x60, 0xaf, 0x51, 0x11, 0x93, 0x8b);

// {97CE1383-EF2D-49CB-9BCF-26A738F3CE32}
DEFINE_GUID(GUID_DXGKDDI_POWER_BANDWIDTH_DOWN,
0x97ce1383, 0xef2d, 0x49cb, 0x9b, 0xcf, 0x26, 0xa7, 0x38, 0xf3, 0xce, 0x32);

// {38751BFD-64BA-4962-A5A9-9F2E627A643E}
// Could be used when miniport requests a change in bandwidth but it is not known in what
// direction it will be changed.
DEFINE_GUID(GUID_DXGKDDI_POWER_BANDWIDTH,
0x38751bfd, 0x64ba, 0x4962, 0xa5, 0xa9, 0x9f, 0x2e, 0x62, 0x7a, 0x64, 0x3e);

//
// The folowing GUIDs are used by Dxgkrnl to notify the miniport driver about certain events.
//

// {CBA549D4-CF3A-445C-9468-2383FD523116}
DEFINE_GUID(GUID_DXGKDDI_POWER_MANAGEMENT_PREPARE_TO_START,
0xcba549d4, 0xcf3a, 0x445c, 0x94, 0x68, 0x23, 0x83, 0xfd, 0x52, 0x31, 0x16);

// {6C929C1D-7D76-4538-93AD-449DC9FDC239}
DEFINE_GUID(GUID_DXGKDDI_POWER_MANAGEMENT_STARTED,
0x6c929c1d, 0x7d76, 0x4538, 0x93, 0xad, 0x44, 0x9d, 0xc9, 0xfd, 0xc2, 0x39);

// {0A9D9621-BC21-4DD4-A0FC-D976E428F738}
DEFINE_GUID(GUID_DXGKDDI_POWER_MANAGEMENT_STOPPED,
0xa9d9621, 0xbc21, 0x4dd4, 0xa0, 0xfc, 0xd9, 0x76, 0xe4, 0x28, 0xf7, 0x38);

typedef struct _DXGK_POWER_RUNTIME_STATE
{
   // This value specifies, in 100 nanosecond units, the time the component takes to return to the F0 state.
   // The   attribute for F0 should be 0.
    ULONGLONG   TransitionLatency;

   // This value specifies, in 100 nanosecond units, the minimal amount of time required to spend in
   // this F-state to make it worthwhile. The attribute for F0 should be 0.
   ULONGLONG    ResidencyRequirement;

   // This value specifies, in microwatt units, the power draw of the component in this F-state.
   // Should be non-zero for the F0 state.
   ULONG        NominalPower;

} DXGK_POWER_RUNTIME_STATE;

typedef enum _DXGK_POWER_COMPONENT_TYPE
{
   DXGK_POWER_COMPONENT_ENGINE	        = 0,
   DXGK_POWER_COMPONENT_MONITOR         = 1,
   DXGK_POWER_COMPONENT_MONITOR_REFRESH = 2,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
   DXGK_POWER_COMPONENT_MEMORY          = 3,
   DXGK_POWER_COMPONENT_MEMORY_REFRESH  = 4,
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
   DXGK_POWER_COMPONENT_OTHER           = 5,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
   DXGK_POWER_COMPONENT_D3_TRANSITION	= 6,
#endif
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
   DXGK_POWER_COMPONENT_SHARED          = 7,
   DXGK_POWER_COMPONENT_MAX             = 8,
#elif (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
   DXGK_POWER_COMPONENT_MAX             = 7,
#else
   DXGK_POWER_COMPONENT_MAX             = 6,
#endif
} DXGK_POWER_COMPONENT_TYPE;

typedef struct _DXGK_POWER_COMPONENT_MAPPING
{
   DXGK_POWER_COMPONENT_TYPE	ComponentType;
   union
   {
      struct DXGK_POWER_COMPONENT_ENGINE_DESC
      {
          UINT  NodeIndex;
      } EngineDesc;
      struct DXGK_POWER_COMPONENT_MONITOR_REFRESH_DESC
      {
          UINT  VidPnSourceID;
      } MonitorRefreshDesc;
      struct DXGK_POWER_COMPONENT_MONITOR_DESC
      {
          UINT  VidPnTargetID;
      } MonitorDesc;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
      struct DXGK_POWER_COMPONENT_MEMORY_DESC
      {
          UINT  SegmentID;		// Zero based memory segment index
      } MemoryDesc;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
   };
} DXGK_POWER_COMPONENT_MAPPING;

typedef struct _DXGK_POWER_COMPONENT_INDEX
{
    union
    {
        struct
        {
            WORD    PhysicalAdapterComponentIndex;  // Zero based index relative to the physical adapter.
            WORD    PhysicalAdapterIndex;           // Physical adapter in a LDA configuration the component belongs to
        };
        UINT    Value;
    };
} DXGK_POWER_COMPONENT_INDEX;

typedef struct _DXGK_POWER_COMPONENT_FLAGS
{
    union
    {
        struct
        {
            UINT    Reserved0                           : 1;    // Old drivers used to set the flag
            UINT    DriverCompletesFStateTransition     : 1;
            UINT    TransitionTo_F0_OnDx                : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
            UINT    NoDebounce                          : 1;
            UINT    ActiveInD3                          : 1;
            UINT    Reserved                            : 27;    // 0xFFFFFFE0
#else
            UINT    Reserved                            : 29;    // 0xFFFFFFF8
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
        };
        UINT Value;
    };
} DXGK_POWER_COMPONENT_FLAGS;

typedef struct _DXGK_POWER_RUNTIME_COMPONENT
{
    ULONG                               StateCount;
    DXGK_POWER_RUNTIME_STATE            States[DXGK_MAX_F_STATES];
    DXGK_POWER_COMPONENT_MAPPING        ComponentMapping;
    DXGK_POWER_COMPONENT_FLAGS          Flags;
    GUID                                ComponentGuid;
    UCHAR                               ComponentName[DXGK_POWER_COMPONENT_NAME_SIZE];
    ULONG                               ProviderCount;
    ULONG                               Providers[DXGK_MAX_POWER_COMPONENT_PROVIDERS];
} DXGK_POWER_RUNTIME_COMPONENT;

#endif // DXGKDDI_INTERFACE_VERSION_WIN8


#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
//
// Defines for Windows Next runtime power management enhancements
//
#define DXGK_MAX_P_STATES                   32

// the primary P-State enumeration structure
typedef struct _DXGK_POWER_P_STATE
{
    ULONG        OperatingFrequency;
} DXGK_POWER_P_STATE;

// placeholder structure for hardware behavioral flags
typedef struct _DXGK_POWER_COMPONENT_P_FLAGS
{
    union
    {
        struct
        {
            UINT    Reserved                            : 32;
        };
        UINT Value;
    };
} DXGK_POWER_COMPONENT_P_FLAGS;

// the per-component p-state information structure
typedef struct _DXGK_POWER_P_COMPONENT
{
    ULONG                               StateCount;
    DXGK_POWER_P_STATE                  States[DXGK_MAX_P_STATES];
    DXGK_POWER_COMPONENT_P_FLAGS        Flags;
} DXGK_POWER_P_COMPONENT;

#endif // DXGKDDI_INTERFACE_VERSION_WDDM1_3

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
typedef struct _DXGK_QUERYADAPTERINFOFLAGS
{
    union
    {
        struct
        {
            UINT    VirtualMachineData          : 1;    // 0x00000001
            UINT    Reserved                    :31;    // 0xFFFFFFFE
        };
        UINT Value;
    };
 } DXGK_QUERYADAPTERINFOFLAGS;
 #endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
 
typedef struct _DXGKARG_QUERYADAPTERINFO
{
    DXGK_QUERYADAPTERINFOTYPE   Type;
    VOID*                       pInputData;
    UINT                        InputDataSize;
    VOID*                       pOutputData;
    UINT                        OutputDataSize;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
    DXGK_QUERYADAPTERINFOFLAGS  Flags;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
} DXGKARG_QUERYADAPTERINFO;

typedef _In_ CONST DXGKARG_QUERYADAPTERINFO*   IN_CONST_PDXGKARG_QUERYADAPTERINFO;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_QUERYADAPTERINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_QUERYADAPTERINFO(
    IN_CONST_HANDLE                         hAdapter,
    IN_CONST_PDXGKARG_QUERYADAPTERINFO      pQueryAdapterInfo
    );

typedef struct _DXGKARG_ACQUIRESWIZZLINGRANGE
{
    HANDLE              hAllocation;
    UINT                PrivateDriverData;  // in: Passed in when UMD calls LockCB
    UINT                RangeId;
    UINT                SegmentId;
    SIZE_T              RangeSize;
    PHYSICAL_ADDRESS    CPUTranslatedAddress;
} DXGKARG_ACQUIRESWIZZLINGRANGE;

typedef _Inout_ DXGKARG_ACQUIRESWIZZLINGRANGE*      INOUT_PDXGKARG_ACQUIRESWIZZLINGRANGE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_ACQUIRESWIZZLINGRANGE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_ACQUIRESWIZZLINGRANGE(
    IN_CONST_HANDLE                         hAdapter,
    INOUT_PDXGKARG_ACQUIRESWIZZLINGRANGE    pAcquireSwizzlingRange
    );

typedef struct _DXGKARG_RELEASESWIZZLINGRANGE
{
    HANDLE              hAllocation;
    UINT                PrivateDriverData;
    UINT                RangeId;
} DXGKARG_RELEASESWIZZLINGRANGE;

typedef _In_ CONST DXGKARG_RELEASESWIZZLINGRANGE*   IN_CONST_PDXGKARG_RELEASESWIZZLINGRANGE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_RELEASESWIZZLINGRANGE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_RELEASESWIZZLINGRANGE(
    IN_CONST_HANDLE                             hAdapter,
    IN_CONST_PDXGKARG_RELEASESWIZZLINGRANGE     pReleaseSwizzlingRange
    );

typedef struct _DXGK_ALLOCATIONINFOFLAGS
{
    union
    {
        struct
        {
            UINT    CpuVisible              : 1;    // 0x00000001
            UINT    PermanentSysMem         : 1;    // 0x00000002
            UINT    Cached                  : 1;    // 0x00000004
            UINT    Protected               : 1;    // 0x00000008
            UINT    ExistingSysMem          : 1;    // 0x00000010
            UINT    ExistingKernelSysMem    : 1;    // 0x00000020
            UINT    FromEndOfSegment        : 1;    // 0x00000040
            UINT    Swizzled                : 1;    // 0x00000080
            UINT    Overlay                 : 1;    // 0x00000100
            UINT    Capture                 : 1;    // 0x00000200
            UINT    UseAlternateVA          : 1;    // 0x00000400
            UINT    SynchronousPaging       : 1;    // 0x00000800
            UINT    LinkMirrored            : 1;    // 0x00001000
            UINT    LinkInstanced           : 1;    // 0x00002000
            UINT    HistoryBuffer           : 1;    // 0x00004000
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
            UINT    AccessedPhysically      : 1;    // 0x00008000
            UINT    ExplicitResidencyNotification : 1;    
                                                    // 0x00010000
            UINT    HardwareProtected       : 1;    // 0x00020000
            UINT    CpuVisibleOnDemand      : 1;    // 0x00040000 Following fields are RESERVED and
#else // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
            UINT    Reserved                : 4;    // 0x00078000 Following fields are RESERVED and
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
            UINT    DXGK_ALLOC_RESERVED16   : 1;
            UINT    DXGK_ALLOC_RESERVED15   : 1;
            UINT    DXGK_ALLOC_RESERVED14   : 1;
            UINT    DXGK_ALLOC_RESERVED13   : 1;
            UINT    DXGK_ALLOC_RESERVED12   : 1;
            UINT    DXGK_ALLOC_RESERVED11   : 1;
            UINT    DXGK_ALLOC_RESERVED10   : 1;
            UINT    DXGK_ALLOC_RESERVED9    : 1;
            UINT    DXGK_ALLOC_RESERVED4    : 1;
            UINT    DXGK_ALLOC_RESERVED3    : 1;
            UINT    DXGK_ALLOC_RESERVED2    : 1;
            UINT    DXGK_ALLOC_RESERVED1    : 1;
            UINT    DXGK_ALLOC_RESERVED0    : 1;
        };
        UINT Value;
    };
} DXGK_ALLOCATIONINFOFLAGS;

typedef struct _DXGK_ALLOCATIONINFOFLAGS_WDDM2_0
{
    union
    {
        struct
        {
            UINT    CpuVisible                      : 1;    // 0x00000001
            UINT    PermanentSysMem                 : 1;    // 0x00000002
            UINT    Cached                          : 1;    // 0x00000004
            UINT    Protected                       : 1;    // 0x00000008
            UINT    ExistingSysMem                  : 1;    // 0x00000010
            UINT    ExistingKernelSysMem            : 1;    // 0x00000020
            UINT    FromEndOfSegment                : 1;    // 0x00000040
            UINT    DisableLargePageMapping         : 1;    // 0x00000080   // Swizzled 
            UINT    Overlay                         : 1;    // 0x00000100
            UINT    Capture                         : 1;    // 0x00000200
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
            UINT    CreateInVpr                     : 1;    // 0x00000400   // UseAlternateVA
#else
            UINT    Reserved00                      : 1;    // 0x00000400   // UseAlternateVA
#endif            
            UINT    DXGK_ALLOC_RESERVED17           : 1;    // 0x00000800   // Reserved
            UINT    Reserved02                      : 1;    // 0x00001000   // LinkMirrored
            UINT    Reserved03                      : 1;    // 0x00002000   // LinkInstanced
            UINT    HistoryBuffer                   : 1;    // 0x00004000
            UINT    AccessedPhysically              : 1;    // 0x00008000
            UINT    ExplicitResidencyNotification   : 1;    // 0x00010000
            UINT    HardwareProtected               : 1;    // 0x00020000
            UINT    CpuVisibleOnDemand              : 1;    // 0x00040000 Following fields are RESERVED and
            UINT    DXGK_ALLOC_RESERVED16           : 1;
            UINT    DXGK_ALLOC_RESERVED15           : 1;
            UINT    DXGK_ALLOC_RESERVED14           : 1;
            UINT    DXGK_ALLOC_RESERVED13           : 1;
            UINT    DXGK_ALLOC_RESERVED12           : 1;
            UINT    DXGK_ALLOC_RESERVED11           : 1;
            UINT    DXGK_ALLOC_RESERVED10           : 1;
            UINT    DXGK_ALLOC_RESERVED9            : 1;
            UINT    DXGK_ALLOC_RESERVED4            : 1;
            UINT    DXGK_ALLOC_RESERVED3            : 1;
            UINT    DXGK_ALLOC_RESERVED2            : 1;
            UINT    DXGK_ALLOC_RESERVED1            : 1;
            UINT    DXGK_ALLOC_RESERVED0            : 1;
        };
        UINT Value;
    };
} DXGK_ALLOCATIONINFOFLAGS_WDDM2_0;

typedef struct _DXGK_ALLOCATIONUSAGEINFO1
{
    union
    {
        struct
        {
            UINT        PrivateFormat  : 1;     // 0x00000001 - Allocation is a private IHV format. Default is standard format.
            UINT        Swizzled       : 1;     // 0x00000002 - Allocation is swizzled/tiled.
            UINT        MipMap         : 1;     // 0x00000004 - Allocation is a mip mapped texture.
            UINT        Cube           : 1;     // 0x00000008 - Allocation is a cube texture.
            UINT        Volume         : 1;     // 0x00000010 - Allocation is a volume texture.
            UINT        Vertex         : 1;     // 0x00000020 - Allocation is a vertex buffer.
            UINT        Index          : 1;     // 0x00000040 - Allocation is an index buffer.
            UINT        Reserved       : 25;    // 0xFFFFFF80 - Reserved must be set to zero.
        };
        UINT            Value;
    } Flags;

    union
    {
        D3DDDIFORMAT    Format;                 // Allocation format (Flags.PrivateFormat==0)
        UINT            PrivateFormat;          // Allocation format (Flags.PrivateFormat==1)
    };

    UINT                SwizzledFormat;         // Swizzled format for the allocation (IHV private).
    UINT                ByteOffset;             // Offset within the VidMm allocation to the start of this allocation.
    UINT                Width;                  // Width (in pixel) of the allocation.
    UINT                Height;                 // Height (in line) of the allocation.
    UINT                Pitch;                  // Pitch (in bytes) of the allocation.
    UINT                Depth;                  // Depth (in level) of the allocation (mipmap/volume only).
    UINT                SlicePitch;             // Pitch from one level to another (cube/volume only).
} DXGK_ALLOCATIONUSAGEINFO1;

typedef struct _DXGK_ALLOCATIONUSAGEHINT
{
    UINT                            Version;
    DXGK_ALLOCATIONUSAGEINFO1       v1;
} DXGK_ALLOCATIONUSAGEHINT;

typedef struct _DXGK_ALLOCATIONINFO
{
    VOID*                             pPrivateDriverData;               // in: Private data for each allocation allocated by the user mode driver
    UINT                              PrivateDriverDataSize;            // in: Size of the private data
    UINT                              Alignment;
    SIZE_T                            Size;                             // out: Allocation size
    SIZE_T                            PitchAlignedSize;                 // out: Allocation pitch aligned size (for aperture segment requiring Pitch alignment only).
    DXGK_SEGMENTBANKPREFERENCE        HintedBank;
    DXGK_SEGMENTPREFERENCE            PreferredSegment;
    UINT                              SupportedReadSegmentSet;
    UINT                              SupportedWriteSegmentSet;
    UINT                              EvictionSegmentSet;
    union
    {
        UINT                          MaximumRenamingListLength;        // out: Used only prior WDDMv2
        UINT                          PhysicalAdapterIndex;             // out: WDDMv2 and higher only
    };
    HANDLE                            hAllocation;                      // out: Private driver data for allocation
    union
    {
        DXGK_ALLOCATIONINFOFLAGS            Flags;                      // out: Except the reserved fields
        DXGK_ALLOCATIONINFOFLAGS_WDDM2_0    FlagsWddm2;                 // out: Except the reserved fields
    };
    DXGK_ALLOCATIONUSAGEHINT*         pAllocationUsageHint;
    UINT                              AllocationPriority;               // out: Starting allocation priority.
} DXGK_ALLOCATIONINFO;

typedef struct _DXGK_CREATEALLOCATIONFLAGS
{
    union
    {
        struct
        {
            UINT                Resource    : 1;    // 0x00000001
            UINT                Reserved    :31;    // 0xFFFFFFFE
        };
        UINT                    Value;
    };
} DXGK_CREATEALLOCATIONFLAGS;

typedef struct _DXGKARG_CREATEALLOCATION
{
    CONST VOID*                 pPrivateDriverData;
    UINT                        PrivateDriverDataSize;
    UINT                        NumAllocations;
    DXGK_ALLOCATIONINFO*        pAllocationInfo;
    HANDLE                      hResource;
    DXGK_CREATEALLOCATIONFLAGS  Flags;
} DXGKARG_CREATEALLOCATION;

typedef _Inout_ DXGKARG_CREATEALLOCATION*     INOUT_PDXGKARG_CREATEALLOCATION;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_CREATEALLOCATION)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_CREATEALLOCATION(
    IN_CONST_HANDLE                     hAdapter,
    INOUT_PDXGKARG_CREATEALLOCATION     pCreateAllocation
    );

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)

typedef struct _DXGK_CREATECONTEXTALLOCATIONFLAGS
{
    union
    {
        struct
        {
            UINT              SharedAcrossContexts  : 1;    // 0x00000001 - If not set, the allocation is associated with the hContext member of DXGKARGCB_CREATECONTEXTALLOCATION,
                                                            // and it will be made resident when hContext is scheduled to run on the GPU.
                                                            // If set, the allocation is associated with all contexts on the hDevice member,
                                                            // and it will be made resident when any context that belongs to hDevice is
                                                            // scheduled to run on the GPU.
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
            UINT              MapGpuVirtualAddress  : 1;    // When set Dxgkrnl will map a GpuMmu virtual address and pass it in InitContextResource.
            UINT              Reserved              :30;    // 0xFFFFFFFC
#else
            UINT              Reserved              :31;    // 0xFFFFFFFE
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
        };
        UINT                  Value;
    };
} DXGK_CREATECONTEXTALLOCATIONFLAGS;

// Context allocation creation callback.
//

typedef struct _DXGKARGCB_CREATECONTEXTALLOCATION
{
    DXGK_CREATECONTEXTALLOCATIONFLAGS   ContextAllocationFlags; // in: Flags that specify the behavior of the allocation being created.
    HANDLE                              hAdapter;               // in: Adapter the allocation is created for.
    HANDLE                              hDevice;                // in: DXG assigned value for the device that was passed to DxgkDdiCreateDevice,
                                                                // or NULL for system device.
    HANDLE                              hContext;               // in: When ContextAllocationFlags.SharedAcrossContexts bit is set to 0,
                                                                // this parameter contains DXG assigned value for the context that was passed to
                                                                // DxgkDdiCreateContext or DxgkDdiCreateHwContext, or NULL for system context.
                                                                // This parameter should be NULL when ContextAllocationFlags.SharedAcrossContexts bit is set to 1.
    HANDLE                              hDriverAllocation;      // Driver created handle that identifies the created allocation on its side,
                                                                // this value is subsequently passed as DXGKARG_BUILDPAGINGBUFFER::Transfer::hAllocation
                                                                // and DXGKARG_BUILDPAGINGBUFFER::InitContextResource::hAllocation
                                                                // to DxgkDdiBuildPagingBuffer driver callback.
    SIZE_T                              Size;                   // in: Allocation size.
    UINT                                Alignment;              // in: The required alignment for the allocation.
    UINT                                SupportedSegmentSet;    // in: Segment identifiers that the display miniport driver can set
                                                                // in the PreferredSegment member for read or write operations.
    UINT                                EvictionSegmentSet;     // in: Identifiers of segments that can be used for eviction.
    DXGK_SEGMENTPREFERENCE              PreferredSegment;       // in: Preferred segments identifiers that the display miniport driver requests that
                                                                // the video memory manager use to page-in the allocation.
    DXGK_SEGMENTBANKPREFERENCE          HintedBank;             // in: Bank ordering preferences that the display miniport driver requests that
                                                                // the video memory manager use to page-in the allocation.
    DXGK_ALLOCATIONINFOFLAGS            Flags;                  // in: Properties that indicate the type of allocation to create.
    HANDLE                              hAllocation;            // out: DXG assigned handle for this allocation. This value is subsequently passed as
                                                                // hAllocation to DxgkCbDestroyContextAllocation
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
    UINT                                PhysicalAdapterIndex;   // in: Physical adapter index (engine ordinal) for WDDMv2
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
} DXGKARGCB_CREATECONTEXTALLOCATION;

typedef _Inout_ DXGKARGCB_CREATECONTEXTALLOCATION*     INOUT_PDXGKARGCB_CREATECONTEXTALLOCATION;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKCB_CREATECONTEXTALLOCATION)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY CALLBACK *DXGKCB_CREATECONTEXTALLOCATION)(
    INOUT_PDXGKARGCB_CREATECONTEXTALLOCATION
    );

// Context allocation destruction callback.
//

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKCB_DESTROYCONTEXTALLOCATION)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY CALLBACK *DXGKCB_DESTROYCONTEXTALLOCATION)(
    IN_CONST_HANDLE hAdapter,       // in: Adapter the allocation was created for.
    IN_CONST_HANDLE hAllocation     // in: DXG assigned handle for this allocation that was returned from DxgkCbCreateContextAllocation
                                    // as DXGKARGCB_CREATECONTEXTALLOCATION::hAllocation member.
    );

#endif // DXGKDDI_INTERFACE_VERSION

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
typedef struct _DXGK_DESCRIBEALLOCATIONFLAGS
{
    union
    {
        struct
        {
            UINT    CheckDisplayMode    : 1;    // 0x00000001   // Indicates that this allocation is being queried to check display mode
            UINT    Reserved            :31;    // 0xFFFFFFFE
        };
        UINT Value;
    };
} DXGK_DESCRIBEALLOCATIONFLAGS;
#endif

typedef struct _DXGKARG_DESCRIBEALLOCATION
{
    HANDLE                          hAllocation;                    //in: Driver returned handle in DXGK_ALLOCATIONINFO upon CreateAllocation
    UINT                            Width;                          //out:Width of specified allocation
    UINT                            Height;                         //out:Height of specified allocation
    D3DDDIFORMAT                    Format;                         //out:Format of specified allocation
    D3DDDI_MULTISAMPLINGMETHOD      MultisampleMethod;              //out:Multisample method used of specified allocation
    D3DDDI_RATIONAL                 RefreshRate;                    //out:RefreshRate the primary surface created with if applicable
    UINT                            PrivateDriverFormatAttribute;   //out:Private format attribute of specified allocation
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    DXGK_DESCRIBEALLOCATIONFLAGS    Flags;
    D3DDDI_ROTATION                 Rotation;                       //out:Rotation for display mode
#endif
} DXGKARG_DESCRIBEALLOCATION;

typedef _Inout_ DXGKARG_DESCRIBEALLOCATION*     INOUT_PDXGKARG_DESCRIBEALLOCATION;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_DESCRIBEALLOCATION)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_DESCRIBEALLOCATION(
    IN_CONST_HANDLE                         hAdapter,
    INOUT_PDXGKARG_DESCRIBEALLOCATION       pDescribeAllocation
    );

typedef struct _DXGKARG_GETSTANDARDALLOCATIONDRIVERDATA
{
    D3DKMDT_STANDARDALLOCATION_TYPE         StandardAllocationType;     // in : Type of standard allocation to describe
    union
    {
        D3DKMDT_SHAREDPRIMARYSURFACEDATA*   pCreateSharedPrimarySurfaceData;
        D3DKMDT_SHADOWSURFACEDATA*          pCreateShadowSurfaceData;
        D3DKMDT_STAGINGSURFACEDATA*         pCreateStagingSurfaceData;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN7)
        D3DKMDT_GDISURFACEDATA*             pCreateGdiSurfaceData;
#endif // DXGKDDI_INTERFACE_VERSION
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
        D3DKMDT_VIRTUALGPUSURFACEDATA*      pCreateVirtualGpuSurfaceData;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
    };
    VOID*                                   pAllocationPrivateDriverData;       // in/out : If non-NULL ptr to buffer driver should place the PrivateDriverData that describes the allocation associated with this standard allocation
    UINT                                    AllocationPrivateDriverDataSize;    // out : Size of buffer required to hold the PrivateDriverData that describes the allocation for this standard allocation
    VOID*                                   pResourcePrivateDriverData;         // in/out : If non-NULL ptr to buffer driver should place the PrivateDriverData that describes the resource associated with this standard allocation
    UINT                                    ResourcePrivateDriverDataSize;      // out : Size of buffer required to hold the PrivateDriverData that describes the resource for this standard allocation
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM_2_0)
    UINT                                    PhysicalAdapterIndex;               // in
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM_2_0)
} DXGKARG_GETSTANDARDALLOCATIONDRIVERDATA;

typedef _Inout_ DXGKARG_GETSTANDARDALLOCATIONDRIVERDATA*    INOUT_PDXGKARG_GETSTANDARDALLOCATIONDRIVERDATA;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_GETSTANDARDALLOCATIONDRIVERDATA)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_GETSTANDARDALLOCATIONDRIVERDATA(
    IN_CONST_HANDLE                                 hAdapter,
    INOUT_PDXGKARG_GETSTANDARDALLOCATIONDRIVERDATA  pGetStandardAllocationDriverData
    );

typedef struct _DXGK_DESTROYALLOCATIONFLAGS
{
    union
    {
        struct
        {
            UINT    DestroyResource : 1;    // 0x00000001
            UINT    Reserved        :31;    // 0xFFFFFFFE
        };
        UINT        Value;
    };
} DXGK_DESTROYALLOCATIONFLAGS;

typedef struct _DXGKARG_DESTROYALLOCATION
{
    UINT            NumAllocations;
    CONST HANDLE*   pAllocationList;
    HANDLE          hResource;
    DXGK_DESTROYALLOCATIONFLAGS Flags;
} DXGKARG_DESTROYALLOCATION;

typedef _In_ CONST DXGKARG_DESTROYALLOCATION*   IN_CONST_PDXGKARG_DESTROYALLOCATION;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_DESTROYALLOCATION)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_DESTROYALLOCATION(
    IN_CONST_HANDLE                         hAdapter,
    IN_CONST_PDXGKARG_DESTROYALLOCATION     pDestroyAllocation
    );

typedef struct _DXGK_PATCHFLAGS
{
    union
    {
        struct
        {
            UINT                    Paging              : 1;            // 0x00000001 command buffer is a paging buffer.
            UINT                    Present             : 1;            // 0x00000002 command buffer contain a present operation.
            UINT                    RedirectedPresent   : 1;            // 0x00000004 command buffer contains a redirected present operation.
            UINT                    NullRendering       : 1;            // 0x00000008 GPU should skip rendering of DMA buffer (perf analysis)
            UINT                    Reserved            :28;            // 0xFFFFFFF0
        };
        UINT                        Value;
    };
} DXGK_PATCHFLAGS;

typedef struct _DXGKARG_PATCH
{
    union
    {
        HANDLE                          hDevice;                                // in: driver device handle for driver not MultiEngineAware.
        HANDLE                          hContext;                               // in: driver context handle for MultiEngineAware driver.
    };
    UINT                            DmaBufferSegmentId;                         // in: segment id of DMA buffer
    PHYSICAL_ADDRESS                DmaBufferPhysicalAddress;                   // in: physical address of DMA buffer
    VOID*                           pDmaBuffer;                                 // in: Virtual address to beginning of
                                                                                //     the DMA buffer.
    UINT                            DmaBufferSize;                              // in: length of the DMA buffer..
    UINT                            DmaBufferSubmissionStartOffset;             // in: Byte offset from the beginning
                                                                                //     of the DMA buffer to the start
                                                                                //     of this submission.
    UINT                            DmaBufferSubmissionEndOffset;               // in: Byte offset from the beginning
                                                                                //     of the DMA buffer to the end of
                                                                                //     this submission.
    VOID*                           pDmaBufferPrivateData;                      // in: Virtual address to the private
                                                                                //     data associated with this DMA buffer.
    UINT                            DmaBufferPrivateDataSize;                   // in: Size of the private data.
    UINT                            DmaBufferPrivateDataSubmissionStartOffset;  // in: Byte offset from the beginning of the
                                                                                //     private data to the start of this
                                                                                //     submission.
    UINT                            DmaBufferPrivateDataSubmissionEndOffset;    // in: Byte offset from the beginning of the
                                                                                //     private data to the end of this
                                                                                //     submission.
    CONST DXGK_ALLOCATIONLIST*      pAllocationList;                            // in: Pointer to the allocation list
                                                                                //     associated with this DMA buffer.
    UINT                            AllocationListSize;                         // in: Size of the allocation list.
    CONST D3DDDI_PATCHLOCATIONLIST* pPatchLocationList;                         // in: Pointer to the patch location list associated
                                                                                //     with this DMA buffer.
    UINT                            PatchLocationListSize;                      // in: Size of the patch location list.
    UINT                            PatchLocationListSubmissionStart;           // in: First element for this submission.
    UINT                            PatchLocationListSubmissionLength;          // in: Number of element in this submission.
    UINT                            SubmissionFenceId;                          // in: Submission fence id.
    DXGK_PATCHFLAGS                 Flags;                                      // in: Flags
    UINT                            EngineOrdinal;                              // in: Engine Ordinal within it's node.
} DXGKARG_PATCH;

typedef _In_ CONST DXGKARG_PATCH*   IN_CONST_PDXGKARG_PATCH;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_PATCH)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_PATCH(
    IN_CONST_HANDLE             hAdapter,
    IN_CONST_PDXGKARG_PATCH     pPatch
    );

typedef struct _DXGK_SUBMITCOMMANDFLAGS
{
    union
    {
        struct
        {
            UINT        Paging              : 1;    // command buffer is a paging buffer.
            UINT        Present             : 1;    // command buffer contain a present operation.
            UINT        RedirectedPresent   : 1;    // command buffer contains a redirected present operation.
            UINT        NullRendering       : 1;    // GPU should skip rendering of DMA buffer (perf analysis)
            UINT        Flip                : 1;    // command buffer is for flip.
            UINT        FlipWithNoWait      : 1;    // command buffer is for flip with no built-in-wait for next vsync.
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
            UINT        ContextSwitch       : 1;    // GPU should switch from the last executed context on this node to the null context.
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
            UINT        Resubmission        : 1;    // Indicates whether this DMA packet is being resubmitted to the GPU due to an earlier preemption.
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
            UINT        VirtualMachineData  : 1;    // Indicates that the submission is from a paravirtualized adapter.
            UINT        Reserved            :23;
#else
            UINT        Reserved            :24;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
#else
            UINT        Reserved            :25;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
#else
            UINT        Reserved            :26;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
        };
        UINT            Value;
    };
} DXGK_SUBMITCOMMANDFLAGS;

// Definition for DXGKARG_SUBMITCOMMAND
//
typedef struct _DXGKARG_SUBMITCOMMAND
{
    union
    {
        HANDLE          hDevice;                                    // in: driver device handle for driver not MultiEngineAware.
        HANDLE          hContext;                                   // in: driver context handle for MultiEngineAware driver.
    };
    UINT                DmaBufferSegmentId;                         // in: segment id of DMA buffer
    PHYSICAL_ADDRESS    DmaBufferPhysicalAddress;                   // in: physical address of DMA buffer
    UINT                DmaBufferSize;                              // in: length of the DMA buffer..
    UINT                DmaBufferSubmissionStartOffset;             // in: Byte offset from the beginning
                                                                    //     of the DMA buffer to the start
                                                                    //     of this submission.
    UINT                DmaBufferSubmissionEndOffset;               // in: Byte offset from the beginning
                                                                    //     of the DMA buffer to the end of
                                                                    //     this submission.
    VOID*               pDmaBufferPrivateData;                      // in: Virtual address to the private
                                                                    //     data associated with this DMA buffer.
    UINT                DmaBufferPrivateDataSize;                   // in: Size of the private data.
    UINT                DmaBufferPrivateDataSubmissionStartOffset;  // in: Byte offset from the beginning of the
                                                                    //     private data to the start of this
                                                                    //     submission.
    UINT                DmaBufferPrivateDataSubmissionEndOffset;    // in: Byte offset from the beginning of the
                                                                    //     private data to the end of this
                                                                    //     submission.
    UINT                SubmissionFenceId;                          // in: Submission fence id.
    D3DDDI_VIDEO_PRESENT_SOURCE_ID VidPnSourceId;                   // in: VidPnSourceId (flip only)
    D3DDDI_FLIPINTERVAL_TYPE       FlipInterval;                    // in: Flip Interval (flip only)
    DXGK_SUBMITCOMMANDFLAGS Flags;                                  // in: Flags
    UINT                EngineOrdinal;                              // in: Engine Ordinal within it's node.
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN7)
    D3DGPU_VIRTUAL_ADDRESS DmaBufferVirtualAddress;                 // in: M1 temporary _ADVSCH_
#endif // DXGKDDI_INTERFACE_VERSION
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    UINT                NodeOrdinal;                                // in: NodeOrdinal to identify the node when hContext is NULL.
#endif // DXGKDDI_INTERFACE_VERSION
} DXGKARG_SUBMITCOMMAND;

// Device Driver Interface to submit command buffer to h/w command execution unit.
//
typedef _In_ CONST DXGKARG_SUBMITCOMMAND*   IN_CONST_PDXGKARG_SUBMITCOMMAND;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_SUBMITCOMMAND)
    _IRQL_requires_(DISPATCH_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_SUBMITCOMMAND(
    IN_CONST_HANDLE                     hAdapter,
    IN_CONST_PDXGKARG_SUBMITCOMMAND     pSubmitCommand
    );

typedef struct _DXGK_PREEMPTCOMMANDFLAGS
{
    union
    {
        struct
        {
            UINT        Reserved    :32;    // 0xFFFFFFFF
        };
        UINT            Value;
    };
} DXGK_PREEMPTCOMMANDFLAGS;

// Definition for DXGKARG_PREEMPTCOMMAND
//
typedef struct _DXGKARG_PREEMPTCOMMAND
{
    UINT                PreemptionFenceId;  // in: preemption uniqueness id
    UINT                NodeOrdinal;        // in: node ordinal to preempt
    UINT                EngineOrdinal;      // in: engine ordinal to preempt
    DXGK_PREEMPTCOMMANDFLAGS Flags;         // in: flags
} DXGKARG_PREEMPTCOMMAND;

// Device Driver Interface to preempt command.
//
typedef _In_ CONST DXGKARG_PREEMPTCOMMAND*      IN_CONST_PDXGKARG_PREEMPTCOMMAND;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_PREEMPTCOMMAND)
    _IRQL_requires_(DISPATCH_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_PREEMPTCOMMAND(
    IN_CONST_HANDLE                     hAdapter,
    IN_CONST_PDXGKARG_PREEMPTCOMMAND    pPreemptCommand
    );

// Device Driver Interface to cancel a command that won't be submitted to hardware.
//
typedef struct _DXGKARG_CANCELCOMMAND
{
    HANDLE                          hContext;                                   // in: driver context handle.
    VOID*                           pDmaBuffer;                                 // in: CPU address of the DMA buffer.
    UINT                            DmaBufferSize;                              // in: length of the DMA buffer.
    UINT                            DmaBufferSubmissionStartOffset;             // in: Byte offset from the beginning
                                                                                //     of the DMA buffer to the start
                                                                                //     of this submission.
    UINT                            DmaBufferSubmissionEndOffset;               // in: Byte offset from the beginning
                                                                                //     of the DMA buffer to the end of
                                                                                //     this submission.
    VOID*                           pDmaBufferPrivateData;                      // in: Virtual address to the private
                                                                                //     data associated with this DMA buffer.
    UINT                            DmaBufferPrivateDataSize;                   // in: Size of the private data.
    UINT                            DmaBufferPrivateDataSubmissionStartOffset;  // in: Byte offset from the beginning of the
                                                                                //     private data to the start of this
                                                                                //     submission.
    UINT                            DmaBufferPrivateDataSubmissionEndOffset;    // in: Byte offset from the beginning of the
                                                                                //     private data to the end of this
                                                                                //     submission.
    CONST DXGK_ALLOCATIONLIST*      pAllocationList;                            // in: Pointer to the allocation list
                                                                                //     associated with this DMA buffer.
    UINT                            AllocationListSize;                         // in: Size of the allocation list.
    CONST D3DDDI_PATCHLOCATIONLIST* pPatchLocationList;                         // in: Pointer to the patch location list associated
                                                                                //     with this DMA buffer.
    UINT                            PatchLocationListSize;                      // in: Size of the patch location list.
    UINT                            PatchLocationListSubmissionStart;           // in: First element for this submission.
    UINT                            PatchLocationListSubmissionLength;          // in: Number of element in this submission.
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
    D3DGPU_VIRTUAL_ADDRESS          DmaBufferVirtualAddress;                    // in: Virtual address of the DMA buffer for virtual contexts
    UINT                            DmaBufferUmdPrivateDataSize;                // in: The size of the private driver data passed from UMD
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
} DXGKARG_CANCELCOMMAND;

typedef _In_ CONST DXGKARG_CANCELCOMMAND*   IN_CONST_PDXGKARG_CANCELCOMMAND;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_CANCELCOMMAND)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_CANCELCOMMAND(
    IN_CONST_HANDLE                 hAdapter,
    IN_CONST_PDXGKARG_CANCELCOMMAND pCancelCommand
    );

// Definition for DXGKARG_QUERYCURRENTFENCE
//
typedef struct _DXGKARG_QUERYCURRENTFENCE
{
    UINT     CurrentFence;
    UINT     NodeOrdinal;
    UINT     EngineOrdinal;
} DXGKARG_QUERYCURRENTFENCE;

// Device Driver Interface to query completed submission fence.
//
typedef _Inout_ DXGKARG_QUERYCURRENTFENCE* INOUT_PDXGKARG_QUERYCURRENTFENCE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_QUERYCURRENTFENCE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_QUERYCURRENTFENCE(
    IN_CONST_HANDLE                    hAdapter,
    INOUT_PDXGKARG_QUERYCURRENTFENCE   pCurrentFence
    );

// Device Driver Interface to control vertical sync interrupt.
//
typedef _In_ CONST DXGK_INTERRUPT_TYPE      IN_CONST_DXGK_INTERRUPT_TYPE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_CONTROLINTERRUPT)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_CONTROLINTERRUPT(
    IN_CONST_HANDLE                 hAdapter,
    IN_CONST_DXGK_INTERRUPT_TYPE    InterruptType,
    IN_BOOLEAN                      EnableInterrupt
    );

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)

//
// WDDM 1.3 DDI for controlling interrupts by extended state
//

// NON-CRTC_VSYNC states
typedef enum _DXGK_INTERRUPT_STATE
{
    DXGK_INTERRUPT_ENABLE    = 0,
    DXGK_INTERRUPT_DISABLE   = 1,
} DXGK_INTERRUPT_STATE;

// CRTC_VSYNC states
typedef enum _DXGK_CRTC_VSYNC_STATE
{
    DXGK_VSYNC_ENABLE              = 0,
    DXGK_VSYNC_DISABLE_KEEP_PHASE  = 1,
    DXGK_VSYNC_DISABLE_NO_PHASE    = 2,
} DXGK_CRTC_VSYNC_STATE;

typedef struct _DXGKARG_CONTROLINTERRUPT2
{
  DXGK_INTERRUPT_TYPE InterruptType;
  union
  {
      DXGK_INTERRUPT_STATE           InterruptState;
      DXGK_CRTC_VSYNC_STATE          CrtcVsyncState;
  };
} DXGKARG_CONTROLINTERRUPT2;

typedef _In_ CONST DXGKARG_CONTROLINTERRUPT2 IN_CONST_DXGKARG_CONTROLINTERRUPT2;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_CONTROLINTERRUPT2)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_CONTROLINTERRUPT2(
    IN_CONST_HANDLE                      hAdapter,
    IN_CONST_DXGKARG_CONTROLINTERRUPT2   InterruptControl
    );

#endif // DXGKDDI_INTERFACE_VERSION_WDDM1_3

typedef enum _DXGK_BUILDPAGINGBUFFER_OPERATION
{
    DXGK_OPERATION_TRANSFER                 = 0,    // WDDMv1 Only
    DXGK_OPERATION_FILL                     = 1,    // WDDMv1 Only
    DXGK_OPERATION_DISCARD_CONTENT          = 2,    // WDDMv1 Only
    DXGK_OPERATION_READ_PHYSICAL            = 3,    // WDDMv1 Only
    DXGK_OPERATION_WRITE_PHYSICAL           = 4,    // WDDMv1 Only
    DXGK_OPERATION_MAP_APERTURE_SEGMENT     = 5,    // Common WDDMv1 & WDDMv2
    DXGK_OPERATION_UNMAP_APERTURE_SEGMENT   = 6,    // Common WDDMv1 & WDDMv2
    DXGK_OPERATION_SPECIAL_LOCK_TRANSFER    = 7,    // WDDMv1 Only
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN7)
    DXGK_OPERATION_VIRTUAL_TRANSFER         = 8,    // WDDMv2 Only
    DXGK_OPERATION_VIRTUAL_FILL             = 9,    // WDDMv2 Only
#endif // DXGKDDI_INTERFACE_VERSION
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
    DXGK_OPERATION_INIT_CONTEXT_RESOURCE    = 10,   // Common WDDMv1 & WDDMv2
#endif // DXGKDDI_INTERFACE_VERSION
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
    DXGK_OPERATION_UPDATE_PAGE_TABLE        = 11,
    DXGK_OPERATION_FLUSH_TLB                = 12,
    DXGK_OPERATION_UPDATE_CONTEXT_ALLOCATION = 13,
    DXGK_OPERATION_COPY_PAGE_TABLE_ENTRIES  = 14,
    DXGK_OPERATION_NOTIFY_RESIDENCY         = 15,
#endif //  DXGKDDI_INTERFACE_VERSION
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
    DXGK_OPERATION_SIGNAL_MONITORED_FENCE   = 16,
#endif //  DXGKDDI_INTERFACE_VERSION
} DXGK_BUILDPAGINGBUFFER_OPERATION;

typedef struct _DXGK_TRANSFERFLAGS
{
    union
    {
        struct
        {
            UINT    Swizzle             : 1;    // 0x00000001
            UINT    Unswizzle           : 1;    // 0x00000002
            UINT    AllocationIsIdle    : 1;    // 0x00000004
            UINT    TransferStart       : 1;    // 0x00000008
            UINT    TransferEnd         : 1;    // 0x00000010
            UINT    Reserved            :27;    // 0xFFFFFFE0
        };
        UINT        Value;
    };
} DXGK_TRANSFERFLAGS;

typedef struct _DXGK_DISCARDCONTENTFLAGS
{
    union
    {
        struct
        {
            UINT    AllocationIsIdle    : 1;    // 0x00000001
            UINT    Reserved            :31;    // 0xFFFFFFFE
        };
        UINT        Value;
    };
} DXGK_DISCARDCONTENTFLAGS;

typedef struct _DXGK_MAPAPERTUREFLAGS
{
    union
    {
        struct
        {
            UINT    CacheCoherent   : 1;    // 0x00000001
            UINT    Reserved        :31;    // 0xFFFFFFFE
        };
        UINT Value;
    };
} DXGK_MAPAPERTUREFLAGS;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
typedef struct _DXGK_BUILDPAGINGBUFFER_COPY_RANGE
{
    UINT                    NumPageTableEntries;
    D3DGPU_VIRTUAL_ADDRESS  SrcPageTableAddress;
    D3DGPU_VIRTUAL_ADDRESS  DstPageTableAddress;
    UINT                    SrcStartPteIndex;
    UINT                    DstStartPteIndex;
} DXGK_BUILDPAGINGBUFFER_COPY_RANGE;

typedef struct _DXGK_BUILDPAGINGBUFFER_FLUSHTLB
{
    D3DGPU_PHYSICAL_ADDRESS RootPageTableAddress;
    HANDLE                  hProcess;
    D3DGPU_VIRTUAL_ADDRESS  StartVirtualAddress;
    D3DGPU_VIRTUAL_ADDRESS  EndVirtualAddress;
} DXGK_BUILDPAGINGBUFFER_FLUSHTLB;

typedef struct _DXGK_BUILDPAGINGBUFFER_UPDATEPAGETABLE
{
    UINT                        PageTableLevel;
    HANDLE                      hAllocation;
    DXGK_PAGETABLEUPDATEADDRESS PageTableAddress;
    DXGK_PTE*                   pPageTableEntries;
    UINT                        StartIndex;
    UINT                        NumPageTableEntries;
    UINT                        Reserved0;
    DXGK_UPDATEPAGETABLEFLAGS   Flags;
    UINT64                      DriverProtection;
    UINT64                      AllocationOffsetInBytes;
    HANDLE                      hProcess;
    DXGK_PAGETABLEUPDATEMODE    UpdateMode;
    DXGK_PTE*                   pPageTableEntries64KB;
    D3DGPU_VIRTUAL_ADDRESS      FirstPteVirtualAddress;
} DXGK_BUILDPAGINGBUFFER_UPDATEPAGETABLE;

typedef struct _DXGK_BUILDPAGINGBUFFER_FILLVIRTUAL
{
    HANDLE  hAllocation;
    UINT64  AllocationOffsetInBytes;
    UINT64  FillSizeInBytes;
    UINT    FillPattern;
    D3DGPU_VIRTUAL_ADDRESS DestinationVirtualAddress;
} DXGK_BUILDPAGINGBUFFER_FILLVIRTUAL;

typedef enum _DXGK_MEMORY_TRANSFER_DIRECTION
{
    DXGK_MEMORY_TRANSFER_LOCAL_TO_SYSTEM = 0,
    DXGK_MEMORY_TRANSFER_SYSTEM_TO_LOCAL = 1,
    DXGK_MEMORY_TRANSFER_LOCAL_TO_LOCAL  = 2,
} DXGK_MEMORY_TRANSFER_DIRECTION;

typedef struct _DXGK_TRANSFERVIRTUALFLAGS
{
   union
   {
        struct
        {
            UINT Src64KBPages   : 1;
            UINT Dst64KBPages   : 1;
            UINT Reserved       : 30;
        };
        UINT Flags;
   };
} DXGK_TRANSFERVIRTUALFLAGS;

typedef struct _DXGK_BUILDPAGINGBUFFER_TRANSFERVIRTUAL
{
    HANDLE                          hAllocation;
    UINT64                          AllocationOffsetInBytes;
    UINT64                          TransferSizeInBytes;
    D3DGPU_VIRTUAL_ADDRESS          SourceVirtualAddress;
    D3DGPU_VIRTUAL_ADDRESS          DestinationVirtualAddress;
    D3DGPU_VIRTUAL_ADDRESS          SourcePageTable;
    DXGK_MEMORY_TRANSFER_DIRECTION  TransferDirection;
    DXGK_TRANSFERVIRTUALFLAGS       Flags;
    D3DGPU_VIRTUAL_ADDRESS          DestinationPageTable;
} DXGK_BUILDPAGINGBUFFER_TRANSFERVIRTUAL;

typedef struct _DXGK_BUILDPAGINGBUFFER_NOTIFYRESIDENCY
{
    HANDLE                  hAllocation;
    D3DGPU_PHYSICAL_ADDRESS PhysicalAddress;
    union 
    {
        UINT Resident  : 1;
        UINT Reserved  : 31;
    };
} DXGK_BUILDPAGINGBUFFER_NOTIFYRESIDENCY;

typedef struct _DXGK_BUILDPAGINGBUFFER_COPYPAGETABLEENTRIES
{
    UINT                                NumRanges;
    DXGK_BUILDPAGINGBUFFER_COPY_RANGE*  pRanges;
} DXGK_BUILDPAGINGBUFFER_COPYPAGETABLEENTRIES;

typedef struct _DXGK_BUILDPAGINGBUFFER_UPDATECONTEXTALLOCATION
{
    D3DGPU_VIRTUAL_ADDRESS  ContextAllocation;
    UINT64                  ContextAllocationSize;
    PVOID                   pDriverPrivateData;
    UINT                    DriverPrivateDataSize;
} DXGK_BUILDPAGINGBUFFER_UPDATECONTEXTALLOCATION;

#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

typedef struct _DXGK_BUILDPAGINGBUFFER_SIGNALMONITOREDFENCE
{
    D3DGPU_VIRTUAL_ADDRESS  MonitoredFenceGpuVa;
    UINT64                  MonitoredFenceValue;
} DXGK_BUILDPAGINGBUFFER_SIGNALMONITOREDFENCE;

#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

typedef struct _DXGKARG_BUILDPAGINGBUFFER
{
    VOID*                                   pDmaBuffer;
    UINT                                    DmaSize;
    VOID*                                   pDmaBufferPrivateData;
    UINT                                    DmaBufferPrivateDataSize;
    DXGK_BUILDPAGINGBUFFER_OPERATION        Operation;
    UINT                                    MultipassOffset;
    union
    {
        struct
        {
            HANDLE  hAllocation;
            UINT    TransferOffset;
            SIZE_T  TransferSize;
            struct
            {
                UINT    SegmentId;
                union
                {
                    LARGE_INTEGER SegmentAddress;
                    MDL* pMdl;
                };
            } Source;
            struct
            {
                UINT    SegmentId;
                union
                {
                    LARGE_INTEGER SegmentAddress;
                    MDL* pMdl;
                };
            } Destination;
            DXGK_TRANSFERFLAGS  Flags;
            UINT MdlOffset;
        } Transfer;

        struct
        {
            HANDLE  hAllocation;
            SIZE_T  FillSize;
            UINT    FillPattern;
            struct
            {
                UINT SegmentId;
                LARGE_INTEGER SegmentAddress;
            } Destination;
        } Fill;

        struct
        {
            HANDLE hAllocation;
            DXGK_DISCARDCONTENTFLAGS Flags;
            UINT SegmentId;
            PHYSICAL_ADDRESS SegmentAddress;
        } DiscardContent;

        struct
        {
            UINT SegmentId;
            PHYSICAL_ADDRESS PhysicalAddress;
        } ReadPhysical;

        struct
        {
            UINT SegmentId;
            PHYSICAL_ADDRESS PhysicalAddress;
        } WritePhysical;

        struct
        {
            HANDLE  hDevice;
            HANDLE  hAllocation;
            UINT    SegmentId;
            SIZE_T  OffsetInPages;
            SIZE_T  NumberOfPages;
            PMDL    pMdl;
            DXGK_MAPAPERTUREFLAGS Flags;
            ULONG   MdlOffset;
        } MapApertureSegment;

        struct
        {
            HANDLE  hDevice;
            HANDLE  hAllocation;
            UINT    SegmentId;
            SIZE_T  OffsetInPages;
            SIZE_T  NumberOfPages;
            PHYSICAL_ADDRESS DummyPage;
        } UnmapApertureSegment;

        struct
        {
            HANDLE hAllocation;
            UINT   TransferOffset;
            SIZE_T TransferSize;
            struct
            {
                UINT SegmentId;
                union
                {
                    LARGE_INTEGER SegmentAddress;
                    MDL* pMdl;
                };
            } Source;
            struct
            {
                UINT SegmentId;
                union
                {
                    LARGE_INTEGER SegmentAddress;
                    MDL* pMdl;
                };
            } Destination;
            DXGK_TRANSFERFLAGS  Flags;
            UINT SwizzlingRangeId;
            UINT SwizzlingRangeData;
        } SpecialLockTransfer;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)

        struct
        {
            HANDLE  hAllocation;
            struct
            {
                UINT SegmentId;
                union
                {
                    LARGE_INTEGER SegmentAddress;
                    MDL* pMdl;
                };
                PVOID VirtualAddress;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
                D3DGPU_VIRTUAL_ADDRESS GpuVirtualAddress;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
            } Destination;
        } InitContextResource;

#endif // DXGKDDI_INTERFACE_VERSION

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

        DXGK_BUILDPAGINGBUFFER_TRANSFERVIRTUAL          TransferVirtual;
        DXGK_BUILDPAGINGBUFFER_FILLVIRTUAL              FillVirtual;
        DXGK_BUILDPAGINGBUFFER_UPDATEPAGETABLE          UpdatePageTable;
        DXGK_BUILDPAGINGBUFFER_FLUSHTLB                 FlushTlb;
        DXGK_BUILDPAGINGBUFFER_COPYPAGETABLEENTRIES     CopyPageTableEntries;    
        DXGK_BUILDPAGINGBUFFER_UPDATECONTEXTALLOCATION  UpdateContextAllocation;    
        DXGK_BUILDPAGINGBUFFER_NOTIFYRESIDENCY          NotifyResidency;    

#endif // DXGKDDI_INTERFACE_VERSION

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

        DXGK_BUILDPAGINGBUFFER_SIGNALMONITOREDFENCE     SignalMonitoredFence;

#endif // DXGKDDI_INTERFACE_VERSION

        struct
        {
            UINT    Reserved[64];
        } Reserved;
    };
    HANDLE hSystemContext;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
    D3DGPU_VIRTUAL_ADDRESS DmaBufferGpuVirtualAddress;      // GPU virtual address of the start of the DMA buffer
    UINT                   DmaBufferWriteOffset;            // Current operation offset in bytes from the start of the DMA buffer. 
                                                            // Available starting from version 0x5012.
#endif // DXGKDDI_INTERFACE_VERSION
} DXGKARG_BUILDPAGINGBUFFER;

// Device Driver Interface to build a paging buffer.
//
typedef _In_ DXGKARG_BUILDPAGINGBUFFER*     IN_PDXGKARG_BUILDPAGINGBUFFER;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_BUILDPAGINGBUFFER)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_BUILDPAGINGBUFFER(
    IN_CONST_HANDLE                 hAdapter,
    IN_PDXGKARG_BUILDPAGINGBUFFER   pBuildPagingBuffer
    );

// DXGK_TRANSFERFLAGS.Swizzle
//
//   This indicates that the source should be swizzled to the destination.
//
// DXGK_TRANSFERFLAGS.Unswizzle
//
//   This indicates that the source should be unswizzled to the destination.
//
// DXGK_TRANSFERFLAGS.AllocationIsIdle
//
//   This indicates that the given allocation is idle, i.e. no work
//   has been queued or will be queued to the GPU referencing this
//   allocation until the call to DdiBuildPagingBuffer returns.
//
// DXGK_TRANSFERFLAGS.FillDestination
//
//   This indicates that the driver should fill the destination
//   with the provided pattern. No source is provided.
//

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

typedef struct _DXGKARG_SETROOTPAGETABLE
{
   HANDLE                   hContext;
   D3DGPU_PHYSICAL_ADDRESS  Address;
   UINT                     NumEntries;
} DXGKARG_SETROOTPAGETABLE;

typedef _In_ CONST DXGKARG_SETROOTPAGETABLE*  IN_CONST_PDXGKARG_SETROOTPAGETABLE;

typedef
    _Function_class_DXGK_(DXGKDDI_SETROOTPAGETABLE)
    _IRQL_requires_(PASSIVE_LEVEL)
VOID
APIENTRY
DXGKDDI_SETROOTPAGETABLE(
    IN_CONST_HANDLE                     hAdapter,
    IN_CONST_PDXGKARG_SETROOTPAGETABLE  pSetPageTable
    );

typedef struct _DXGKARG_GETROOTPAGETABLESIZE
{
    UINT    NumberOfPte;            // In/Out
    UINT    PhysicalAdapterIndex;   // In
} DXGKARG_GETROOTPAGETABLESIZE;
typedef _Inout_ DXGKARG_GETROOTPAGETABLESIZE*  INOUT_PDXGKARG_GETROOTPAGETABLESIZE;

typedef
    _Function_class_DXGK_(DXGKDDI_GETROOTPAGETABLESIZE)
    _IRQL_requires_(PASSIVE_LEVEL)
SIZE_T
APIENTRY
DXGKDDI_GETROOTPAGETABLESIZE(
    IN_CONST_HANDLE hAdapter,
    INOUT_PDXGKARG_GETROOTPAGETABLESIZE pArgs
    );

typedef struct _DXGK_CREATEPROCESSFLAGS
{
    union
    {
        struct
        {
            UINT    SystemProcess           : 1;
            UINT    GdiProcess              : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
            UINT    VirtualMachineProcess   : 1;
            UINT    Reserved                : 29;
#else
            UINT    Reserved                : 30;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
        };
        UINT Value;
    };
} DXGK_CREATEPROCESSFLAGS;

typedef struct _DXGKARG_CREATEPROCESS
{
    HANDLE                  hDxgkProcess;   // in
    HANDLE                  hKmdProcess;    // out
    DXGK_CREATEPROCESSFLAGS Flags;          // in 
    UINT                    NumPasid;       // in
    _Field_size_(NumPasid)
    ULONG*                  pPasid;         // in
} DXGKARG_CREATEPROCESS;
typedef _Inout_ DXGKARG_CREATEPROCESS*   INOUT_PDXGKARG_CREATEPROCESS;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_CREATEPROCESS)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_CREATEPROCESS(
    IN_CONST_HANDLE             hAdapter,
    INOUT_PDXGKARG_CREATEPROCESS   pArgs
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_DESTROYPROCESS)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_DESTROYPROCESS(
    IN_CONST_HANDLE hAdapter,
    IN_CONST_HANDLE hKmdProcess
    );

typedef struct _DXGKARG_SUBMITCOMMANDVIRTUAL
{
    HANDLE                          hContext;
    D3DGPU_VIRTUAL_ADDRESS          DmaBufferVirtualAddress;
    UINT                            DmaBufferSize;
    VOID*                           pDmaBufferPrivateData;
    UINT                            DmaBufferPrivateDataSize;
    UINT                            DmaBufferUmdPrivateDataSize;
    UINT                            SubmissionFenceId;
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;
    D3DDDI_FLIPINTERVAL_TYPE        FlipInterval;
    DXGK_SUBMITCOMMANDFLAGS         Flags;
    UINT                            EngineOrdinal;
    UINT                            NodeOrdinal;
} DXGKARG_SUBMITCOMMANDVIRTUAL;

typedef _In_ CONST DXGKARG_SUBMITCOMMANDVIRTUAL*   IN_CONST_PDXGKARG_SUBMITCOMMANDVIRTUAL;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_SUBMITCOMMANDVIRTUAL)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_SUBMITCOMMANDVIRTUAL(
    IN_CONST_HANDLE                         hAdapter,
    IN_CONST_PDXGKARG_SUBMITCOMMANDVIRTUAL  pSubmitCommand
    );

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

typedef struct _DXGKARG_SUBMITCOMMANDTOHWQUEUE
{
    HANDLE                          hHwQueue;
    UINT64                          HwQueueProgressFenceId; // Hardware queue progress fence ID that will be signaled upon this DMA buffer completion.
    D3DGPU_VIRTUAL_ADDRESS          DmaBufferVirtualAddress;
    UINT                            DmaBufferSize;
    UINT                            DmaBufferPrivateDataSize;
    _Field_size_bytes_             (DmaBufferPrivateDataSize)
    VOID*                           pDmaBufferPrivateData;
    UINT                            DmaBufferUmdPrivateDataSize;
} DXGKARG_SUBMITCOMMANDTOHWQUEUE;

typedef _In_ CONST DXGKARG_SUBMITCOMMANDTOHWQUEUE*   IN_CONST_PDXGKARG_SUBMITCOMMANDTOHWQUEUE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_SUBMITCOMMANDTOHWQUEUE)
    _IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_SUBMITCOMMANDTOHWQUEUE(
    IN_CONST_HANDLE                             hAdapter,
    IN_CONST_PDXGKARG_SUBMITCOMMANDTOHWQUEUE    pSubmitCommandToHwQueue
    );

typedef struct _DXGKARG_SWITCHTOHWCONTEXTLIST
{
    HANDLE  hHwContextFirst;    // Hardware context that should be executed by the GPU first. If the GPU is currently not executing this context,
                                // it needs to preempt the current work and switch to hHwContextFirst.
                                // May be NULL if the GPU is instructed to become idle.
    HANDLE  hHwContextSecond;   // Hardware context that should be executed by the GPU
                                // once all queues in hHwContextFirst are idle or blocked on waits.
                                // May be NULL.
    UINT    NodeOrdinal;        // Node ordinal of engine that is instructed to switch to the new context(s).
    UINT    EngineOrdinal;      // Engine ordinal of engine that is instructed to switch to the new context(s).
} DXGKARG_SWITCHTOHWCONTEXTLIST;

typedef _In_ CONST DXGKARG_SWITCHTOHWCONTEXTLIST*   IN_CONST_PDXGKARG_SWITCHTOHWCONTEXTLIST;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_SWITCHTOHWCONTEXTLIST)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_SWITCHTOHWCONTEXTLIST(
    IN_CONST_HANDLE                             hAdapter,
    IN_CONST_PDXGKARG_SWITCHTOHWCONTEXTLIST pHwContextList
    );

#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)

typedef struct _DXGK_UPDATEHWCONTEXTSTATE_FLAGS
{
    union
    {
        struct
        {
            UINT Suspended                      : 1;    // The context is asked to be suspended. Otherwise, the context is runnable.
            UINT InterruptOnSwitchCompletion    : 1;    // HW is required to raise DXGK_INTERRUPT_HWCONTEXTLIST_SWITCH_COMPLETED
                                                        // interrupt when the context state update is effective on the GPU.
            UINT Reserved                       :30;
        };
        UINT Value;
    };
} DXGK_UPDATEHWCONTEXTSTATE_FLAGS;

typedef struct _DXGKARG_UPDATEHWCONTEXTSTATE
{
    HANDLE                          hHwContext;         // Hardware context whose priority or execution state is being changed.
    UINT64                          ContextSwitchFence; // Context switch fence value associated with this state change request.
    UINT                            Priority;           // Execution priority of this context relative to other running contexts on this node.
    DXGK_UPDATEHWCONTEXTSTATE_FLAGS Flags;              // Context execution state flags.
} DXGKARG_UPDATEHWCONTEXTSTATE;

typedef _In_ CONST DXGKARG_UPDATEHWCONTEXTSTATE*   IN_CONST_PDXGKARG_UPDATEHWCONTEXTSTATE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_UPDATEHWCONTEXTSTATE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_UPDATEHWCONTEXTSTATE(
    IN_CONST_HANDLE                        hAdapter,
    IN_CONST_PDXGKARG_UPDATEHWCONTEXTSTATE pUpdateHwContextState
    );

#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)

typedef struct _DXGKARG_RENDERGDI
{
    CONST VOID* CONST           pCommand;
    CONST UINT                  CommandLength;
    VOID*                       pDmaBuffer;
    D3DGPU_VIRTUAL_ADDRESS      DmaBufferGpuVirtualAddress;
    UINT                        DmaSize;
    VOID*                       pDmaBufferPrivateData;
    UINT                        DmaBufferPrivateDataSize;
    DXGK_ALLOCATIONLIST*        pAllocationList;
    UINT                        AllocationListSize;
    UINT                        MultipassOffset;
} DXGKARG_RENDERGDI;

typedef _Inout_ DXGKARG_RENDERGDI*   INOUT_PDXGKARG_RENDERGDI;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_RENDERGDI)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_RENDERGDI(
    IN_CONST_HANDLE          hContext,
    INOUT_PDXGKARG_RENDERGDI pRenderGdi
    );

typedef struct _DXGKARG_MAPCPUHOSTAPERTURE
{ 
    HANDLE  hAllocation;
    WORD    SegmentId;
    WORD    PhysicalAdapterIndex;
    UINT64  NumberOfPages;
    UINT32* pCpuHostAperturePages;
    UINT64* pMemorySegmentPages;
} DXGKARG_MAPCPUHOSTAPERTURE;

typedef _In_ CONST DXGKARG_MAPCPUHOSTAPERTURE*   IN_CONST_PDXGKARG_MAPCPUHOSTAPERTURE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MAPCPUHOSTAPERTURE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_MAPCPUHOSTAPERTURE(
    IN_CONST_HANDLE                      hAdapter,
    IN_CONST_PDXGKARG_MAPCPUHOSTAPERTURE pArgs
    );

typedef struct _DXGKARG_UNMAPCPUHOSTAPERTURE
{ 
    UINT64  NumberOfPages;
    UINT32* pCpuHostAperturePages;
    WORD    SegmentId;
    WORD    PhysicalAdapterIndex;
} DXGKARG_UNMAPCPUHOSTAPERTURE;

typedef _In_ CONST DXGKARG_UNMAPCPUHOSTAPERTURE*   IN_CONST_PDXGKARG_UNMAPCPUHOSTAPERTURE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_UNMAPCPUHOSTAPERTURE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_UNMAPCPUHOSTAPERTURE(
    IN_CONST_HANDLE                         hAdapter,
    IN_CONST_PDXGKARG_UNMAPCPUHOSTAPERTURE  pArgs
    );

typedef struct DXGKARG_SETSTABLEPOWERSTATE
{ 
    BOOL Enabled;
} DXGKARG_SETSTABLEPOWERSTATE;

typedef _In_ CONST DXGKARG_SETSTABLEPOWERSTATE*   IN_CONST_PDXGKARG_SETSTABLEPOWERSTATE;

typedef
    _Function_class_DXGK_(DXGKDDI_SETSTABLEPOWERSTATE)
    _IRQL_requires_(PASSIVE_LEVEL)
VOID
APIENTRY
DXGKDDI_SETSTABLEPOWERSTATE(
    IN_CONST_HANDLE                        hAdapter,
    IN_CONST_PDXGKARG_SETSTABLEPOWERSTATE  pArgs
    );

typedef struct _DXGKARG_SETVIDEOPROTECTEDREGION
{
    UINT    PhysicalAdapterIndex;   // In
    UINT    SegmentIndex;           // In
    UINT    VprIndex;               // In
    SIZE_T  CurrentStartOffset;     // In
    SIZE_T  CurrentSize;            // In
    SIZE_T  NewStartOffset;         // In
    SIZE_T  NewSize;                // In
} DXGKARG_SETVIDEOPROTECTEDREGION;
typedef _In_ CONST DXGKARG_SETVIDEOPROTECTEDREGION*   IN_CONST_PDXGKARG_SETVIDEOPROTECTEDREGION;

typedef
    _Function_class_DXGK_(DXGKDDI_SETVIDEOPROTECTEDREGION)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_SETVIDEOPROTECTEDREGION(
    IN_CONST_HANDLE                             hAdapter,
    IN_CONST_PDXGKARG_SETVIDEOPROTECTEDREGION   pArgs
    );

#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

typedef struct _DXGKARG_ESCAPE
{
    HANDLE             hDevice;                // in: driver device handle
    D3DDDI_ESCAPEFLAGS Flags;                  // in: flags
    VOID*              pPrivateDriverData;     // in/out: escape data
    UINT               PrivateDriverDataSize;  // in: size of escape data
    HANDLE             hContext;               // in: driver context handle
} DXGKARG_ESCAPE;

typedef _In_ CONST DXGKARG_ESCAPE*   IN_CONST_PDXGKARG_ESCAPE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_ESCAPE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_ESCAPE(
    IN_CONST_HANDLE                 hAdapter,
    IN_CONST_PDXGKARG_ESCAPE        pEscape
    );

#define DXGK_SECONDARY_BUCKETING_TAG ((DWORD)'bSsM')

typedef struct _DXGKARG_COLLECTDBGINFO_EXT
{
    UINT BucketingKey;           // out: Key for IHV specific secondary OCA bucketing
    UINT CurrentDmaBufferOffset; // out: execution offset in the current DMA buffer
    UINT Reserved2;
    UINT Reserved3;
    UINT Reserved4;
    UINT Reserved5;
    UINT Reserved6;
    UINT Reserved7;
} DXGKARG_COLLECTDBGINFO_EXT;

typedef struct _DXGKARG_COLLECTDBGINFO
{
    UINT    Reason;                         // in:  bugcheck code for debug report
    VOID*   pBuffer;                        // out: pointer to the buffer to save the info
    SIZE_T  BufferSize;                     // in:  maximum size of the buffer in bytes
    DXGKARG_COLLECTDBGINFO_EXT* pExtension; // out: optional extension
} DXGKARG_COLLECTDBGINFO;

typedef _In_ CONST DXGKARG_COLLECTDBGINFO*   IN_CONST_PDXGKARG_COLLECTDBGINFO;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_COLLECTDBGINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_COLLECTDBGINFO(
    IN_CONST_HANDLE                         hAdapter,
    IN_CONST_PDXGKARG_COLLECTDBGINFO        pCollectDbgInfo
    );

typedef struct _DXGK_OVERLAYINFO
{
    HANDLE                 hAllocation;           // in: Allocation to be displayed
    PHYSICAL_ADDRESS       PhysicalAddress;       // in: Physical address of allocation
    UINT                   SegmentId;             // in: Segment ID of allocation
    RECT                   DstRect;               // in: Source rect
    RECT                   SrcRect;               // in: Dest rect
    VOID*                  pPrivateDriverData;    // in: Private driver data
    UINT                   PrivateDriverDataSize; // in: Size of private driver data
} DXGK_OVERLAYINFO;

typedef struct _DXGKARG_CREATEOVERLAY
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID VidPnSourceId; // in:  VidPn where overlay is displayed
    DXGK_OVERLAYINFO               OverlayInfo;   // in:  Overlay info
    HANDLE                         hOverlay;      // out: Driver handle
} DXGKARG_CREATEOVERLAY;

typedef _Inout_ DXGKARG_CREATEOVERLAY*      INOUT_PDXGKARG_CREATEOVERLAY;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_CREATEOVERLAY)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_CREATEOVERLAY(
    IN_CONST_HANDLE                 hAdapter,
    INOUT_PDXGKARG_CREATEOVERLAY    pCreateOverlay
    );

typedef struct _DXGKARG_UPDATEOVERLAY
{
    DXGK_OVERLAYINFO       OverlayInfo;            // in: Overlay info
} DXGKARG_UPDATEOVERLAY;

typedef _In_ CONST DXGKARG_UPDATEOVERLAY*   IN_CONST_PDXGKARG_UPDATEOVERLAY;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_UPDATEOVERLAY)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_UPDATEOVERLAY(
    IN_CONST_HANDLE                     hOverlay,
    IN_CONST_PDXGKARG_UPDATEOVERLAY     pUpdateOverlay
    );

typedef struct _DXGKARG_FLIPOVERLAY
{
    HANDLE                 hSource;                // in: Source allocation
    PHYSICAL_ADDRESS       SrcPhysicalAddress;     // in: Physical address of source allocation
    UINT                   SrcSegmentId;           // in: Segment ID of source allocation
    VOID*                  pPrivateDriverData;     // in: Private driver data
    UINT                   PrivateDriverDataSize;  // in: Size of private driver data
} DXGKARG_FLIPOVERLAY;

typedef _In_ CONST DXGKARG_FLIPOVERLAY*     IN_CONST_PDXGKARG_FLIPOVERLAY;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_FLIPOVERLAY)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_FLIPOVERLAY(
    IN_CONST_HANDLE                 hOverlay,
    IN_CONST_PDXGKARG_FLIPOVERLAY   pFlipOverlay
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_DESTROYOVERLAY)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_DESTROYOVERLAY(
    IN_CONST_HANDLE     hOverlay
    );

typedef struct _DXGKARG_GETSCANLINE
{
    D3DDDI_VIDEO_PRESENT_TARGET_ID  VidPnTargetId;      // in: adapter's VidPN Target ID
    BOOLEAN                         InVerticalBlank;    // out: Within vertical blank
    UINT                            ScanLine;           // out: Current scan line
} DXGKARG_GETSCANLINE;

typedef _Inout_ DXGKARG_GETSCANLINE*    INOUT_PDXGKARG_GETSCANLINE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_GETSCANLINE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_GETSCANLINE(
    IN_CONST_HANDLE             hAdapter,
    INOUT_PDXGKARG_GETSCANLINE  pGetScanLine
    );

///////////////////////// LDDM display miniport VidPN management DDI /////////////////////////////


/*++
Routine Description:
    IsSupportedVidPn LDDM display miniport VidPN management DDI method

Arguments:
    hAdapter                - LDDM display miniport adapter handle.

    pIsSupportedVidPnArg
       ->pDesiredVidPn      - VidPN whose support with respect to display adapter's capabilities
                              is in question.

       ->bIsVidPnSupported - Placeholder for the predicate specifying whether the specified VidPN
                             is supported by the specified display adapter.

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

    STATUS_NO_MEMORY
      - Low memory condition prevented successful completion of this request.

    One of the invalid parameter STATUS_GRAPHICS_* codes that can be returned by the OS via
    DXGDDI_VIDPN* interfaces. These codes should only occur during development since they
    indicate a bug in the driver or OS.

Remarks:
    Predicate specifying whether the provided VidPN configuration is supported (i.e. can be extended
    to a functional VidPN).

Assumptions:
    Specified VidPN must at a minimum specify a valid topology, but can also have some or all
    of its targets/sources configured with respectively pinned modes.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/
typedef struct _DXGKARG_ISSUPPORTEDVIDPN
{
    IN   D3DKMDT_HVIDPN                       hDesiredVidPn;
    OUT  BOOLEAN                              IsVidPnSupported;
} DXGKARG_ISSUPPORTEDVIDPN;

typedef _Inout_ DXGKARG_ISSUPPORTEDVIDPN*     INOUT_PDXGKARG_ISSUPPORTEDVIDPN;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_ISSUPPORTEDVIDPN)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_ISSUPPORTEDVIDPN(
    IN_CONST_HANDLE                     hAdapter,
    INOUT_PDXGKARG_ISSUPPORTEDVIDPN     pIsSupportedVidPn
    );


/*++
Routine Description:
    EnumVidPnCofuncModality LDDM display miniport VidPN management DDI method

Arguments:
    hAdapter                - LDDM display miniport adapter handle.

    hConstrainingVidPn      - VidPN whose cofunctional mode sets are to be (re)enumerated
                              with respect to its topology and pinned modes (if any).

    EnumPivotType           - Specifies what is the type of the mode enumeration pivot (if any).
                              No pivot is specified using D3DKMDT_EPT_NOPIVOT.

    EnumPivot.VidPnSourceId - If (EnumPivotType == D3DKMDT_EPT_VIDPNSOURCE), specifies the ID
                              of the VidPN source whose mode set must not be changed during the enumeration.
                              If EnumPivotType is D3DKMDT_EPT_SCALING or D3DKMDT_EPT_ROTATION,
                              the VidPnSourceId and VidPnTargetId specifies the path whose scaling or rotation support does
                              not need to be updated.
                              Undefined otherwise.

    EnumPivot.VidPnSourceId - If (EnumPivotType == D3DKMDT_EPT_VIDPNTARGET), specifies the ID
                              of the VidPN source whose mode set must not be changed during the enumeration.
                              If EnumPivotType is D3DKMDT_EPT_SCALING or D3DKMDT_EPT_ROTATION,
                              the VidPnSourceId and VidPnTargetId specifies the path whose scaling or rotation support does
                              not need to be updated.
                              Undefined otherwise.

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

    STATUS_NO_MEMORY
      - Low memory condition prevented successful completion of this request.

    One of the invalid parameter STATUS_GRAPHICS_* codes that can be returned by the OS via
    DXGDDI_VIDPN* interfaces. These codes should only occur during development since they
    indicate a bug in the driver or OS.

Remarks:
   Enumerates cofunctional video present source and target mode sets on each video present path
   in the specified VidPN's topology.

Assumptions:
    Specified VidPN's support has been confirmed via IsSupportedVidPn call by the OS.
    Miniport can assume it reported that it supports this VidPN.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/
typedef struct _DXGK_ENUM_PIVOT
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;
    D3DDDI_VIDEO_PRESENT_TARGET_ID  VidPnTargetId;
} DXGK_ENUM_PIVOT;


typedef struct _DXGKARG_ENUMVIDPNCOFUNCMODALITY
{
    IN  D3DKMDT_HVIDPN                         hConstrainingVidPn;
    IN  D3DKMDT_ENUMCOFUNCMODALITY_PIVOT_TYPE  EnumPivotType;
    IN  DXGK_ENUM_PIVOT                        EnumPivot;
} DXGKARG_ENUMVIDPNCOFUNCMODALITY;

typedef _In_ CONST DXGKARG_ENUMVIDPNCOFUNCMODALITY* CONST       IN_CONST_PDXGKARG_ENUMVIDPNCOFUNCMODALITY_CONST;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_ENUMVIDPNCOFUNCMODALITY)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_ENUMVIDPNCOFUNCMODALITY(
    IN_CONST_HANDLE                                     hAdapter,
    IN_CONST_PDXGKARG_ENUMVIDPNCOFUNCMODALITY_CONST     pEnumCofuncModality
    );


/*++
Routine Description:
    RecommendFunctionalVidPn LDDM display miniport VidPN management DDI method

Arguments:
    hAdapter
      - LDDM display miniport adapter handle.

    pRecommendFunctionalVidPnArg

       ->NumberOfVidPnTargets
           - Number of VidPN target IDs listed in pVidPnTargetPrioritizationVector.

       ->pVidPnTargetPrioritizationVector
           - Vector of VidPN targets IDs, ordered most important first, representing the
             importance of monitors connected to them.

       ->hRecommendedFunctionalVidPn
           - Handle of an empty VidPN object to be populated by miniport with the
             functional VidPN recommended for the current state of display adapter.

       ->RequestReason
           - Type of reason behind OS'es request of a new functional VidPN.
             Note that hotkey, power, and thermal events are mapped directly from the
             respective invalidation reasons specified via
             DXGK_INTERFACESPECIFICDATA::pfnInvalidateActiveVidPn.

       ->hContext
           - Optional context originating from the miniport on calls such as
             DXGK_INTERFACESPECIFICDATA::pfnInvalidateActiveVidPn. When miniport needs
             to invalidate an active VidPN, it should pass private context to be received
             via this parameter so it could distinguish between different concurrent requests
             of the same type leading OS to request a new functional VidPN.

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

    STATUS_GRAPHICS_NO_RECOMMENDED_VIDPN
      - Installed LDDM display adapter miniport has no VidPN recommendation
      for the current configuration of the display adapter.

    STATUS_NO_MEMORY
      - Low memory condition prevented successful completion of this request.

    One of the invalid parameter STATUS_GRAPHICS_* codes that can be returned by the OS via
    DXGDDI_{VIDPN|MONITOR}* interfaces. These codes should only occur during development since they
    indicate a bug in the driver or OS.

Remarks:
    Obtains a VidPN recommended by the LDDM display miniport, given the current state of the h/w.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/
typedef enum _DXGK_RECOMMENDFUNCTIONALVIDPN_REASON
{
    DXGK_RFVR_UNINITIALIZED  = 0,
    DXGK_RFVR_HOTKEY         = 1,
    DXGK_RFVR_USERMODE       = 2,
    DXGK_RFVR_FIRMWARE       = 3,
}
DXGK_RECOMMENDFUNCTIONALVIDPN_REASON;

typedef struct _DXGKARG_RECOMMENDFUNCTIONALVIDPN
{
    IN  UINT                                    NumberOfVidPnTargets;
    IN  CONST D3DDDI_VIDEO_PRESENT_TARGET_ID*   pVidPnTargetPrioritizationVector;
    IN  D3DKMDT_HVIDPN                          hRecommendedFunctionalVidPn;
    IN  DXGK_RECOMMENDFUNCTIONALVIDPN_REASON    RequestReason;
    IN  OPTIONAL VOID*                          pPrivateDriverData;
    IN  UINT                                    PrivateDriverDataSize;
} DXGKARG_RECOMMENDFUNCTIONALVIDPN;

typedef _In_ CONST DXGKARG_RECOMMENDFUNCTIONALVIDPN* CONST      IN_CONST_PDXGKARG_RECOMMENDFUNCTIONALVIDPN_CONST;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_RECOMMENDFUNCTIONALVIDPN)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_RECOMMENDFUNCTIONALVIDPN(
    IN_CONST_HANDLE                                     hAdapter,
    IN_CONST_PDXGKARG_RECOMMENDFUNCTIONALVIDPN_CONST    pRecommendFunctionalVidPn
    );

/*++
Routine Description:
    SetVidPnSourceAddress LDDM display miniport VidPN management DDI method

Arguments:
    hAdapter              - LDDM display miniport adapter handle.

    pSetVidPnSourceVisibility
       ->VidPnSourceId    - ID of the VidPN source whose state needs to be changed.

       ->PrimarySegment   - Segment of the primary surface to scan from.

       ->PrimaryAddress   - Address of the primary surface to scan from.

       ->hAllocation      - Driver assigned allocation handle for the primary surface

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

Side-effects:
    On success, adapters starts scanning from the specified primary surface on the specified VidPN source.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/

typedef struct _DXGK_SETVIDPNSOURCEADDRESS_FLAGS
{
    union
    {
        struct
        {

            UINT ModeChange                 : 1;    // 0x00000001
            UINT FlipImmediate              : 1;    // 0x00000002
            UINT FlipOnNextVSync            : 1;    // 0x00000004
#if ((DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8) || \
     (D3D_UMD_INTERFACE_VERSION >= D3D_UMD_INTERFACE_VERSION_WIN8))
            UINT FlipStereo                 : 1;    // 0x00000008 This is a flip from a stereo alloc. Used in addition to FlipImmediate or FlipOnNextVSync.
            UINT FlipStereoTemporaryMono    : 1;    // 0x00000010 This is a flip from a stereo alloc. The left image should used. Used in addition to FlipImmediate or FlipOnNextVSync.
            UINT FlipStereoPreferRight      : 1;    // 0x00000010 This is a flip from a stereo alloc. The right image should used when cloning to a mono monitor. Used in addition to FlipImmediate or FlipOnNextVSync.
            UINT SharedPrimaryTransition    : 1;    // 0x00000020 We are transitioning to or away from a shared managed primary allocation
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
            UINT IndependentFlipExclusive   : 1;    // 0x00000040 
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
            UINT MoveFlip                   : 1;    // 0x00000080
            UINT Reserved                   :23;
#else
            UINT Reserved                   :24;    // 0xFFFFFF80
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
#else
            UINT Reserved                   :25;    // 0xFFFFFFC0
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
#else
            UINT Reserved                   :29;    // 0xFFFFFFF8
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
        };
        UINT Value;
    };
} DXGK_SETVIDPNSOURCEADDRESS_FLAGS;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
typedef struct _DXGK_SETVIDPNSOURCEADDRESS_INPUT_FLAGS
{
    union
    {
        struct
        {
            UINT FlipStereo                 : 1;    // 0x00000001 This is a flip from a stereo alloc. Used in addition to FlipImmediate or FlipOnNextVSync.
            UINT FlipStereoTemporaryMono    : 1;    // 0x00000002 This is a flip from a stereo alloc. The left image should used. Used in addition to FlipImmediate or FlipOnNextVSync.
            UINT FlipStereoPreferRight      : 1;    // 0x00000004 This is a flip from a stereo alloc. The right image should used when cloning to a mono monitor. Used in addition to FlipImmediate or FlipOnNextVSync.
            UINT RetryAtLowerIrql           : 1;    // 0x00000008 This is called at lower IRQL after receiving a PrePresent request.
            UINT Reserved                   :28;    // 0xFFFFFFF8
        };
        UINT Value;
    };
} DXGK_SETVIDPNSOURCEADDRESS_INPUT_FLAGS;

typedef struct _DXGK_SETVIDPNSOURCEADDRESS_OUTPUT_FLAGS
{
    union
    {
        struct
        {
            UINT PrePresentNeeded           : 1;    
            UINT Reserved                   :31;    // 0xFFFFFFFE
        };
        UINT Value;
    };
} DXGK_SETVIDPNSOURCEADDRESS_OUTPUT_FLAGS;

typedef struct _DXGK_PLANE_SPECIFIC_INPUT_FLAGS
{
    union
    {
        struct
        {
            UINT    Enabled                    : 1;   // 0x00000001
            UINT    FlipImmediate              : 1;   // 0x00000002
            UINT    FlipOnNextVSync            : 1;   // 0x00000004
            UINT    SharedPrimaryTransition    : 1;   // 0x00000008 We are transitioning to or away from a shared managed primary allocation
            UINT    IndependentFlipExclusive   : 1;   // 0x00000010 
            UINT Reserved                      :27;   // 0xFFFFFFE0
        };
        UINT Value;
    };
} DXGK_PLANE_SPECIFIC_INPUT_FLAGS;

typedef struct _DXGK_PLANE_SPECIFIC_OUTPUT_FLAGS
{
    union
    {
        struct
        {
            UINT FlipConvertedToImmediate   : 1;	// 0x00000001
            UINT PostPresentNeeded          : 1;    // 0x00000002 Should only be set for immediate flips if driver requires a postpresent call on this plane
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
            UINT HsyncInterruptCompletion   : 1;    // 0x00000004 Should be set for immediate flips that are completed on Hsync interrupt notification and not upon the return from the DDI.
            UINT Reserved                   :29;    // 0xFFFFFFF8
#else
            UINT Reserved					:30;	// 0xFFFFFFFC
#endif
        };
        UINT Value;
    };
} DXGK_PLANE_SPECIFIC_OUTPUT_FLAGS;

typedef struct _DXGK_MULTIPLANE_OVERLAY_ATTRIBUTES3
{
    DXGK_MULTIPLANE_OVERLAY_FLAGS                Flags;   
    RECT                                         SrcRect;  
    RECT                                         DstRect;  
    RECT                                         ClipRect;
    D3DDDI_ROTATION                              Rotation; 
    DXGK_MULTIPLANE_OVERLAY_BLEND                Blend;    
    D3DDDI_COLOR_SPACE_TYPE                      ColorSpaceType;   
    DXGK_MULTIPLANE_OVERLAY_STRETCH_QUALITY      StretchQuality;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)
    UINT                                         SDRWhiteLevel;
#endif
} DXGK_MULTIPLANE_OVERLAY_ATTRIBUTES3;

typedef struct _DXGK_HDR_METADATA
{
    D3DDDI_HDR_METADATA_TYPE Type;
    UINT                     Size;
    VOID*                    pMetaData;
} DXGK_HDR_METADATA;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
typedef struct _DXGK_PRIMARYDATA
{
    HANDLE                           hAllocation;
    WORD                             SegmentId;
    PHYSICAL_ADDRESS                 SegmentAddress;
} DXGK_PRIMARYDATA;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)

typedef struct _DXGKARG_SETVIDPNSOURCEADDRESS
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID   VidPnSourceId;
    UINT                             PrimarySegment;
    PHYSICAL_ADDRESS                 PrimaryAddress;
    HANDLE                           hAllocation;
    UINT                             ContextCount;
    HANDLE                           Context[1+D3DDDI_MAX_BROADCAST_CONTEXT];
    DXGK_SETVIDPNSOURCEADDRESS_FLAGS Flags;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
    UINT                             Duration;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
    DXGK_PRIMARYDATA                 PrimaryData[D3DDDI_MAX_BROADCAST_CONTEXT];
    UINT                             DriverPrivateDataSize;
    _Field_size_bytes_(DriverPrivateDataSize)
    PVOID                            pDriverPrivateData;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
#endif // DXGKDDI_INTERFACE_VERSION_WDDM1_3
} DXGKARG_SETVIDPNSOURCEADDRESS;

typedef _In_ CONST DXGKARG_SETVIDPNSOURCEADDRESS*   IN_CONST_PDXGKARG_SETVIDPNSOURCEADDRESS;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_SETVIDPNSOURCEADDRESS)
    _IRQL_requires_min_(PASSIVE_LEVEL)
    _IRQL_requires_max_(PROFILE_LEVEL  - 1)
NTSTATUS
APIENTRY
DXGKDDI_SETVIDPNSOURCEADDRESS(
    IN_CONST_HANDLE                             hAdapter,
    IN_CONST_PDXGKARG_SETVIDPNSOURCEADDRESS     pSetVidPnSourceAddress
    );

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
typedef struct _DXGKARG_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY
{
    UINT                             ContextCount;
    HANDLE                           Context[1+D3DDDI_MAX_BROADCAST_CONTEXT];

    DXGK_SETVIDPNSOURCEADDRESS_FLAGS Flags;
    D3DDDI_VIDEO_PRESENT_SOURCE_ID   VidPnSourceId;

    UINT                             PlaneCount;
    DXGK_MULTIPLANE_OVERLAY_PLANE*   pPlanes;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
    UINT                             Duration;
#endif // DXGKDDI_INTERFACE_VERSION_WDDM1_3
} DXGKARG_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY;

typedef _In_ CONST DXGKARG_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY* IN_CONST_PDXGKARG_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY)
    _IRQL_requires_max_(PROFILE_LEVEL  - 1)
NTSTATUS
APIENTRY
DXGKDDI_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY(
    IN_CONST_HANDLE hAdapter,
    IN_CONST_PDXGKARG_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY
                  pSetVidPnSourceAddressWithMultiPlaneOverlay
    );

typedef _In_ CONST DXGKARG_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY*
     IN_CONST_PDXGKARG_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY;
#endif // DXGKDDI_INTERFACE_VERSION

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
typedef struct _DXGK_MULTIPLANE_OVERLAY_PLANE2
{
    UINT                                 LayerIndex;        // The zero-based index of the overlay plane to display. The top plane (in the z-direction) has index zero. The planes' index values must be sequential from top to bottom.
    BOOL                                 Enabled;           // Indicates whether the overlay plane specified by LayerIndex is enabled for display.

    UINT                                 AllocationSegment; // The identifier of a segment that data is read from.
    PHYSICAL_ADDRESS                     AllocationAddress; // A PHYSICAL_ADDRESS data type (which is defined as LARGE_INTEGER) that indicates the physical address, within the segment that AllocationSegment specifies, where the data is read.
    HANDLE                               hAllocation;       // A handle to the allocation to be displayed on the overlay plane.
    DXGK_MULTIPLANE_OVERLAY_ATTRIBUTES2  PlaneAttributes;   // A structure of type DXGK_MULTIPLANE_OVERLAY_ATTRIBUTES1 that specifies overlay plane attributes.
} DXGK_MULTIPLANE_OVERLAY_PLANE2;

typedef struct _DXGKARG_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY2
{
    UINT                             ContextCount;      // The number of contexts in the array that the Context member specifies.
    HANDLE                           Context[1+D3DDDI_MAX_BROADCAST_CONTEXT];   // An array of handles to the contexts that contributed to a display operation.

    DXGK_SETVIDPNSOURCEADDRESS_FLAGS Flags;             // A DXGK_SETVIDPNSOURCEADDRESS_FLAGS structure that identifies the type of display operation to perform.
    D3DDDI_VIDEO_PRESENT_SOURCE_ID   VidPnSourceId;     // An integer that identifies a video present source on the display adapter.

    UINT                             PlaneCount;        // The number of overlay planes in the pPlanes list.
    DXGK_MULTIPLANE_OVERLAY_PLANE2*  pPlanes;           // An array of DXGK_MULTIPLANE_OVERLAY_PLANE2 structures that specify the overlay planes to display.
    UINT                             Duration;          // The length of time, in units of 100 nanoseconds, between when the current present operation flips to the screen and the next vertical blanking interrupt occurs.
} DXGKARG_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY2;

typedef _In_ CONST DXGKARG_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY2* IN_CONST_PDXGKARG_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY2;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY2)
    _IRQL_requires_max_(PROFILE_LEVEL  - 1)
NTSTATUS
APIENTRY
DXGKDDI_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY2(
    IN_CONST_HANDLE hAdapter,
    IN_CONST_PDXGKARG_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY2
                  pSetVidPnSourceAddressWithMultiPlaneOverlay
    );

typedef _In_ CONST DXGKARG_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY2*
     IN_CONST_PDXGKARG_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY2;

#endif // DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
typedef struct _DXGK_PRIMARYCONTEXTDATA
{
    HANDLE                           hContext;
    HANDLE                           hAllocation;
    WORD                             SegmentId;
    PHYSICAL_ADDRESS                 SegmentAddress;
} DXGK_PRIMARYCONTEXTDATA;

typedef struct _DXGK_MULTIPLANE_OVERLAY_PLANE3
{
    UINT                                                 LayerIndex;    
    ULONGLONG                                            PresentId; 
    DXGK_PLANE_SPECIFIC_INPUT_FLAGS                      InputFlags;           
    DXGK_PLANE_SPECIFIC_OUTPUT_FLAGS                     OutputFlags;     
    UINT                                                 MaxImmediateFlipLine;      
    UINT                                                 ContextCount;
    _Field_size_(ContextCount) DXGK_PRIMARYCONTEXTDATA** ppContextData; 
    
    UINT                                                 DriverPrivateDataSize;
    _Field_size_bytes_(DriverPrivateDataSize)
    PVOID                                                pDriverPrivateData;
    
    DXGK_MULTIPLANE_OVERLAY_ATTRIBUTES3                  PlaneAttributes;  
} DXGK_MULTIPLANE_OVERLAY_PLANE3;

typedef struct _DXGK_MULTIPLANE_OVERLAY_POST_COMPOSITION_FLAGS
{
    union
    {
        struct
        {
            UINT    VerticalFlip              : 1;    // 0x00000001
            UINT    HorizontalFlip            : 1;    // 0x00000002
            UINT    Reserved                  :30;    // 0xFFFFFFFC
        };
        UINT Value;
    };
} DXGK_MULTIPLANE_OVERLAY_POST_COMPOSITION_FLAGS;

typedef struct _DXGK_MULTIPLANE_OVERLAY_POST_COMPOSITION
{
    DXGK_MULTIPLANE_OVERLAY_POST_COMPOSITION_FLAGS       Flags;   
    RECT                                                 SrcRect;  
    RECT                                                 DstRect;  
    D3DDDI_ROTATION                                      Rotation; 
} DXGK_MULTIPLANE_OVERLAY_POST_COMPOSITION;

typedef struct _DXGKARG_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY3
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID                            VidPnSourceId; 
    DXGK_SETVIDPNSOURCEADDRESS_INPUT_FLAGS                    InputFlags;
    DXGK_SETVIDPNSOURCEADDRESS_OUTPUT_FLAGS                   OutputFlags;

    UINT                                                      PlaneCount;     
    _Field_size_(PlaneCount) DXGK_MULTIPLANE_OVERLAY_PLANE3** ppPlanes; 
    DXGK_MULTIPLANE_OVERLAY_POST_COMPOSITION*                 pPostComposition;
    UINT                                                      Duration;   
    DXGK_HDR_METADATA*                                        pHDRMetaData; 
} DXGKARG_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY3;

typedef _Inout_ DXGKARG_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY3* IN_OUT_PDXGKARG_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY3;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY3)
    _IRQL_requires_max_(PROFILE_LEVEL  - 1)
NTSTATUS
APIENTRY
DXGKDDI_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY3(
    IN_CONST_HANDLE hAdapter,
    IN_OUT_PDXGKARG_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY3
                  pSetVidPnSourceAddressWithMultiPlaneOverlay
    );

typedef struct _DXGKARG_POSTMULTIPLANEOVERLAYPRESENT
{
    D3DDDI_VIDEO_PRESENT_TARGET_ID      VidPnTargetId;
    UINT                                PhysicalAdapterMask;
    DWORD                               LayerIndex;
    ULONGLONG                           PresentID;
} DXGKARG_POSTMULTIPLANEOVERLAYPRESENT;

typedef _In_ CONST DXGKARG_POSTMULTIPLANEOVERLAYPRESENT* IN_CONST_PDXGKARG_POSTMULTIPLANEOVERLAYPRESENT;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_POSTMULTIPLANEOVERLAYPRESENT)
    _IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_POSTMULTIPLANEOVERLAYPRESENT(
    IN_CONST_HANDLE hAdapter,
    IN_CONST_PDXGKARG_POSTMULTIPLANEOVERLAYPRESENT
                  pPostPresent
    );

typedef struct _DXGKARG_VALIDATEUPDATEALLOCPROPERTY
{
    HANDLE                              hAllocation;            // [in] Handle to the driver open allocation to be updated.
    UINT                                SupportedSegmentSet;    // [in] New supported segment set, ignored if the same.
    D3DDDI_SEGMENTPREFERENCE            PreferredSegment;       // [in] New preferred segment set, ignored if the same.
    D3DDDI_UPDATEALLOCPROPERTY_FLAGS    Flags;                  // [in] Flags to set on the allocation, ignored if the same.
    union
    {
        struct
        {                
            UINT SetAccessedPhysically : 1;     // [in] When set to 1, will set AccessedPhysically to new value
            UINT SetSupportedSegmentSet : 1;    // [in] When set to 1, will set SupportedSegmentSet to new value
            UINT SetPreferredSegment : 1;       // [in] When set to 1, will set PreferredSegment to new value
            UINT Reserved : 29;
        };
        UINT PropertyMaskValue;
    };
} DXGKARG_VALIDATEUPDATEALLOCPROPERTY;

typedef _In_ CONST DXGKARG_VALIDATEUPDATEALLOCPROPERTY* IN_CONST_PDXGKARG_VALIDATEUPDATEALLOCPROPERTY;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VALIDATEUPDATEALLOCATIONPROPERTY)
    _IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_VALIDATEUPDATEALLOCATIONPROPERTY(
    IN_CONST_HANDLE hAdapter,
    IN_CONST_PDXGKARG_VALIDATEUPDATEALLOCPROPERTY pValidateUpdateAllocProperty
    );
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

typedef struct _DXGKARG_CREATEPERIODICFRAMENOTIFICATION
{
    HANDLE                          hAdapter;       // [in] Handle to the adapter associated with the VidPnSource
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnTargetId;  // [in] The output that the notification will be attached to
    UINT64                          Time;           // [in] Represents an offset before the VSync.
                                                    // The Time value may not be longer than a VSync interval.
                                                    // In units of 100ns.
    UINT                            NotificationID; // [in] Id that represents this instance of the notification
                                                    // used to identify which interrupt has fired.
    HANDLE                          hNotification;  // [out] Handle to the notification object, later used to destroy
} DXGKARG_CREATEPERIODICFRAMENOTIFICATION;

typedef _Inout_ DXGKARG_CREATEPERIODICFRAMENOTIFICATION* INOUT_PDXGKARG_CREATEPERIODICFRAMENOTIFICATION;

typedef
    _Check_return_
    _Function_class_DXGK_ (DXGKARG_CREATEPERIODICFRAMENOTIFICATION)
    _IRQL_requires_max_ (PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_CREATEPERIODICFRAMENOTIFICATION (
    INOUT_PDXGKARG_CREATEPERIODICFRAMENOTIFICATION pCreatePeriodicFrameNotification
    );

typedef struct _DXGKARG_DESTROYPERIODICFRAMENOTIFICATION
{
    HANDLE      hNotification;  // [in] Handle to the notification object to destroy
    HANDLE      hAdapter;       // [in] Handle to the adapter associated with the notification
} DXGKARG_DESTROYPERIODICFRAMENOTIFICATION;

typedef _In_ CONST DXGKARG_DESTROYPERIODICFRAMENOTIFICATION* IN_CONST_PDXGKARG_DESTROYPERIODICFRAMENOTIFICATION;

typedef
    _Check_return_
    _Function_class_DXGK_ (DXGKARG_DESTROYPERIODICFRAMENOTIFICATION)
    _IRQL_requires_max_ (PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_DESTROYPERIODICFRAMENOTIFICATION (
    IN_CONST_PDXGKARG_DESTROYPERIODICFRAMENOTIFICATION pDestroyPeriodicFrameNotification
    );

typedef struct _DXGK_MULTIPLANEOVERLAYCAPS
{
    union
    {
        struct
        {
            UINT Rotation                        : 1;    // Full rotation
            UINT RotationWithoutIndependentFlip  : 1;    // Rotation, but without simultaneous IndependentFlip support
            UINT VerticalFlip                    : 1;    // Can flip the data vertically
            UINT HorizontalFlip                  : 1;    // Can flip the data horizontally
            UINT StretchRGB                      : 1;    // Supports RGB formats
            UINT StretchYUV                      : 1;    // Supports YUV formats
            UINT BilinearFilter                  : 1;    // Blinear filtering
            UINT HighFilter                      : 1;    // Better than bilinear filtering
            UINT Shared                          : 1;    // MPO resources are shared across VidPnSources
            UINT Immediate                       : 1;    // Immediate flip support
            UINT Plane0ForVirtualModeOnly        : 1;    // Stretching plane 0 will also stretch the HW cursor and should only be used for virtual mode support
            UINT Reserved                        : 21;
        };
        UINT Value;
    };
} DXGK_MULTIPLANEOVERLAYCAPS;

typedef struct _DXGKARG_GETMULTIPLANEOVERLAYCAPS
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID         VidPnSourceId;        // [in] 
    UINT                                   MaxPlanes;            // [out] Total number of planes supported (including the DWM's primary)
    UINT                                   MaxRGBPlanes;         // [out] Maximum number of RGB planes supported (including the DWM's primary)
    UINT                                   MaxYUVPlanes;         // [out] Maximum number of YUV planes supported
    DXGK_MULTIPLANEOVERLAYCAPS             OverlayCaps;          // [out] Plane capabilities
    float                                  MaxStretchFactor;     // [out] 
    float                                  MaxShrinkFactor;      // [out]
} DXGKARG_GETMULTIPLANEOVERLAYCAPS;

typedef _Inout_ DXGKARG_GETMULTIPLANEOVERLAYCAPS* IN_OUT_PDXGKARG_GETMULTIPLANEOVERLAYCAPS;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_GETMULTIPLANEOVERLAYCAPS)
    _IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_GETMULTIPLANEOVERLAYCAPS(
    IN_CONST_HANDLE hAdapter,
    IN_OUT_PDXGKARG_GETMULTIPLANEOVERLAYCAPS
                  pGetMultiPlaneOverlayCaps
    );

typedef struct _DXGKARG_GETPOSTCOMPOSITIONCAPS
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID         VidPnSourceId;        // [in]
    float                                  MaxStretchFactor;     // [out] 
    float                                  MaxShrinkFactor;      // [out]
} DXGKARG_GETPOSTCOMPOSITIONCAPS;

typedef _Inout_ DXGKARG_GETPOSTCOMPOSITIONCAPS* IN_OUT_PDXGKARG_GETPOSTCOMPOSITIONCAPS;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_GETPOSTCOMPOSITIONCAPS)
    _IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_GETPOSTCOMPOSITIONCAPS(
    IN_CONST_HANDLE hAdapter,
    IN_OUT_PDXGKARG_GETPOSTCOMPOSITIONCAPS
                  pGetPostCompositionCaps
    );
#endif //(DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
typedef struct _DXGKARG_CHECKMULTIPLANEOVERLAYSUPPORT
{
    UINT                                                PlaneCount;
    DXGK_CHECK_MULTIPLANE_OVERLAY_SUPPORT_PLANE*        pPlanes;
    BOOL                                                Supported;
    DXGK_CHECK_MULTIPLANE_OVERLAY_SUPPORT_RETURN_INFO   ReturnInfo;
} DXGKARG_CHECKMULTIPLANEOVERLAYSUPPORT;

typedef _Inout_ DXGKARG_CHECKMULTIPLANEOVERLAYSUPPORT* IN_OUT_PDXGKARG_CHECKMULTIPLANEOVERLAYSUPPORT;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_CHECKMULTIPLANEOVERLAYSUPPORT)
    _IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_CHECKMULTIPLANEOVERLAYSUPPORT(
    IN_CONST_HANDLE hAdapter,
    IN_OUT_PDXGKARG_CHECKMULTIPLANEOVERLAYSUPPORT
                  pCheckMultiPlaneOverlaySupport
    );
#endif // DXGKDDI_INTERFACE_VERSION

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_CHECKMULTIPLANEOVERLAYSUPPORT2)
    _IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_CHECKMULTIPLANEOVERLAYSUPPORT2(
    IN_CONST_HANDLE hAdapter,
    IN_OUT_PDXGKARG_CHECKMULTIPLANEOVERLAYSUPPORT2
                  pCheckMultiPlaneOverlaySupport
    );
#endif // DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
typedef struct _DXGK_MULTIPLANE_OVERLAY_PLANE_WITH_SOURCE2
{
    HANDLE                                  hAllocation;     
    D3DDDI_VIDEO_PRESENT_SOURCE_ID          VidPnSourceId;          
    UINT                                    LayerIndex;
    DXGK_MULTIPLANE_OVERLAY_ATTRIBUTES3     PlaneAttributes;            
} DXGK_MULTIPLANE_OVERLAY_PLANE_WITH_SOURCE2;

typedef struct _DXGK_MULTIPLANE_OVERLAY_POST_COMPOSITION_WITH_SOURCE
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID           VidPnSourceId;          
    DXGK_MULTIPLANE_OVERLAY_POST_COMPOSITION PostComposition;            
} DXGK_MULTIPLANE_OVERLAY_POST_COMPOSITION_WITH_SOURCE;

typedef struct _DXGKARG_CHECKMULTIPLANEOVERLAYSUPPORT3
{
    UINT                                                                                      PlaneCount; 
    _Field_size_(PlaneCount) DXGK_MULTIPLANE_OVERLAY_PLANE_WITH_SOURCE2**                     ppPlanes;       
    UINT                                                                                      PostCompositionCount; 
    _Field_size_(PostCompositionCount) DXGK_MULTIPLANE_OVERLAY_POST_COMPOSITION_WITH_SOURCE** ppPostComposition;       
    BOOL                                                                                      Supported; 
    DXGK_CHECK_MULTIPLANE_OVERLAY_SUPPORT_RETURN_INFO                                         ReturnInfo;
} DXGKARG_CHECKMULTIPLANEOVERLAYSUPPORT3;

typedef _Inout_ DXGKARG_CHECKMULTIPLANEOVERLAYSUPPORT3* IN_OUT_PDXGKARG_CHECKMULTIPLANEOVERLAYSUPPORT3;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_CHECKMULTIPLANEOVERLAYSUPPORT3)
    _IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_CHECKMULTIPLANEOVERLAYSUPPORT3(
    IN_CONST_HANDLE hAdapter,
    IN_OUT_PDXGKARG_CHECKMULTIPLANEOVERLAYSUPPORT3
                  pCheckMultiPlaneOverlaySupport
    );
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)

/*++
Routine Description:
    SetVidPnSourceVisibility LDDM display miniport VidPN management DDI method

Arguments:
    hAdapter              - LDDM display miniport adapter handle.

    pSetVidPnSourceVisibility
       ->VidPnSourceId    - ID of the VidPN source whose state needs to be changed.

       ->Visible          - Visible or not for the specified VidPN source.

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

Side-effects:
    When Visible == TRUE, tells the miniport to scan out data from the primary surface
    associated with the the specified VidPN source to the VidPN target(s) connected
    to that source by the active VidPN's topology.
    When Visible == FALSE, tells miniport the miniport to stop reading from the primary surface
    associated with the specified VidPN source and present black on all the VidPN targets
    connected to that source via by active VidPN's topology.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/

typedef struct _DXGKARG_SETVIDPNSOURCEVISIBILITY
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;
    BOOLEAN                         Visible;
} DXGKARG_SETVIDPNSOURCEVISIBILITY;

typedef _In_ CONST DXGKARG_SETVIDPNSOURCEVISIBILITY*    IN_CONST_PDXGKARG_SETVIDPNSOURCEVISIBILITY;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_SETVIDPNSOURCEVISIBILITY)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_SETVIDPNSOURCEVISIBILITY(
    IN_CONST_HANDLE                             hAdapter,
    IN_CONST_PDXGKARG_SETVIDPNSOURCEVISIBILITY  pSetVidPnSourceVisibility
    );

/*++
Routine Description:
    CommitVidPn LDDM display miniport VidPN management DDI method

Arguments:
    hAdapter                       - LDDM display miniport adapter handle.

    pCommitVidPnArg
       ->hFunctionalVidPn          - Handle of a functional VidPN to commit to h/w.

       ->AffectedVidPnSourceId     - ID of the VidPN source for which the commit should take place.

       ->MonitorConnectivityChecks - Specifies miniport whether to validate specified VidPN's topology
                                     against connected monitors or ignore its monitor connectivity checks.

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

    STATUS_NO_MEMORY
      - There is insufficient memory to complete this request.

    One of the invalid parameter STATUS_GRAPHICS_* codes that can be returned by the OS via
    DXGDDI_VIDPN* interfaces. These codes should only occur during development since they
    indicate a bug in the driver or OS.

Side-effects:
    Commits the specified functional VidPN to h/w.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/
typedef struct _DXGKARG_COMMITVIDPN_FLAGS
{
    UINT PathPowerTransition   :  1;
    UINT PathPoweredOff        :  1;
    UINT Reserved              : 30;
} DXGKARG_COMMITVIDPN_FLAGS;

typedef struct _DXGKARG_COMMITVIDPN
{
    IN  D3DKMDT_HVIDPN                      hFunctionalVidPn;
    IN  D3DDDI_VIDEO_PRESENT_SOURCE_ID      AffectedVidPnSourceId;
    IN  D3DKMDT_MONITOR_CONNECTIVITY_CHECKS MonitorConnectivityChecks;
    IN  HANDLE                              hPrimaryAllocation; // Driver assigned primary surface allocation handle.
    IN  DXGKARG_COMMITVIDPN_FLAGS           Flags;
} DXGKARG_COMMITVIDPN;

typedef _In_ CONST DXGKARG_COMMITVIDPN* CONST       IN_CONST_PDXGKARG_COMMITVIDPN_CONST;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_COMMITVIDPN)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_COMMITVIDPN(
    IN_CONST_HANDLE                         hAdapter,
    IN_CONST_PDXGKARG_COMMITVIDPN_CONST     pCommitVidPn
    );


/*++
Routine Description:
    UpdateActiveVidPnPresentPath LDDM display miniport VidPN management DDI method

Arguments:
    hAdapter                   - LDDM display miniport adapter handle.

    pUpdateActiveVidPnPresentPathArg
       ->VidPnPresentPathInfo - VidPN present path information to update the respective
                                present path in the active VidPN with.

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

    STATUS_NO_MEMORY
      - There is insufficient memory to complete this request.

    One of the invalid parameter STATUS_GRAPHICS_* codes that can be returned by the OS via
    DXGDDI_VIDPN* interfaces. These codes should only occur during development since they
    indicate a bug in the driver or OS.

Side-effects:
    Updates settings on the specified VidPN present path of the active VidPN set on the adapter.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/
typedef struct _DXGKARG_UPDATEACTIVEVIDPNPRESENTPATH
{
    IN D3DKMDT_VIDPN_PRESENT_PATH  VidPnPresentPathInfo;
} DXGKARG_UPDATEACTIVEVIDPNPRESENTPATH;

typedef _In_ CONST DXGKARG_UPDATEACTIVEVIDPNPRESENTPATH* CONST      IN_CONST_PDXGKARG_UPDATEACTIVEVIDPNPRESENTPATH_CONST;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_UPDATEACTIVEVIDPNPRESENTPATH)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_UPDATEACTIVEVIDPNPRESENTPATH(
    IN_CONST_HANDLE                                         hAdapter,
    IN_CONST_PDXGKARG_UPDATEACTIVEVIDPNPRESENTPATH_CONST    pUpdateActiveVidPnPresentPath
    );


/*++
Routine Description:
    RecommendVidPnTopology LDDM display miniport VidPN management DDI method

Arguments:
    hAdapter - LDDM display miniport adapter handle.

    pUpdateActiveVidPnPresentPathArg
       ->hVidPn - Handle of the VidPN whose topology is to be augmented with miniport's recommendation.

       ->VidPnSourceId - ID of the VidPN source for which miniport is asked to recommend path(s).

       ->RequestReason - Reason why OS asked for recommendation.

       ->hFallbackVidPn - Handle of the VidPN that OS will use if miniport provides no recommendation.

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

    STATUS_NO_MEMORY
      - There is insufficient memory to complete this request.

    STATUS_GRAPHICS_NO_RECOMMENDED_VIDPN_TOPOLOGY
      - Miniport has no recommendation for augmentation of the specified VidPN's topology.

    One of the invalid parameter STATUS_GRAPHICS_* codes that can be returned by the OS via
    DXGDDI_{VIDPN|MONITOR|* interfaces. These codes should only occur during development since they
    indicate a bug in the driver or OS.

Side-effects:
    On success, topology of the specified VidPN is augmented with miniport's recommendation with path(s)
    originating from the specified source.

Remarks:
    On success, miniport must add at least one path to the specified VidPN's source.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/
typedef enum _DXGK_RECOMMENDVIDPNTOPOLOGY_REASON
{
    DXGK_RVT_UNINITIALIZED              = 0,
    DXGK_RVT_INITIALIZATION_NOLKG       = 1,
    DXGK_RVT_AUGMENTATION_NOLKG         = 2,
    DXGK_RVT_AUGMENTATION_LKGOVERRIDE   = 3,
    DXGK_RVT_INITIALIZATION_LKGOVERRIDE = 4,
}
DXGK_RECOMMENDVIDPNTOPOLOGY_REASON;

typedef struct _DXGKARG_RECOMMENDVIDPNTOPOLOGY
{
    IN D3DKMDT_HVIDPN                      hVidPn;
    IN D3DDDI_VIDEO_PRESENT_SOURCE_ID      VidPnSourceId;
    IN DXGK_RECOMMENDVIDPNTOPOLOGY_REASON  RequestReason;
    IN D3DKMDT_HVIDPNTOPOLOGY              hFallbackTopology;
} DXGKARG_RECOMMENDVIDPNTOPOLOGY;

typedef _In_ CONST DXGKARG_RECOMMENDVIDPNTOPOLOGY* CONST    IN_CONST_PDXGKARG_RECOMMENDVIDPNTOPOLOGY_CONST;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_RECOMMENDVIDPNTOPOLOGY)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_RECOMMENDVIDPNTOPOLOGY(
    IN_CONST_HANDLE                                 hAdapter,
    IN_CONST_PDXGKARG_RECOMMENDVIDPNTOPOLOGY_CONST  pRecommendVidPnTopology
    );


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DXGK_VIDPNTOPOLOGY_INTERFACE
// NOTE: Exposed by OS to miniport via DXGK_VIDPN_INTERFACE::pfnGetTopology

typedef _In_        CONST D3DKMDT_HVIDPNTOPOLOGY            IN_CONST_D3DKMDT_HVIDPNTOPOLOGY;
typedef _In_              D3DKMDT_HVIDPNTOPOLOGY            IN_D3DKMDT_HVIDPNTOPOLOGY;
typedef _In_        CONST D3DDDI_VIDEO_PRESENT_SOURCE_ID    IN_CONST_D3DDDI_VIDEO_PRESENT_SOURCE_ID;
typedef _In_        CONST D3DDDI_VIDEO_PRESENT_TARGET_ID    IN_CONST_D3DDDI_VIDEO_PRESENT_TARGET_ID;
typedef _In_        CONST D3DKMDT_VIDPN_PRESENT_PATH_INDEX  IN_CONST_D3DKMDT_VIDPN_PRESENT_PATH_INDEX;
typedef _Out_             D3DDDI_VIDEO_PRESENT_TARGET_ID*   OUT_PD3DDDI_VIDEO_PRESENT_TARGET_ID;
typedef _Out_             D3DDDI_VIDEO_PRESENT_SOURCE_ID*   OUT_PD3DDDI_VIDEO_PRESENT_SOURCE_ID;
typedef _Outptr_       D3DKMDT_VIDPN_PRESENT_PATH**      DEREF_OUT_PPD3DKMDT_VIDPN_PRESENT_PATH;
typedef _Outptr_ CONST D3DKMDT_VIDPN_PRESENT_PATH**      DEREF_OUT_CONST_PPD3DKMDT_VIDPN_PRESENT_PATH;
typedef _In_              D3DKMDT_VIDPN_PRESENT_PATH*       IN_PD3DKMDT_VIDPN_PRESENT_PATH;
typedef _In_        CONST D3DKMDT_VIDPN_PRESENT_PATH*       IN_CONST_PD3DKMDT_VIDPN_PRESENT_PATH;
typedef _In_        CONST D3DKMDT_VIDPN_PRESENT_PATH* CONST IN_CONST_PD3DKMDT_VIDPN_PRESENT_PATH_CONST;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNTOPOLOGY_GETNUMPATHS)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNTOPOLOGY_GETNUMPATHS)(
    IN_CONST_D3DKMDT_HVIDPNTOPOLOGY  hVidPnTopology,
    OUT_PSIZE_T                      pNumPaths
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNTOPOLOGY_GETNUMPATHSFROMSOURCE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNTOPOLOGY_GETNUMPATHSFROMSOURCE)(
    IN_CONST_D3DKMDT_HVIDPNTOPOLOGY            hVidPnTopology,
    IN_CONST_D3DDDI_VIDEO_PRESENT_SOURCE_ID    VidPnSourceId,
    OUT_PSIZE_T                                pNumPathsFromSource
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNTOPOLOGY_ENUMPATHTARGETSFROMSOURCE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNTOPOLOGY_ENUMPATHTARGETSFROMSOURCE)(
    IN_CONST_D3DKMDT_HVIDPNTOPOLOGY            hVidPnTopology,
    IN_CONST_D3DDDI_VIDEO_PRESENT_SOURCE_ID    VidPnSourceId,
    IN_CONST_D3DKMDT_VIDPN_PRESENT_PATH_INDEX  VidPnPresentPathIndex,
    OUT_PD3DDDI_VIDEO_PRESENT_TARGET_ID        pVidPnTargetId
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNTOPOLOGY_GETPATHSOURCEFROMTARGET)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNTOPOLOGY_GETPATHSOURCEFROMTARGET)(
    IN_CONST_D3DKMDT_HVIDPNTOPOLOGY            hVidTopology,
    IN_CONST_D3DDDI_VIDEO_PRESENT_TARGET_ID    VidPnTargetId,
    OUT_PD3DDDI_VIDEO_PRESENT_SOURCE_ID        pVidPnSourceId
    );

// NOTE: To dispose of use DXGDMM_VIDPNTOPOLOGY_INTERFACE::pfnReleasePathInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNTOPOLOGY_ACQUIREPATHINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNTOPOLOGY_ACQUIREPATHINFO)(
    IN_CONST_D3DKMDT_HVIDPNTOPOLOGY              hVidPnTopology,
    IN_CONST_D3DDDI_VIDEO_PRESENT_SOURCE_ID      VidPnSourceId,
    IN_CONST_D3DDDI_VIDEO_PRESENT_TARGET_ID      VidPnTargetId,
    DEREF_OUT_CONST_PPD3DKMDT_VIDPN_PRESENT_PATH ppVidPnPresentPathInfo
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNTOPOLOGY_ACQUIREFIRSTPATHINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNTOPOLOGY_ACQUIREFIRSTPATHINFO)(
    IN_CONST_D3DKMDT_HVIDPNTOPOLOGY              hVidPnTopology,
    DEREF_OUT_CONST_PPD3DKMDT_VIDPN_PRESENT_PATH ppFirstVidPnPresentPathInfo
    );


typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNTOPOLOGY_ACQUIRENEXTPATHINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNTOPOLOGY_ACQUIRENEXTPATHINFO)(
    IN_CONST_D3DKMDT_HVIDPNTOPOLOGY              hVidPnTopology,
    IN_CONST_PD3DKMDT_VIDPN_PRESENT_PATH_CONST   pVidPnPresentPathInfo,
    DEREF_OUT_CONST_PPD3DKMDT_VIDPN_PRESENT_PATH ppNextVidPnPresentPathInfo
    );

// NOTE: This updates what the path supports for transformations.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNTOPOLOGY_UPDATEPATHSUPPORTINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNTOPOLOGY_UPDATEPATHSUPPORTINFO)(
     IN_CONST_D3DKMDT_HVIDPNTOPOLOGY              i_hVidPnTopology,
     IN_CONST_PD3DKMDT_VIDPN_PRESENT_PATH         i_pVidPnPresentPathInfo
     );

// NOTE: To dispose of use DXGDMM_VIDPNTOPOLOGY_INTERFACE::pfnReleasePathInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNTOPOLOGY_RELEASEPATHINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNTOPOLOGY_RELEASEPATHINFO)(
     IN_CONST_D3DKMDT_HVIDPNTOPOLOGY             hVidPnTopology,
     IN_CONST_PD3DKMDT_VIDPN_PRESENT_PATH_CONST  pVidPnPresentPathInfo
     );

// NOTE: To dispose of use DXGDMM_VIDPNTOPOLOGY_INTERFACE::pfnReleasePathInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNTOPOLOGY_CREATENEWPATHINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNTOPOLOGY_CREATENEWPATHINFO)(
     IN_CONST_D3DKMDT_HVIDPNTOPOLOGY             hVidPnTopology,
     DEREF_OUT_PPD3DKMDT_VIDPN_PRESENT_PATH      ppNewVidPnPresentPathInfo
     );

// NOTE: Releases the new path info, rendering it inaccessible.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNTOPOLOGY_ADDPATH)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNTOPOLOGY_ADDPATH)(
     IN_D3DKMDT_HVIDPNTOPOLOGY                   hVidPnTopology,
     IN_PD3DKMDT_VIDPN_PRESENT_PATH              pVidPnPresentPath
     );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNTOPOLOGY_REMOVEPATH)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNTOPOLOGY_REMOVEPATH)(
    IN_CONST_D3DKMDT_HVIDPNTOPOLOGY           hVidPnTopology,
    IN_CONST_D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId,
    IN_CONST_D3DDDI_VIDEO_PRESENT_TARGET_ID  VidPnTargetId
    );

typedef struct _DXGK_VIDPNTOPOLOGY_INTERFACE
{
    DXGKDDI_VIDPNTOPOLOGY_GETNUMPATHS                pfnGetNumPaths;
    DXGKDDI_VIDPNTOPOLOGY_GETNUMPATHSFROMSOURCE      pfnGetNumPathsFromSource;
    DXGKDDI_VIDPNTOPOLOGY_ENUMPATHTARGETSFROMSOURCE  pfnEnumPathTargetsFromSource;
    DXGKDDI_VIDPNTOPOLOGY_GETPATHSOURCEFROMTARGET    pfnGetPathSourceFromTarget;
    DXGKDDI_VIDPNTOPOLOGY_ACQUIREPATHINFO            pfnAcquirePathInfo;
    DXGKDDI_VIDPNTOPOLOGY_ACQUIREFIRSTPATHINFO       pfnAcquireFirstPathInfo;
    DXGKDDI_VIDPNTOPOLOGY_ACQUIRENEXTPATHINFO        pfnAcquireNextPathInfo;
    DXGKDDI_VIDPNTOPOLOGY_UPDATEPATHSUPPORTINFO      pfnUpdatePathSupportInfo;
    DXGKDDI_VIDPNTOPOLOGY_RELEASEPATHINFO            pfnReleasePathInfo;
    DXGKDDI_VIDPNTOPOLOGY_CREATENEWPATHINFO          pfnCreateNewPathInfo;
    DXGKDDI_VIDPNTOPOLOGY_ADDPATH                    pfnAddPath;
    DXGKDDI_VIDPNTOPOLOGY_REMOVEPATH                 pfnRemovePath;
} DXGK_VIDPNTOPOLOGY_INTERFACE;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DXGK_VIDPNSOURCEMODESET_INTERFACE (exposed by OS to miniport)
// NOTE: Exposed by OS to miniport via DXGK_VIDPN_INTERFACE::pfnAcquireSourceModeSet.

typedef _In_              D3DKMDT_HVIDPNSOURCEMODESET          IN_D3DKMDT_HVIDPNSOURCEMODESET;
typedef _In_        CONST D3DKMDT_HVIDPNSOURCEMODESET          IN_CONST_D3DKMDT_HVIDPNSOURCEMODESET;
typedef _In_              D3DKMDT_VIDPN_SOURCE_MODE* CONST     IN_PD3DKMDT_VIDPN_SOURCE_MODE_CONST;
typedef _In_        CONST D3DKMDT_VIDPN_SOURCE_MODE* CONST     IN_CONST_PD3DKMDT_VIDPN_SOURCE_MODE_CONST;
typedef _Outptr_       D3DKMDT_VIDPN_SOURCE_MODE**          DEREF_OUT_PPD3DKMDT_VIDPN_SOURCE_MODE;
typedef _Outptr_ CONST D3DKMDT_VIDPN_SOURCE_MODE**          DEREF_OUT_CONST_PPD3DKMDT_VIDPN_SOURCE_MODE;
typedef _In_        CONST D3DKMDT_VIDEO_PRESENT_SOURCE_MODE_ID IN_CONST_D3DKMDT_VIDEO_PRESENT_SOURCE_MODE_ID;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNSOURCEMODESET_GETNUMMODES)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNSOURCEMODESET_GETNUMMODES)(
    IN_CONST_D3DKMDT_HVIDPNSOURCEMODESET          hVidPnSourceModeSet,
    OUT_PSIZE_T_CONST                             pNumSourceModes
    );

// NOTE: To dispose of use DXGK_VIDPNSOURCEMODESET_INTERFACE::pfnReleaseModeInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNSOURCEMODESET_ACQUIREFIRSTMODEINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNSOURCEMODESET_ACQUIREFIRSTMODEINFO)(
    IN_CONST_D3DKMDT_HVIDPNSOURCEMODESET          hVidPnSourceModeSet,
    DEREF_OUT_CONST_PPD3DKMDT_VIDPN_SOURCE_MODE   ppFirstVidPnSourceModeInfo
    );

// NOTE: To dispose of use DXGK_VIDPNSOURCEMODESET_INTERFACE::pfnReleaseModeInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNSOURCEMODESET_ACQUIRENEXTMODEINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNSOURCEMODESET_ACQUIRENEXTMODEINFO)(
    IN_CONST_D3DKMDT_HVIDPNSOURCEMODESET          hVidPnSourceModeSet,
    IN_CONST_PD3DKMDT_VIDPN_SOURCE_MODE_CONST     pVidPnSourceModeInfo,
    DEREF_OUT_CONST_PPD3DKMDT_VIDPN_SOURCE_MODE   ppNextVidPnSourceModeInfo
    );

// NOTE: To dispose of use DXGK_VIDPNSOURCEMODESET_INTERFACE::pfnReleaseModeInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNSOURCEMODESET_ACQUIREPINNEDMODEINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNSOURCEMODESET_ACQUIREPINNEDMODEINFO)(
    IN_CONST_D3DKMDT_HVIDPNSOURCEMODESET          hVidPnSourceModeSet,
    DEREF_OUT_CONST_PPD3DKMDT_VIDPN_SOURCE_MODE  ppPinnedVidPnSourceModeInfo
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNSOURCEMODESET_RELEASEMODEINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNSOURCEMODESET_RELEASEMODEINFO)(
    IN_CONST_D3DKMDT_HVIDPNSOURCEMODESET          hVidPnSourceModeSet,
    IN_CONST_PD3DKMDT_VIDPN_SOURCE_MODE_CONST     pVidPnSourceModeInfo
    );

// NOTE: To dispose of use DXGK_VIDPNSOURCEMODESET_INTERFACE::pfnReleaseModeInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNSOURCEMODESET_CREATENEWMODEINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNSOURCEMODESET_CREATENEWMODEINFO)(
    IN_CONST_D3DKMDT_HVIDPNSOURCEMODESET          hVidPnSourceModeSet,
    DEREF_OUT_PPD3DKMDT_VIDPN_SOURCE_MODE         ppNewVidPnSourceModeInfo
    );

// NOTE: On success, releases the new mode info, rendering it inaccessible.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNSOURCEMODESET_ADDMODE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNSOURCEMODESET_ADDMODE)(
    IN_D3DKMDT_HVIDPNSOURCEMODESET          hVidPnSourceModeSet,
    IN_PD3DKMDT_VIDPN_SOURCE_MODE_CONST     pVidPnSourceModeInfo
    );

// NOTE: Mode ID is assigned to the mode by Windows Graphics Kernel at creation time
//       using DXGK_VIDPNSOURCEMODESET_INTERFACE::pfnCreateNewModeInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNSOURCEMODESET_PINMODE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNSOURCEMODESET_PINMODE)(
    IN_D3DKMDT_HVIDPNSOURCEMODESET                 hVidPnSourceModeSet,
    IN_CONST_D3DKMDT_VIDEO_PRESENT_SOURCE_MODE_ID  VidPnSourceModeId
    );

typedef struct _DXGK_VIDPNSOURCEMODESET_INTERFACE
{
    DXGKDDI_VIDPNSOURCEMODESET_GETNUMMODES              pfnGetNumModes;
    DXGKDDI_VIDPNSOURCEMODESET_ACQUIREFIRSTMODEINFO     pfnAcquireFirstModeInfo;
    DXGKDDI_VIDPNSOURCEMODESET_ACQUIRENEXTMODEINFO      pfnAcquireNextModeInfo;
    DXGKDDI_VIDPNSOURCEMODESET_ACQUIREPINNEDMODEINFO    pfnAcquirePinnedModeInfo;
    DXGKDDI_VIDPNSOURCEMODESET_RELEASEMODEINFO          pfnReleaseModeInfo;
    DXGKDDI_VIDPNSOURCEMODESET_CREATENEWMODEINFO        pfnCreateNewModeInfo;
    DXGKDDI_VIDPNSOURCEMODESET_ADDMODE                  pfnAddMode;
    DXGKDDI_VIDPNSOURCEMODESET_PINMODE                  pfnPinMode;
} DXGK_VIDPNSOURCEMODESET_INTERFACE;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DXGK_VIDPNTARGETMODESET_INTERFACE
// NOTE: Exposed by OS to miniport via DXGK_VIDPN_INTERFACE::pfnAcquireTargetModeSet.

typedef _In_              D3DKMDT_HVIDPNTARGETMODESET          IN_D3DKMDT_HVIDPNTARGETMODESET;
typedef _In_        CONST D3DKMDT_HVIDPNTARGETMODESET          IN_CONST_D3DKMDT_HVIDPNTARGETMODESET;
typedef _In_              D3DKMDT_VIDPN_TARGET_MODE* CONST     IN_PD3DKMDT_VIDPN_TARGET_MODE_CONST;
typedef _In_        CONST D3DKMDT_VIDPN_TARGET_MODE* CONST     IN_CONST_PD3DKMDT_VIDPN_TARGET_MODE_CONST;
typedef _Outptr_       D3DKMDT_VIDPN_TARGET_MODE**          DEREF_OUT_PPD3DKMDT_VIDPN_TARGET_MODE;
typedef _Outptr_ CONST D3DKMDT_VIDPN_TARGET_MODE**          DEREF_OUT_CONST_PPD3DKMDT_VIDPN_TARGET_MODE;
typedef _In_        CONST D3DKMDT_VIDEO_PRESENT_TARGET_MODE_ID IN_CONST_D3DKMDT_VIDEO_PRESENT_TARGET_MODE_ID;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNTARGETMODESET_GETNUMMODES)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNTARGETMODESET_GETNUMMODES)(
    IN_CONST_D3DKMDT_HVIDPNTARGETMODESET           hVidPnTargetModeSet,
    OUT_PSIZE_T_CONST                              pNumTargetModes
    );

// NOTE: To dispose of use pfnReleaseModeInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNTARGETMODESET_ACQUIREFIRSTMODEINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNTARGETMODESET_ACQUIREFIRSTMODEINFO)(
    IN_CONST_D3DKMDT_HVIDPNTARGETMODESET           hVidPnTargetModeSet,
    DEREF_OUT_CONST_PPD3DKMDT_VIDPN_TARGET_MODE    ppFirstVidPnTargetModeInfo
    );

// NOTE: To dispose of use pfnReleaseModeInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNTARGETMODESET_ACQUIRENEXTMODEINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNTARGETMODESET_ACQUIRENEXTMODEINFO)(
    IN_CONST_D3DKMDT_HVIDPNTARGETMODESET           hVidPnTargetModeSet,
    IN_CONST_PD3DKMDT_VIDPN_TARGET_MODE_CONST      pVidPnTargetModeInfo,
    DEREF_OUT_CONST_PPD3DKMDT_VIDPN_TARGET_MODE    ppNextVidPnTargetModeInfo
    );

// NOTE: To dispose of use pfnReleaseModeInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNTARGETMODESET_ACQUIREPINNEDMODEINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNTARGETMODESET_ACQUIREPINNEDMODEINFO)(
    IN_CONST_D3DKMDT_HVIDPNTARGETMODESET           hVidPnTargetModeSet,
    DEREF_OUT_CONST_PPD3DKMDT_VIDPN_TARGET_MODE    ppPinnedVidPnTargetModeInfo
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNTARGETMODESET_RELEASEMODEINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNTARGETMODESET_RELEASEMODEINFO)(
    IN_CONST_D3DKMDT_HVIDPNTARGETMODESET           hVidPnTargetModeSet,
    IN_CONST_PD3DKMDT_VIDPN_TARGET_MODE_CONST      pVidPnTargetModeInfo
    );

// NOTE: To dispose of use pfnReleaseModeInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNTARGETMODESET_CREATENEWMODEINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNTARGETMODESET_CREATENEWMODEINFO)(
    IN_CONST_D3DKMDT_HVIDPNTARGETMODESET           hVidPnTargetModeSet,
    DEREF_OUT_PPD3DKMDT_VIDPN_TARGET_MODE          ppNewVidPnTargetModeInfo
    );

// NOTE: On success, releases the new mode info, rendering it inaccessible.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNTARGETMODESET_ADDMODE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNTARGETMODESET_ADDMODE)(
    IN_D3DKMDT_HVIDPNTARGETMODESET                 hVidPnTargetModeSet,
    IN_PD3DKMDT_VIDPN_TARGET_MODE_CONST            pVidPnTargetModeInfo
    );

// NOTE: Mode ID is assigned to the mode by Windows Graphics Kernel at creation time
//       using DXGKTARGETMODESET_INTERFACE::pfnCreateNewModeInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPNTARGETMODESET_PINMODE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPNTARGETMODESET_PINMODE)(
    IN_D3DKMDT_HVIDPNTARGETMODESET                 hVidPnTargetModeSet,
    IN_CONST_D3DKMDT_VIDEO_PRESENT_TARGET_MODE_ID  VidPnTargetModeId
    );

typedef struct _DXGK_VIDPNTARGETMODESET_INTERFACE
{
    DXGKDDI_VIDPNTARGETMODESET_GETNUMMODES              pfnGetNumModes;
    DXGKDDI_VIDPNTARGETMODESET_ACQUIREFIRSTMODEINFO     pfnAcquireFirstModeInfo;
    DXGKDDI_VIDPNTARGETMODESET_ACQUIRENEXTMODEINFO      pfnAcquireNextModeInfo;
    DXGKDDI_VIDPNTARGETMODESET_ACQUIREPINNEDMODEINFO    pfnAcquirePinnedModeInfo;
    DXGKDDI_VIDPNTARGETMODESET_RELEASEMODEINFO          pfnReleaseModeInfo;
    DXGKDDI_VIDPNTARGETMODESET_CREATENEWMODEINFO        pfnCreateNewModeInfo;
    DXGKDDI_VIDPNTARGETMODESET_ADDMODE                  pfnAddMode;
    DXGKDDI_VIDPNTARGETMODESET_PINMODE                  pfnPinMode;
} DXGK_VIDPNTARGETMODESET_INTERFACE;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DXGK_VIDPN_INTERFACE
// NOTE: Exposed by OS to miniport via DXGK_INTERFACESPECIFICDATA::pfnQueryVidPnInterface.

typedef _In_              D3DKMDT_HVIDPN                       IN_D3DKMDT_HVIDPN;
typedef _In_        CONST D3DKMDT_HVIDPN                       IN_CONST_D3DKMDT_HVIDPN;
typedef _Out_             D3DKMDT_HVIDPNTOPOLOGY*              OUT_PD3DKMDT_HVIDPNTOPOLOGY;
typedef _Outptr_ CONST DXGK_VIDPNTOPOLOGY_INTERFACE**       DEREF_OUT_CONST_PPDXGK_VIDPNTOPOLOGY_INTERFACE;

//////////////
// Topology //
//////////////

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPN_GETTOPOLOGY)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPN_GETTOPOLOGY)(
    IN_CONST_D3DKMDT_HVIDPN                                hVidPn,
    OUT_PD3DKMDT_HVIDPNTOPOLOGY                            phVidPnTopology,
    DEREF_OUT_CONST_PPDXGK_VIDPNTOPOLOGY_INTERFACE         ppVidPnTopologyInterface
    );


/////////////////////
// Source modality //
/////////////////////

typedef _In_        CONST D3DKMDT_HVIDPNSOURCEMODESET          IN_CONST_D3DKMDT_HVIDPNSOURCEMODESET;
typedef _Out_             D3DKMDT_HVIDPNSOURCEMODESET*         OUT_PD3DKMDT_HVIDPNSOURCEMODESET;
typedef _Outptr_ CONST DXGK_VIDPNSOURCEMODESET_INTERFACE**  DEREF_OUT_CONST_PPDXGK_VIDPNSOURCEMODESET_INTERFACE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPN_ACQUIRESOURCEMODESET)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPN_ACQUIRESOURCEMODESET)(
    IN_CONST_D3DKMDT_HVIDPN                                hVidPn,
    IN_CONST_D3DDDI_VIDEO_PRESENT_SOURCE_ID                VidPnSourceId,
    OUT_PD3DKMDT_HVIDPNSOURCEMODESET                       phVidPnSourceModeSet,
    DEREF_OUT_CONST_PPDXGK_VIDPNSOURCEMODESET_INTERFACE    ppVidPnSourceModeSetInterface
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPN_RELEASESOURCEMODESET)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPN_RELEASESOURCEMODESET)(
    IN_CONST_D3DKMDT_HVIDPN                                hVidPn,
    IN_CONST_D3DKMDT_HVIDPNSOURCEMODESET                   hVidPnSourceModeSet
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPN_CREATENEWSOURCEMODESET)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPN_CREATENEWSOURCEMODESET)(
    IN_CONST_D3DKMDT_HVIDPN                                hVidPn,
    IN_CONST_D3DDDI_VIDEO_PRESENT_SOURCE_ID                VidPnSourceId,
    OUT_PD3DKMDT_HVIDPNSOURCEMODESET                       phNewVidPnSourceModeSet,
    DEREF_OUT_CONST_PPDXGK_VIDPNSOURCEMODESET_INTERFACE    ppVidPnSourceModeSetInterface
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPN_ASSIGNSOURCEMODESET)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPN_ASSIGNSOURCEMODESET)(
    IN_D3DKMDT_HVIDPN                                      hVidPn,
    IN_CONST_D3DDDI_VIDEO_PRESENT_SOURCE_ID                VidPnSourceId,
    IN_CONST_D3DKMDT_HVIDPNSOURCEMODESET                   hVidPnSourceModeSet
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPN_ASSIGNMULTISAMPLINGMETHODSET)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPN_ASSIGNMULTISAMPLINGMETHODSET)(
    IN_D3DKMDT_HVIDPN                                       hVidPn,
    IN_CONST_D3DDDI_VIDEO_PRESENT_SOURCE_ID                 VidPnSourceId,
    IN_CONST_SIZE_T                                         NumMethods,
    _In_reads_(NumMethods) CONST D3DDDI_MULTISAMPLINGMETHOD* pSupportedMethodSet
    );


/////////////////////
// Target modality //
/////////////////////

typedef _In_        CONST D3DKMDT_HVIDPNTARGETMODESET          IN_CONST_D3DKMDT_HVIDPNTARGETMODESET;
typedef _Out_             D3DKMDT_HVIDPNTARGETMODESET*         OUT_PD3DKMDT_HVIDPNTARGETMODESET;
typedef _Outptr_ CONST DXGK_VIDPNTARGETMODESET_INTERFACE**  DEREF_OUT_CONST_PPDXGK_VIDPNTARGETMODESET_INTERFACE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPN_ACQUIRETARGETMODESET)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPN_ACQUIRETARGETMODESET)(
    IN_CONST_D3DKMDT_HVIDPN                                  hVidPn,
    IN_CONST_D3DDDI_VIDEO_PRESENT_TARGET_ID                  VidPnTargetId,
    OUT_PD3DKMDT_HVIDPNTARGETMODESET                         phVidPnTargetModeSet,
    DEREF_OUT_CONST_PPDXGK_VIDPNTARGETMODESET_INTERFACE      ppVidPnTargetModeSetInterface
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPN_RELEASETARGETMODESET)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPN_RELEASETARGETMODESET)(
    IN_CONST_D3DKMDT_HVIDPN                                  hVidPn,
    IN_CONST_D3DKMDT_HVIDPNTARGETMODESET                     hVidPnTargetModeSet
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPN_CREATENEWTARGETMODESET)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPN_CREATENEWTARGETMODESET)(
    IN_CONST_D3DKMDT_HVIDPN                               hVidPn,
    IN_CONST_D3DDDI_VIDEO_PRESENT_TARGET_ID               VidPnTargetId,
    OUT_PD3DKMDT_HVIDPNTARGETMODESET                      phNewVidPnTargetModeSet,
    DEREF_OUT_CONST_PPDXGK_VIDPNTARGETMODESET_INTERFACE   ppVidPnTargetModeSetInterace
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_VIDPN_ASSIGNTARGETMODESET)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_VIDPN_ASSIGNTARGETMODESET)(
    IN_D3DKMDT_HVIDPN                                     hVidPn,
    IN_CONST_D3DDDI_VIDEO_PRESENT_TARGET_ID               VidPnTargetId,
    IN_CONST_D3DKMDT_HVIDPNTARGETMODESET                  hVidPnTargetModeSet
    );


// DXGK_VIDPN_INTERFACE interface versions.
typedef enum _DXGK_VIDPN_INTERFACE_VERSION
{
    DXGK_VIDPN_INTERFACE_VERSION_UNINITIALIZED = 0,
    DXGK_VIDPN_INTERFACE_VERSION_V1            = 1,
} DXGK_VIDPN_INTERFACE_VERSION;

typedef struct _DXGK_VIDPN_INTERFACE
{
    // Specifies the version of this interface as well as all the sub-interfaces, which are accessible
    // only via this interface (i.e. DXGK_VIDPNTOPOLOGY_INTERFACE, DXGK_VIDPNSOURCEMODESET_INTERFACE,
    // and DXGK_VIDPNTARGETMODESET_INTERFACE).
    DXGK_VIDPN_INTERFACE_VERSION                 Version;

    // Topology
    DXGKDDI_VIDPN_GETTOPOLOGY                    pfnGetTopology;

    // Source modality
    DXGKDDI_VIDPN_ACQUIRESOURCEMODESET           pfnAcquireSourceModeSet;
    DXGKDDI_VIDPN_RELEASESOURCEMODESET           pfnReleaseSourceModeSet;
    DXGKDDI_VIDPN_CREATENEWSOURCEMODESET         pfnCreateNewSourceModeSet;
    DXGKDDI_VIDPN_ASSIGNSOURCEMODESET            pfnAssignSourceModeSet;
    DXGKDDI_VIDPN_ASSIGNMULTISAMPLINGMETHODSET   pfnAssignMultisamplingMethodSet;

    // Target modality
    DXGKDDI_VIDPN_ACQUIRETARGETMODESET           pfnAcquireTargetModeSet;
    DXGKDDI_VIDPN_RELEASETARGETMODESET           pfnReleaseTargetModeSet;
    DXGKDDI_VIDPN_CREATENEWTARGETMODESET         pfnCreateNewTargetModeSet;
    DXGKDDI_VIDPN_ASSIGNTARGETMODESET            pfnAssignTargetModeSet;
}
DXGK_VIDPN_INTERFACE;


// Callback miniport uses to query DXGK_VIDPN_INTERFACE.

typedef _In_        CONST DXGK_VIDPN_INTERFACE_VERSION        IN_CONST_DXGK_VIDPN_INTERFACE_VERSION;
typedef _Outptr_ CONST DXGK_VIDPN_INTERFACE**              DEREF_OUT_CONST_PPDXGK_VIDPN_INTERFACE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKCB_QUERYVIDPNINTERFACE)
    _IRQL_requires_max_(APC_LEVEL)
NTSTATUS
(APIENTRY CALLBACK *DXGKCB_QUERYVIDPNINTERFACE)(
    IN_CONST_D3DKMDT_HVIDPN                                 hVidPn,
    IN_CONST_DXGK_VIDPN_INTERFACE_VERSION                   VidPnInterfaceVersion,
    DEREF_OUT_CONST_PPDXGK_VIDPN_INTERFACE                  ppVidPnInterface
    );


/////////////////////////////
// Monitor source modality //
/////////////////////////////

typedef _In_        CONST D3DKMDT_HMONITORSOURCEMODESET        IN_CONST_D3DKMDT_HMONITORSOURCEMODESET;
typedef _In_              D3DKMDT_MONITOR_SOURCE_MODE* CONST   IN_PD3DKMDT_MONITOR_SOURCE_MODE_CONST;
typedef _In_        CONST D3DKMDT_MONITOR_SOURCE_MODE* CONST   IN_CONST_PD3DKMDT_MONITOR_SOURCE_MODE_CONST;
typedef _Outptr_       D3DKMDT_MONITOR_SOURCE_MODE**        DEREF_OUT_PPD3DKMDT_MONITOR_SOURCE_MODE;
typedef _Outptr_ CONST D3DKMDT_MONITOR_SOURCE_MODE**        DEREF_OUT_CONST_PPD3DKMDT_MONITOR_SOURCE_MODE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DXGK_MONITORSOURCEMODESET_INTERFACE
// NOTE: Exposed by OS to miniport via DXGK_MONITOR_INTERFACE::pfnAcquireMonitorSourceModeSet.

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITORSOURCEMODESET_GETNUMMODES)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITORSOURCEMODESET_GETNUMMODES)(
    IN_CONST_D3DKMDT_HMONITORSOURCEMODESET                  hMonitorSourceModeSet,
    OUT_PSIZE_T_CONST                                       pNumMonitorSourceModes
    );

// NOTE: To dispose of use pfnReleaseModeInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITORSOURCEMODESET_ACQUIREPREFERREDMODEINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITORSOURCEMODESET_ACQUIREPREFERREDMODEINFO)(
    IN_CONST_D3DKMDT_HMONITORSOURCEMODESET                  hMonitorSourceModeSet,
    DEREF_OUT_CONST_PPD3DKMDT_MONITOR_SOURCE_MODE           ppFirstMonitorSourceModeInfo
    );

// NOTE: To dispose of use pfnReleaseModeInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITORSOURCEMODESET_ACQUIREFIRSTMODEINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITORSOURCEMODESET_ACQUIREFIRSTMODEINFO)(
    IN_CONST_D3DKMDT_HMONITORSOURCEMODESET                  hMonitorSourceModeSet,
    DEREF_OUT_CONST_PPD3DKMDT_MONITOR_SOURCE_MODE           ppFirstMonitorSourceModeInfo
    );

// NOTE: To dispose of use pfnReleaseModeInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITORSOURCEMODESET_ACQUIRENEXTMODEINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITORSOURCEMODESET_ACQUIRENEXTMODEINFO)(
    IN_CONST_D3DKMDT_HMONITORSOURCEMODESET                  hMonitorSourceModeSet,
    IN_CONST_PD3DKMDT_MONITOR_SOURCE_MODE_CONST             pMonitorSourceModeInfo,
    DEREF_OUT_CONST_PPD3DKMDT_MONITOR_SOURCE_MODE           ppNextMonitorSourceModeInfo
    );

// NOTE: To dispose of use pfnReleaseModeInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITORSOURCEMODESET_CREATENEWMODEINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITORSOURCEMODESET_CREATENEWMODEINFO)(
    IN_CONST_D3DKMDT_HMONITORSOURCEMODESET                  hMonitorSourceModeSet,
    DEREF_OUT_PPD3DKMDT_MONITOR_SOURCE_MODE                 ppNewMonitorSourceModeInfo
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITORSOURCEMODESET_ADDMODE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITORSOURCEMODESET_ADDMODE)(
    IN_CONST_D3DKMDT_HMONITORSOURCEMODESET                  hMonitorSourceModeSet,
    IN_PD3DKMDT_MONITOR_SOURCE_MODE_CONST                   pMonitorSourceModeInfo
    );

// NOTE: On success, releases the new mode info, rendering it inaccessible.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITORSOURCEMODESET_RELEASEMODEINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITORSOURCEMODESET_RELEASEMODEINFO)(
     IN_CONST_D3DKMDT_HMONITORSOURCEMODESET                 hMonitorSourceModeSet,
     IN_CONST_PD3DKMDT_MONITOR_SOURCE_MODE_CONST            pMonitorSourceModeInfo
     );


typedef struct _DXGK_MONITORSOURCEMODESET_INTERFACE
{
    DXGKDDI_MONITORSOURCEMODESET_GETNUMMODES               pfnGetNumModes;
    DXGKDDI_MONITORSOURCEMODESET_ACQUIREPREFERREDMODEINFO  pfnAcquirePreferredModeInfo;
    DXGKDDI_MONITORSOURCEMODESET_ACQUIREFIRSTMODEINFO      pfnAcquireFirstModeInfo;
    DXGKDDI_MONITORSOURCEMODESET_ACQUIRENEXTMODEINFO       pfnAcquireNextModeInfo;
    DXGKDDI_MONITORSOURCEMODESET_CREATENEWMODEINFO         pfnCreateNewModeInfo;
    DXGKDDI_MONITORSOURCEMODESET_ADDMODE                   pfnAddMode;
    DXGKDDI_MONITORSOURCEMODESET_RELEASEMODEINFO           pfnReleaseModeInfo;
} DXGK_MONITORSOURCEMODESET_INTERFACE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DXGK_MONITORFREQUENCYRANGESET_INTERFACE
// NOTE: Exposed by OS to miniport via DXGK_MONITOR_INTERFACE::pfnAcquireMonitorFrequencyRangeSet.

typedef _In_        CONST D3DKMDT_HMONITORFREQUENCYRANGESET       IN_CONST_D3DKMDT_HMONITORFREQUENCYRANGESET;
typedef _In_        CONST D3DKMDT_MONITOR_FREQUENCY_RANGE* CONST  IN_CONST_PD3DKMDT_MONITOR_FREQUENCY_RANGE_CONST;
typedef _Outptr_ CONST D3DKMDT_MONITOR_FREQUENCY_RANGE**       DEREF_OUT_CONST_PPD3DKMDT_MONITOR_FREQUENCY_RANGE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITORFREQUENCYRANGESET_GETNUMFREQUENCYRANGES)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITORFREQUENCYRANGESET_GETNUMFREQUENCYRANGES)(
    IN_CONST_D3DKMDT_HMONITORFREQUENCYRANGESET    hMonitorFrequencyRangeSet,
    OUT_PSIZE_T_CONST                             pNumMonitorFrequencyRanges
    );

// NOTE: To dispose of use pfnReleaseFrequencyRangeInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITORFREQUENCYRANGESET_ACQUIREFIRSTFREQUENCYRANGEINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITORFREQUENCYRANGESET_ACQUIREFIRSTFREQUENCYRANGEINFO)(
    IN_CONST_D3DKMDT_HMONITORFREQUENCYRANGESET          hMonitorFrequencyRangeSet,
    DEREF_OUT_CONST_PPD3DKMDT_MONITOR_FREQUENCY_RANGE   ppFirstMonitorFrequencyRangeInfo
    );

// NOTE: To dispose of use pfnReleaseFrequencyRangeInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITORFREQUENCYRANGESET_ACQUIRENEXTFREQUENCYRANGEINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITORFREQUENCYRANGESET_ACQUIRENEXTFREQUENCYRANGEINFO)(
    IN_CONST_D3DKMDT_HMONITORFREQUENCYRANGESET          hMonitorFrequencyRangeSet,
    IN_CONST_PD3DKMDT_MONITOR_FREQUENCY_RANGE_CONST     pMonitorFrequencyRangeInfo,
    DEREF_OUT_CONST_PPD3DKMDT_MONITOR_FREQUENCY_RANGE   ppNextMonitorFrequencyRangeInfo
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITORFREQUENCYRANGESET_RELEASEFREQUENCYRANGEINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITORFREQUENCYRANGESET_RELEASEFREQUENCYRANGEINFO)(
     IN_CONST_D3DKMDT_HMONITORFREQUENCYRANGESET         hMonitorFrequencyRangeSet,
     IN_CONST_PD3DKMDT_MONITOR_FREQUENCY_RANGE_CONST    pMonitorFrequencyRangeInfo
     );

typedef struct _DXGK_MONITORFREQUENCYRANGESET_INTERFACE
{
    DXGKDDI_MONITORFREQUENCYRANGESET_GETNUMFREQUENCYRANGES           pfnGetNumFrequencyRanges;
    DXGKDDI_MONITORFREQUENCYRANGESET_ACQUIREFIRSTFREQUENCYRANGEINFO  pfnAcquireFirstFrequencyRangeInfo;
    DXGKDDI_MONITORFREQUENCYRANGESET_ACQUIRENEXTFREQUENCYRANGEINFO   pfnAcquireNextFrequencyRangeInfo;
    DXGKDDI_MONITORFREQUENCYRANGESET_RELEASEFREQUENCYRANGEINFO       pfnReleaseFrequencyRangeInfo;
} DXGK_MONITORFREQUENCYRANGESET_INTERFACE;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DXGK_MONITORDESCRIPTORSET_INTERFACE
// NOTE: Exposed by OS to miniport via DXGK_MONITOR_INTERFACE::pfnAcquireMonitorDescriptorSet.

typedef _In_        CONST D3DKMDT_HMONITORDESCRIPTORSET        IN_CONST_D3DKMDT_HMONITORDESCRIPTORSET;
typedef _In_        CONST D3DKMDT_MONITOR_DESCRIPTOR* CONST    IN_CONST_PD3DKMDT_MONITOR_DESCRIPTOR_CONST;
typedef _Outptr_ CONST D3DKMDT_MONITOR_DESCRIPTOR**         DEREF_OUT_CONST_PPD3DKMDT_MONITOR_DESCRIPTOR;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITORDESCRIPTORSET_GETNUMDESCRIPTORS)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITORDESCRIPTORSET_GETNUMDESCRIPTORS)(
    IN_CONST_D3DKMDT_HMONITORDESCRIPTORSET              hMonitorDescriptorSet,
    OUT_PSIZE_T_CONST                                   pNumMonitorDescriptors
    );

// NOTE: To dispose of use pfnReleaseDescriptorInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITORDESCRIPTORSET_ACQUIREFIRSTDESCRIPTORINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITORDESCRIPTORSET_ACQUIREFIRSTDESCRIPTORINFO)(
    IN_CONST_D3DKMDT_HMONITORDESCRIPTORSET              hMonitorDescriptorSet,
    DEREF_OUT_CONST_PPD3DKMDT_MONITOR_DESCRIPTOR        ppFirstMonitorDescriptorInfo
    );

// NOTE: To dispose of use pfnReleaseDescriptorInfo.
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITORDESCRIPTORSET_ACQUIRENEXTDESCRIPTORINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITORDESCRIPTORSET_ACQUIRENEXTDESCRIPTORINFO)(
    IN_CONST_D3DKMDT_HMONITORDESCRIPTORSET              hMonitorDescriptorSet,
    IN_CONST_PD3DKMDT_MONITOR_DESCRIPTOR_CONST          pMonitorDescriptorInfo,
    DEREF_OUT_CONST_PPD3DKMDT_MONITOR_DESCRIPTOR        ppNextMonitorDescriptorInfo
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITORDESCRIPTORSET_RELEASEDESCRIPTORINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITORDESCRIPTORSET_RELEASEDESCRIPTORINFO)(
     IN_CONST_D3DKMDT_HMONITORDESCRIPTORSET             hMonitorDescriptorSet,
     IN_CONST_PD3DKMDT_MONITOR_DESCRIPTOR_CONST         pMonitorDescriptorInfo
     );

typedef struct _DXGK_MONITORDESCRIPTORSET_INTERFACE
{
    DXGKDDI_MONITORDESCRIPTORSET_GETNUMDESCRIPTORS           pfnGetNumDescriptors;
    DXGKDDI_MONITORDESCRIPTORSET_ACQUIREFIRSTDESCRIPTORINFO  pfnAcquireFirstDescriptorInfo;
    DXGKDDI_MONITORDESCRIPTORSET_ACQUIRENEXTDESCRIPTORINFO   pfnAcquireNextDescriptorInfo;
    DXGKDDI_MONITORDESCRIPTORSET_RELEASEDESCRIPTORINFO       pfnReleaseDescriptorInfo;
} DXGK_MONITORDESCRIPTORSET_INTERFACE;


typedef _In_        CONST D3DKMDT_ADAPTER                           IN_CONST_D3DKMDT_ADAPTER;
typedef _Out_             D3DKMDT_HMONITORDESCRIPTORSET*            OUT_PD3DKMDT_HMONITORDESCRIPTORSET;
typedef _Out_             D3DKMDT_HMONITORSOURCEMODESET*            OUT_PD3DKMDT_HMONITORSOURCEMODESET;
typedef _Out_             D3DKMDT_HMONITORFREQUENCYRANGESET*        OUT_PD3DKMDT_HMONITORFREQUENCYRANGESET;
typedef _Outptr_ CONST DXGK_MONITORSOURCEMODESET_INTERFACE**     DEREF_OUT_CONST_PPDXGK_MONITORSOURCEMODESET_INTERFACE;
typedef _Outptr_ CONST DXGK_MONITORFREQUENCYRANGESET_INTERFACE** DEREF_OUT_CONST_PPDXGK_MONITORFREQUENCYRANGESET_INTERFACE;
typedef _Outptr_ CONST DXGK_MONITORDESCRIPTORSET_INTERFACE**     DEREF_OUT_CONST_PPDXGK_MONITORDESCRIPTORSET_INTERFACE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITOR_ACQUIREMONITORSOURCEMODESET)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITOR_ACQUIREMONITORSOURCEMODESET)(
    IN_CONST_D3DKMDT_ADAPTER                              hAdapter,
    IN_CONST_D3DDDI_VIDEO_PRESENT_TARGET_ID               VideoPresentTargetId,
    OUT_PD3DKMDT_HMONITORSOURCEMODESET                    phMonitorSourceModeSet,
    DEREF_OUT_CONST_PPDXGK_MONITORSOURCEMODESET_INTERFACE ppMonitorSourceModeSetInterface
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITOR_RELEASEMONITORSOURCEMODESET)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITOR_RELEASEMONITORSOURCEMODESET)(
    IN_CONST_D3DKMDT_ADAPTER                hAdapter,
    IN_CONST_D3DKMDT_HMONITORSOURCEMODESET  hMonitorSourceModeSet
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITOR_GETMONITORFREQUENCYRANGESET)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITOR_GETMONITORFREQUENCYRANGESET)(
    IN_CONST_D3DKMDT_ADAPTER                                  hAdapter,
    IN_CONST_D3DDDI_VIDEO_PRESENT_TARGET_ID                   VideoPresentTargetId,
    OUT_PD3DKMDT_HMONITORFREQUENCYRANGESET                    phMonitorFrequencyRangeSet,
    DEREF_OUT_CONST_PPDXGK_MONITORFREQUENCYRANGESET_INTERFACE ppMonitorFrequencyRangeSetInterface
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITOR_GETMONITORDESCRIPTORSET)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITOR_GETMONITORDESCRIPTORSET)(
    IN_CONST_D3DKMDT_ADAPTER                                  hAdapter,
    IN_CONST_D3DDDI_VIDEO_PRESENT_TARGET_ID                   VideoPresentTargetId,
    OUT_PD3DKMDT_HMONITORDESCRIPTORSET                        phMonitorDescriptorSet,
    DEREF_OUT_CONST_PPDXGK_MONITORDESCRIPTORSET_INTERFACE     ppMonitorDescriptorSetInterface
    );


// DXGK_MONITOR_INTERFACE interface versions.
typedef enum _DXGK_MONITOR_INTERFACE_VERSION
{
    DXGK_MONITOR_INTERFACE_VERSION_UNINITIALIZED = 0,
    DXGK_MONITOR_INTERFACE_VERSION_V1            = 1,
    DXGK_MONITOR_INTERFACE_VERSION_V2            = 2,
} DXGK_MONITOR_INTERFACE_VERSION;

typedef struct _DXGK_MONITOR_INTERFACE
{
    // Specifies the version of this interface as well as all the sub-interfaces, which are accessible
    // only via this interface (i.e. DXGK_VIDPNTOPOLOGY_INTERFACE, DXGK_VIDPNSOURCEMODESET_INTERFACE,
    // and DXGK_VIDPNTARGETMODESET_INTERFACE).
    DXGK_MONITOR_INTERFACE_VERSION                 Version;

    DXGKDDI_MONITOR_ACQUIREMONITORSOURCEMODESET    pfnAcquireMonitorSourceModeSet;
    DXGKDDI_MONITOR_RELEASEMONITORSOURCEMODESET    pfnReleaseMonitorSourceModeSet;
    DXGKDDI_MONITOR_GETMONITORFREQUENCYRANGESET    pfnGetMonitorFrequencyRangeSet;
    DXGKDDI_MONITOR_GETMONITORDESCRIPTORSET        pfnGetMonitorDescriptorSet;
}
DXGK_MONITOR_INTERFACE;

// Definition of DXGK_MONITOR_INTERFACE interface versions 2

typedef _In_        CONST DXGK_TARGETMODE_DETAIL_TIMING*              IN_CONST_PDXGK_TARGETMODE_DETAIL_TIMING;
typedef DXGK_TARGETMODE_DETAIL_TIMING**  DEREF_ECOUNT_PPDXGK_TARGETMODE_DETAIL_TIMING;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITOR_GETADDITIONALMONITORMODESET)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITOR_GETADDITIONALMONITORMODESET)(
    IN_CONST_D3DKMDT_ADAPTER                     hAdapter,
    IN_CONST_D3DDDI_VIDEO_PRESENT_TARGET_ID      VideoPresentTargetId,
    OUT_PUINT                                    pNumberModes,
    _At_(*ppAdditionalModesSet, _Inout_updates_(*pNumberModes))
    DEREF_ECOUNT_PPDXGK_TARGETMODE_DETAIL_TIMING ppAdditionalModesSet
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_MONITOR_RELEASEADDITIONALMONITORMODESET)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY *DXGKDDI_MONITOR_RELEASEADDITIONALMONITORMODESET)(
    IN_CONST_D3DKMDT_ADAPTER                     hAdapter,
    IN_CONST_D3DDDI_VIDEO_PRESENT_TARGET_ID      VideoPresentTargetId,
    IN_CONST_PDXGK_TARGETMODE_DETAIL_TIMING      pAdditionalModesSet
    );


typedef struct _DXGK_MONITOR_INTERFACE_V2
{
    // Specifies the version of this interface as well as all the sub-interfaces, which are accessible
    // only via this interface (i.e. DXGK_VIDPNTOPOLOGY_INTERFACE, DXGK_VIDPNSOURCEMODESET_INTERFACE,
    // and DXGK_VIDPNTARGETMODESET_INTERFACE). Miniport driver MUST check interface version before using
    // this interface. All the old field in this interface must keep exactly same sequence as old
    // DXGK_MONITOR_INTERFACE.
    DXGK_MONITOR_INTERFACE_VERSION                   Version;

    DXGKDDI_MONITOR_ACQUIREMONITORSOURCEMODESET      pfnAcquireMonitorSourceModeSet;
    DXGKDDI_MONITOR_RELEASEMONITORSOURCEMODESET      pfnReleaseMonitorSourceModeSet;
    DXGKDDI_MONITOR_GETMONITORFREQUENCYRANGESET      pfnGetMonitorFrequencyRangeSet;
    DXGKDDI_MONITOR_GETMONITORDESCRIPTORSET          pfnGetMonitorDescriptorSet;

    // New added functions for DXGK_MONITOR_INTERFACE_V2
    DXGKDDI_MONITOR_GETADDITIONALMONITORMODESET      pfnGetAdditionalMonitorModeSet;
    DXGKDDI_MONITOR_RELEASEADDITIONALMONITORMODESET  pfnReleaseAdditionalMonitorModeSet;
}
DXGK_MONITOR_INTERFACE_V2;

// Callback miniport uses to query DXGK_MONITOR_INTERFACE.

typedef _In_        CONST DXGK_MONITOR_INTERFACE_VERSION              IN_CONST_DXGK_MONITOR_INTERFACE_VERSION;
typedef _Outptr_ CONST DXGK_MONITOR_INTERFACE**                    DEREF_OUT_CONST_PPDXGK_MONITOR_INTERFACE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKCB_QUERYMONITORINTERFACE)
    _IRQL_requires_max_(APC_LEVEL)
NTSTATUS
(APIENTRY CALLBACK *DXGKCB_QUERYMONITORINTERFACE)(
    IN_CONST_HANDLE                          hAdapter,
    IN_CONST_DXGK_MONITOR_INTERFACE_VERSION  MonitorInterfaceVersion,
    DEREF_OUT_CONST_PPDXGK_MONITOR_INTERFACE ppMonitorInterface
    );



#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN7)

///////////////////////////////////////////////////////////////
// New DMM DDIs for CCD support
//

typedef struct _DXGKARG_QUERYVIDPNHWCAPABILITY
{
    IN   D3DKMDT_HVIDPN                         hFunctionalVidPn;
    IN   D3DDDI_VIDEO_PRESENT_SOURCE_ID         SourceId;
    IN   D3DDDI_VIDEO_PRESENT_TARGET_ID         TargetId;
    OUT  D3DKMDT_VIDPN_HW_CAPABILITY            VidPnHWCaps;
}
DXGKARG_QUERYVIDPNHWCAPABILITY;

typedef _Inout_ DXGKARG_QUERYVIDPNHWCAPABILITY*  INOUT_PDXGKARG_QUERYVIDPNHWCAPABILITY;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_QUERYVIDPNHWCAPABILITY)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_QUERYVIDPNHWCAPABILITY(
    IN_CONST_HANDLE                             i_hAdapter,
    INOUT_PDXGKARG_QUERYVIDPNHWCAPABILITY       io_pVidPnHWCaps
    );
/*++
Routine Description:
    Calls miniport to report the hardware capability on a specified functional VidPN
    supported by the adapter.

Arguments:
    i_hAdapter
       -> WDDM display miniport adapter handle.

    io_pVidPnHWCaps

       -> hFunctionalVidPn
           - handle of a functional VidPn to query hardware capability on.

       -> hTargetId
           - ID of the target in the path this query on.

       -> VidPnHWCaps
           - structure to hold the returned hardware capability.

Return Value:
    STATUS_SUCCESS
      - Request completed successfully.

    STATUS_NO_MEMORY
      - Low memory condition prevented successful completion of this request.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/

#endif // DXGKDDI_INTERFACE_VERSION

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)

//
// Definitions for the kernel mode display only device present.
//

typedef
    _Function_class_DXGK_(DXGKCB_PRESENT_DISPLAYONLY_PROGRESS)
    _IRQL_requires_min_(PASSIVE_LEVEL)
    _IRQL_requires_max_(PROFILE_LEVEL  - 1)
VOID (APIENTRY CALLBACK *DXGKCB_PRESENT_DISPLAYONLY_PROGRESS)(
    IN_CONST_HANDLE hAdapter, IN_CONST_PDXGKARGCB_PRESENT_DISPLAYONLY_PROGRESS
    );

typedef struct _D3DKMT_PRESENT_DISPLAY_ONLY_FLAGS
{
    union
    {
        struct
        {
            UINT    Rotate                      :  1;       // 0x00000001
            UINT    Reserved                    : 31;       // 0xFFFFFFFE
        };
        UINT    Value;
    };
} D3DKMT_PRESENT_DISPLAY_ONLY_FLAGS;

typedef struct _DXGKARG_PRESENT_DISPLAYONLY
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID      VidPnSourceId;                  // in:  VidPn where the image is presented
    VOID*                               pSource;                        // in:  Start address of source image
    ULONG                               BytesPerPixel;                  // in:  Bytes per pixel in source image
    LONG                                Pitch;                          // in:  Bytes per line in source image
    D3DKMT_PRESENT_DISPLAY_ONLY_FLAGS   Flags;                          // in:  Flags of current present,
    ULONG                               NumMoves;                       // in:  Number of screen to screen moves
    _Field_size_(NumMoves)
    D3DKMT_MOVE_RECT*                   pMoves;                         // in:  Point to the list of moves
    ULONG                               NumDirtyRects;                  // in:  Number of direct rects
    _Field_size_(NumDirtyRects)
    RECT*                               pDirtyRect;                     // in:  Point to the list of dirty rects
    DXGKCB_PRESENT_DISPLAYONLY_PROGRESS pfnPresentDisplayOnlyProgress;  // in:  Point to present progress callback
} DXGKARG_PRESENT_DISPLAYONLY;

typedef _In_ CONST DXGKARG_PRESENT_DISPLAYONLY*   IN_CONST_PDXGKARG_PRESENT_DISPLAYONLY;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_PRESENTDISPLAYONLY)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_PRESENTDISPLAYONLY(
    IN_CONST_HANDLE                        hAdapter,
    IN_CONST_PDXGKARG_PRESENT_DISPLAYONLY  pPresentDisplayOnly
    );

#endif // DXGKDDI_INTERFACE_VERSION

//////////////////// Timeout Detection and Recovery /////////////////////////////////////////////////////////

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)

///////////////////////////////////////////////////////////////
// New DDIs for TDR support.
//

typedef struct _DXGKARG_QUERYDEPENDENTENGINEGROUP
{
    UINT        NodeOrdinal;                // in: node ordinal for the engine being reset
    UINT        EngineOrdinal;              // in: engine ordinal for the engine being reset
    ULONGLONG   DependentNodeOrdinalMask;   // out: bit mask describing all nodes affected by the engine being reset
} DXGKARG_QUERYDEPENDENTENGINEGROUP;

typedef _Inout_ DXGKARG_QUERYDEPENDENTENGINEGROUP*    INOUT_DXGKARG_QUERYDEPENDENTENGINEGROUP;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_QUERYDEPENDENTENGINEGROUP)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_QUERYDEPENDENTENGINEGROUP(
    IN_CONST_HANDLE                             hAdapter,
    INOUT_DXGKARG_QUERYDEPENDENTENGINEGROUP     pQueryDependentEngineGroup
    );

typedef struct _DXGK_ENGINESTATUS
{
    union
    {
        struct
        {
            UINT Responsive : 1;                // 0x00000001   // set to 1 if the engine is making progress, set to 0 if the engine is not responding to requests to report its progress
            UINT Reserved   : 31;               // 0xFFFFFFFE
        };
        UINT Value;
    };
} DXGK_ENGINESTATUS;

typedef struct _DXGKARG_QUERYENGINESTATUS
{
    UINT                NodeOrdinal;    // in: node ordinal
    UINT                EngineOrdinal;  // in: engine ordinal
    DXGK_ENGINESTATUS   EngineStatus;   // out: engine status
} DXGKARG_QUERYENGINESTATUS;

typedef _Inout_ DXGKARG_QUERYENGINESTATUS*  INOUT_PDXGKARG_QUERYENGINESTATUS;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_QUERYENGINESTATUS)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_QUERYENGINESTATUS(
    IN_CONST_HANDLE                     hAdapter,
    INOUT_PDXGKARG_QUERYENGINESTATUS    pQueryEngineStatus
    );

typedef struct _DXGKARG_RESETENGINE
{
    UINT                NodeOrdinal;        // in: node ordinal
    UINT                EngineOrdinal;      // in: engine ordinal
    UINT                LastAbortedFenceId; // out: fence ID of the last packet aborted in the middle of the execution
} DXGKARG_RESETENGINE;

typedef _Inout_ DXGKARG_RESETENGINE*    INOUT_PDXGKARG_RESETENGINE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_RESETENGINE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_RESETENGINE(
    IN_CONST_HANDLE             hAdapter,
    INOUT_PDXGKARG_RESETENGINE  pResetEngine
    );

#endif // DXGKDDI_INTERFACE_VERSION

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

typedef struct _DXGKARG_RESETHWENGINE
{
    UINT                NodeOrdinal;            // in: node ordinal
    UINT                EngineOrdinal;          // in: engine ordinal
} DXGKARG_RESETHWENGINE;

typedef _Inout_ DXGKARG_RESETHWENGINE*    INOUT_PDXGKARG_RESETHWENGINE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_RESETHWENGINE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_RESETHWENGINE(
    IN_CONST_HANDLE                 hAdapter,
    INOUT_PDXGKARG_RESETHWENGINE    pResetHwEngine
    );

typedef struct _DXGKARGCB_INVALIDATEHWCONTEXT
{
    HANDLE                              hHwContext; // in: For contexts that were invalidated by HW engine reset operation,
                                                    // DXG assigned value for the context that was passed to
                                                    // DxgkDdiCreateHwContext.
} DXGKARGCB_INVALIDATEHWCONTEXT;

typedef _In_ CONST DXGKARGCB_INVALIDATEHWCONTEXT*   IN_CONST_PDXGKARGCB_INVALIDATEHWCONTEXT;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKCB_INVALIDATEHWCONTEXT)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY CALLBACK *DXGKCB_INVALIDATEHWCONTEXT)(
    IN_CONST_PDXGKARGCB_INVALIDATEHWCONTEXT
    );

typedef
_Function_class_DXGK_(DXGKCB_INDICATE_CONNECTOR_CHANGE)
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
(APIENTRY *DXGKCB_INDICATE_CONNECTOR_CHANGE)(
    IN_CONST_HANDLE     hAdapter
    );

#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_RESETFROMTIMEOUT)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY CALLBACK
DXGKDDI_RESETFROMTIMEOUT(
    IN_CONST_HANDLE     hAdapter
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_RESTARTFROMTIMEOUT)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY CALLBACK
DXGKDDI_RESTARTFROMTIMEOUT(
    IN_CONST_HANDLE     hAdapter
    );

typedef enum _DXGK_ACTIVE_VIDPN_INVALIDATION_REASON
{
    DXGK_AVIR_UNINITIALIZED = DXGK_RFVR_UNINITIALIZED,
    DXGK_AVIR_HOTKEY        = DXGK_RFVR_HOTKEY,
    DXGK_AVIR_USERMODE      = DXGK_RFVR_USERMODE,
}
DXGK_ACTIVE_VIDPN_INVALIDATION_REASON;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
typedef
    _Check_return_
    _Function_class_DXGK_(DXGKCB_UNBLOCKUEFIFRAMEBUFFERRANGES)
    _IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
(APIENTRY CALLBACK *DXGKCB_UNBLOCKUEFIFRAMEBUFFERRANGES)(
    IN_CONST_HANDLE                   hAdapter,
    IN_CONST_PDXGK_SEGMENTMEMORYSTATE pSegmentMemoryState);
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

typedef struct _DXGK_INTERFACESPECIFICDATA
{
    HANDLE hAdapter;       // in: handle to dxgkrnl's adapter object

    //
    // D3DDDI interface callback functions
    //
    DXGKCB_GETHANDLEDATA          pfnGetHandleDataCb;
    DXGKCB_GETHANDLEPARENT        pfnGetHandleParentCb;
    DXGKCB_ENUMHANDLECHILDREN     pfnEnumHandleChildrenCb;
    DXGKCB_NOTIFY_INTERRUPT       pfnNotifyInterruptCb;
    DXGKCB_NOTIFY_DPC             pfnNotifyDpcCb;
    DXGKCB_QUERYVIDPNINTERFACE    pfnQueryVidPnInterfaceCb;
    DXGKCB_GETCAPTUREADDRESS      pfnGetCaptureAddressCb;
} DXGK_INTERFACESPECIFICDATA;

typedef struct _DXGKARG_SETDISPLAYPRIVATEDRIVERFORMAT
{
    D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;                  // in: Identifies which VidPn we are changing the private driver format attribute of
    HANDLE                          PrimaryAllocation;              // in: If non zero specifies the current primary allocation for the given VidPn
    UINT                            PrivateDriverFormatAttribute;   // in: PrivateFormatAttribute to set for the given VidPn
} DXGKARG_SETDISPLAYPRIVATEDRIVERFORMAT;

typedef _In_ DXGKARG_SETDISPLAYPRIVATEDRIVERFORMAT*    IN_CONST_PDXGKARG_SETDISPLAYPRIVATEDRIVERFORMAT;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_SETDISPLAYPRIVATEDRIVERFORMAT)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_SETDISPLAYPRIVATEDRIVERFORMAT(
    IN_CONST_HANDLE                                 hAdapter,
    IN_CONST_PDXGKARG_SETDISPLAYPRIVATEDRIVERFORMAT pSetDisplayPrivateDriverFormat
    );


/*++
Routine Description:
    RecommendMonitorModes LDDM display miniport VidPN management DDI method

Arguments:
    hAdapter           - LDDM display miniport adapter handle.

    pUpdateActiveVidPnPresentPathArg
       ->VideoPresentTargetId - ID of the video present target to which the monitor in question is connected.

       ->hMonitorSourceModeSet - Handle of the monitor mode set.

       ->pMonitorSourceModeSetInterface - Reference to the monitor mode set interface.

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

    STATUS_NO_MEMORY
      - There is insufficient memory to complete this request.

    One of the invalid parameter STATUS_GRAPHICS_* codes that can be returned by the OS via
    DXGDDI_{VIDPN|MONITOR|* interfaces. These codes should only occur during development since they
    indicate a bug in the driver or OS.

Side-effects:
    On success, optionally, adds one or more monitor source modes to the mode set of the monitor connected to the specified target.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/
typedef struct _DXGKARG_RECOMMENDMONITORMODES
{
    IN D3DDDI_VIDEO_PRESENT_TARGET_ID              VideoPresentTargetId;
    IN D3DKMDT_HMONITORSOURCEMODESET               hMonitorSourceModeSet;
    IN CONST DXGK_MONITORSOURCEMODESET_INTERFACE*  pMonitorSourceModeSetInterface;

} DXGKARG_RECOMMENDMONITORMODES;

typedef _In_ CONST DXGKARG_RECOMMENDMONITORMODES* CONST     IN_CONST_PDXGKARG_RECOMMENDMONITORMODES_CONST;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_RECOMMENDMONITORMODES)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_RECOMMENDMONITORMODES(
    IN_CONST_HANDLE                                 hAdapter,
    IN_CONST_PDXGKARG_RECOMMENDMONITORMODES_CONST   pRecommendMonitorModes
    );

//////////////////// Power management /////////////////////////////////////////////////////////

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDISETPOWERCOMPONENTFSTATE)
    _IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
APIENTRY
DXGKDDISETPOWERCOMPONENTFSTATE(
    IN_CONST_HANDLE DriverContext,
    UINT            ComponentIndex,
    UINT            FState
    );

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDISETPOWERPSTATE)
    _IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDISETPOWERPSTATE(
    IN_CONST_HANDLE DriverContext,
    UINT ComponentIndex,
    UINT RequestedComponentPState
);

#endif // DXGKDDI_INTERFACE_VERSION_WDDM1_3

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDIPOWERRUNTIMECONTROLREQUEST)
    _IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
APIENTRY
DXGKDDIPOWERRUNTIMECONTROLREQUEST(
    IN_CONST_HANDLE DriverContext,
    IN              LPCGUID PowerControlCode,
    IN OPTIONAL     PVOID InBuffer,
    IN              SIZE_T InBufferSize,
    OUT OPTIONAL    PVOID OutBuffer,
    IN              SIZE_T OutBufferSize,
    OUT OPTIONAL    PSIZE_T BytesReturned
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_POWERRUNTIMESETDEVICEHANDLE)
    _IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_POWERRUNTIMESETDEVICEHANDLE(
    IN_CONST_HANDLE DriverContext,
    IN HANDLE PoDeviceHandle
    );

typedef
    _Function_class_DXGK_(DXGKCB_SETPOWERCOMPONENTACTIVE)
    _IRQL_requires_max_(PASSIVE_LEVEL)
VOID
(APIENTRY CALLBACK *DXGKCB_SETPOWERCOMPONENTACTIVE)(
    IN_CONST_HANDLE hAdapter,
    UINT            ComponentIndex
    );

typedef DXGKCB_SETPOWERCOMPONENTACTIVE  *PDXGKCB_SETPOWERCOMPONENTACTIVE;

typedef
    _Function_class_DXGK_(DXGKCB_POWERRUNTIMECONTROLREQUEST)
    _IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
(APIENTRY CALLBACK *DXGKCB_POWERRUNTIMECONTROLREQUEST)(
    IN_CONST_HANDLE hAdapter,
    IN LPCGUID      PowerControlCode,
    IN OPTIONAL     PVOID InBuffer,
    IN              SIZE_T InBufferSize,
    OUT OPTIONAL    PVOID OutBuffer,
    IN              SIZE_T OutBufferSize,
    OUT OPTIONAL    PSIZE_T BytesReturned
    );

typedef DXGKCB_POWERRUNTIMECONTROLREQUEST *PDXGKCB_POWERRUNTIMECONTROLREQUEST;

typedef
    _Function_class_DXGK_(DXGKCB_SETPOWERCOMPONENTIDLE)
    _IRQL_requires_max_(DISPATCH_LEVEL)
VOID
(APIENTRY CALLBACK *DXGKCB_SETPOWERCOMPONENTIDLE)(
    IN_CONST_HANDLE hAdapter,
    UINT            ComponentIndex
    );

typedef DXGKCB_SETPOWERCOMPONENTIDLE  *PDXGKCB_SETPOWERCOMPONENTIDLE;

typedef
    _Function_class_DXGK_(DXGKCB_SETPOWERCOMPONENTLATENCY)
    _IRQL_requires_max_(DISPATCH_LEVEL)
VOID
(APIENTRY CALLBACK *DXGKCB_SETPOWERCOMPONENTLATENCY)(
    IN_CONST_HANDLE hAdapter,
    UINT            ComponentIndex,
    ULONGLONG       Latency
    );

typedef DXGKCB_SETPOWERCOMPONENTLATENCY  *PDXGKCB_SETPOWERCOMPONENTLATENCY;

typedef
    _Function_class_DXGK_(DXGKCB_SETPOWERCOMPONENTRESIDENCY)
    _IRQL_requires_max_(DISPATCH_LEVEL)
VOID
(APIENTRY CALLBACK *DXGKCB_SETPOWERCOMPONENTRESIDENCY)(
    IN_CONST_HANDLE hAdapter,
    UINT            ComponentIndex,
    ULONGLONG       Residency
    );

typedef DXGKCB_SETPOWERCOMPONENTRESIDENCY  *PDXGKCB_SETPOWERCOMPONENTRESIDENCY;

typedef
    _Function_class_DXGK_(DXGKCB_COMPLETEFSTATETRANSITION)
    _IRQL_requires_max_(DISPATCH_LEVEL)
VOID
(APIENTRY CALLBACK *DXGKCB_COMPLETEFSTATETRANSITION)(
    IN_CONST_HANDLE hAdapter,
    UINT            ComponentIndex
    );

typedef DXGKCB_COMPLETEFSTATETRANSITION *PDXGKCB_COMPLETEFSTATETRANSITION;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

typedef enum _DXGK_HARDWARE_CONTENT_PROTECTION_TEARDOWN_FLAGS 
{ 
    DXGK_HARDWARE_CONTENT_PROTECTION_TEARDOWN_FLAG_PREEMPTIVE   = 1 
} DXGK_HARDWARE_CONTENT_PROTECTION_TEARDOWN_FLAGS; 

typedef
    _Function_class_DXGK_(DXGKCB_HARDWARECONTENTPROTECTIONTEARDOWN)
    _IRQL_requires_max_(DISPATCH_LEVEL)
VOID
(APIENTRY CALLBACK *DXGKCB_HARDWARECONTENTPROTECTIONTEARDOWN)(
    IN_CONST_HANDLE hAdapter,
    UINT Flags
    );

#endif

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)

typedef
    _Function_class_DXGK_(DXGKCB_MULTIPLANEOVERLAYDISABLED)
    _IRQL_requires_max_(DISPATCH_LEVEL)
VOID
(APIENTRY CALLBACK *DXGKCB_MULTIPLANEOVERLAYDISABLED)(
    IN_CONST_HANDLE hAdapter,
    UINT VidPnSourceId
    );

typedef
    _Function_class_DXGK_(DXGKCB_MITIGATEDRANGEUPDATE)
    _IRQL_requires_max_(PASSIVE_LEVEL)
VOID
(APIENTRY CALLBACK *DXGKCB_DXGKCB_MITIGATEDRANGEUPDATE)(
    IN_CONST_HANDLE hAdapter,
    IN ULONG VirtualFunctionIndex
    );

#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)

typedef _Out_ DXGKARG_GETNODEMETADATA*   OUT_PDXGKARG_GETNODEMETADATA;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_GETNODEMETADATA)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_GETNODEMETADATA(
    IN_CONST_HANDLE                     hAdapter,
    UINT                                NodeOrdinalAndAdapterIndex,     // WDDMv2: High word is physical adapter index, low word is node ordinal
    OUT_PDXGKARG_GETNODEMETADATA        pGetNodeMetadata
    );

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
#define DXGKNODEMETADATA_GETNODEORDINAL(NodeOrdinalAndAdapterIndex) (NodeOrdinalAndAdapterIndex & 0xFFFF)
#define DXGKNODEMETADATA_GETPHYSICALADAPTERINDEX(NodeOrdinalAndAdapterIndex) (NodeOrdinalAndAdapterIndex >> 16)
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

// Callback for p-state completion
typedef
    _Function_class_DXGK_(DXGKCB_COMPLETEPSTATETRANSITION)
    _IRQL_requires_max_(DISPATCH_LEVEL)
VOID
(APIENTRY CALLBACK *DXGKCB_COMPLETEPSTATETRANSITION)(
    IN_CONST_HANDLE hAdapter,
    IN UINT         ComponentIndex,
    IN UINT         CompletedPState
    );

typedef DXGKCB_COMPLETEPSTATETRANSITION *PDXGKCB_COMPLETEPSTATETRANSITION;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

typedef struct _DXGKARGCB_MAPCONTEXTALLOCATION 
{
    D3DGPU_VIRTUAL_ADDRESS                      BaseAddress;
    D3DGPU_VIRTUAL_ADDRESS                      MinimumAddress;
    D3DGPU_VIRTUAL_ADDRESS                      MaximumAddress;
    HANDLE                                      hAllocation;    
    D3DGPU_SIZE_T                               OffsetInPages;
    D3DGPU_SIZE_T                               SizeInPages;
    D3DDDIGPUVIRTUALADDRESS_PROTECTION_TYPE     Protection;
    UINT64                                      DriverProtection;
} DXGKARGCB_MAPCONTEXTALLOCATION;

typedef _In_ CONST DXGKARGCB_MAPCONTEXTALLOCATION*   IN_CONST_PDXGKARGCB_MAPCONTEXTALLOCATION;

typedef
    _Function_class_DXGK_(DXGKCB_MAPCONTEXTALLOCATION)
    _IRQL_requires_max_(PASSIVE_LEVEL)
D3DGPU_VIRTUAL_ADDRESS
(APIENTRY CALLBACK *DXGKCB_MAPCONTEXTALLOCATION)(
    IN_CONST_HANDLE hAdapter,
    IN_CONST_PDXGKARGCB_MAPCONTEXTALLOCATION pArgs
    );

typedef struct _DXGKARGCB_UPDATECONTEXTALLOCATION 
{
    HANDLE      hAllocation;    
    PVOID       pPrivateDriverData;
    UINT        PrivateDriverDataSize;
} DXGKARGCB_UPDATECONTEXTALLOCATION;

typedef _In_ CONST DXGKARGCB_UPDATECONTEXTALLOCATION*   IN_CONST_PDXGKARGCB_UPDATECONTEXTALLOCATION;

typedef
    _Function_class_DXGK_(DXGKCB_UPDATECONTEXTALLOCATION)
    _IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY CALLBACK *DXGKCB_UPDATECONTEXTALLOCATION)(
    IN_CONST_HANDLE hAdapter,
    IN_CONST_PDXGKARGCB_UPDATECONTEXTALLOCATION pArgs
    );

typedef struct _DXGKARGCB_RESERVEGPUVIRTUALADDRESSRANGE
{
    HANDLE  hDxgkProcess;               // in
    UINT64  SizeInBytes;                // in: size of the virtual address range. Must be multiple of the leaf page table coverage size.
    UINT    Alignment;                  // in: number of bytes to align the start address to. Must be power of 2.
    UINT64  StartVirtualAddress;        // out
    UINT64  BaseAddress;                // in: base address of the virtual address range in bytes. Must be aligned to the leaf page table coverage size.
    union
    {
        struct
        {
            UINT AllowUserModeMapping   : 1;    // in: Allow UMD to map allocations to the range.
        };
        UINT Flags;
    };
} DXGKARGCB_RESERVEGPUVIRTUALADDRESSRANGE;

typedef _Inout_ DXGKARGCB_RESERVEGPUVIRTUALADDRESSRANGE*   INOUT_PDXGKARGCB_RESERVEGPUVIRTUALADDRESSRANGE;

typedef
    _Function_class_DXGK_(DXGKCB_RESERVEGPUVIRTUALADDRESSRANGE)
    _IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY CALLBACK *DXGKCB_RESERVEGPUVIRTUALADDRESSRANGE)(
    IN_CONST_HANDLE hAdapter,
    INOUT_PDXGKARGCB_RESERVEGPUVIRTUALADDRESSRANGE pArgs
    );

#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)

typedef
    _Function_class_DXGK_(DXGKCB_NOTIFYVSYNC)
    _IRQL_requires_max_(DISPATCH_LEVEL)
VOID
(APIENTRY CALLBACK *DXGKCB_NOTIFYVSYNC)(
    IN_CONST_HANDLE                    hAdapter,
    D3DDDI_VIDEO_PRESENT_SOURCE_ID     VidPnSourceId
    );

typedef DXGKCB_NOTIFYVSYNC  *PDXGKCB_NOTIFYVSYNC;

//
// History buffer precision information
// Used with QueryAdapterInfo + DXGKQAITYPE_HISTORYBUFFERPRECISION to
// obtain precision ifnormation for nodes.
//
typedef struct _DXGKARG_HISTORYBUFFERPRECISION
{
    UINT32 PrecisionBits;
} DXGKARG_HISTORYBUFFERPRECISION;


typedef struct _DXGK_HISTORY_BUFFER_HEADER
{
    UINT32 RenderCbSequence;
    UINT32 NumTimestamps;
    UINT32 PrivateDataSize;
	UINT32 Reserved;
} DXGK_HISTORY_BUFFER_HEADER;

typedef struct _DXGK_HISTORY_BUFFER
{
    DXGK_HISTORY_BUFFER_HEADER Header;
    UINT8 DriverPrivateData[1];
} DXGK_HISTORY_BUFFER;

//
// History buffer format DDI.
// Called during DMA completion DPC
//
typedef struct _DXGKARG_FORMATHISTORYBUFFER
{
    DXGK_HISTORY_BUFFER*              pHistoryBuffer;
    UINT32                            HistoryBufferSize;
    PVOID                             pFormattedBuffer;
    UINT32                            FormattedBufferSize;
    UINT32                            NumTimestamps;
    DXGKARG_HISTORYBUFFERPRECISION    Precision;
    UINT32                            Offset;
 } DXGKARG_FORMATHISTORYBUFFER;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_FORMATHISTORYBUFFER)
    _IRQL_requires_(DISPATCH_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_FORMATHISTORYBUFFER(
    IN_CONST_HANDLE                 hContext,
    IN DXGKARG_FORMATHISTORYBUFFER* pFormatData
    );

//
// GPU Clock calibration DDI
// Called on timer
//

typedef _Out_ DXGKARG_CALIBRATEGPUCLOCK*   OUT_PDXGKARG_CALIBRATEGPUCLOCK;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_CALIBRATEGPUCLOCK)
    _IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_CALIBRATEGPUCLOCK(
    IN_CONST_HANDLE                             hAdapter,
    IN UINT32                                   NodeOrdinal,
    IN UINT32                                   EngineOrdinal,
    OUT_PDXGKARG_CALIBRATEGPUCLOCK	            pClockCalibration
    );

#endif // DXGKDDI_INTERFACE_VERSION_WDDM1_3

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
/*++
Routine Description:
    ControlModeBehavior - requests high-level mode enumeration and setting behaviors

Arguments:
    hAdapter                        WDDM display miniport adapter handle.

    pControlModeBehaviorArg
       ->Request                    Input flags indicating the behaviors the OS is requesting.

       ->Satisfied                  Output flags reporting which requests were satisfied.

       ->NotSatisfied               Output flags reporting which requests were NOT satisfied.

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

    STATUS_NO_MEMORY
      - There is insufficient memory to complete this request.

    One of the invalid parameter STATUS_GRAPHICS_* codes that can be returned by the OS via
    DXGDDI_VIDPN* interfaces. These codes should only occur during development since they
    indicate a bug in the driver or OS.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/

typedef union _DXGK_MODE_BEHAVIOR_FLAGS
{
    struct
    {
        UINT    PrioritizeHDR               : 1;    // 0x00000001
        UINT    Reserved                    :31;    // 0xFFFFFFFE
    };
    UINT    Value;
} DXGK_MODE_BEHAVIOR_FLAGS;


typedef struct _DXGKARG_CONTROLMODEBEHAVIOR
{
    IN  DXGK_MODE_BEHAVIOR_FLAGS                Request;
    OUT DXGK_MODE_BEHAVIOR_FLAGS                Satisfied;
    OUT DXGK_MODE_BEHAVIOR_FLAGS                NotSatisfied;
} DXGKARG_CONTROLMODEBEHAVIOR;


typedef _Inout_ DXGKARG_CONTROLMODEBEHAVIOR* INOUT_PDXGKARG_CONTROLMODEBEHAVIOR;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_CONTROLMODEBEHAVIOR)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_CONTROLMODEBEHAVIOR(
    IN_CONST_HANDLE                             hAdapter,
    INOUT_PDXGKARG_CONTROLMODEBEHAVIOR          pControlModeBehaviorArg
    );


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Exposes driver/hardware per monitor/target capabilities.
//  Mode enumeration is typically required to discover if the capability is supported in a particular display 
//  configuration but if the capability is not supported then mode enumeration is unnecessary.
//
typedef struct _DXGK_MONITORLINKINFO
{
    DXGK_MONITORLINKINFO_USAGEHINTS     UsageHints;
    DXGK_MONITORLINKINFO_CAPABILITIES   Capabilities;
} DXGK_MONITORLINKINFO;


/*++
Routine Description:
    UpdateMonitorLinkInfo - Reports static per monitor capabilities

Arguments:
    hAdapter           - WDDM display miniport adapter handle.

    pUpdateMonitorLinkInfoArg
       ->VideoPresentTargetId - ID of the video present target to which the monitor in question is connected.

       ->MonitorLinkInfo - Structure with overrides from the OS and space for the caps from the driver.

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

    STATUS_NO_MEMORY
      - There is insufficient memory to complete this request.

    One of the invalid parameter STATUS_GRAPHICS_* codes that can be returned by the OS via
    DXGDDI_{VIDPN|MONITOR|* interfaces. These codes should only occur during development since they
    indicate a bug in the driver or OS.

Side-effects:
    None

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/
typedef struct _DXGKARG_UPDATEMONITORLINKINFO
{
    IN D3DDDI_VIDEO_PRESENT_TARGET_ID               VideoPresentTargetId;
    IN DXGK_MONITORLINKINFO                         MonitorLinkInfo;

} DXGKARG_UPDATEMONITORLINKINFO;

typedef _Inout_ DXGKARG_UPDATEMONITORLINKINFO*       INOUT_PDXGKARG_UPDATEMONITORLINKINFO;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_UPDATEMONITORLINKINFO)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_UPDATEMONITORLINKINFO(
    IN_CONST_HANDLE                                 hAdapter,
    INOUT_PDXGKARG_UPDATEMONITORLINKINFO            pUpdateMonitorLinkInfoArg
    );


#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)


#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

#if defined(__cplusplus) && !defined(SORTPP_PASS)
typedef enum _DXGK_CONNECTION_STATUS : UINT {
    ConnectionStatusUninitialized   = 0,

    TargetStatusDisconnected        = 4,
    TargetStatusConnected,
    TargetStatusJoined,

    MonitorStatusDisconnected       = 8,
    MonitorStatusUnknown,
    MonitorStatusConnected,

    LinkConfigurationStarted        =12,
    LinkConfigurationFailed,
    LinkConfigurationSucceeded,
} DXGK_CONNECTION_STATUS, *PDXGK_CONNECTION_STATUS;
#else
typedef UINT DXGK_CONNECTION_STATUS;
#endif // defined(__cplusplus) && !defined(SORTPP_PASS)


//
// Connection change structure which is indicated as available by the miniport
// and then picked up by the OS from the driver.
//
typedef struct _DXGK_CONNECTION_CHANGE {
    ULONGLONG                       ConnectionChangeId;
    D3DDDI_VIDEO_PRESENT_TARGET_ID  TargetId            :24;
    DXGK_CONNECTION_STATUS          ConnectionStatus    : 4;
    UINT                            Reserved            : 4;
    union {
        struct {
            D3DKMDT_VIDEO_OUTPUT_TECHNOLOGY LinkTargetType;
        } MonitorConnect;
        struct {
            D3DKMDT_VIDEO_OUTPUT_TECHNOLOGY BaseTargetType;
            D3DDDI_VIDEO_PRESENT_TARGET_ID  NewTargetId;
        } TargetConnect;
        struct {
            D3DKMDT_VIDEO_OUTPUT_TECHNOLOGY BaseTargetType;
            D3DDDI_VIDEO_PRESENT_TARGET_ID  NewTargetId;
        } TargetJoin;
    };
} DXGK_CONNECTION_CHANGE, *PDXGK_CONNECTION_CHANGE;


/*++
Routine Description:
    SetTimingsFromVidPn WDDM display miniport VidPN management DDI method

Arguments:
    hAdapter                        WDDM display miniport adapter handle.

    pSetTimingsFromVidPnArg
       ->hFunctionalVidPn           Handle of a functional VidPN to applyt to hardware.

       ->SetFlags                   Flags to modify the behavior of the call.

       ->PathCount                  Count of paths in the pSetTimingPathInfo array of pointers.

       ->pSetTimingPathInfo       - Array of pointers, one per path, describing the timing changes 
                                        The structure for each path, provides details beyond those 
                                        in the VidPn and contain fields for the driver to describe 
                                        the results of the request

Return Value:
    STATUS_SUCCESS
      - Request has been completed successfully.

    STATUS_NO_MEMORY
      - There is insufficient memory to complete this request.

    One of the invalid parameter STATUS_GRAPHICS_* codes that can be returned by the OS via
    DXGDDI_VIDPN* interfaces. These codes should only occur during development since they
    indicate a bug in the driver or OS.

Side-effects:
    The driver may report changes in link status triggered by attmepting to change the timings.

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/

typedef struct _DXGK_SET_TIMING_FLAGS
{
    union
    {
        struct
        {
            UINT    Reserved;
        };
        UINT    Value;
    };
} DXGK_SET_TIMING_FLAGS;

typedef struct _DXGK_SET_TIMING_RESULTS
{
    union
    {
        struct
        {
            UINT    ConnectionStatusChanges : 1;    // One or more connection status changes were detected in the course of this call
            UINT    Reserved                :31;
        };
        UINT    Value;
    };
} DXGK_SET_TIMING_RESULTS, *PDXGK_SET_TIMING_RESULTS;


#if defined(__cplusplus) && !defined(SORTPP_PASS)

typedef enum _DXGK_PATH_UPDATE : UINT
{
    DXGK_PATH_UPDATE_UNMODIFIED             = 0,
    DXGK_PATH_UPDATE_ADDED                  = 1,
    DXGK_PATH_UPDATE_MODIFIED               = 2,
    DXGK_PATH_UPDATE_REMOVED                = 3
} DXGK_PATH_UPDATE;

typedef enum _DXGK_GLITCH_CAUSE : UINT8
{
    DXGK_GLITCH_CAUSE_DRIVER_ERROR          = 0,
    DXGK_GLITCH_CAUSE_TIMING_CHANGE         = 1,
    DXGK_GLITCH_CAUSE_PIPELINE_CHANGE       = 2,
    DXGK_GLITCH_CAUSE_MEMORY_TIMING         = 3,
    DXGK_GLITCH_CAUSE_ENCODER_RECONFIG      = 4,
    DXGK_GLITCH_CAUSE_MODIFIED_WIRE_USAGE   = 5,
    DXGK_GLITCH_CAUSE_METADATA_CHANGE       = 6,
    DXGK_GLITCH_CAUSE_NONE                  =255
} DXGK_GLITCH_CAUSE;

typedef enum _DXGK_GLITCH_EFFECT : UINT8
{
    DXGK_GLITCH_EFFECT_SYNC_LOSS            = 0,
    DXGK_GLITCH_EFFECT_GARBAGE_CONTENT      = 1,
    DXGK_GLITCH_EFFECT_STALE_CONTENT        = 2,
    DXGK_GLITCH_EFFECT_BLACK_CONTENT        = 3,
    DXGK_GLITCH_EFFECT_DEGRADED_CONTENT     = 4,
    DXGK_GLITCH_EFFECT_SEAMLESS             =255
} DXGK_GLITCH_EFFECT;

typedef enum _DXGK_GLITCH_DURATION : UINT8
{
    DXGK_GLITCH_DURATION_INDEFINITE         = 0,
    DXGK_GLITCH_DURATION_MULTI_FRAME        = 1,
    DXGK_GLITCH_DURATION_SINGLE_FRAME       = 2,
    DXGK_GLITCH_DURATION_MULTI_LINE         = 3,
    DXGK_GLITCH_DURATION_SINGLE_LINE        = 4,
    DXGK_GLITCH_DURATION_NONE               =255
} DXGK_GLITCH_DURATION;

#else
typedef UINT DXGK_PATH_UPDATE;
typedef UINT8 DXGK_GLITCH_CAUSE;
typedef UINT8 DXGK_GLITCH_EFFECT;
typedef UINT8 DXGK_GLITCH_DURATION;
#endif // defined(__cplusplus) && !defined(SORTPP_PASS)

typedef struct _DXGK_SET_TIMING_PATH_INFO
{
    D3DDDI_VIDEO_PRESENT_TARGET_ID      VidPnTargetId;

    union
    {
        // Since this enum type is also used by OS to specify the input
        // colorspace of MPOs hence we are deprecating its use starting
        // WDDM2.3. WDDM2.3 and above drivers should use the new
        // type D3DDDI_OUTPUT_WIRE_COLOR_SPACE_TYPE
        D3DDDI_COLOR_SPACE_TYPE             OutputColorSpace;

        D3DDDI_OUTPUT_WIRE_COLOR_SPACE_TYPE OutputWireColorSpace;
    };

    D3DKMDT_WIRE_FORMAT_AND_PREFERENCE  SelectedWireFormat;

    union
    {
        struct
        {
            DXGK_PATH_UPDATE    VidPnPathUpdates    : 2;    // Indicates how the VidPn description of this path has been modified since the last successful call
            UINT                Active              : 1;    // The host should be driving a signal to the target (timing or training)
            UINT                IgnoreConnectivity  : 1;    // Used to force output to an undetected monitor on an analog target
            UINT                PreserveInherited   : 1;    // Driver should preserve the timings and content inherited from previous driver 
            UINT                Reserved            :27;
        } Input;
        UINT InputFlags;
    };

    union
    {
        struct
        {
            UINT    RecheckMPO              : 1;    // Active plane(s) on other paths need to be released before visibility can be turned on
            UINT    Reserved                :31;
        } Output;
        UINT OutputFlags;
    };

    DXGK_CONNECTION_CHANGE              TargetState;   // Indicates the target state as a result of this call

    union
    {
        struct
        {
            DXGK_GLITCH_CAUSE       GlitchCause; 
            DXGK_GLITCH_EFFECT      GlitchEffect; 
            DXGK_GLITCH_DURATION    GlitchDuration;
            UINT8                   Reserved;
        };
        UINT    DiagnosticInfo;
    };
} DXGK_SET_TIMING_PATH_INFO;

typedef struct _DXGKARG_SETTIMINGSFROMVIDPN
{
    D3DKMDT_HVIDPN                                      hFunctionalVidPn;
    DXGK_SET_TIMING_FLAGS                               SetFlags;
    PDXGK_SET_TIMING_RESULTS                            pResultsFlags;
    UINT                                                PathCount;
    _Field_size_(PathCount) DXGK_SET_TIMING_PATH_INFO * pSetTimingPathInfo;
} DXGKARG_SETTIMINGSFROMVIDPN;


typedef _Inout_ DXGKARG_SETTIMINGSFROMVIDPN*       IN_OUT_PDXGKARG_SETTIMINGSFROMVIDPN;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_SETTIMINGSFROMVIDPN)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_SETTIMINGSFROMVIDPN(
    IN_CONST_HANDLE                             hAdapter,
    IN_OUT_PDXGKARG_SETTIMINGSFROMVIDPN         pSetTimings
    );



/*++
Routine Description:
    SetTargetGamma - Sets the gama ramp on the specified target id

Arguments:
    hAdapter                        WDDM display miniport adapter handle.

    pSetTargetGammaArg
       ->TargetId                   Target to be modified

       ->GammaRamp                  Gamma look up table

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/

typedef struct _DXGKARG_SETTARGETGAMMA
{
    IN  D3DDDI_VIDEO_PRESENT_TARGET_ID  TargetId;
    IN  D3DKMDT_GAMMA_RAMP              GammaRamp;
} DXGKARG_SETTARGETGAMMA;


typedef _In_ CONST DXGKARG_SETTARGETGAMMA* IN_CONST_PDXGKARG_SETTARGETGAMMA;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_SETTARGETGAMMA)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_SETTARGETGAMMA(
    IN_CONST_HANDLE                             hAdapter,
    IN_CONST_PDXGKARG_SETTARGETGAMMA            pSetTargetGammaArg
    );




/*++
Routine Description:
    SetTargetContentType - Sets the content type for which the driver should be optimizing

Arguments:
    hAdapter                        WDDM display miniport adapter handle.

    pSetTargetContentTypeArg
       ->TargetId                   Target to be modified

       ->ContentType                New type of content being displayed

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/

typedef struct _DXGKARG_SETTARGETCONTENTTYPE
{
    IN  D3DDDI_VIDEO_PRESENT_TARGET_ID      TargetId;
    IN  D3DKMDT_VIDPN_PRESENT_PATH_CONTENT  ContentType;
} DXGKARG_SETTARGETCONTENTTYPE;


typedef _In_ CONST DXGKARG_SETTARGETCONTENTTYPE* IN_CONST_PDXGKARG_SETTARGETCONTENTTYPE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_SETTARGETCONTENTTYPE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_SETTARGETCONTENTTYPE(
    IN_CONST_HANDLE                             hAdapter,
    IN_CONST_PDXGKARG_SETTARGETCONTENTTYPE      pSetTargetContentTypeArg
    );




/*++
Routine Description:
    SetTargetAnalogCopyProtection - Sets the analog copy protection on the specified target id

Arguments:
    hAdapter                        WDDM display miniport adapter handle.

    pSetTargetAnalogCopyProtectionArg
       ->TargetId                   Target to be modified

       ->AnalogCopyProtection       Analog copy protection 

Environment:
    Kernel mode. PASSIVE_LEVEL.

--*/

typedef struct _DXGKARG_SETTARGETANALOGCOPYPROTECTION
{
    IN  D3DDDI_VIDEO_PRESENT_TARGET_ID                  TargetId;
    D3DKMDT_VIDPN_PRESENT_PATH_COPYPROTECTION_TYPE      CopyProtectionType;
    UINT                                                APSTriggerBits;
    D3DKMDT_VIDPN_PRESENT_PATH_COPYPROTECTION_SUPPORT   CopyProtectionSupport;
} DXGKARG_SETTARGETANALOGCOPYPROTECTION;


typedef _In_ CONST DXGKARG_SETTARGETANALOGCOPYPROTECTION* IN_CONST_PDXGKARG_SETTARGETANALOGCOPYPROTECTION;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_SETTARGETANALOGCOPYPROTECTION)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_SETTARGETANALOGCOPYPROTECTION(
    IN_CONST_HANDLE                                 hAdapter,
    IN_CONST_PDXGKARG_SETTARGETANALOGCOPYPROTECTION pSetTargetAnalogCopyProtectionArg
    );


#if defined(__cplusplus) && !defined(SORTPP_PASS)
typedef enum _DXGK_DISPLAYDETECTCONTROLTYPE : UINT
{
    DXGK_DDCT_UNINITIALIZED  = 0,
    DXGK_DDCT_POLLONE,
    DXGK_DDCT_POLLALL,
    DXGK_DDCT_ENABLEHPD,
    DXGK_DDCT_DISABLEHPD,
} DXGK_DISPLAYDETECTCONTROLTYPE;
#else
typedef UINT DXGK_DISPLAYDETECTCONTROLTYPE;
#endif // defined(__cplusplus) && !defined(SORTPP_PASS)


typedef struct _DXGKARG_DISPLAYDETECTCONTROL
{
    D3DDDI_VIDEO_PRESENT_TARGET_ID  TargetId            :24;
    DXGK_DISPLAYDETECTCONTROLTYPE   Type                : 4;
    UINT                            NonDestructiveOnly  : 1;
    UINT                            Reserved            : 3;
} DXGKARG_DISPLAYDETECTCONTROL;

typedef _In_ CONST DXGKARG_DISPLAYDETECTCONTROL* IN_CONST_PDXGKARG_DISPLAYDETECTCONTROL;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_DISPLAYDETECTCONTROL)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_DISPLAYDETECTCONTROL(
    IN_CONST_HANDLE                         hAdapter,
    IN_CONST_PDXGKARG_DISPLAYDETECTCONTROL  pDisplayDetectControl
    );


typedef struct _DXGKARG_QUERYCONNECTIONCHANGE
{
    DXGK_CONNECTION_CHANGE                  ConnectionChange;          // out: Buffer into which the oldest available change is copied by driver
} DXGKARG_QUERYCONNECTIONCHANGE;

typedef _In_ DXGKARG_QUERYCONNECTIONCHANGE* IN_PDXGKARG_QUERYCONNECTIONCHANGE;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_QUERYCONNECTIONCHANGE)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_QUERYCONNECTIONCHANGE(
    IN_CONST_HANDLE                         hAdapter,
    IN_PDXGKARG_QUERYCONNECTIONCHANGE       pQueryConnectionChange
    );

typedef struct _DXGK_INHERITED_TIMING_INFO
{
    union
    {
        // Since this enum type is also used by OS to specify the input
        // colorspace of MPOs hence we are deprecating its use starting
        // WDDM2.3. WDDM2.3 and above drivers should use the new
        // type D3DDDI_OUTPUT_WIRE_COLOR_SPACE_TYPE
        D3DDDI_COLOR_SPACE_TYPE             OutputColorSpace;

        D3DDDI_OUTPUT_WIRE_COLOR_SPACE_TYPE OutputWireColorSpace;
    };

    D3DKMDT_WIRE_FORMAT_AND_PREFERENCE  SelectedWireFormat;
    union
    {
        struct
        {
            DXGK_GLITCH_CAUSE           GlitchCause; 
            DXGK_GLITCH_EFFECT          GlitchEffect; 
            DXGK_GLITCH_DURATION        GlitchDuration;
            UINT8                       Reserved;
        };
        UINT    DiagnosticInfo;
    };
} DXGK_INHERITED_TIMING_INFO, *PDXGK_INHERITED_TIMING_INFO;

#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_2

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)

typedef struct _DXGKARG_CREATEPROTECTEDSESSION
{
    HANDLE     hProtectedSession;       // in: DXG assigned value for the protected session that was passed to
                                        //     DxgkDdiCreateProtectedSession.
                                        // out: Driver generated handle.
    PVOID      pPrivateDriverData;
    UINT       PrivateDriverDataSize;
} DXGKARG_CREATEPROTECTEDSESSION;

typedef _Inout_ DXGKARG_CREATEPROTECTEDSESSION* INOUT_PDXGKARG_CREATEPROTECTEDSESSION;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_CREATEPROTECTEDSESSION)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_CREATEPROTECTEDSESSION(
    IN_CONST_HANDLE                       hAdapter,
    INOUT_PDXGKARG_CREATEPROTECTEDSESSION pCreateProtectedSession
    );

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKDDI_DESTROYPROTECTEDSESSION)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
APIENTRY
DXGKDDI_DESTROYPROTECTEDSESSION(
    IN_CONST_HANDLE                       hAdapter,
    IN_CONST_HANDLE                       hProtectedSession // in: Driver generated handle driver returned at DxgkDdiCreateProtectedSession.
    );

typedef enum _DXGK_PROTECTED_SESSION_STATUS
{
    DXGK_PROTECTED_SESSION_STATUS_OK         = 0,
    DXGK_PROTECTED_SESSION_STATUS_INVALID    = 1,
} DXGK_PROTECTED_SESSION_STATUS;

typedef struct _DXGKARGCB_PROTECTEDSESSIONSTATUS
{
    HANDLE                                hProtectedSession; // in: DXG handle
                                                             // in: DXG assigned value for the protected session that was passed to
                                                             //     DxgkDdiCreateProtectedSession.
    DXGK_PROTECTED_SESSION_STATUS         Status;
} DXGKARGCB_PROTECTEDSESSIONSTATUS;

typedef _In_ CONST DXGKARGCB_PROTECTEDSESSIONSTATUS* IN_CONST_PDXGKARGCB_PROTECTEDSESSIONSTATUS;

typedef
    _Check_return_
    _Function_class_DXGK_(DXGKCB_SETPROTECTEDSESSIONSTATUS)
    _IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
(APIENTRY CALLBACK *DXGKCB_SETPROTECTEDSESSIONSTATUS)(
    IN_CONST_PDXGKARGCB_PROTECTEDSESSIONSTATUS pProtectedSessionStatus
    );

#endif // DXGKDDI_INTERFACE_VERSION_WDDM2_3

//
//     Function pointer typedefs
//

typedef DXGKDDI_QUERYADAPTERINFO                *PDXGKDDI_QUERYADAPTERINFO;
typedef DXGKDDI_CREATEDEVICE                    *PDXGKDDI_CREATEDEVICE;
typedef DXGKDDI_CREATEALLOCATION                *PDXGKDDI_CREATEALLOCATION;
typedef DXGKDDI_DESTROYALLOCATION               *PDXGKDDI_DESTROYALLOCATION;
typedef DXGKDDI_DESCRIBEALLOCATION              *PDXGKDDI_DESCRIBEALLOCATION;
typedef DXGKDDI_GETSTANDARDALLOCATIONDRIVERDATA *PDXGKDDI_GETSTANDARDALLOCATIONDRIVERDATA;
typedef DXGKDDI_ACQUIRESWIZZLINGRANGE           *PDXGKDDI_ACQUIRESWIZZLINGRANGE;
typedef DXGKDDI_RELEASESWIZZLINGRANGE           *PDXGKDDI_RELEASESWIZZLINGRANGE;
typedef DXGKDDI_PATCH                           *PDXGKDDI_PATCH;
typedef DXGKDDI_SUBMITCOMMAND                   *PDXGKDDI_SUBMITCOMMAND;
typedef DXGKDDI_PREEMPTCOMMAND                  *PDXGKDDI_PREEMPTCOMMAND;
typedef DXGKDDI_CANCELCOMMAND                   *PDXGKDDI_CANCELCOMMAND;
typedef DXGKDDI_BUILDPAGINGBUFFER               *PDXGKDDI_BUILDPAGINGBUFFER;
typedef DXGKDDI_SETPALETTE                      *PDXGKDDI_SETPALETTE;
typedef DXGKDDI_SETPOINTERPOSITION              *PDXGKDDI_SETPOINTERPOSITION;
typedef DXGKDDI_SETPOINTERSHAPE                 *PDXGKDDI_SETPOINTERSHAPE;
typedef DXGKDDI_RESETFROMTIMEOUT                *PDXGKDDI_RESETFROMTIMEOUT;
typedef DXGKDDI_RESTARTFROMTIMEOUT              *PDXGKDDI_RESTARTFROMTIMEOUT;
typedef DXGKDDI_ESCAPE                          *PDXGKDDI_ESCAPE;
typedef DXGKDDI_COLLECTDBGINFO                  *PDXGKDDI_COLLECTDBGINFO;
typedef DXGKDDI_QUERYCURRENTFENCE               *PDXGKDDI_QUERYCURRENTFENCE;
typedef DXGKDDI_ISSUPPORTEDVIDPN                *PDXGKDDI_ISSUPPORTEDVIDPN;
typedef DXGKDDI_RECOMMENDFUNCTIONALVIDPN        *PDXGKDDI_RECOMMENDFUNCTIONALVIDPN;
typedef DXGKDDI_ENUMVIDPNCOFUNCMODALITY         *PDXGKDDI_ENUMVIDPNCOFUNCMODALITY;
typedef DXGKDDI_SETVIDPNSOURCEADDRESS           *PDXGKDDI_SETVIDPNSOURCEADDRESS;
typedef DXGKDDI_SETVIDPNSOURCEVISIBILITY        *PDXGKDDI_SETVIDPNSOURCEVISIBILITY;
typedef DXGKDDI_COMMITVIDPN                     *PDXGKDDI_COMMITVIDPN;
typedef DXGKDDI_UPDATEACTIVEVIDPNPRESENTPATH    *PDXGKDDI_UPDATEACTIVEVIDPNPRESENTPATH;
typedef DXGKDDI_RECOMMENDMONITORMODES           *PDXGKDDI_RECOMMENDMONITORMODES;
typedef DXGKDDI_RECOMMENDVIDPNTOPOLOGY          *PDXGKDDI_RECOMMENDVIDPNTOPOLOGY;
typedef DXGKDDI_GETSCANLINE                     *PDXGKDDI_GETSCANLINE;
typedef DXGKDDI_STOPCAPTURE                     *PDXGKDDI_STOPCAPTURE;
typedef DXGKDDI_CONTROLINTERRUPT                *PDXGKDDI_CONTROLINTERRUPT;
typedef DXGKDDI_CREATEOVERLAY                   *PDXGKDDI_CREATEOVERLAY;
typedef DXGKDDI_DESTROYDEVICE                   *PDXGKDDI_DESTROYDEVICE;
typedef DXGKDDI_OPENALLOCATIONINFO              *PDXGKDDI_OPENALLOCATIONINFO;
typedef DXGKDDI_CLOSEALLOCATION                 *PDXGKDDI_CLOSEALLOCATION;
typedef DXGKDDI_RENDER                          *PDXGKDDI_RENDER;
typedef DXGKDDI_PRESENT                         *PDXGKDDI_PRESENT;
typedef DXGKDDI_UPDATEOVERLAY                   *PDXGKDDI_UPDATEOVERLAY;
typedef DXGKDDI_FLIPOVERLAY                     *PDXGKDDI_FLIPOVERLAY;
typedef DXGKDDI_DESTROYOVERLAY                  *PDXGKDDI_DESTROYOVERLAY;
typedef DXGKDDI_CREATECONTEXT                   *PDXGKDDI_CREATECONTEXT;
typedef DXGKDDI_DESTROYCONTEXT                  *PDXGKDDI_DESTROYCONTEXT;
typedef DXGKDDI_SETDISPLAYPRIVATEDRIVERFORMAT   *PDXGKDDI_SETDISPLAYPRIVATEDRIVERFORMAT;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN7)
typedef DXGKDDI_RENDERKM                        *PDXGKDDI_RENDERKM;
typedef DXGKDDI_QUERYVIDPNHWCAPABILITY          *PDXGKDDI_QUERYVIDPNHWCAPABILITY;
#endif // DXGKDDI_INTERFACE_VERSION
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
typedef DXGKDDISETPOWERCOMPONENTFSTATE          *PDXGKDDISETPOWERCOMPONENTFSTATE;
typedef DXGKDDIPOWERRUNTIMECONTROLREQUEST       *PDXGKDDIPOWERRUNTIMECONTROLREQUEST;
typedef DXGKDDI_QUERYDEPENDENTENGINEGROUP       *PDXGKDDI_QUERYDEPENDENTENGINEGROUP;
typedef DXGKDDI_QUERYENGINESTATUS               *PDXGKDDI_QUERYENGINESTATUS;
typedef DXGKDDI_RESETENGINE                     *PDXGKDDI_RESETENGINE;
typedef DXGKDDI_PRESENTDISPLAYONLY              *PDXGKDDI_PRESENTDISPLAYONLY;
typedef DXGKDDI_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY *PDXGKDDI_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY;
#endif // DXGKDDI_INTERFACE_VERSION
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
typedef DXGKDDI_GETNODEMETADATA                 *PDXGKDDI_GETNODEMETADATA;
typedef DXGKDDISETPOWERPSTATE                   *PDXGKDDISETPOWERPSTATE;
typedef DXGKDDI_CONTROLINTERRUPT2               *PDXGKDDI_CONTROLINTERRUPT2;
typedef DXGKDDI_CHECKMULTIPLANEOVERLAYSUPPORT   *PDXGKDDI_CHECKMULTIPLANEOVERLAYSUPPORT;
typedef DXGKDDI_FORMATHISTORYBUFFER             *PDXGKDDI_FORMATHISTORYBUFFER;
typedef DXGKDDI_CALIBRATEGPUCLOCK               *PDXGKDDI_CALIBRATEGPUCLOCK; 
#endif // DXGKDDI_INTERFACE_VERSION_WDDM1_3
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
typedef DXGKDDI_RENDERGDI                       *PDXGKDDI_RENDERGDI; 
typedef DXGKDDI_SUBMITCOMMANDVIRTUAL            *PDXGKDDI_SUBMITCOMMANDVIRTUAL; 
typedef DXGKDDI_SETROOTPAGETABLE                *PDXGKDDI_SETROOTPAGETABLE; 
typedef DXGKDDI_GETROOTPAGETABLESIZE            *PDXGKDDI_GETROOTPAGETABLESIZE; 
typedef DXGKDDI_MAPCPUHOSTAPERTURE              *PDXGKDDI_MAPCPUHOSTAPERTURE; 
typedef DXGKDDI_UNMAPCPUHOSTAPERTURE            *PDXGKDDI_UNMAPCPUHOSTAPERTURE; 
typedef DXGKDDI_CREATEPROCESS                   *PDXGKDDI_CREATEPROCESS; 
typedef DXGKDDI_DESTROYPROCESS                  *PDXGKDDI_DESTROYPROCESS; 
typedef DXGKDDI_CHECKMULTIPLANEOVERLAYSUPPORT2              *PDXGKDDI_CHECKMULTIPLANEOVERLAYSUPPORT2;
typedef DXGKDDI_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY2 *PDXGKDDI_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY2;
typedef DXGKDDI_POWERRUNTIMESETDEVICEHANDLE     *PDXGKDDI_POWERRUNTIMESETDEVICEHANDLE;
typedef DXGKDDI_SETSTABLEPOWERSTATE             *PDXGKDDI_SETSTABLEPOWERSTATE;
typedef DXGKDDI_SETVIDEOPROTECTEDREGION         *PDXGKDDI_SETVIDEOPROTECTEDREGION;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)
typedef DXGKDDI_CHECKMULTIPLANEOVERLAYSUPPORT3              *PDXGKDDI_CHECKMULTIPLANEOVERLAYSUPPORT3;
typedef DXGKDDI_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY3 *PDXGKDDI_SETVIDPNSOURCEADDRESSWITHMULTIPLANEOVERLAY3;
typedef DXGKDDI_POSTMULTIPLANEOVERLAYPRESENT                *PDXGKDDI_POSTMULTIPLANEOVERLAYPRESENT;
typedef DXGKDDI_CONTROLMODEBEHAVIOR                         *PDXGKDDI_CONTROLMODEBEHAVIOR;
typedef DXGKDDI_UPDATEMONITORLINKINFO                       *PDXGKDDI_UPDATEMONITORLINKINFO;
typedef DXGKDDI_VALIDATEUPDATEALLOCATIONPROPERTY            *PDXGKDDI_VALIDATEUPDATEALLOCATIONPROPERTY;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_1)

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

typedef DXGKDDI_CREATEHWCONTEXT         *PDXGKDDI_CREATEHWCONTEXT;
typedef DXGKDDI_DESTROYHWCONTEXT        *PDXGKDDI_DESTROYHWCONTEXT;
typedef DXGKDDI_CREATEHWQUEUE           *PDXGKDDI_CREATEHWQUEUE;
typedef DXGKDDI_DESTROYHWQUEUE          *PDXGKDDI_DESTROYHWQUEUE;
typedef DXGKDDI_SUBMITCOMMANDTOHWQUEUE  *PDXGKDDI_SUBMITCOMMANDTOHWQUEUE;
typedef DXGKDDI_SWITCHTOHWCONTEXTLIST   *PDXGKDDI_SWITCHTOHWCONTEXTLIST;
typedef DXGKDDI_RESETHWENGINE           *PDXGKDDI_RESETHWENGINE;

typedef DXGKDDI_CREATEPERIODICFRAMENOTIFICATION     *PDXGKDDI_CREATEPERIODICFRAMENOTIFICATION;
typedef DXGKDDI_DESTROYPERIODICFRAMENOTIFICATION    *PDXGKDDI_DESTROYPERIODICFRAMENOTIFICATION;

typedef DXGKDDI_SETTIMINGSFROMVIDPN             *PDXGKDDI_SETTIMINGSFROMVIDPN;
typedef DXGKDDI_SETTARGETGAMMA                  *PDXGKDDI_SETTARGETGAMMA;
typedef DXGKDDI_SETTARGETCONTENTTYPE            *PDXGKDDI_SETTARGETCONTENTTYPE;
typedef DXGKDDI_SETTARGETANALOGCOPYPROTECTION   *PDXGKDDI_SETTARGETANALOGCOPYPROTECTION;
typedef DXGKDDI_DISPLAYDETECTCONTROL            *PDXGKDDI_DISPLAYDETECTCONTROL;
typedef DXGKDDI_QUERYCONNECTIONCHANGE           *PDXGKDDI_QUERYCONNECTIONCHANGE;
typedef DXGKDDI_GETMULTIPLANEOVERLAYCAPS        *PDXGKDDI_GETMULTIPLANEOVERLAYCAPS;
typedef DXGKDDI_GETPOSTCOMPOSITIONCAPS          *PDXGKDDI_GETPOSTCOMPOSITIONCAPS;
#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)

typedef DXGKDDI_UPDATEHWCONTEXTSTATE   *PDXGKDDI_UPDATEHWCONTEXTSTATE;

typedef DXGKDDI_CREATEPROTECTEDSESSION*  PDXGKDDI_CREATEPROTECTEDSESSION;
typedef DXGKDDI_DESTROYPROTECTEDSESSION* PDXGKDDI_DESTROYPROTECTEDSESSION;

#endif // (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)

#pragma warning(pop)

#endif /* _D3DKMDDI_H_ */



