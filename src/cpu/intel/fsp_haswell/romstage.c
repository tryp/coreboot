/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2012 ChromeOS Authors
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
 * Foundation, Inc.
 */

#include <stdint.h>
#include <string.h>
#include <cbfs.h>
#include <console/console.h>
#include <arch/cpu.h>
#include <cpu/x86/bist.h>
#include <cpu/x86/msr.h>
#include <cpu/x86/mtrr.h>
#include <halt.h>
#include <lib.h>
#include <timestamp.h>
#include <arch/io.h>
#include <arch/stages.h>
#include <device/pci_def.h>
#include <cpu/x86/lapic.h>
#include <cbfs.h>
#include <romstage_handoff.h>
#include <reset.h>
#include <console/usb.h>
#include "haswell.h"
#include "fsp_util.h"
#include "northbridge/intel/fsp_haswell/haswell.h"
#include "northbridge/intel/fsp_haswell/raminit.h"
#include "southbridge/intel/lynxpoint/pch.h"
#include "southbridge/intel/lynxpoint/me.h"

extern char _car_data_start[];
extern char _car_data_end[];

static inline void reset_system(void)
{
	while (1) {
		post_code(0xff);
	}
}

/* The cache-as-ram assembly file calls romstage_main() after setting up
 * cache-as-ram.  romstage_main() will then call the mainboards's
 * mainboard_romstage_entry() function. That function then calls
 * romstage_common() below. The reason for the back and forth is to provide
 * common entry point from cache-as-ram while still allowing for code sharing.
 * Because we can't use global variables the stack is used for allocations --
 * thus the need to call back and forth. */


void asmlinkage romstage_main(uint32_t bist, uint32_t stackbase)
{
	mainboard_romstage_entry(bist, stackbase);
}

void romstage_common(const struct romstage_params *params)
{
	int boot_mode;
	int wake_from_s3;
	size_t car_data_size = &_car_data_end[0] - &_car_data_start[0];


	if (params->bist == 0)
		enable_lapic();

	/* FSP Doesn't seem to zero */
	memset(&_car_data_start[0], 0, car_data_size);

	wake_from_s3 = early_pch_init(params->gpio_map, params->rcba_config);

	/* Halt if there was a built in self test failure */
	report_bist_failure(params->bist);

	/* Perform some early chipset initialization required
	 * before RAM initialization can work
	 */
	haswell_early_initialization(HASWELL_MOBILE);
	printk(BIOS_DEBUG, "Back from haswell_early_initialization()\n");

	if (wake_from_s3) {
#if CONFIG_HAVE_ACPI_RESUME
		printk(BIOS_DEBUG, "Resume from S3 detected.\n");
#else
		printk(BIOS_DEBUG, "Resume from S3 detected, but disabled.\n");
		wake_from_s3 = 0;
#endif
	}

	/* There are hard coded for UEFI compatiable,
	 * refer to boot mode defined in fspbootmode.h. */
	boot_mode = wake_from_s3 ? BOOT_ON_S3_RESUME : BOOT_WITH_FULL_CONFIGURATION;

	/* Prepare USB controller early in S3 resume */
	if (wake_from_s3)
		enable_usb_bar();

	post_code(0x3a);
	params->pei_data->boot_mode = boot_mode;

	report_platform_info();

	FspInitWrapper(CONFIG_RAMTOP,  boot_mode,  find_fsp_nvs_data());

	die("Uh Oh! FSP INIT API should not return here.\n");
}

void romstage_common_continue(void)
{
	post_code(0x3b);

	intel_early_me_status();

	post_code(0x3e);
	quick_ram_check();

	post_code(0x3f);
}

static inline void prepare_for_resume(struct romstage_handoff *handoff)
{
/* Only need to save memory when ramstage isn't relocatable. */
#if !CONFIG_RELOCATABLE_RAMSTAGE
#if CONFIG_HAVE_ACPI_RESUME
	/* Back up the OS-controlled memory where ramstage will be loaded. */
	if (handoff != NULL && handoff->s3_resume) {
		void *src = (void *)CONFIG_RAMBASE;
		void *dest = cbmem_find(CBMEM_ID_RESUME);
		if (dest != NULL)
			memcpy(dest, src, HIGH_MEMORY_SAVE);
	}
#endif
#endif
}

void romstage_after_car(void)
{
	int wake_from_s3;
	struct romstage_handoff *handoff;

	/* Get s3 sleep type and clear it */
	wake_from_s3 = 0;

	if (!wake_from_s3) {
		/* Save data returned from FSP. */
		romstage_after_car_continue();
	} else if (cbmem_initialize()) {
	#if CONFIG_HAVE_ACPI_RESUME
		/* Failed S3 resume, reset to come up cleanly */
		reset_system();
	#endif
	}

	handoff = romstage_handoff_find_or_add();
	if (handoff != NULL)
		handoff->s3_resume = wake_from_s3;
	else
		printk(BIOS_DEBUG, "Romstage handoff structure not added!\n");

	prepare_for_resume(handoff);

	/* Load the ramstage. */
	copy_and_run();
}
