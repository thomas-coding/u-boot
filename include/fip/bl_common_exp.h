/*
 * Copyright (c) 2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef ARM_TRUSTED_FIRMWARE_EXPORT_COMMON_BL_COMMON_EXP_H
#define ARM_TRUSTED_FIRMWARE_EXPORT_COMMON_BL_COMMON_EXP_H

#include "utils_def_exp.h"
/* EXPORT HEADER -- See include/export/README for details! -- EXPORT HEADER */


/*
 * The following are used for image state attributes.
 * Image can only be in one of the following state.
 */
#define IMAGE_STATE_RESET		U(0)
#define IMAGE_STATE_COPIED		U(1)
#define IMAGE_STATE_COPYING		U(2)
#define IMAGE_STATE_AUTHENTICATED	U(3)
#define IMAGE_STATE_EXECUTED		U(4)
#define IMAGE_STATE_INTERRUPTED		U(5)

#define IMAGE_ATTRIB_SKIP_LOADING	U(0x02)
#define IMAGE_ATTRIB_PLAT_SETUP		U(0x04)

#define INVALID_IMAGE_ID		U(0xFFFFFFFF)

#ifndef __ASSEMBLER__

/*****************************************************************************
 * Image info binary provides information from the image loader that
 * can be used by the firmware to manage available trusted RAM.
 * More advanced firmware image formats can provide additional
 * information that enables optimization or greater flexibility in the
 * common firmware code
 *****************************************************************************/
typedef struct fip_image_info {
	uintptr_t image_base;	/* physical address of base of image */
	uint32_t image_size;	/* bytes read from image file */
	uint32_t image_max_size;
} fip_image_info_t;

/* BL image node in the BL image loading sequence */
typedef struct bl_load_info_node {
	unsigned int image_id;
	fip_image_info_t *image_info;
	struct bl_load_info_node *next_load_info;
} bl_load_info_node_t;

/* BL image head node in the BL image loading sequence */
typedef struct bl_load_info {
	bl_load_info_node_t *head;
} bl_load_info_t;

#endif /* __ASSEMBLER__ */

#endif /* ARM_TRUSTED_FIRMWARE_EXPORT_COMMON_BL_COMMON_EXP_H */
