/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2013 Sage Electronic Engineering, LLC.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#include <types.h>
#include <string.h>
#include <console/console.h>
#include <cbmem.h>
#include <ip_checksum.h>
#include "haswell.h"
#include "northbridge/intel/fsp_haswell/haswell.h"
#include "northbridge/intel/fsp_haswell/pei_data.h"
#include "fsp_util.h"
#include "fsp_vpd.h"

#ifndef __PRE_RAM__

void fsp_notify (u32 Phase)
{
	EFI_STATUS             Status;

	printk(BIOS_INFO,"FSP API NotifyPhase 0x%x\n", Phase);
	Status = FspNotifyWrapper ((FSP_INFO_HEADER *)fsp_get_fsp_header(), Phase);
	if (Status != 0) {
		printk(BIOS_ERR,"FSP API NotifyPhase failed for phase 0x%x with status: 0x%x\n", Phase, Status);
	}
}

#else

void *find_fsp_nvs_data(void)
{
	struct mrc_data_container *mrc_data;

	if ((mrc_data = find_current_mrc_cache()) == NULL) {
		/* error message printed in find_current_mrc_cache */
		printk(BIOS_DEBUG, "FSP MRC DATA NOT found.\n");
		return NULL;
	}

	printk(BIOS_DEBUG, "FSP MRC DATA at %p (size = 0x%x).\n",
	       mrc_data->mrc_data, mrc_data->mrc_data_size);

  return mrc_data->mrc_data;

}

static void save_fsp_data(void *HobListPtr)
{
	u32 *hob_ptr;
	u32 hob_size;
	struct mrc_data_container *mrc_data;
	int output_len;

	/* MRC DATA HOB */
	hob_ptr = (u32 *)GetFspNvsDataBuffer (HobListPtr, &hob_size);
	if (hob_ptr == NULL) {
		printk(BIOS_DEBUG, "FSP MRC DATA HOB NOT found.\n");
	} else {
		output_len = ALIGN(hob_size, 16);

		/* Save the MRC S3/Fastboot/ADR restore data to cbmem */
		mrc_data = cbmem_add (CBMEM_ID_MRCDATA,
			output_len + sizeof(struct mrc_data_container));

		/* Just return if there was a problem with getting CBMEM */
		if (mrc_data == NULL) return;

		printk(BIOS_DEBUG, "Relocate FSP MRC DATA from %p to %p (%u bytes)\n",
			(void *)hob_ptr, mrc_data, output_len);

		mrc_data->mrc_signature = MRC_DATA_SIGNATURE;
		mrc_data->mrc_data_size = output_len;
		mrc_data->reserved = 0;
		memcpy(mrc_data->mrc_data, (const void *)hob_ptr, hob_size);

		/* Zero the unused space in aligned buffer. */
		if (output_len > hob_size)
			memset((mrc_data->mrc_data + hob_size), 0,
				output_len - hob_size);

		mrc_data->mrc_checksum = compute_ip_checksum(mrc_data->mrc_data,
			mrc_data->mrc_data_size);
	}
}

/*
 * The FSP fsp_initialize function returns to this function.
 * Memory is setup and the stack is set by the FSP.
 */
void bl_main_continue(void *hob_list, SHARED_DATA *shared_data)
{
	uint32_t         *rom_stack;

	romstage_common_continue();

	rom_stack = shared_data->NewStackTop - 1;

	/* FSP Header */
	*rom_stack-- = (UINT32)(shared_data->FspInfoHeader);

	/* Save the hob list pointer */
	*rom_stack-- = (uint32_t)hob_list;

	/* Find available memory top to use */
	*rom_stack-- = GetUsableLowMemTop (hob_list);

	/*
	* FSP retuns to this function instead of main, so we can't return back
	* to the cache_as_ram.inc. Just jump there to finish the ramstage loading.
	*/
	asm volatile (
		"jmp   romstage_main_return;"
	);

	die("Uh Oh! Never here!");
}

void romstage_after_car_continue(void)
{
	void *HobListPtr;

	HobListPtr = (void *) fsp_get_hob_list_ptr();

	cbmem_initialize_empty();

	/* Save data returned from FSP. */
	save_fsp_data(HobListPtr);
}
#endif

uint32_t
fsp_get_fsp_header (
  void
)
{
	uint32_t *stack = (uint32_t *)(CONFIG_RAMTOP);

	return *(stack - 1);
}

uint32_t
fsp_get_hob_list_ptr (
  void
)
{
	uint32_t *stack = (uint32_t *)(CONFIG_RAMTOP);

	return *(stack - 2);
}

uint32_t
fsp_get_low_mem_top (
  void
)
{
	uint32_t *stack = (uint32_t *)(CONFIG_RAMTOP);

	return *(stack - 3);
}
