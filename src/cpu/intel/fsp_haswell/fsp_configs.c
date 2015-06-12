/** @file

Copyright (C) 2013, Intel Corporation

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.
* Neither the name of Intel Corporation nor the names of its contributors may
  be used to endorse or promote products derived from this software without
  specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
  THE POSSIBILITY OF SUCH DAMAGE.

**/

#include <types.h>
#include <string.h>
#include "fsp_support.h"

#define  VERB_TABLE_INIT_EXAMPLE   0
#define  MEMORY_DOWN_INIT_EXAMPLE  1

#if MEMORY_DOWN_INIT_EXAMPLE
const UINT8 ExampleSpd[] = {
	0x92,	// 0   Number of Serial PD Bytes Written / SPD Device Size / CRC Coverage 1, 2
	0x11,	// 1   SPD Revision
	0x0b,	// 2   DRAM Device Type
	0x02,	// 3   Module Type

	// 4Gb, 8 banks
	0x04,	// 4   SDRAM Density and Banks

	// 15 row address bits, 10 column address bits  --  0001 1001
	0x19,	// 5   SDRAM Addressing

	// 1.35V and 1.5V operable
	0x02,	// 6   Module Nominal Voltage

	// 1 rank, 16 bits -- 00 000 010
	0x02,	// 7   Module Organization

	// 8 bit extension, 64 bit primary -- 00 001 011
	0x0b,	// 8   Module Memory Bus Width

	// fine timebase = 1ps -- 0001 0001
	0x11,	// 9   Fine Timebase (FTB) Dividend / Divisor

	// medium timebase 1/8 = 0.125 ns
	0x01,	// 10  Medium Timebase (MTB) Dividend
	0x08,	// 11  Medium Timebase (MTB) Divisor

	// 1.25ns = .125 * 10 = 0x0a
	0x0a,	// 12  SDRAM Minimum Cycle Time (tCKmin)
	0x00,	// 13  Reserved0

	// CAS Latencies 5, 6, 7, 8, 9, 10, 11 = 0xfe, 0x00
	0xfe,	// 14  CAS Latencies Supported, Least Significant Byte
	0x00,	// 15  CAS Latencies Supported, Most Significant Byte

	// tAAmin = 13.75ns = .125 * 110 = 0x6e
	0x6e,	// 16  Minimum CAS Latency Time (tAAmin)

	// tWRmin = 15ns = .125 * 120 = 0x78
	0x78,	// 17  Minimum Write Recovery Time (tWRmin)

	// tRCDmin = 13.75ns
	0x6e,	// 18  Minimum RAS# to CAS# Delay Time (tRCDmin)

	// tRRDmin = 7.5ns = .125 * 60 = 0x3c
	0x3c,	// 19  Minimum Row Active to Row Active Delay Time (tRRDmin)

	// tRPmin = 13.75ns
	0x6e,	// 20  Minimum Row Precharge Delay Time (tRPmin)

	// tRAS = 35ns = .125 * 280 = 0x118
	// tRC = 48.75 = .125 * 390 = 0x186
	0x11,	// 21  Upper Nibbles for tRAS and tRC
	0x18,	// 22  Minimum Active to Precharge Delay Time (tRASmin), Least Significant Byte
	0x86,	// 23  Minimum Active to Active/Refresh Delay Time (tRCmin), Least Significant Byte

	// tRFCmin = 260ns = .125 * 2080 = 0x820
	0x20,	// 24  Minimum Refresh Recovery Delay Time (tRFCmin), Least Significant Byte
	0x08,	// 25  Minimum Refresh Recovery Delay Time (tRFCmin), Most Significant Byte

	// tWTRmin = 7.5ns = .125 * 60 = 0x3c
	0x3c,	// 26  Minimum Internal Write to Read Command Delay Time (tWTRmin)

	// tRTPmin = 7.5ns
	0x3c,	// 27  Minimum Internal Read to Precharge Command Delay Time (tRTPmin)

	// tFAW = 40ns = .125 * 320 = 0x140
	0x01,	// 28  Upper Nibble for tFAW
	0x40,	// 29  Minimum Four Activate Window Delay Time (tFAWmin)

	// supports DLL-off and RZQ/7 and RZQ/6
	0x83,	// 30  SDRAM Optional Features

	// supports ASR, ext temp refresh is 2x rate, ext temp range
	0x05,	// 31  SDRAMThermalAndRefreshOptions
	0x00,	// 32  ModuleThermalSensor
	0x00,	// 33  SDRAM Device Type
	0x00,	// 34  Fine Offset for SDRAM Minimum Cycle Time (tCKmin)
	0x00,	// 35  Fine Offset for Minimum CAS Latency Time (tAAmin)
	0x00,	// 36  Fine Offset for Minimum RAS# to CAS# Delay Time (tRCDmin)
	0x00,	// 37  Fine Offset for Minimum Row Precharge Delay Time (tRPmin)
	0x00,	// 38  Fine Offset for Minimum Active to Active/Refresh Delay Time (tRCmin)

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  ///< 40 - 49
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  ///< 50 - 59

	0x0F, 0x11, ///< 60 - 61
	0x00,	// 62  Reference Raw Card Used
	0x00,	// 63  Address Mapping from Edge Connector to DRAM
	0x00,	// 64  ThermalHeatSpreaderSolution

	0, 0, 0, 0, 0,                        ///< 65 - 69
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 70 - 79
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 80 - 89
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 90 - 99
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,         ///< 100 - 109
	0, 0, 0, 0, 0, 0, 0,                  ///< 110 - 116

	0x00,	// 117 Module Manufacturer ID Code, Least Significant Byte
	0x00,	// 118 Module Manufacturer ID Code, Most Significant Byte
	0x00,	// 119 Module Manufacturing Location
	0x00,	// 120 Module Manufacturing Date Year
	0x00,	// 121 Module Manufacturing Date creation work week
	0x00,	// 122 Module Serial Number A
	0x00,	// 123 Module Serial Number B
	0x00,	// 124 Module Serial Number C
	0x00,	// 125 Module Serial Number D
	0x16,	// 126 CRC A
	0x64	// 127 CRC B
};

