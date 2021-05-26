/*
 *
 * include/linux/dma/sunxi/dma-sun50iw9.h
 *
 * Copyright (C) 2017 Allwinner.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 */

#ifndef __DMA_SUN50IW10__
#define __DMA_SUN50IW10__

/*
 * The source DRQ type and port corresponding relation
 */
#define DRQSRC_SRAM			0
#define DRQSRC_SDRAM		0  /* DRQDST_DRAM = 1 ? */
#define DRQSRC_SPDIFRX		2
#define DRQSRC_DAUDIO_0_RX      3
#define DRQSRC_DAI0_RX          DRQSRC_DAUDIO_0_RX
#define DRQSRC_DAUDIO_1_RX      4
#define DRQSRC_DAI1_RX          DRQSRC_DAUDIO_1_RX
#define DRQSRC_DAUDIO_2_RX      5
#define DRQSRC_DAI2_RX          DRQSRC_DAUDIO_2_RX
#define DRQSRC_DAUDIO_3_RX      6
#define DRQSRC_DAI3_RX          DRQSRC_DAUDIO_3_RX
#define DRQSRC_AUDIO_CODEC	7
#define DRQSRC_DMIC			8
/* #define DRQSRC_RESERVE       8 */
/* #define DRQSRC_RESERVE       9 */
#define DRQSRC_NAND0		10
/* #define DRQSRC_RESERVE       11 */
#define DRQSRC_GPADC		12
/* #define DRQSRC_RESERVE       13 */
#define DRQSRC_UART0_RX		14
#define DRQSRC_UART1_RX		15
#define DRQSRC_UART2_RX		16
#define DRQSRC_UART3_RX		17
#define DRQSRC_UART4_RX		18
#define DRQSRC_UART5_RX		19
#define DRQSRC_UART6_RX		20
/* #define DRQSRC_RESERVE       20 */
/* #define DRQSRC_RESERVE       21 */
#define DRQSRC_SPI0_RX		22
#define DRQSRC_SPI1_RX		23
#define DRQSRC_SPI2_RX		24
/* #define DRQSRC_RESERVE		24 */
/* #define DRQSRC_RESERVE		25 */
/* #define DRQSRC_RESERVE       26 */
/* #define DRQSRC_RESERVE       27 */
/* #define DRQSRC_RESERVE       28 */
/* #define DRQSRC_RESERVE       29 */
#define DRQSRC_OTG_EP1		30
#define DRQSRC_OTG_EP2		31
#define DRQSRC_OTG_EP3		32
#define DRQSRC_OTG_EP4		33
#define DRQSRC_OTG_EP5		34
/* reserved: 35~39 */
#define DRQSRC_R_UART_RX	40
/* reserved: 41~42 */
#define DRQSRC_TWI0_RX		43
#define DRQSRC_TWI1_RX		44
#define DRQSRC_TWI2_RX		45
#define DRQSRC_TWI3_RX		46
#define DRQSRC_TWI4_RX		47
#define DRQSRC_TWI5_RX		48
#define DRQSRC_R_TWI0		50  /* new */
#define DRQSRC_R_TWI1		51  /* new */

/*
 * The destination DRQ type and port corresponding relation
 */
#define DRQDST_SRAM			0
#define DRQDST_SDRAM		0  /* DRQDST_DRAM = 1 ? */
#define DRQDST_SPDIFTX		2
#define DRQDST_DAUDIO_0_TX      3
#define DRQDST_DAI0_TX          DRQDST_DAUDIO_0_TX
#define DRQDST_DAUDIO_1_TX      4
#define DRQDST_DAI1_TX          DRQDST_DAUDIO_1_TX
#define DRQDST_DAUDIO_2_TX      5
#define DRQDST_DAI2_TX          DRQDST_DAUDIO_2_TX
#define DRQDST_DAUDIO_3_TX      6
#define DRQDST_DAI3_TX          DRQDST_DAUDIO_3_TX
#define DRQDST_AUDIO_CODEC	7
/* #define DRQDST_RESERVE       7 */
/* #define DRQDST_RESERVE       8 */
/* #define DRQDST_RESERVE       9 */
#define DRQDST_NAND0		10
#define DRQDST_LEDC             11
/* #define DRQDST_RESERVE       12 */
#define DRQDST_IR_TX		13
#define DRQDST_UART0_TX		14
#define DRQDST_UART1_TX		15
#define DRQDST_UART2_TX		16
#define DRQDST_UART3_TX		17
#define DRQDST_UART4_TX		18
#define DRQDST_UART5_TX		19
#define DRQDST_UART6_TX		20
/* #define DRQDST_RESERVE       20 */
/* #define DRQDST_RESERVE       21 */
#define DRQDST_SPI0_TX		22
#define DRQDST_SPI1_TX		23
#define DRQDST_SPI2_TX		24
/* #define DRQDST_RESERVE		24 */
/* #define DRQDST_RESERVE		25 */
/* #define DRQDST_RESERVE       26 */
/* #define DRQDST_RESERVE       27 */
/* #define DRQDST_RESERVE       28 */
/* #define DRQDST_RESERVE       29 */
#define DRQDST_OTG_EP1		30
#define DRQDST_OTG_EP2		31
#define DRQDST_OTG_EP3		32
#define DRQDST_OTG_EP4		33
#define DRQDST_OTG_EP5		34
/* reserved: 35~39 */
#define DRQDST_R_UART_TX		40
/* reserved: 41~42 */
#define DRQDST_TWI0_TX		43
#define DRQDST_TWI1_TX		44
#define DRQDST_TWI2_TX		45
#define DRQDST_TWI3_TX		46
#define DRQDST_TWI4_TX		47
#define DRQDST_TWI5_TX		48
#define DRQDST_R_TWI0		50  /* new */
#define DRQDST_R_TWI1		51  /* new */

#endif /*__DMA_SUN50IW10__  */
