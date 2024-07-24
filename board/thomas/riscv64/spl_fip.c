// SPDX-License-Identifier: GPL-2.0+
#include <common.h>
#include <bloblist.h>
#include <binman_sym.h>
#include <bootstage.h>
#include <dm.h>
#include <handoff.h>
#include <hang.h>
#include <init.h>
#include <irq_func.h>
#include <log.h>
#include <spl.h>
#include <image.h>
#include <io/io_driver.h>
#include <io/io_fip.h>
#include <io/io_memmap.h>
#include <io/io_storage.h>
#include <fip/tbbr_img_def_exp.h>
#include <fip/firmware_image_package.h>
#include <fip/bl_common_exp.h>
#include "platform_def.h"


static const io_dev_connector_t *fip_dev_con;
static uintptr_t fip_dev_handle;

static const io_dev_connector_t *memmap_dev_con;
static uintptr_t memmap_dev_handle;

static io_block_spec_t fip_mem_spec = {.offset = PLAT_THOMAS_RISCV64_FIP_MEM_BASE,
                                       .length = PLAT_THOMAS_RISCV64_FIP_MEM_SIZE};


static const io_uuid_spec_t bl31_uuid_spec = {
    .uuid = UUID_EL3_RUNTIME_FIRMWARE_BL31,
};

static const io_uuid_spec_t opensbi_dtb_uuid_spec = {
    .uuid = UUID_OPENSBI_DTB,
};

static const io_uuid_spec_t bl33_uuid_spec = {
    .uuid = UUID_NON_TRUSTED_FIRMWARE_BL33,
};

static int check_fip(const uintptr_t spec);
static int check_memmap(const uintptr_t spec);

struct plat_io_policy {
    uintptr_t *dev_handle;
    uintptr_t image_spec;
    int (*check)(const uintptr_t spec);
};

/* By default, ARM platforms load images from the FIP */
static struct plat_io_policy policies[] = {
    [FIP_IMAGE_ID]  = {&memmap_dev_handle, (uintptr_t)&fip_mem_spec, check_memmap},
    [BL31_IMAGE_ID] = {&fip_dev_handle, (uintptr_t)&bl31_uuid_spec, check_fip},
    [OPENSBI_DTB_IMAGE_ID] = {&fip_dev_handle, (uintptr_t)&opensbi_dtb_uuid_spec, check_fip},
    [BL33_IMAGE_ID] = {&fip_dev_handle, (uintptr_t)&bl33_uuid_spec, check_fip},
};

static int check_fip(const uintptr_t spec)
{
    int result                   = 0;
    uintptr_t local_image_handle = 0;

    result = io_dev_init(fip_dev_handle, (uintptr_t)FIP_IMAGE_ID);

    if (result == 0) {
        result = io_open(fip_dev_handle, spec, &local_image_handle);
        if (result == 0)
            io_close(local_image_handle);
    }

    return result;
}

static int check_memmap(const uintptr_t spec)
{
    int result                   = 0;
    uintptr_t local_image_handle = 0;

    result = io_dev_init(memmap_dev_handle, (uintptr_t)NULL);
    if (result == 0) {
        result = io_open(memmap_dev_handle, spec, &local_image_handle);
        if (result == 0)
            io_close(local_image_handle);
    }
    return result;
}

int plat_get_image_source(unsigned int image_id, uintptr_t *dev_handle, uintptr_t *image_spec)
{
    int result = 0;
    const struct plat_io_policy *policy;

    assert(image_id < ARRAY_SIZE(policies));
    policy = &policies[image_id];
    result = policy->check(policy->image_spec);
    if (result == 0) {
        *image_spec = policy->image_spec;
        *dev_handle = *(policy->dev_handle);
    } else {
        printf("Trying alternative IO\n");
    }

    return result;
}

void spl_fip_io_setup(void)
{
	int io_result = 0;

    /* Get connector and register device handle */
    io_result = register_io_dev_fip(&fip_dev_con);
    assert(io_result == 0);

    io_result = register_io_dev_memmap(&memmap_dev_con);
    assert(io_result == 0);
 
    io_result = io_dev_open(fip_dev_con, (uintptr_t)NULL, &fip_dev_handle);
    assert(io_result == 0);

    io_result = io_dev_open(memmap_dev_con, (uintptr_t)NULL, &memmap_dev_handle);
    assert(io_result == 0);

	/* Ignore improbable errors in release builds */
	(void)io_result;
}

void spl_fip_prepare_jump(struct spl_image_info *spl_image) {
	spl_image->os = IH_OS_OPENSBI;
	spl_image->load_addr = PLAT_THOMAS_RISCV64_OPENSBI_LOAD_ADDR;
	spl_image->entry_point = PLAT_THOMAS_RISCV64_OPENSBI_ENTRY;
	spl_image->fdt_addr = (void *)PLAT_THOMAS_RISCV64_OPENSBI_FDT_ADDR;
}
