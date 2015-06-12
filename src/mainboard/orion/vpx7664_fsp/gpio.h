/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2011 The Chromium OS Authors. All rights reserved.
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

#ifndef VPX7664_GPIO_H
#define VPX7664_GPIO_H

#include "southbridge/intel/lynxpoint/gpio.h"

const struct pch_gpio_set1 pch_gpio_set1_mode = {
	.gpio0 = GPIO_MODE_GPIO,    /* TP_PCH_GP0, NOT USED */
	.gpio1 = GPIO_MODE_GPIO,    /* TP_PCH_GP1, NOT USED */
	.gpio2 = GPIO_MODE_GPIO,    /* INT_PIRQE_N, NOT USED */
	.gpio3 = GPIO_MODE_GPIO,    /* INT_PIRQF_N, NOT USED */
	.gpio4 = GPIO_MODE_GPIO,    /* INT_PIRQG_N, NOT USED */
	.gpio5 = GPIO_MODE_GPIO,    /* INT_PIRQH_N, NOT USED */
	.gpio6 = GPIO_MODE_GPIO,    /* TP_PCH_GP6, NOT USED */
	.gpio7 = GPIO_MODE_GPIO,    /* TP_PCH_GP7, NOT USED */
	.gpio8 = GPIO_MODE_GPIO, /* vpx7664 XMC MPRESENT_N */
	.gpio9  = GPIO_MODE_GPIO, /* NOT USED */
	.gpio10 = GPIO_MODE_GPIO, /* USB2_OC6_12_13_N */
	.gpio11 = GPIO_MODE_NATIVE,   /* SMBALERT_N */
	.gpio12 = GPIO_MODE_GPIO,   /* PCH_LANPHY_EN */
	.gpio13 = GPIO_MODE_GPIO, /* NOT USED */
	.gpio14 = GPIO_MODE_GPIO,   /* NOT USED */
	.gpio15 = GPIO_MODE_GPIO,   /* PCH_GP15_BT_KILL_N */
	.gpio16 = GPIO_MODE_GPIO, /* SATA_DET4_N */
	.gpio17 = GPIO_MODE_GPIO,   /* TP_PCH_GP17 */
	.gpio18 = GPIO_MODE_GPIO, /* vpx7764 D20 [1] */
	.gpio19 = GPIO_MODE_GPIO,   /* BBS_BIT0 - STRAP */
	.gpio20 = GPIO_MODE_GPIO, /* vpx7764 D19 [2] */
	.gpio21 = GPIO_MODE_GPIO,   /* NOT USED */
	.gpio22 = GPIO_MODE_GPIO,   /* PCH_GP22_BIOS_RCVRY */
	.gpio23 = GPIO_MODE_GPIO, /* TP_PCH_GP23, NOT USED */
	.gpio24 = GPIO_MODE_GPIO,   /* vpx7664 LPT_GPIO24 */
	.gpio25 = GPIO_MODE_GPIO, /* vpx7764 D18 [3] */
	.gpio26 = GPIO_MODE_GPIO, /* vpx7764 D17 [4] */
	.gpio27 = GPIO_MODE_GPIO,   /* vpx7664 LPT_GPIO27 */
	.gpio28 = GPIO_MODE_GPIO,   /* vpx7664 LPT_GPIO28 */
	.gpio29 = GPIO_MODE_NATIVE, /* PCH_SLP_WLAN_N */
	.gpio30 = GPIO_MODE_NATIVE, /* PCH_SUSWARN_N */
	.gpio31 = GPIO_MODE_GPIO, /* AC_PRESENT */
};

const struct pch_gpio_set1 pch_gpio_set1_direction = {
	.gpio0 = GPIO_DIR_INPUT,
	.gpio1 = GPIO_DIR_INPUT,
	.gpio2 = GPIO_DIR_INPUT,
	.gpio4 = GPIO_DIR_INPUT,
	.gpio5 = GPIO_DIR_INPUT,
	.gpio6 = GPIO_DIR_INPUT,
	.gpio7 = GPIO_DIR_INPUT,
	.gpio8 = GPIO_DIR_INPUT,
	.gpio9 = GPIO_DIR_INPUT,
	.gpio10 = GPIO_DIR_INPUT,
	/* .gpio11 NATIVE */
	.gpio12 = GPIO_DIR_INPUT,
	.gpio13 = GPIO_DIR_INPUT,
	.gpio14 = GPIO_DIR_INPUT,
	.gpio15 = GPIO_DIR_INPUT,
	.gpio16 = GPIO_DIR_INPUT,
	.gpio17 = GPIO_DIR_INPUT,
	.gpio18 = GPIO_DIR_OUTPUT, /* vpx7764 D20 [1] */
	.gpio19 = GPIO_DIR_INPUT,
	.gpio20 = GPIO_DIR_OUTPUT,  /* vpx7764 D19 [2] */
	.gpio21 = GPIO_DIR_INPUT,
	.gpio22 = GPIO_DIR_INPUT,
	.gpio23 = GPIO_DIR_INPUT,
	.gpio24 = GPIO_DIR_INPUT,
	.gpio25 = GPIO_DIR_OUTPUT, /* vpx7764 D18 [3] */
	.gpio26 = GPIO_DIR_OUTPUT, /* vpx7764 D17 [4] */
	.gpio27 = GPIO_DIR_INPUT,
	.gpio28 = GPIO_DIR_INPUT,
	/* .gpio29  NATIVE */
	/* .gpio30  NATIVE */
	.gpio31 = GPIO_DIR_INPUT,
};

