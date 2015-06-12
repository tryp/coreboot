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

#ifndef FSP_UTIL_H
#define FSP_UTIL_H

#include "fsp_types.h"
#include "fsp_fv.h"
#include "fsp_ffs.h"
#include "fsp_api.h"
#include "fsp_hob.h"
#include "fsp_support.h"
#include "fsp_platform.h"
#include "fsp_infoheader.h"
#include "fsp_bootmode.h"

void     *find_fsp_nvs_data(void);
void      fsp_notify(u32 Phase);
void      romstage_main_continue(EFI_STATUS Status, VOID *HobListPtr);
uint32_t  fsp_get_low_mem_top  (void);
uint32_t  fsp_get_hob_list_ptr (void);
uint32_t  fsp_get_fsp_header   (void);

/* Additional HOB types not included in the FSP:
 * #define EFI_HOB_TYPE_HANDOFF 0x0001
 * #define EFI_HOB_TYPE_MEMORY_ALLOCATION 0x0002
 * #define EFI_HOB_TYPE_RESOURCE_DESCRIPTOR 0x0003
 * #define EFI_HOB_TYPE_GUID_EXTENSION 0x0004
 * #define EFI_HOB_TYPE_FV 0x0005
 * #define EFI_HOB_TYPE_CPU 0x0006
 * #define EFI_HOB_TYPE_MEMORY_POOL 0x0007
 * #define EFI_HOB_TYPE_CV 0x0008
 * #define EFI_HOB_TYPE_UNUSED 0xFFFE
 * #define EFI_HOB_TYPE_END_OF_HOB_LIST 0xffff
 */
#define EFI_HOB_TYPE_HANDOFF		0x0001
#define EFI_HOB_TYPE_MEMORY_POOL	0x0007

#define GET_HOB_MEM_TYPE(HobStart) \
  ((*(EFI_HOB_MEMORY_ALLOCATION **)&(HobStart))->AllocDescriptor.MemoryType)

#define GET_HOB_MEM_NAME(HobStart) \
  ((*(EFI_HOB_MEMORY_ALLOCATION **)&(HobStart))->AllocDescriptor.Name)

#define GET_HOB_MEM_ADDR(HobStart) \
  ((*(EFI_HOB_MEMORY_ALLOCATION **)&(HobStart))->AllocDescriptor.MemoryBaseAddress)

#define GET_HOB_MEM_LENGTH(HobStart) \
  ((*(EFI_HOB_MEMORY_ALLOCATION **)&(HobStart))->AllocDescriptor.MemoryLength)

#define GET_HOB_RES_TYPE(HobStart) \
  ((*(EFI_HOB_RESOURCE_DESCRIPTOR **)&(HobStart))->ResourceType)

#define GET_HOB_RES_ATTR(HobStart) \
  ((*(EFI_HOB_RESOURCE_DESCRIPTOR **)&(HobStart))->ResourceAttribute)

#define GET_HOB_RES_ADDR(HobStart) \
  ((*(EFI_HOB_RESOURCE_DESCRIPTOR **)&(HobStart))->PhysicalStart)

#define GET_HOB_RES_LENGTH(HobStart) \
  ((*(EFI_HOB_RESOURCE_DESCRIPTOR **)&(HobStart))->ResourceLength)

#define GET_HOB_RES_NAME(HobStart) \
  ((*(EFI_HOB_RESOURCE_DESCRIPTOR **)&(HobStart))->Owner)

#endif				/* FSP_UTIL_H */
