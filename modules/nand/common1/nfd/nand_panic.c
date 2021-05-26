// SPDX-License-Identifier: GPL-2.0
/*
 *
 *
 * Copyright (C) 2019 liaoweixiong <liaoweixiong@gallwinnertech.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include "nand_panic.h"
#include "nand_lib.h"
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/string.h>
#include <linux/sunxi-panicpart.h>
/*#include <linux/types.h>*/
#if 1
#define PANIC_INFO(fmt, args...) \
	printk(KERN_INFO "[NI]" fmt, ##args)
#define PANIC_DBG(fmt, args...) \
	printk(KERN_DEBUG "[ND]" fmt, ##args)
#define PANIC_ERR(fmt, args...) \
	printk(KERN_ERR "[NE]" fmt, ##args)


/*static dma_addr_t panic_dma;*/
struct dma_buf {
	void *buf;
	size_t size;
};
/*static struct dma_buf panic_buf;*/
/*static struct dma_buf panic_map;*/
static struct _nftl_blk *g_nftl_blk;
#ifdef USE
static ssize_t nand_panic_read(struct panic_part *part, loff_t sec_off,
			       size_t sec_cnt, char *buf)
{
	int ret;
	struct _nftl_blk *nftl_blk = part->private;

	if (!is_panic_enable()) {
		PANIC_ERR("not support panic nand\n");
		return -EBUSY;
	}

	if (sec_off > part->sects) {
		PANIC_ERR("start sector is out of range\n");
		return -EACCES;
	}

	if (sec_off + sec_cnt > part->sects) {
		PANIC_ERR("sectors %lu with start sector %lld is out of range\n",
			  sec_cnt, sec_off);
		return -EACCES;
	}

	if (!nftl_blk) {
		PANIC_ERR("invalid nftl_blk\n");
		return -EINVAL;
	}

	ret = panic_read(nftl_blk, sec_off + part->start_sect, sec_cnt, buf);
	if (ret)
		return ret;
	return sec_cnt;
}

static ssize_t nand_panic_write(struct panic_part *part, loff_t sec_off,
				size_t sec_cnt, const char *buf)
{
	int ret;
	struct _nftl_blk *nftl_blk = part->private;

	if (!is_panic_enable()) {
		PANIC_ERR("not support panic nand\n");
		return -EBUSY;
	}

	if (sec_off > part->sects) {
		PANIC_ERR("start sector is out of range\n");
		return -EACCES;
	}

	if (sec_off + sec_cnt > part->sects) {
		PANIC_ERR("sectors %lu with start sector %lld is out of range\n",
			  sec_cnt, sec_off);
		return -EACCES;
	}

	if (!nftl_blk) {
		PANIC_ERR("invalid nftl_blk\n");
		return -EINVAL;
	}

	ret = panic_write(nftl_blk, sec_off + part->start_sect, sec_cnt, (uchar *)buf);
	if (ret)
		return ret;

	return sec_cnt;
}
static struct panic_part nand_panic = {
    .type = SUNXI_FLASH_NAND,
    .panic_read = nand_panic_read,
    .panic_write = nand_panic_write,
};
static int rawnand_panic_alloc_dma_buf(size_t size)
{
	char *buf;

	buf = dma_alloc_coherent(NULL, size, &panic_dma, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;
	panic_buf.buf = buf;
	panic_buf.size = size;

	return 0;
}
#endif
#ifdef CONFIG_SUNXI_PANICPART
dma_addr_t nand_panic_dma_map(__u32 rw, void *buf, __u32 len)
{
	if (!is_panic_enable())
		return -EBUSY;

	/* ONLY rawnand allow to use DMA */
	if (get_storage_type() != NAND_STORAGE_TYPE_RAWNAND)
		return -EINVAL;

	if (rw == 1) {
		size_t size = min_t(size_t, len, panic_buf.size);
		memcpy(panic_buf.buf, buf, size);
	} else {
		panic_map.buf = buf;
		panic_map.size = (size_t)len;
	}

	return panic_dma;
}

void nand_panic_dma_unmap(__u32 rw, dma_addr_t dma_handle, __u32 len)
{
	if (!is_panic_enable())
		return;

	/* ONLY rawnand allow to use DMA */
	if (get_storage_type() != NAND_STORAGE_TYPE_RAWNAND)
		return -EINVAL;

	if (rw == 0) {
		size_t size = min_t(size_t, panic_map.size, panic_buf.size);
		memcpy(panic_map.buf, panic_buf.buf, size);
	}

	return;
}

int nand_support_panic(void)
{
	int ret;

	ret = sunxi_parse_blkdev(NULL, 0);
	if (ret)
		return ret;

	/* allocate memory for rawnand dma transfer */
	if (get_storage_type() == NAND_STORAGE_TYPE_RAWNAND) {
		ret = rawnand_panic_alloc_dma_buf(32 * 1024);
		if (ret)
			return ret;
	}

	panic_mark_enable();
	return 0;
}

int nand_panic_init(struct _nftl_blk *nftl_blk)
{
	int ret;

	if (!is_panic_enable())
		return -EBUSY;

	ret = sunxi_panicpart_init(&nand_panic);
	if (ret)
		return ret;

	g_nftl_blk = nand_panic.private = (void *)nftl_blk;
	PANIC_INFO("panic nand version: %s\n", PANIC_NAND_VERSION);
	return 0;
}
#else

dma_addr_t __maybe_unused nand_panic_dma_map(__u32 rw, void *buf, __u32 len)
{
	return -1;
}

void __maybe_unused nand_panic_dma_unmap(__u32 rw, dma_addr_t dma_handle, __u32 len)
{
	return;
}

int __maybe_unused nand_support_panic(void)
{
	return -1;
}

int __maybe_unused nand_panic_init(struct _nftl_blk *nftl_blk)
{
	return -1;
}
#endif
int critical_dev_nand_write(const char *dev, loff_t sec_off,
			    size_t sec_cnt, char *buf)
{
	struct block_device *bdev;
	struct hd_struct *part;
	size_t part_off, part_size;
	int ret = -EACCES;

	if (!is_panic_enable()) {
		PANIC_ERR("not support panic nand\n");
		return -EBUSY;
	}

	if (!g_nftl_blk) {
		PANIC_ERR("invalid nftl_blk\n");
		return -EINVAL;
	}

	bdev = blkdev_get_by_path(dev, FMODE_WRITE, NULL);
	if (IS_ERR(bdev)) {
		PANIC_ERR("get bdev failed - %ld\n", PTR_ERR(bdev));
		return PTR_ERR(bdev);
	}
	part = bdev->bd_part;
	part_off = (size_t)part->start_sect;
	part_size = (size_t)part_nr_sects_read(part);

	if (sec_off > part_size) {
		PANIC_ERR("start sector is out of range\n");
		goto out;
	}

	if (sec_off + sec_cnt > part_size) {
		PANIC_ERR("sectors %lu with start sector %lld is out of range\n",
			  sec_cnt, sec_off);
		goto out;
	}

	ret = panic_write(g_nftl_blk, sec_off + part_off, sec_cnt, buf);
	if (ret)
		goto out;

	ret = 0;
out:
	blkdev_put(bdev, FMODE_WRITE);
	return ret;
}

int critical_dev_nand_read(const char *dev, loff_t sec_off,
			   size_t sec_cnt, char *buf)
{
	struct block_device *bdev;
	struct hd_struct *part;
	size_t part_off, part_size;
	int ret = -EACCES;

	if (!is_panic_enable()) {
		PANIC_ERR("not support panic nand\n");
		return -EBUSY;
	}

	if (!g_nftl_blk) {
		PANIC_ERR("invalid nftl_blk\n");
		return -EINVAL;
	}

	bdev = blkdev_get_by_path(dev, FMODE_READ, NULL);
	if (IS_ERR(bdev)) {
		PANIC_ERR("get bdev failed - %ld\n", PTR_ERR(bdev));
		return PTR_ERR(bdev);
	}
	part = bdev->bd_part;
	part_off = (size_t)part->start_sect;
	part_size = (size_t)part_nr_sects_read(part);

	if (sec_off > part_size) {
		PANIC_ERR("start sector is out of range\n");
		goto out;
	}

	if (sec_off + sec_cnt > part_size) {
		PANIC_ERR("sectors %lu with start sector %lld is out of range\n",
			  sec_cnt, sec_off);
		goto out;
	}

	ret = panic_read(g_nftl_blk, sec_off + part_off, sec_cnt, buf);
	if (ret)
		goto out;

	ret = 0;
out:
	blkdev_put(bdev, FMODE_READ);
	return ret;
}
#endif