const MEMORY_DOWN_DATA  MemoryDownData = {
  .SlotStatus = {
      {
        MEMORY_DOWN_ONLY,    ///< Slot 0
        MEMORY_ABSENT        ///< Slot 1
      },  ///< Channel 0
      {
        MEMORY_DOWN_ONLY,    ///< Slot 0
        MEMORY_ABSENT        ///< Slot 1
      }   ///< Channel 1
  },
  .SpdDataLen = sizeof(ExampleSpd),
  .SpdDataPtr = {
      {
        (UINT8 *)ExampleSpd, ///< Slot 0
        (UINT8 *)0           ///< Slot 1
      },  ///< Channel 0
      {
        (UINT8 *)ExampleSpd, ///< Slot 0
        (UINT8 *)0           ///< Slot 1
      }   ///< Channel 1
  }
};

#endif

#if VERB_TABLE_INIT_EXAMPLE
const UINT32 AzaliaTableData[] =  {
    //===================================================================================================
    //
    //                               Realtek Semiconductor Corp.
    //
    //===================================================================================================

    //Realtek High Definition Audio Configuration
    //Realtek HD Audio Codec : ALC892
    //PCI PnP ID : PCI\VEN_0000&DEV_0000&SUBSYS_00000000
    //HDA Codec PnP ID : HDAUDIO\FUNC_01&VEN_10EC&DEV_0892&SUBSYS_00000000
    //The number of verb command block : 16

    //    NID 0x11 : 0x411110F0
    //    NID 0x12 : 0x411111F0
    //    NID 0x14 : 0x0101F030
    //    NID 0x15 : 0x01011031
    //    NID 0x16 : 0x01016032
    //    NID 0x17 : 0x41012033
    //    NID 0x18 : 0x01A19850
    //    NID 0x19 : 0x42A19C80
    //    NID 0x1A : 0x01813051
    //    NID 0x1B : 0x42214C40
    //    NID 0x1C : 0x5993105F
    //    NID 0x1D : 0x40000100
    //    NID 0x1E : 0x01442070
    //    NID 0x1F : 0x41C46060


    //===== HDA Codec Subsystem ID Verb-table =====
    //HDA Codec Subsystem ID  : 0x80867270
    0x00172070,
    0x00172172,
    0x00172286,
    0x00172380,


    //===== Pin Widget Verb-table =====
    //Widget node 0x01 :
    0x0017FF00,
    0x0017FF00,
    0x0017FF00,
    0x0017FF00,
    //Pin widget 0x11 S/PDIF-OUT2
    0x01171CF0,
    0x01171D10,
    0x01171E11,
    0x01171F41,
    //Pin widget 0x12 DMIC
    0x01271CF0,
    0x01271D11,
    0x01271E11,
    0x01271F41,
    //Pin widget 0x14 FRONT (Port-D)
    0x01471C30,
    0x01471DF0,
    0x01471E01,
    0x01471F01,
    //Pin widget 0x15 SURR (Port-A)
    0x01571C31,
    0x01571D10,
    0x01571E01,
    0x01571F01,
    //Pin widget 0x16 CEN/LFE (Port-G)
    0x01671C32,
    0x01671D60,
    0x01671E01,
    0x01671F01,
    //Pin widget 0x17 SIDESURR (Port-H)
    0x01771C33,
    0x01771D20,
    0x01771E01,
    0x01771F41,
    //Pin widget 0x18 MIC1 (Port-B)
    0x01871C50,
    0x01871D98,
    0x01871EA1,
    0x01871F01,
    //Pin widget 0x19 MIC2 (Port-F)
    0x01971C80,
    0x01971D9C,
    0x01971EA1,
    0x01971F42,
    //Pin widget 0x1A LINE1 (Port-C)
    0x01A71C51,
    0x01A71D30,
    0x01A71E81,
    0x01A71F01,
    //Pin widget 0x1B LINE2 (Port-E)
    0x01B71C40,
    0x01B71D4C,
    0x01B71E21,
    0x01B71F42,
    //Pin widget 0x1C CD-IN
    0x01C71C5F,
    0x01C71D10,
    0x01C71E93,
    0x01C71F59,
    //Pin widget 0x1D BEEP-IN
    0x01D71C00,
    0x01D71D01,
    0x01D71E00,
    0x01D71F40,
    //Pin widget 0x1E S/PDIF-OUT
    0x01E71C70,
    0x01E71D20,
    0x01E71E44,
    0x01E71F02,
};

