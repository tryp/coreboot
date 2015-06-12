ramstage-y += haswell_init.c
ramstage-y += tsc_freq.c
romstage-y += romstage.c
romstage-y += tsc_freq.c
romstage-y += fsp_util.c
romstage-y += fsp_support.c
romstage-y += fsp_configs.c

ramstage-y += acpi.c
ramstage-$(CONFIG_HAVE_SMI_HANDLER) += smmrelocate.c
ramstage-$(CONFIG_MONOTONIC_TIMER_MSR) += monotonic_timer.c
ramstage-y += fsp_util.c
ramstage-y += fsp_support.c

cpu_microcode-$(CONFIG_CPU_MICROCODE_CBFS_GENERATE)  += microcode_blob.c

smm-$(CONFIG_HAVE_SMI_HANDLER) += finalize.c
smm-$(CONFIG_HAVE_SMI_HANDLER) += tsc_freq.c
smm-$(CONFIG_MONOTONIC_TIMER_MSR) += monotonic_timer.c

cpu_incs += $(src)/cpu/intel/fsp_haswell/cache_as_ram.inc

# We don't ship that, but booting without it is bound to fail
cbfs-files-$(CONFIG_HAVE_FSP) += fsp.bin
fsp.bin-file := $(call strip_quotes,$(CONFIG_FSP_FILE))
fsp.bin-position := $(CONFIG_FSP_LOCATION)
fsp.bin-type := 0xab

ifneq ($(CONFIG_MICROCODE_INCLUDE_PATH),)
ifneq ($(wildcard $(shell readlink -f "$(top)/$(CONFIG_MICROCODE_INCLUDE_PATH)")),)
CPPFLAGS_common += -I$(CONFIG_MICROCODE_INCLUDE_PATH)
endif
endif

subdirs-y += ../../x86/tsc
subdirs-y += ../../x86/mtrr
subdirs-y += ../../x86/lapic
subdirs-y += ../../x86/cache
subdirs-y += ../../x86/smm
subdirs-y += ../microcode
subdirs-y += ../turbo
