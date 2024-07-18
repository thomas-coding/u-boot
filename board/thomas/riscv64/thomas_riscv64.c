/*
 * Copyright (c) 2024 Thomas
 */

#include <dm.h>
#include <common.h>
#include <command.h>
#include <malloc.h>
#include <asm/io.h>
//#include <asm/arch/hardware.h>
#define BOOT_DEVICE_RAM                 0x00
#define BOOT_DEVICE_MMC                 0x01

DECLARE_GLOBAL_DATA_PTR;

int dram_init(void)
{
	return fdtdec_setup_mem_size_base();
}

int board_early_init_f(void)
{
	return 0;
}

int dram_init_banksize(void)
{
	return fdtdec_setup_memory_banksize();
}

int board_init(void)
{
	return 0;
}

u32 sys_get_boot_mode(void)
{
	u32 mode = 0;

	mode = BOOT_DEVICE_RAM;

	return mode;
}

static int do_is_emmc_boot(struct cmd_tbl *cmdtp, int flag, int argc,
		  char *const argv[])
{
	if (BOOT_DEVICE_MMC == sys_get_boot_mode())
		return CMD_RET_SUCCESS;
	else
		return CMD_RET_FAILURE;
}

U_BOOT_CMD(
	is_emmc_boot, 1, 0, do_is_emmc_boot,
	"is emmc boot ?",
	""
);
