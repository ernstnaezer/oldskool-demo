#ifndef __VESA_H__
#define __VESA_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <dos.h>

#define DPMI_INT    0x31

// error message:
#define VESAok                  0
#define VESAERR_NO_DOS_MEM      1
#define VESAERR_NO_VESA         2
#define VESAERR_BAD_VERSION     3
#define VESAERR_NO_MEM          4

#pragma pack(1)
// vbe2 structures:
typedef struct {
    uint32_t      VbeSignature;       // VBE Signature
    uint16_t       VbeVersion;         // VBE Version
    uint32_t      OemStringPtr;       // Pointer to OEM String
    uint8_t       Capabilities[4];    // Capabilities of graphics cont.
    uint32_t      VideoModePtr;       // Pointer to Video Mode List
    uint16_t       TotalMemory;        // Number of 64kb memory blocks
                                    // Added for VBE 2.0
    uint16_t       OemSoftwareRev;     // VBE implementation Software revision
    uint32_t      OemVendorNamePtr;   // Pointer to Vendor Name String
    uint32_t      OemProductNamePtr;  // Pointer to Product Name String
    uint32_t      OemProductRevPtr;   // Pointer to Product Revision String
    uint8_t       Reserved[222];      // Reserved for VBE implementation
                                    // scratch area
    uint8_t       OemData[256];       // Data Area for OEM Strings
}   VESAINFO;

typedef struct {
    // Mandatory information for all VBE revisions
    uint16_t       ModeAttributes;     // mode attributes
    uint8_t       WinAAttributes;     // window A attributes
    uint8_t       WinBAttributes;     // window B attributes
    uint16_t       WinGranularity;     // window granularity
    uint16_t       WinSize;            // window size
    uint16_t       WinASegment;        // window A start segment
    uint16_t       WinBSegment;        // window B start segment
    uint32_t      WinFuncPtr;         // pointer to window function
    uint16_t       BytesPerScanLine;   // bytes per scan line

    // Mandatory information for VBE 1.2 and above
    uint16_t       XResolution;        // horizontal resolution in pixels or chars
    uint16_t       YResolution;        // vertical resolution in pixels or chars
    uint8_t       XCharSize;          // character cell width in pixels
    uint8_t       YCharSize;          // character cell height in pixels
    uint8_t       NumberOfPlanes;     // number of memory planes
    uint8_t       BitsPerPixel;       // bits per pixel
    uint8_t       NumberOfBanks;      // number of banks
    uint8_t       MemoryModel;        // memory model type
    uint8_t       BankSize;           // bank size in KB
    uint8_t       NumberOfImagePages; // number of images
    uint8_t       Reserved;           // reserved for page function

    // Direct Color fields (required for direct/6 and YUV/7 memory models)
    uint8_t       RedMaskSize;        // size of direct color red mask in bits
    uint8_t       RedFieldPosition;   // bit position of lsb of red mask
    uint8_t       GreenMaskSize;      // size of direct color green mask in bits
    uint8_t       GreenFieldPosition; // bit position of lsb of green mask
    uint8_t       BlueMaskSize;       // size of direct color blue mask in bits
    uint8_t       BlueFieldPosition;  // bit position of lsb of blue mask
    uint8_t       RsvdMaskSize;       // size of direct color reserved mask in bits
    uint8_t       RsvdFieldPosition;  // bit position of lsb of reserved mask
    uint8_t       DirectColorModeInfo;// direct color mode attributes

    // Mandatory information for VBE 2.0 and above
    uint32_t      PhysBasePtr;        // physical address for flat frame buffer
    uint32_t      OffScreenMemOffset; // pointer to start of off screen memory
    uint16_t       OffScreenMemSize;   // amount of off screen memory in 1k units
    uint8_t       Reserved2[206];     // remainder of ModeInfoBlock
}   MODEINFO;

#pragma pack()

// flags:
#define LINEAR_MODE     1
#define BANKED_MODE     2

// Realmode call structure:
typedef struct {
    uint32_t      edi, esi, ebp, reserved, ebx, edx, ecx, eax;
    uint16_t       flags, es, ds, fs, gs, ip, cs, sp, ss;
}   RMS;

// Surface information: 
typedef struct {
    int     xsize;                  
    int     ysize;
    int     bpp;                    // bits per pixel (8,15,16,24,32...)
    int     vram;                   // amount of video memory
    int     numpages;               // number of pages available
    int     pagesize;               // size of page in bytes
    int     flags;                  // bit flags
    uint8_t   *lfb;
}   SURFACE;

// functions:
typedef     void (*VESAset_display_start_t)(int x, int y);
typedef     void (*VESAset_bank_t)(int bank);

int         VESAdetect(void);
void        VESAshutdown(void);
void        VESAerror(int err);

SURFACE*    VESAopen_surface(int xsize, int ysize, int bpp, int search);
void        VESAclose_surface(SURFACE *surface);
int         VESAfind_surface(int xsize, int ysize, int bpp, int search);
void        VESAset_mode(int mode);

extern      VESAset_display_start_t VESAset_display_start;
extern      VESAset_bank_t          VESAset_bank;

#endif
