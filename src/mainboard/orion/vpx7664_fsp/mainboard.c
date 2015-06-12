/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007-2009 coresystems GmbH
 * Copyright (C) 2011 Google Inc.
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

#include <types.h>
#include <string.h>
#include <smbios.h>
#include <device/device.h>
#include <device/device.h>
#include <device/pci_def.h>
#include <device/pci_ops.h>
#include <console/console.h>
#include <drivers/intel/gma/int15.h>
#include <pc80/mc146818rtc.h>
#include <arch/acpi.h>
#include <arch/io.h>
#include <arch/interrupt.h>
#include <boot/coreboot_tables.h>
#include <cpu/intel/fsp_haswell/haswell.h>
#include <southbridge/intel/lynxpoint/pch.h>


/* vpx7664 POST LED gpios [0..7] */
static uint16_t post_gpios[] = {73, 18, 20, 25, 26, 44, 45, 46};
void mainboard_post(uint8_t val)
{
	int i;

	for(i = 0; i < 8; i++) {
		set_gpio(post_gpios[i], ~((val >> i) & 0x01));
	}
}


// mainboard_enable is executed as first thing after
// enumerate_buses().

static void mainboard_enable(device_t dev)
{
	install_intel_vga_int15_handler(GMA_INT15_ACTIVE_LFP_NONE, GMA_INT15_PANEL_FIT_DEFAULT, GMA_INT15_BOOT_DISPLAY_DEFAULT, 0);
	cmos_init(1); /* force reset of CMOS / RTC */
	cmos_check_update_date();
}

struct chip_operations mainboard_ops = {
	.enable_dev = mainboard_enable,
};

