/*
 * Horizon SoC Checksum Tool.
 *
 * Maintainer: Tim <Wenjun.gu@verisilicon.com>
 *
 * Copyright (C) 2023 VeriSilicon Microelectronics (Shanghai) Co., Ltd.
 *
 */


#ifndef FIRMWARE_CHECKSUM_H
#define FIRMWARE_CHECKSUM_H

#include <stdint.h>

/* This is used as a signature to validate the checksum header */

#define HEADER_CHECKSUM_MAGIC		0xE5ECCE01


struct horizon_header {
	unsigned int magic_number;
	unsigned int image_checksum;
	unsigned char flag;
	unsigned char reserved0;
	unsigned char reserved1;
	unsigned char reserved2;
};


#endif /* FIRMWARE_CHECKSUM_H */
