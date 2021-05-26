/*
 * Copyright (C) 2019 Allwinner Technology Limited. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * Author: Albert Yu <yuxyun@allwinnertech.com>
 */

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

struct reg {
	unsigned long phys;
	void __iomem *ioaddr;
};

struct sunxi_regs {
	struct reg ppu_gating_rst;	
	struct reg gpu_rstn;
	struct reg gpu_clk_gate;
	struct reg poweroff_gating;
	struct reg gpu_pswon;
	struct reg gpu_pswoff;
	struct reg pd_stat; /* power domain status */
	struct reg ppu_pw_ctrl;
	struct reg gpu_clk_ctrl;
};

struct sunxi_clks {
	struct clk *pll;
	struct clk *core;
};

struct sunxi_data {
	bool initialized;
	u32 reg_base;
	u32 reg_size;
	u32 irq_num;
	struct sunxi_regs regs;
	struct device *dev;
	struct sunxi_clks clks;
};

int sunxi_platform_init(struct device *dev);
void sunxi_platform_term(void);

#endif /* _PLATFORM_H_ */