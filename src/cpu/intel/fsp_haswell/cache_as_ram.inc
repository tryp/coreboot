/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2000,2007 Ronald G. Minnich <rminnich@gmail.com>
 * Copyright (C) 2007-2008 coresystems GmbH
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

#include <cpu/x86/mtrr.h>
#include <cpu/x86/cache.h>
#include <cpu/x86/post_code.h>
#include <cbmem.h>

#define  CFG_CPU_MICROCODE_BASE     CONFIG_CPU_MICROCODE_CBFS_LOC
//#define  CFG_CPU_MICROCODE_SIZE	    0x0000FF80

#define  CFG_CPU_MICROCODE_SIZE	    0xf040
#define  CFG_CACHABLE_ROM_BASE      0xFFFFFFFF - CONFIG_ROM_SIZE + 1
#define  CFG_CACHABLE_ROM_SIZE      CONFIG_ROM_SIZE

	/* Save the BIST result. */
	movl	%eax, %ebp

  /* Check INIT# is asserted by port 0xCF9 */
  mov $0xCF9, %dx
  in  %dx, %al
  cmp $0x4, %al
  jnz cache_as_ram

  /* Issue hard reset since CPU Only Reset not supported */
  mov $0xCF9, %dx
  mov $0x0, %ax
  out %ax, %dx
  mov $0x6, %ax
  out %ax, %dx
  hlt
  jmp .

cache_as_ram:
	post_code(0x20)

	/* Send INIT IPI to all excluding ourself. */
	movl	$0x000C4500, %eax
	movl	$0xFEE00300, %esi
	movl	%eax, (%esi)

	/* All CPUs need to be in Wait for SIPI state */
wait_for_sipi:
	movl	(%esi), %eax
	bt	$12, %eax
	jc	wait_for_sipi

	post_code(0x22)

  #include "fsp_support.inc"

	/* Pass stack base into C function */
	pushl	%ecx

	/* Restore the BIST result. */
	xorl	%eax, %eax	/* Force it 0 */
	pushl	%eax

before_romstage:
	post_code(0x29)
	/* Call romstage.c main function. */
	call	romstage_main

	.global romstage_main_return
romstage_main_return:

	post_code(0x2f)

__main:
	post_code(POST_PREPARE_RAMSTAGE)
	cld			/* Clear direction flag. */
	call	romstage_after_car


