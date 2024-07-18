/*
 * Copyright (c) 2024 Thomas
 */

#ifndef __CONFIG_THOMAS_RISCV64_H
#define __CONFIG_THOMAS_RISCV64_H

#define CFG_SYS_HZ_CLOCK               24000000

/* ram memory-related information */
#define CFG_SYS_INIT_RAM_ADDR	       0x20030000
#define CFG_SYS_INIT_RAM_SIZE          0x10000

#define CFG_SYS_BOOTMAPSZ              (256 << 20) /* Initial Memory map for Linux*/

#define THOMAS_RISCV64_MEM_BOOT                               \
    "memboot="                                         \
    "bootm ${fit_kernel}; "

#define CONFIG_BOOTCOMMAND \
    "if test ${sd_boot} = yes ; then " \
        "echo Trying to boot Linux from sd card ...; " \
        "fatload mmc ${mmcdev}:1 ${fit_kernel} ${fit_name}; " \
        "run memboot; " \
    "else " \
        "echo Trying to boot Linux from memory ...; " \
        "run memboot; " \
    "fi; "

#define CFG_EXTRA_ENV_SETTINGS                                           \
    "bootdelay=3\0"                                                      \
    "fit_kernel=0x42000000\0"                                          \
    "fit_name=thomas_riscv64.itb\0"                                             \
    "sd_boot=no\0"                                                      \
    "mmcdev=0\0"                                                         \
    THOMAS_RISCV64_MEM_BOOT

#endif /* __CONFIG_THOMAS_RISCV64_H */
