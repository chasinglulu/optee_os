/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2014, Linaro Limited
 */

#ifndef PLATFORM_CONFIG_H
#define PLATFORM_CONFIG_H

#include <mm/generic_ram_layout.h>

/* Make stacks aligned to data cache line length */
#define STACK_ALIGNMENT		64


#if defined(PLATFORM_FLAVOR_sigi)

#define GIC_BASE		0x30B00000
#define UART0_BASE		0x39050000
#define UART1_BASE		0x39060000


#define CONSOLE_UART_BASE	UART0_BASE
#define CONSOLE_UART_SIZE	ULL(0x1000)

#define SZ_1G			0x40000000

#define DRAM_BASE		0x1000000000UL
#define DRAM_SIZE		(ULL(0x10) * SZ_1G)

#else
#error "Unknown platform flavor"
#endif


#if defined(PLATFORM_FLAVOR_sigi)

#define GICD_OFFSET		0
#define GICR_OFFSET		0x60000

#else
#error "Unknown platform flavor"
#endif

#ifdef GIC_BASE
#define GICD_BASE		(GIC_BASE + GICD_OFFSET)
#define GICR_BASE		(GIC_BASE + GICR_OFFSET)
#define GIC_REDIST_SIZE (0x20000 * 6)
#endif

#ifndef UART_BAUDRATE
#define UART_BAUDRATE		115200
#endif
#ifndef CONSOLE_BAUDRATE
#define CONSOLE_BAUDRATE	UART_BAUDRATE
#endif

#define CONSOLE_UART_CLK_IN_HZ	24000000

#endif /*PLATFORM_CONFIG_H*/