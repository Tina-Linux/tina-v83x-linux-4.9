obj-$(CONFIG_CSI_VIN) += modules/sensor/
obj-$(CONFIG_CSI_VIN) += modules/actuator/
obj-$(CONFIG_CSI_VIN) += vin_io.o
vin_io-$(CONFIG_CSI_CCI)				:= vin-cci/csi_cci_reg.o
vin_io-$(CONFIG_CSI_CCI)				+= vin-cci/bsp_cci.o
vin_io-y					+= vin-cci/cci_helper.o
vin_io-y					+= vin-cci/sunxi_cci.o
vin_io-y					+= utility/vin_supply.o
vin_io-y					+= utility/vin_os.o
vin_io-y					+= modules/sensor/sensor-compat-ioctl32.o
vin_io-y					+= modules/sensor/sensor_helper.o

obj-$(CONFIG_CSI_VIN) += vin_v4l2.o
vin_v4l2-y					:= vin-csi/sunxi_csi.o
vin_v4l2-y					+= vin-csi/parser_reg.o

vin_v4l2-y					+= vin-mipi/sunxi_mipi.o
ifneq ($(strip $(CONFIG_ARCH_SUN8IW15P1)),)
vin_v4l2-y					+= vin-mipi/bsp_mipi_csi.o
else ifneq ($(strip $(CONFIG_ARCH_SUN8IW19P1)),)
vin_v4l2-y					+= vin-mipi/bsp_mipi_csi.o
else ifneq ($(strip $(CONFIG_ARCH_SUN8IW17)),)
vin_v4l2-y					+= vin-mipi/bsp_mipi_csi_v1.o \
							vin-mipi/combo_rx/combo_rx_reg_null.o\
							vin-mipi/protocol/protocol_reg.o \
							vin-mipi/dphy/dphy_reg.o
else ifneq ($(strip $(CONFIG_ARCH_SUN8IW16)),)
vin_v4l2-y					+= vin-mipi/combo_rx/combo_rx_reg.o
else ifneq ($(strip $(CONFIG_ARCH_SUN50IW10)),)
vin_v4l2-y					+= vin-mipi/combo_csi/combo_csi_reg.o
else
vin_v4l2-y					+= vin-mipi/bsp_mipi_csi_null.o \
							vin-mipi/combo_rx/combo_rx_reg_null.o
endif

vin_v4l2-y					+= vin-isp/sunxi_isp.o
ifneq ($(strip $(CONFIG_ARCH_SUN8IW16P1)),)
vin_v4l2-y					+= vin-isp/isp520/isp520_reg_cfg.o
else ifneq ($(strip $(CONFIG_ARCH_SUN8IW19P1)),)
vin_v4l2-y					+= vin-isp/isp521/isp521_reg_cfg.o
else ifneq ($(strip $(CONFIG_ARCH_SUN50IW10P1)),)
vin_v4l2-y					+= vin-isp/isp522/isp522_reg_cfg.o
else
vin_v4l2-y					+= vin-isp/isp500/isp500_reg_cfg.o
endif

vin_v4l2-$(CONFIG_SUPPORT_ISP_TDM)			+= vin-tdm/vin_tdm.o
vin_v4l2-$(CONFIG_SUPPORT_ISP_TDM)			+= vin-tdm/tdm_reg.o
vin_v4l2-y					+= vin-vipp/sunxi_scaler.o
vin_v4l2-y					+= vin-vipp/vipp_reg.o
vin_v4l2-y					+= modules/flash/flash.o
vin_v4l2-y					+= utility/bsp_common.o
vin_v4l2-y					+= utility/config.o
vin_v4l2-y					+= utility/cfg_op.o
vin_v4l2-y					+= vin-stat/vin_h3a.o
vin_v4l2-y					+= vin-video/vin_video.o
vin_v4l2-y					+= vin-video/vin_core.o
vin_v4l2-y					+= vin-video/dma_reg.o
vin_v4l2-y					+= top_reg.o
vin_v4l2-y					+= vin.o