const AUDIO_AZALIA_VERB_TABLE AzaliaVerbTable = {
  //
  //  VerbTable: (RealTek ALC892)
  //  Revision ID = 0xff
  //  Codec Verb Table For Azalia on Lava Canyon
  //  Codec Address: CAd value (0/1/2)
  //  Codec Vendor: 0x10EC0892
  //
    {
    0x10EC,     // Vendor ID
    0x0892,     // Device ID
    0xFF,       // Revision ID (any)
    0xFF,       // SDI number (any)
    15 * 4,     // Data size in DWORDs
    0x00000000  // Reserved
    },
    (UINT32 *)AzaliaTableData
};

const UINT32 SaAudioTableData[] = {
  ///
  /// Audio Verb Table - 0x80862807
  ///
  /// Pin Widget 5 - PORT B
  ///
  0x00571C10,
  0x00571D00,
  0x00571E56,
  0x00571F18,
  ///
  /// Pin Widget 6 - PORT C
  ///
  0x00671C20,
  0x00671D00,
  0x00671E56,
  0x00671F19,

};

const AUDIO_SA_VERB_TABLE SaVerbTable = {
  ///
  ///  VerbTable:
  ///  Revision ID = 0xFF
  ///  Codec Vendor: 0x80862807
  ///
    {
    0x80862807, ///< Vendor ID/Device ID
    0x0000,     ///< SubSystem ID
    0xFF,       ///< Revision ID
    0x02,       ///< Front panel support (1=yes, 2=no)
    0x0002,     ///< Number of Rear Jacks
    0x0000,     ///< Number of Front Jacks
    },
    (UINT32 *)SaAudioTableData
};
#endif

