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
//#define UART_CLK			(24000000)
//#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
//#define CONFIG_SYS_NS16550_CLK		UART_CLK
//#define CONFIG_SYS_NS16550_COM1		0x40000000
//#define CONFIG_SYS_NS16550_SERIAL
//#define CONFIG_PL01x_PORTS		{(void *)(0x40000000)}

#define A55_FATFS_LOAD \
	"fatfsload=" \
		"echo Trying to fatfsload ...; " \
		"if test ${boot_fit} = yes ; then " \
			"fatload mmc 0:1 ${kernel_addr} ${fit_name}; " \
		"else " \
			"fatload mmc 0:1 ${fdt_addr} ${fdt_name}; " \
			"fatload mmc 0:1 ${kernel_addr} ${kernel_name}; " \
		"fi;\0"

#define A55_RAW_BLK_LOAD \
	"rawblkload=" \
		"echo Trying to rawblkload ...; " \
		"mmc read ${kernel_addr} ${linux_start_sector} ${linux_size_sectors}; " \
		"if test ${boot_fit} = yes ; then " \
			"echo skip dtb load for fit; " \
		"else " \
			"mmc read ${fdt_addr} ${dtb_start_sector} ${dtb_size_sectors}; " \
		"fi;\0"

#define A55_MMC_LOAD \
	"mmcload=" \
		"if test ${fatfsboot} = yes ; then " \
			"run fatfsload; " \
		"else " \
			"run rawblkload; " \
		"fi;\0"

#define CONFIG_EXTRA_ENV_SETTINGS \
	"bootdelay=5\0" \
	"fdt_addr=0x36000000\0" \
	"kernel_addr=0x35000000\0" \
	"kernel_name=Image\0" \
	"fdt_name=a55.dtb\0" \
	"sdemmc_boot=yes\0" \
	"fatfsboot=yes\0" \
	"boot_fit=no\0" \
	"dtb_start_sector=0x8000\0"   /* DTB start sector in eMMC at 16MB */ \
	"dtb_size_sectors=0x400\0"    /* DTB size: 512K */ \
	"linux_start_sector=0x9000\0" /* Linux start sector in eMMC at 18MB */  \
	"linux_size_sectors=0x20000\0" /* Linux size: 64MB */ \
	A55_RAW_BLK_LOAD \
	A55_MMC_LOAD \
	A55_FATFS_LOAD

#define CONFIG_BOOTCOMMAND \
	"if test ${sdemmc_boot} = yes ; then " \
		"echo Trying to boot Linux from sd/emmc card ...; " \
		"if run mmcload ; then " \
			"booti ${kernel_addr} - ${fdt_addr}; " \
		"else " \
			"echo mmc load failure; " \
		"fi; " \
	"else " \
		"echo Trying to boot Linux from memory ...; " \
		"booti ${kernel_addr} - ${fdt_addr}; " \
	"fi; "

#endif /* __A55_H */
