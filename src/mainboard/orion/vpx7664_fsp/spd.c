#include <types.h>
#include <string.h>
#include "fsp_support.h"

/* SPD data for Micron MT41K256M16HA-125 IT:D 4Gb DDR3 x5 */
/* from Micron datasheet:
1600 MT/s t_RCD-t_RP-CP = 11-11-11
(t_RCD=13.75ns t_RP=13.75ns CL=13.75ns)
Organization: 32 Meg x 16 x 8 banks
Refresh Count: 8k
Row Addressing: 32K (A[14:0])
Bank Addressing: 8 (BA[2:0])
Column Addressing: 1K (A[9:0])
Page Size: 2K
*/

static const uint8_t spd_MT41K256M16HA_125[] = {
	0x92,	// 0   Number of Serial PD Bytes Written / SPD Device Size / CRC Coverage 1, 2
	0x11,	// 1   SPD Revision
	0x0b,	// 2   DRAM Device Type
	0x02,	// 3   Module Type

	// 4Gb, 8 banks
	0x04,	// 4   SDRAM Density and Banks

	// 15 row address bits, 10 column address bits  -- 00 011 001
	0x31,	// 5   SDRAM Addressing

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

	// 60 0x0f
	// 61 0x01
	0x00,	// 62  Reference Raw Card Used
	0x00,	// 63  Address Mapping from Edge Connector to DRAM
	0x00,	// 64  ThermalHeatSpreaderSolution

	0x00,	// 117 Module Manufacturer ID Code, Least Significant Byte
	0x00,	// 118 Module Manufacturer ID Code, Most Significant Byte
	0x00,	// 119 Module Manufacturing Location
	0x00,	// 120 Module Manufacturing Date Year
	0x00,	// 121 Module Manufacturing Date creation work week
	0x00,	// 122 Module Serial Number A
	0x00,	// 123 Module Serial Number B
	0x00,	// 124 Module Serial Number C
	0x00,	// 125 Module Serial Number D
	0x00,	// 126 CRC A
	0x00	// 127 CRC B
};


const MEMORY_DOWN_DATA  MemoryDownData = {
  .SlotStatus = {
      {
        MEMORY_DOWN_ONLY,    ///< Slot 0
        MEMORY_ABSENT        ///< Slot 1
      },  ///< Channel 0
      {
        MEMORY_ABSENT,       ///< Slot 0
        MEMORY_ABSENT        ///< Slot 1
      }   ///< Channel 1
  },
  .SpdDataLen = sizeof(spd_MT41K256M16HA_125),
  .SpdDataPtr = {
      {
        (UINT8 *)spd_MT41K256M16HA_125, ///< Slot 0
        (UINT8 *)0           ///< Slot 1
      },  ///< Channel 0
      {
        (UINT8 *)spd_MT41K256M16HA_125,          ///< Slot 0
        (UINT8 *)0           ///< Slot 1
      }   ///< Channel 1
  }
};


