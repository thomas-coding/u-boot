// SPDX-License-Identifier: GPL-2.0+

#include <common.h>
#include <log.h>
#include <spl.h>
#include <spl_load.h>
#include <io/io_driver.h>
#include <io/io_memmap.h>
#include <io/io_storage.h>
#include <fip/tbbr_img_def_exp.h>
#include <fip/firmware_image_package.h>
#include <fip/bl_common_exp.h>
#include <fip/spl_fip.h>

static int load_image(unsigned int image_id, fip_image_info_t *image_data)
{
	uintptr_t dev_handle;
	uintptr_t image_handle;
	uintptr_t image_spec;
	uintptr_t image_base;
	size_t image_size;
	size_t bytes_read;
	int io_result;

	assert(image_data != NULL);

	image_base = image_data->image_base;

	printf("load start, image :%d\n", image_id);

	/* Obtain a reference to the image by querying the platform layer */
	io_result = plat_get_image_source(image_id, &dev_handle, &image_spec);

	if (io_result != 0) {
		printf("Failed to obtain reference to image id=%u (%i)\n",
			image_id, io_result);
		return io_result;
	}

	/* Attempt to access the image */
	io_result = io_open(dev_handle, image_spec, &image_handle);

	if (io_result != 0) {
		printf("Failed to access image id=%u (%i)\n",
			image_id, io_result);
		return io_result;
	}

	printf("Loading image id=%u at address 0x%lx\n", image_id, image_base);

	/* Find the size of the image */
	io_result = io_size(image_handle, &image_size);
	if ((io_result != 0) || (image_size == 0U)) {
		printf("Failed to determine the size of the image id=%u (%i)\n",
			image_id, io_result);
		goto exit;
	}

	/* Check that the image size to load is within limit */
	if (image_size > image_data->image_max_size) {
		printf("Image id=%u size out of bounds\n", image_id);
		io_result = -EFBIG;
		goto exit;
	}

	/*
	 * image_data->image_max_size is a uint32_t so image_size will always
	 * fit in image_data->image_size.
	 */
	image_data->image_size = (uint32_t)image_size;

	/* We have enough space so load the image now */
	/* TODO: Consider whether to try to recover/retry a partially successful read */
	io_result = io_read(image_handle, image_base, image_size, &bytes_read);
	if ((io_result != 0) || (bytes_read < image_size)) {
		printf("Failed to load image id=%u (%i)\n", image_id, io_result);
		goto exit;
	}
	printf("Image id=%u loaded: 0x%lx - 0x%lx\n", image_id, image_base,
	     (uintptr_t)(image_base + image_size));

exit:
	(void)io_close(image_handle);
	/* Ignore improbable/unrecoverable error in 'close' */

	/* TODO: Consider maintaining open device connection from this bootloader stage */
	(void)io_dev_close(dev_handle);
	/* Ignore improbable/unrecoverable error in 'dev_close' */

	return io_result;
}

static int load_auth_image_internal(unsigned int image_id,
				    fip_image_info_t *image_data)
{
	return load_image(image_id, image_data);
}

int plat_try_next_boot_source(void)
{
	return 0;
}

int load_auth_image(unsigned int image_id, fip_image_info_t *image_data)
{
	int err;

	do {
		err = load_auth_image_internal(image_id, image_data);
	} while ((err != 0) && (plat_try_next_boot_source() != 0));

	if (err == 0) {
		/*
		 * Flush the image to main memory so that it can be executed
		 * later by any CPU, regardless of cache and MMU state.
		 */
		//TODO: flush cache
		//flush_dcache_range(image_data->image_base,
				   //image_data->image_size);
	}

	return err;
}

int spl_fip_load_image(void)
{
	bl_load_info_t *bl2_load_info;
	const bl_load_info_node_t *bl2_node_info;
	int err;

	/*
	 * Get information about the images to load.
	 */
	bl2_load_info = get_bl_load_info_from_mem_params_desc();
	assert(bl2_load_info != NULL);
	assert(bl2_load_info->head != NULL);

	bl2_node_info = bl2_load_info->head;

	while (bl2_node_info != NULL) {

		//TODO: do some pre here

		printf("SPL: Loading image id %u\n", bl2_node_info->image_id);
		err = load_auth_image(bl2_node_info->image_id,
			bl2_node_info->image_info);
		if (err != 0) {
			printf("SPL: Failed to load image id %u (%i)\n",
				bl2_node_info->image_id, err);
		}

		//TODO: do some post here

		/* Go to next image */
		bl2_node_info = bl2_node_info->next_load_info;
	}


	return 0;
}