const struct pch_gpio_set1 pch_gpio_set1_level = {
};

const struct pch_gpio_set1 pch_gpio_set1_reset = {
};

const struct pch_gpio_set1 pch_gpio_set1_invert = {
};

const struct pch_gpio_set1 pch_gpio_set1_blink = {
};

const struct pch_gpio_set2 pch_gpio_set2_mode = {
	.gpio32 = GPIO_MODE_GPIO, /* Always GPIO on desktop. Mobile Native. PCH_CKRUN_N */
	.gpio33 = GPIO_MODE_GPIO, /* TP_PCH_GP33, NOT USED */
	.gpio34 = GPIO_MODE_GPIO,   /* vpx7664 LPT_GPIO34 */
	.gpio35 = GPIO_MODE_GPIO,   /* vpx7664 LPT_GPIO35 */
	.gpio36 = GPIO_MODE_GPIO, /* TP_PCH_GP36, NOT USED */
	.gpio37 = GPIO_MODE_GPIO, /* PCH_GP37 */
	.gpio38 = GPIO_MODE_GPIO,   /* vpx7664 DDR_SPD_0 */
	.gpio39 = GPIO_MODE_GPIO,   /* vpx7664 DDR_SPD_1 */
	.gpio40 = GPIO_MODE_NATIVE, /* USB3_OC0_1_N */
	.gpio41 = GPIO_MODE_GPIO,   /* NOT USED */
	.gpio42 = GPIO_MODE_GPIO, /* USB2_OC3_6_7_N */
	.gpio43 = GPIO_MODE_GPIO, /* NOT USED */
	.gpio44 = GPIO_MODE_GPIO, /* vpx7664 D16 [5] */
	.gpio45 = GPIO_MODE_GPIO, /* vpx7664 D13 [6] */
	.gpio46 = GPIO_MODE_GPIO,   /* vpx7664 D15 [7] */
	.gpio47 = GPIO_MODE_GPIO, /* SLOT_PEGA_CLKREQ_N */
	.gpio48 = GPIO_MODE_GPIO,   /* vpx7664 DDR_SPD_2 */
	.gpio49 = GPIO_MODE_GPIO,   /* TP_PCH_GP49, NOT USED */
	.gpio50 = GPIO_MODE_GPIO, /* vpx7664 PM_ID[0] */
	.gpio51 = GPIO_MODE_GPIO,   /* BBS_BIT1 Strap */
	.gpio52 = GPIO_MODE_GPIO, /* vpx7664 PM_ID[1] */
	.gpio53 = GPIO_MODE_GPIO, /* NOT USED */
	.gpio54 = GPIO_MODE_GPIO, /* vpx7664 PM_ID[2] */
	.gpio55 = GPIO_MODE_GPIO,   /* Internal Pull-up */
	.gpio56 = GPIO_MODE_GPIO, /* MC_PEGB_CKREQ_N */
	.gpio57 = GPIO_MODE_GPIO,   /* vpx7664 LPT_GPIO57 */
	.gpio58 = GPIO_MODE_NATIVE, /* SML1_CLK */
	.gpio59 = GPIO_MODE_GPIO, /* USB3_OC0_0_N */
	.gpio60 = GPIO_MODE_GPIO,   /* DRAMRST_CNTRL_PCH */
	.gpio61 = GPIO_MODE_GPIO, /* PM_SUS_STAT_N */
	.gpio62 = GPIO_MODE_GPIO, /* Internal Pull-up */
	.gpio63 = GPIO_MODE_NATIVE, /* SLP_S5_R_N */
};

