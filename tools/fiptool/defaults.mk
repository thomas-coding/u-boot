#
# Copyright (c) 2016-2022, Arm Limited. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

# Default, static values for build variables, listed in alphabetic order.
# Dependencies between build options, if any, are handled in the top-level
# Makefile, after this file is included. This ensures that the former is better
# poised to handle dependencies, as all build variables would have a default
# value by then.

# Build option to provide OpenSSL directory path
OPENSSL_DIR			:= /usr

# Select the openssl binary provided in OPENSSL_DIR variable
ifeq ("$(wildcard ${OPENSSL_DIR}/bin)", "")
    OPENSSL_BIN_PATH = ${OPENSSL_DIR}/apps
else
    OPENSSL_BIN_PATH = ${OPENSSL_DIR}/bin
endif
