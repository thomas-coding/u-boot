// SPDX-License-Identifier: GPL-2.0+

#include <common.h>
#include <fdtdec.h>
#include <init.h>
#include <asm/global_data.h>
#include <linux/sizes.h>

DECLARE_GLOBAL_DATA_PTR;
#if 0
int dram_init(void)
{
	return fdtdec_setup_mem_size_base();
}

int dram_init_banksize(void)
{
	return fdtdec_setup_memory_banksize();
}

phys_addr_t board_get_usable_ram_top(phys_size_t total_size)
{
	return gd->ram_top;
}
#endif
