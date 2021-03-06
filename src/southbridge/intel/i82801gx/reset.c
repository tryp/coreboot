/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2008-2009 coresystems GmbH
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of
 * the License.
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

#include <arch/io.h>
#include <reset.h>

void soft_reset(void)
{
        outb(0x04, 0xcf9);
}

#if 0
void hard_reset(void)
{
	/* Try rebooting through port 0xcf9. */
	outb((1 << 2) | (1 << 1), 0xcf9);
}
#endif

void hard_reset(void)
{
        outb(0x02, 0xcf9);
        outb(0x06, 0xcf9);
}