#define IGD_PREALLOC_0MB 0
#define IGD_PREALLOC_32MB 1
#define IGD_PREALLOC_64MB 2
#define IGD_PREALLOC_128MB 3
#define IGD_PREALLOC_256MB 4
#define IGD_PREALLOC_512MB 5

#define PCD_APERATURE_128MB 0
#define PCD_APERATURE_256MB 1
#define PCD_APERATURE_512MB 2

#define PCD_MMIO_SIZE_1_0GB 0
#define PCD_MMIO_SIZE_1_5GB 1
#define PCD_MMIO_SIZE_2_0GB 2

#define PCD_PRIMARY_DISPLAY_IGFX 0
#define PCD_PRIMARY_DISPLAY_PEG 1
#define PCD_PRIMARY_DISPLAY_PCI 2
#define PCD_PRIMARY_DISPLAY_AUTO 3

#define BT_CBR_MOBILE 0
#define BT_CRB_DESKTOP 1
#define BT_SV_MOBILE 2
#define BT_SV_DESKTOP 3
#define BT_SV_SERVER 4
#define BT_ULT 5
#define BT_CRB_EMBEDDED 6
#define BT_UNKNOWN 7


/**
  This function overrides the default configurations in the UPD data region.

  @param   UpdDataRgn   A pointer to the UPD_DATA_REGION data strcture.

  @return  None
**/
VOID
UpdateFspUpdConfigs (
  UPD_DATA_REGION        *FspUpdRgn
)
{
#if MEMORY_DOWN_INIT_EXAMPLE
  // Examples on how to initialize the pointers in UPD region.
  FspUpdRgn->PcdMemoryDownSpdPtr = (MEMORY_DOWN_DATA *)&MemoryDownData;
  FspUpdRgn->SerialDebugPortAddress = 0x3f8;
  FspUpdRgn->SerialDebugPortType = 1;
  FspUpdRgn->PcdMrcDebugMsg = 0;
  FspUpdRgn->PcdEnableRmt = 0;
#endif

#if VERB_TABLE_INIT_EXAMPLE
  FspUpdRgn->SaHdaVerbTablePtr  = (AUDIO_SA_VERB_TABLE *)&SaVerbTable;
  FspUpdRgn->AzaliaVerbTablePtr = (AUDIO_AZALIA_VERB_TABLE *)&AzaliaVerbTable;
#endif

	/* For VPX7664, use GPIO29 as PEG link partner reset line
	 * Note that PcdPegResetGpio must be assigned a valid GPIO
	 * number [0-73] either here or in the binary-edited
	 * defaults. If PcdResetGpio is not a valid GPIO, then
	 * the FSP will attempt a null-pointer dereference during
	 * PCIe Gen3 link training. */
	FspUpdRgn->PcdPegResetGpio = 29;
	FspUpdRgn->PcdPegResetGpioActive = 0;

	/* cjd: Explicit Graphics settings */
	FspUpdRgn->PcdInternalGfx = 1; /* Enable (1) or Disable (0) */
	FspUpdRgn->PcdPrimaryDisplay = PCD_PRIMARY_DISPLAY_IGFX;
	FspUpdRgn->PcdApertureSize = PCD_APERATURE_512MB;
	FspUpdRgn->PcdIgdDvmt50PreAlloc = IGD_PREALLOC_32MB;
	FspUpdRgn->PcdMmioSize = PCD_MMIO_SIZE_2_0GB;

	FspUpdRgn->PcdUserCrbBoardType = BT_CBR_MOBILE;
}