const struct pch_gpio_set2 pch_gpio_set2_direction = {
	.gpio32 = GPIO_DIR_INPUT,
	.gpio33 = GPIO_DIR_INPUT,
	.gpio34 = GPIO_DIR_INPUT,
	.gpio35 = GPIO_DIR_INPUT,
	.gpio36 = GPIO_DIR_INPUT,
	.gpio37 = GPIO_DIR_INPUT,
	.gpio38 = GPIO_DIR_INPUT,
	.gpio39 = GPIO_DIR_INPUT,
	/* .gpio40  NATIVE */
	.gpio41 = GPIO_DIR_INPUT,
	.gpio42 = GPIO_DIR_INPUT,
	.gpio43 = GPIO_DIR_INPUT,
	.gpio44 = GPIO_DIR_OUTPUT, /* vpx7664 D16 [5] */
	.gpio45 = GPIO_DIR_OUTPUT, /* vpx7664 D15 [6] */
	.gpio46 = GPIO_DIR_OUTPUT, /* vpx7664 D13 [7] */
	.gpio47 = GPIO_DIR_INPUT,
	.gpio48 = GPIO_DIR_INPUT,
	.gpio49 = GPIO_DIR_INPUT,
	.gpio50 = GPIO_DIR_INPUT,
	.gpio51 = GPIO_DIR_INPUT,
	.gpio52 = GPIO_DIR_INPUT,
	.gpio53 = GPIO_DIR_INPUT,
	.gpio54 = GPIO_DIR_INPUT,
	.gpio55 = GPIO_DIR_INPUT,
	.gpio56 = GPIO_DIR_INPUT,
	.gpio57 = GPIO_DIR_INPUT,
	/* .gpio58  NATIVE */
	.gpio59 = GPIO_DIR_INPUT,
	.gpio60 = GPIO_DIR_INPUT,
	.gpio61 = GPIO_DIR_INPUT,
	.gpio62 = GPIO_DIR_INPUT,
	/* .gpio63  NATIVE */
};

const struct pch_gpio_set2 pch_gpio_set2_level = {
};

const struct pch_gpio_set2 pch_gpio_set2_reset = {
};

const struct pch_gpio_set3 pch_gpio_set3_mode = {
	.gpio64 = GPIO_MODE_GPIO, /* NOT USED */
	.gpio65 = GPIO_MODE_GPIO, /* NOT USED */
	.gpio66 = GPIO_MODE_GPIO,   /* CK_FLEX2 */
	.gpio67 = GPIO_MODE_GPIO,   /* NOT USED */
	.gpio68 = GPIO_MODE_GPIO,   /* vpx7664 BOARD_ID[3] */
	.gpio69 = GPIO_MODE_GPIO,   /* vpx7664 BOARD_ID[2] */
	.gpio70 = GPIO_MODE_GPIO,   /* vpx7664 BOARD_ID[1] */
	.gpio71 = GPIO_MODE_GPIO,   /* vpx7664 BOARD_ID[0] */
	.gpio72 = GPIO_MODE_GPIO, /* PCH_BATLOW_N */
	.gpio73 = GPIO_MODE_GPIO, /* vpx7764 D21 [0] */
	.gpio74 = GPIO_MODE_GPIO, /* PCH_HOT_N */
	.gpio75 = GPIO_MODE_NATIVE, /* SML1_DAT */
};

const struct pch_gpio_set3 pch_gpio_set3_direction = {
	.gpio64 = GPIO_DIR_INPUT,
	.gpio65 = GPIO_DIR_INPUT,
	.gpio66 = GPIO_DIR_INPUT,
	.gpio67 = GPIO_DIR_INPUT,
	.gpio68 = GPIO_DIR_INPUT,
	.gpio69 = GPIO_DIR_INPUT,
	.gpio70 = GPIO_DIR_INPUT,
	.gpio71 = GPIO_DIR_INPUT,
	.gpio72 = GPIO_DIR_INPUT,
	.gpio73 = GPIO_DIR_OUTPUT, /* vpx7764 D10 [0] */
	.gpio74 = GPIO_DIR_INPUT,
	/* .gpio75  NATIVE */
};

const struct pch_gpio_set3 pch_gpio_set3_level = {
};

const struct pch_gpio_map mainboard_gpio_map = {
	.set1 = {
		.mode      = &pch_gpio_set1_mode,
		.direction = &pch_gpio_set1_direction,
		.level     = &pch_gpio_set1_level,
		.reset     = &pch_gpio_set1_reset,
		.invert    = &pch_gpio_set1_invert,
		.blink     = &pch_gpio_set1_blink,
	},
	.set2 = {
		.mode      = &pch_gpio_set2_mode,
		.direction = &pch_gpio_set2_direction,
		.level     = &pch_gpio_set2_level,
		.reset     = &pch_gpio_set2_reset,
	},
	.set3 = {
		.mode      = &pch_gpio_set3_mode,
		.direction = &pch_gpio_set3_direction,
		.level     = &pch_gpio_set3_level,
	},
};

#endif
