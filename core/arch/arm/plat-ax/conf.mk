
include core/arch/arm/cpu/cortex-armv8-0.mk

CFG_ARM64_core ?= y
CFG_CRYPTO_WITH_CE ?= y
default-user-ta-target ?= ta_arm64
CFG_TEE_CORE_LOG_LEVEL ?= 2
CFG_ARM32_ta_arm32 ?= n
CFG_TEE_BENCHMARK ?= n
CFG_USER_TA_TARGETS ?= ta_arm64

$(call force,CFG_WITH_ARM_TRUSTED_FW,y)
$(call force,CFG_GIC,y)
$(call force,CFG_ARM_GICV3,n)
$(call force,CFG_16550_UART,y)
$(call force,CFG_SECURE_TIME_SOURCE_CNTPCT,y)
$(call force,CFG_DT,y)
$(call force,CFG_CORE_DYN_SHM,n)
$(call force,CFG_LPAE_ADDR_SPACE_BITS,40)
$(call force,CFG_CORE_ARM64_PA_BITS,40)
$(call force,CFG_CORE_LARGE_PHYS_ADDR,y)
$(call force,CFG_INSECURE,n)

# Disable core ASLR for two reasons:
# 1. There is no source for ALSR seed, as ATF does not provide a
#    DTB to OP-TEE. Hardware RNG is also not currently supported.
# 2. OP-TEE does not boot with enabled CFG_CORE_ASLR.
$(call force,CFG_CORE_ASLR,n)

CFG_WITH_STATS ?= y
# CFG_ENABLE_EMBEDDED_TESTS ?= y

ifeq ($(PLATFORM_FLAVOR),lmt)
CFG_TEE_CORE_NB_CORE ?= 8

# [0e00_0000 0e0f_ffff] is reserved to early boot
#CFG_TZDRAM_START ?= 0x05080000
CFG_TZDRAM_START ?= 0x404000000
CFG_TZDRAM_SIZE ?= 0x02000000
# SHM chosen arbitrary, in a way that it does not interfere
# with initial location of linux kernel, dtb and initrd.
CFG_SHMEM_START ?= 0x406000000
CFG_SHMEM_SIZE ?= 0x02000000
endif

ifeq ($(PLATFORM_FLAVOR),lua)
CFG_TEE_CORE_NB_CORE ?= 4

# [0e00_0000 0e0f_ffff] is reserved to early boot
#CFG_TZDRAM_START ?= 0x05080000
CFG_TZDRAM_START ?= 0x104000000
CFG_TZDRAM_SIZE ?= 0x02000000
# SHM chosen arbitrary, in a way that it does not interfere
# with initial location of linux kernel, dtb and initrd.
CFG_SHMEM_START ?= 0x106000000
CFG_SHMEM_SIZE ?= 0x02000000
endif

CFG_IN_TREE_EARLY_TAS += avb/023f8f1a-292a-432b-8fc4-de8471358067
