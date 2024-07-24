#
# Copyright (c) 2024 Thomas
#

ifdef CONFIG_SPL_BUILD
obj-y += spl.o
ifdef CONFIG_SPL_FIP
obj-y += spl_fip.o
obj-y += spl_mem_params_desc.o
endif
else
obj-y += thomas_riscv64.o
endif
