/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2011 Linaro
 * Ryan Harkin, <ryan.harkin@linaro.org>
 *
 * Configuration for Versatile Express. Parts were derived from other ARM
 *   configurations.
 */

#ifndef __A55_H
#define __A55_H

/* 0x31000000 .. 0x3fffffff : DDR(256 - 16 M) */
#define PHYS_SDRAM			0x31000000
#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define PHYS_SDRAM_SIZE		0x0f000000 /* 256 - 16 MB */

/* Serial (ns16550)       */
#define UART_CLK			(24000000)
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
#define CONFIG_SYS_NS16550_CLK		UART_CLK
#define CONFIG_SYS_NS16550_COM1		0x40000000
#define CONFIG_SYS_NS16550_SERIAL
//#define CONFIG_PL01x_PORTS		{(void *)(0x40000000)}

#endif /* __A55_H */
