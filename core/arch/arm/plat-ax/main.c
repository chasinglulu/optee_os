// SPDX-License-Identifier: BSD-2-Clause
/*
 * Copyright (C) 2023 Charley wangkart@aliyun.com
 */

#include <console.h>
#include <drivers/gic.h>
#include <drivers/ns16550.h>
#include <kernel/boot.h>
#include <kernel/panic.h>
#include <mm/core_memprot.h>
#include <platform_config.h>

static struct ns16550_data console_data __nex_bss;

register_phys_mem_pgdir(MEM_AREA_IO_NSEC, CONSOLE_UART_BASE, CONSOLE_UART_SIZE);

#ifdef DRAM_BASE
register_ddr(DRAM_BASE, DRAM_SIZE);
#endif

#ifdef CFG_GIC
register_phys_mem_pgdir(MEM_AREA_IO_SEC, GICC_BASE, GIC_CPU_REG_SIZE);
register_phys_mem_pgdir(MEM_AREA_IO_SEC, GICD_BASE, GIC_DIST_REG_SIZE);

void boot_primary_init_intc(void)
{
	gic_init(GICC_BASE, GICD_BASE);
}

void boot_secondary_init_intc(void)
{
	gic_init_per_cpu();
}
#endif /* CFG_GIC */

void console_init(void)
{
	ns16550_init(&console_data, CONSOLE_UART_BASE, IO_WIDTH_U32, 2);
	register_serial_console(&console_data.chip);
}
