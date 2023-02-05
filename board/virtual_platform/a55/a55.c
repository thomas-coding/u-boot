#include <dm.h>
#include <common.h>
#include <command.h>
#include <malloc.h>
#include <asm/io.h>
#include <asm/armv8/mmu.h>

static struct mm_region a55_mem_map[] = {
	{
		/* Lowmem peripherals */
		.virt = 0x40000000UL,
		.phys = 0x40000000UL,
		.size = 0x10000000,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		/* RAM */
		.virt = 0x31000000UL,
		.phys = 0x31000000UL,
		.size = 0xf000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			 PTE_BLOCK_INNER_SHARE
	}, {
		/* List terminator */
		0,
	}
};

struct mm_region *mem_map = a55_mem_map;

/*
 * Board specific reset that is system reset.
 */
void reset_cpu(void)
{
	/* TODO */
}

int print_cpuinfo(void)
{
	printf("CPU:   QEMU Thomas a55\n");
	return 0;
}

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

