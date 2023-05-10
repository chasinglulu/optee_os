// SPDX-License-Identifier: BSD-2-Clause
/*
 * Copyright (c) 2016-2020, Linaro Limited
 * Copyright (c) 2014, STMicroelectronics International N.V.
 */

#include <arm.h>
#include <console.h>
#include <drivers/gic.h>
#include <drivers/ns16550.h>
#include <initcall.h>
#include <keep.h>
#include <kernel/boot.h>
#include <kernel/interrupt.h>
#include <kernel/misc.h>
#include <kernel/notif.h>
#include <kernel/panic.h>
#include <kernel/spinlock.h>
#include <kernel/tee_time.h>
#include <mm/core_memprot.h>
#include <mm/core_mmu.h>
#include <platform_config.h>
#include <sm/psci.h>
#include <stdint.h>
#include <string.h>
#include <trace.h>

static struct gic_data gic_data __nex_bss;
static struct ns16550_data console_data __nex_bss;

register_phys_mem_pgdir(MEM_AREA_IO_NSEC, CONSOLE_UART_BASE, CONSOLE_UART_SIZE);

#ifdef DRAM_BASE
register_ddr(DRAM_BASE, DRAM_SIZE);
#endif

register_phys_mem_pgdir(MEM_AREA_IO_SEC, GICD_BASE, GIC_DIST_REG_SIZE);
register_phys_mem_pgdir(MEM_AREA_IO_SEC, GICC_BASE, GIC_DIST_REG_SIZE);

void main_init_gic(void)
{
	DMSG("main_init_gic begin\n");

	/* On ARMv8, GIC configuration is initialized in ARM-TF */
	gic_init_base_addr(&gic_data, GIC_BASE + GICC_OFFSET,
			   GIC_BASE + GICD_OFFSET);
	itr_init(&gic_data.chip);
}

void itr_core_handler(void)
{
	gic_it_handle(&gic_data);
}

void console_init(void)
{
	ns16550_init(&console_data, CONSOLE_UART_BASE, IO_WIDTH_U32, 2);
	register_serial_console(&console_data.chip);
	EMSG("console_init end\n");
}
