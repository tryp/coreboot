/*
 * This file is part of the coreboot project.
 *
 * Copyright 2014 Google Inc.
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

#ifndef __SOC_NVIDIA_TEGRA132_INCLUDE_SOC_ID_H__
#define __SOC_NVIDIA_TEGRA132_INCLUDE_SOC_ID_H__


#include <arch/io.h>
#include <soc/addressmap.h>

static inline int context_avp(void)
{
	const uint32_t avp_id = 0xaaaaaaaa;
	void * const uptag = (void *)(uintptr_t)TEGRA_PG_UP_BASE;

	return read32(uptag) == avp_id;
}

#endif /* define __SOC_NVIDIA_TEGRA132_INCLUDE_SOC_ID_H__ */
