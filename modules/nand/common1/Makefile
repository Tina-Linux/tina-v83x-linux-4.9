obj-$(CONFIG_SUNXI_NAND) += nand.o

ifdef CONFIG_ARM64
nftl = nftl_v8.S
obj-$(CONFIG_SUNXI_NAND) += nftl_v8.o
endif

ifdef CONFIG_ARM
nftl = nftl_v7.S
obj-$(CONFIG_SUNXI_NAND) += nftl_v7.o
endif


ifdef CONFIG_ARCH_SUN8IW18
	ndfc-v=phy-nand/rawnand/controller/ndfc_v2px.c
else
	ndfc-v=phy-nand/rawnand/controller/ndfc_v1px.c
endif

ifdef CONFIG_SUNXI_RAWNAND
	BUILD_RAWNAND=y
else
	BUILD_SPINAND=y
endif

$(obj)/$(nftl) : FORCE
ifneq ($(wildcard $(obj)/lib),)
	$(MAKE) -C $(obj)/.. \
		LICHEE_KDIR="$(shell pwd)" \
		build
endif

nand-y += nand_interface.o
nand-y += phy2nftl.o
nand-y += nfd/nand_ota_burn.o
nand-y += nfd/nand_base.o
nand-y += nfd/nand_blk.o
nand-y += nfd/nand_dev.o
nand-y += nfd/nand_class.o
nand-y += nfd/nand_test.o
nand-y += nfd/nand_osal_for_linux.o
nand-y += nfd/nand_panic.o
nand-y += phy-nand/nand_boot.o
nand-y += phy-nand/nand-partition/build_nand_partition.o
nand-y += phy-nand/nand-partition/build_phy_partition.o
nand-y += phy-nand/nand-partition/nand_info_init.o
nand-y += phy-nand/nand-partition2/build_phy_partition_v2.o
nand-y += phy-nand/nand-partition2/nand_info_init_v2.o
nand-y += phy-nand/nand_physic_interface.o
nand-y += phy-nand/nand_secure_storage.o
nand-y += phy-nand/version.o
nand-y += phy-nand/nand_weak.o
nand-y += phy-nand/nand_weak.o
nand-$(BUILD_RAWNAND) += phy-nand/rawnand/controller/ndfc_base.o
nand-$(BUILD_RAWNAND) += phy-nand/rawnand/controller/ndfc_timings.o
nand-$(BUILD_RAWNAND) += phy-nand/rawnand/controller/ndfc_v1px.o
nand-$(BUILD_RAWNAND) += $(basename $(ndfc-v)).o
nand-$(BUILD_RAWNAND) += phy-nand/rawnand/rawnand_base.o
nand-$(BUILD_RAWNAND) += phy-nand/rawnand/rawnand_boot1.o
nand-$(BUILD_RAWNAND) += phy-nand/rawnand/rawnand_boot0.o
nand-$(BUILD_RAWNAND) += phy-nand/rawnand/rawnand_cfg.o
nand-$(BUILD_RAWNAND) += phy-nand/rawnand/rawnand_ops.o
nand-$(BUILD_RAWNAND) += phy-nand/rawnand/rawnand_chip.o
nand-$(BUILD_RAWNAND) += phy-nand/rawnand/rawnand_debug.o
nand-$(BUILD_RAWNAND) += phy-nand/rawnand/rawnand_ids.o
nand-$(BUILD_RAWNAND) += phy-nand/rawnand/rawnand_readretry.o
nand-$(BUILD_RAWNAND) += phy-nand/rawnand/rawnand_timings.o
nand-$(BUILD_SPINAND) += phy-nand/spinand/spinand_boot.o
nand-$(BUILD_SPINAND) += phy-nand/spinand/spinand.o
#nand-y += $(libnand)
