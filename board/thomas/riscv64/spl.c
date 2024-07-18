// SPDX-License-Identifier: GPL-2.0+

#include <init.h>
#include <spl.h>
#include <misc.h>
#include <log.h>
#include <hang.h>
#include <linux/delay.h>
#include <linux/io.h>

extern char _end[];

// This is called in board_init_f of arch/riscv/lib/spl.c
int spl_board_init_f(void)
{
	// TODO you can init your DDR memory here
	return 0;
}

void spl_board_init(void)
{
	// TODO do your basic board initialization for uboot spl
	log_info("Do initialization for spl board, sizeof(struct global_data)=%lu!\n", sizeof(struct global_data));
}

u32 spl_boot_device(void)
{
	return BOOT_DEVICE_RAM;
}

void *board_fdt_blob_setup(int *err)
{
	void *fdt_blob = NULL;
	fdt_blob = (ulong *)&_end;
	*err = 0;
	return fdt_blob;
}

// board_init_f weak version is defined arch/riscv/lib/spl.c
// you should never select CONFIG_SPL_FRAMEWORK_BOARD_INIT_F in kconfig

#ifdef CONFIG_SPL_DISPLAY_PRINT
void spl_display_print(void)
{
	DECLARE_GLOBAL_DATA_PTR;
	const char *model;

	/* same code than show_board_info() but not compiled for SPL
	 * see CONFIG_DISPLAY_BOARDINFO & common/board_info.c
	 */
	model = fdt_getprop(gd->fdt_blob, 0, "model", NULL);
	if (model)
		log_info("Model: %s\n", model);
}
#endif

#ifdef CONFIG_SPL_LOAD_FIT
int board_fit_config_name_match(const char *name)
{
	/* boot using first FIT config */
	return 0;
}
#endif
