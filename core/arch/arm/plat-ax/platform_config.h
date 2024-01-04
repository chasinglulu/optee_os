/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2023 Charley wangkart@aliyun.com
 */

#ifndef PLATFORM_CONFIG_H
#define PLATFORM_CONFIG_H

#include <mm/generic_ram_layout.h>

/* Make stacks aligned to data cache line length */
#define STACK_ALIGNMENT      64

#if defined(PLATFORM_FLAVOR_lmt)
#define GIC_BASE        0x00449000
#define UART0_BASE      0x1068a000
#define UART1_BASE      0x1068b000

#define CONSOLE_UART_BASE   UART0_BASE
#define CONSOLE_UART_SIZE   ULL(0x1000)

#define SZ_1G               0x40000000
#define DRAM_BASE           0x400000000UL
#define DRAM_SIZE           (ULL(16) * SZ_1G)

#define GICD_OFFSET         0
#define GICC_OFFSET         0x1000
#else
#error "Unknown platform flavor"
#endif

#ifdef GIC_BASE
#define GICD_BASE           (GIC_BASE + GICD_OFFSET)
#define GICC_BASE           (GIC_BASE + GICC_OFFSET)
#endif

#ifndef UART_BAUDRATE
#define UART_BAUDRATE       115200
#endif
#ifndef CONSOLE_BAUDRATE
#define CONSOLE_BAUDRATE    UART_BAUDRATE
#endif

#define CONSOLE_UART_CLK_IN_HZ     24000000

#endif /* PLATFORM_CONFIG_H */
