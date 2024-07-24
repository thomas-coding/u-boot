/*
 * Horizon SoC bl31/bl33 params descripts.
 *
 * Maintainer: Tim <Wenjun.gu@verisilicon.com>
 *
 * Copyright (C) 2023 VeriSilicon Microelectronics (Shanghai) Co., Ltd.
 *
 */
#include <fip/desc_image_load.h>
#include <fip/tbbr_img_def_exp.h>
#include <fip/spl_fip.h>
#include "platform_def.h"

/*******************************************************************************
 * Following descriptor provides BL image/ep information that gets used
 * by BL2 to load the images and also subset of this information is
 * passed to next BL image. The image loading sequence is managed by
 * populating the images in required loading order. The image execution
 * sequence is managed by populating the `next_handoff_image_id` with
 * the next executable image id.
 ******************************************************************************/
static bl_mem_params_node_t bl2_mem_params_descs[] = {
    /* Fill BL31 related information */
    {
        .image_id = BL31_IMAGE_ID,
        .image_info.image_base     = PLAT_THOMAS_RISCV64_OPENSBI_LOAD_ADDR,
        .image_info.image_max_size = PLAT_THOMAS_RISCV64_OPENSBI_MAX_SIZE,
        .next_handoff_image_id = OPENSBI_DTB_IMAGE_ID,
    },
    /* Fill opensbi dtb related information */
    {
        .image_id = OPENSBI_DTB_IMAGE_ID,
        .image_info.image_base     = PLAT_THOMAS_RISCV64_OPENSBI_FDT_ADDR,
        .image_info.image_max_size = PLAT_THOMAS_RISCV64_OPENSBI_FDT_MAX_SIZE,
        .next_handoff_image_id = BL33_IMAGE_ID,
    },

    /* Fill BL33 related information */
    {
        .image_id = BL33_IMAGE_ID,
        .image_info.image_base     = PLAT_THOMAS_RISCV64_UBOOT_LOAD_ADDR,
        .image_info.image_max_size = PLAT_THOMAS_RISCV64_UBOOT_MAX_SIZE,
        .next_handoff_image_id = INVALID_IMAGE_ID,
    }};

REGISTER_BL_IMAGE_DESCS(bl2_mem_params_descs)

static bl_load_info_t bl_load_info;

bl_load_info_t *get_bl_load_info_from_mem_params_desc(void)
{
	unsigned int index = 0;

	/* If there is no image to start with, return NULL */
	if (bl_mem_params_desc_num == 0U)
		return NULL;

	/* Assign initial data structures */
	bl_load_info_node_t *bl_node_info =
		&bl_mem_params_desc_ptr[index].load_node_mem;
	bl_load_info.head = bl_node_info;
	//SET_PARAM_HEAD(&bl_load_info, PARAM_BL_LOAD_INFO, VERSION_2, 0U);

	/* Go through the image descriptor array and create the list */
	for (; index < bl_mem_params_desc_num; index++) {

		/* Populate the image information */
		bl_node_info->image_id = bl_mem_params_desc_ptr[index].image_id;
		bl_node_info->image_info = &bl_mem_params_desc_ptr[index].image_info;

		/* Link next image if present */
		if ((index + 1U) < bl_mem_params_desc_num) {
			/* Get the memory and link the next node */
			bl_node_info->next_load_info =
				&bl_mem_params_desc_ptr[index + 1U].load_node_mem;
			bl_node_info = bl_node_info->next_load_info;
		}
	}

	return &bl_load_info;
}
