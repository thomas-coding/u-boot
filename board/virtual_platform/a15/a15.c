#include <dm.h>
#include <common.h>
#include <command.h>
#include <malloc.h>
#include <asm/io.h>

int board_early_init_f(void)
{
	return 0;
}

int dram_init(void)
{
	gd->ram_size = PHYS_SDRAM_SIZE;
	return 0;
}

int board_init(void)
{
	return 0;
}

