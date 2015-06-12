/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2008-2009 coresystems GmbH
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
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <arch/io.h>
#include <console/console.h>
#include <cpu/x86/smm.h>
#include <southbridge/intel/lynxpoint/nvs.h>
#include <southbridge/intel/lynxpoint/pch.h>
#include <southbridge/intel/lynxpoint/me.h>
#include <northbridge/intel/fsp_haswell/haswell.h>
#include <cpu/intel/fsp_haswell/haswell.h>

void mainboard_post_smi(uint8_t val);

/* vpx7664 POST LED gpios [0..7] */
static uint16_t post_gpios[] = {73, 18, 20, 25, 26, 44, 45, 46};
void mainboard_post_smi(uint8_t val)
{
	int i;

	for(i = 0; i < 8; i++) {
		set_gpio(post_gpios[i], ~((val >> i) & 0x01));
	}
}

int mainboard_io_trap_handler(int smif)
{
	switch (smif) {
	case 0x99:
		printk(BIOS_DEBUG, "Sample\n");
		smm_get_gnvs()->smif = 0;
		break;
	default:
		return 0;
	}

	/* On success, the IO Trap Handler returns 0
	 * On failure, the IO Trap Handler returns a value != 0
	 *
	 * For now, we force the return value to 0 and log all traps to
	 * see what's going on.
	 */
	//gnvs->smif = 0;
	return 1;
}

/*
 * Specific tasks base on sleep type.
 * The IO address is hardcoded as we don't have device path in SMM.
 */
#define SIO_GPIO_BASE_SET4	(0x730 + 3)
#define SIO_GPIO_BLINK_GPIO45	0x25
void mainboard_smi_sleep(u8 slp_typ)
{
	switch (slp_typ) {
	case SLP_TYP_S3:
	case SLP_TYP_S4:
		break;

	case SLP_TYP_S5:
		break;
	}
}

#define APMC_FINALIZE 0xcb

static int mainboard_finalized = 0;

int mainboard_smi_apmc(u8 apmc)
{
	switch (apmc) {
	case APMC_FINALIZE:
		if (mainboard_finalized) {
			printk(BIOS_DEBUG, "SMI#: Already finalized\n");
			return 0;
		}

		intel_me_finalize_smm();
		intel_pch_finalize_smm();
		intel_northbridge_haswell_finalize_smm();
		intel_cpu_haswell_finalize_smm();

		mainboard_finalized = 1;
		break;
	}
	return 0;
}
