#
# Copyright (C) 2015-2019 Allwinner Technology Limited. All rights reserved.
#
# This program is free software and is provided to you under the terms of the GNU
# General Public License version 2 as published by the Free Software Foundation, and
# any use by you of this program is subject to the terms of such GNU licence.
#
# Author: Albert Yu <yuxyun@allwinnertech.com>
#

ifneq ($(LICHEE_KDIR),)
export KERNEL_DIR = $(LICHEE_KDIR)
endif

export KDIR = $(KERNEL_DIR)
export KERNELDIR = $(KERNEL_DIR)

GPU_BUILD_TYPE ?= release

include $(KERNEL_DIR)/.config

ifneq ($(LICHEE_MOD_DIR),)
GPU_KM_OUT_DIR=$(LICHEE_MOD_DIR)
else
GPU_KM_OUT_DIR=${GPU_OUT_DIR}/kernel_mode
endif

ifneq ($(wildcard $(CROSS_COMPILE)gcc),)
export CROSS_COMPILE
else
$(warning CROSS_COMPILE($(CROSS_COMPILE)) is invalid)
endif

##############################################################
###################     Set GPU_TYPE     #####################
##############################################################
GPU_TYPE ?= $(CONFIG_SUNXI_GPU_TYPE)

##############################################################
##############     Set WINDOW_SYSTEM_TYPE      ###############
##############################################################
ifneq ($(LICHEE_PLATFORM),)
ifeq ($(LICHEE_PLATFORM),android)
OS_NAME := android
else ifeq ($(LICHEE_PLATFORM),secureandroid)
OS_NAME := android
else ifeq ($(LICHEE_PLATFORM),camdroid)
OS_NAME := android
else ifeq ($(LICHEE_PLATFORM),linux)
OS_NAME := linux
else ifeq ($(LICHEE_PLATFORM),dragonboard)
OS_NAME := linux
else
$(error LICHEE_PLATFORM($(LICHEE_PLATFORM)) is invalid)
endif
endif

ifeq ($(LICHEE_PLATFORM),)
ifeq ($(WINDOW_SYSTEM_TYPE),android)
OS_NAME := android
else ifeq ($(WINDOW_SYSTEM_TYPE),fbdev)
OS_NAME := linux
else
$(error WINDOW_SYSTEM_TYPE($(WINDOW_SYSTEM_TYPE)) is invalid)
endif
endif

ifneq ($(findstring mali400, $(GPU_TYPE)),)
GPU_ARCH := mali-utgard
else ifneq ($(findstring mali450, $(GPU_TYPE)),)
GPU_ARCH := mali-utgard
else ifneq ($(findstring mali-t720, $(GPU_TYPE)),)
GPU_ARCH := mali-midgard
else ifneq ($(findstring mali-t760, $(GPU_TYPE)),)
GPU_ARCH := mali-midgard
else ifneq ($(findstring sgx544, $(GPU_TYPE)),)
GPU_ARCH := img-sgx
else ifneq ($(findstring rgx6230, $(GPU_TYPE)),)
GPU_ARCH := img-rgx
else ifneq ($(findstring ge8300, $(GPU_TYPE)),)
GPU_ARCH := img-rgx
else
$(error GPU_TYPE($(GPU_TYPE)) is invalid)
endif

##############################################################
##########     Set GPU_BUILD_DIR and GPU_KO_NAME     #########
##############################################################
ifeq ($(GPU_ARCH),mali-utgard)
GPU_BUILD_DIR = mali-utgard/driver/src/devicedrv/mali
GPU_KO_NAME   = $(GPU_BUILD_DIR)/mali.ko
else ifeq ($(GPU_ARCH),mali-midgard)
GPU_BUILD_DIR = mali-midgard/driver
GPU_KO_NAME   = $(GPU_BUILD_DIR)/drivers/gpu/arm/midgard/mali_kbase.ko
GPU_KO_NAME  += $(GPU_BUILD_DIR)/drivers/base/kds/kds.ko
GPU_KO_NAME  += $(GPU_BUILD_DIR)/drivers/base/dma_buf_test_exporter/dma-buf-test-exporter.ko
else ifeq ($(GPU_ARCH),img-sgx)
GPU_BUILD_DIR = img-sgx/$(OS_NAME)/eurasia_km/eurasiacon/build/linux2/sunxi_$(OS_NAME)
GPU_KO_NAME   = img-sgx/$(OS_NAME)/eurasia_km/eurasiacon/binary2_sunxi_$(OS_NAME)_$(GPU_BUILD_TYPE)/target/pvrsrvkm.ko
ifeq ($(OS_NAME),linux)
GPU_KO_NAME   += img-sgx/$(OS_NAME)/eurasia_km/eurasiacon/binary2_sunxi_$(OS_NAME)_$(GPU_BUILD_TYPE)/target/dc_sunxi.ko
endif
else ifeq ($(GPU_ARCH),img-rgx)
GPU_BUILD_DIR = img-rgx/$(OS_NAME)/rogue_km/build/linux/sunxi_$(OS_NAME)
GPU_KO_NAME   = img-rgx/linux/rogue_km/binary_sunxi_linux_nullws_$(GPU_BUILD_TYPE)/target_aarch64/pvrsrvkm.ko
GPU_KO_NAME   = img-rgx/linux/rogue_km/binary_sunxi_linux_nullws_$(GPU_BUILD_TYPE)/target_aarch64/dc_sunxi.ko
else
$(error GPU_ARCH ($(GPU_ARCH)) is invalid)
endif

##############################################################

.PHONY: all build install clean

all: build install

build:
	$(MAKE) -j -C $(GPU_BUILD_DIR) BUILD=$(GPU_BUILD_TYPE)

install:
	@cp -uv $(GPU_KO_NAME) $(GPU_KM_OUT_DIR)

clean:
	$(MAKE) -C $(GPU_BUILD_DIR) clean
