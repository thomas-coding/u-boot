/*
 * Copyright (c) 2016-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef	ARM_TRUSTED_FIRMWARE_EXPORT_LIB_UTILS_DEF_EXP_H
#define	ARM_TRUSTED_FIRMWARE_EXPORT_LIB_UTILS_DEF_EXP_H

/* EXPORT HEADER -- See include/export/README for details! -- EXPORT HEADER */

/*
 * For those constants to be shared between C and other sources, apply a 'U',
 * 'UL', 'ULL', 'L' or 'LL' suffix to the argument only in C, to avoid
 * undefined or unintended behaviour.
 *
 * The GNU assembler and linker do not support these suffixes (it causes the
 * build process to fail) therefore the suffix is omitted when used in linker
 * scripts and assembler files.
*/
#if defined(__ASSEMBLER__)

#ifndef U
# define   U(_x)	(_x)
#endif

#ifndef UL
# define  UL(_x)	(_x)
#endif

#ifndef ULL
# define ULL(_x)	(_x)
#endif

#ifndef L
# define   L(_x)	(_x)
#endif

#ifndef LL
# define  LL(_x)	(_x)
#endif

#else

#ifndef U_
# define  U_(_x)	(_x##U)
#endif

#ifndef U
# define   U(_x)	U_(_x)
#endif

#ifndef UL
# define  UL(_x)	(_x##UL)
#endif

#ifndef ULL
# define ULL(_x)	(_x##ULL)
#endif

#ifndef L
# define   L(_x)	(_x##L)
#endif

#ifndef LL
# define  LL(_x)	(_x##LL)
#endif

#endif

#endif /* ARM_TRUSTED_FIRMWARE_EXPORT_LIB_UTILS_DEF_EXP_H */
