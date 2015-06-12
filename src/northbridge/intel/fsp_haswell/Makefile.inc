#
# This file is part of the coreboot project.
#
# Copyright (C) 2010 Google Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; version 2 of the License.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc.
#

ifeq ($(CONFIG_NORTHBRIDGE_INTEL_FSP_HASWELL),y)

ramstage-y += ram_calc.c
ramstage-y += northbridge.c
ramstage-y += gma.c

ramstage-y += acpi.c
ramstage-y += mrccache.c

romstage-y += ram_calc.c
romstage-y += mrccache.c
romstage-y += early_init.c
romstage-y += report_platform.c
romstage-y += ../../../arch/x86/lib/walkcbfs.S

smm-$(CONFIG_HAVE_SMI_HANDLER) += finalize.c

endif