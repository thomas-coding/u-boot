/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2011 Linaro
 * Ryan Harkin, <ryan.harkin@linaro.org>
 *
 * Configuration for Versatile Express. Parts were derived from other ARM
 *   configurations.
 */

#ifndef __A15_H
#define __A15_H

/*  0x20000000 .. 0x27ffffff : DDR(128M) */
#define PHYS_SDRAM			0x20000000
#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define PHYS_SDRAM_SIZE		0x8000000 /* 128 MB */

//define sp to u-boot 16M top
#define CONFIG_SYS_INIT_SP_ADDR		0x21000000

/* Serial (pl011)       */
#define UART_CLK			(24000000)
#define CONFIG_PL011_CLOCK		UART_CLK
#define CONFIG_PL01x_PORTS		{(void *)(0x40000000)}

#endif /* __A15_H */
