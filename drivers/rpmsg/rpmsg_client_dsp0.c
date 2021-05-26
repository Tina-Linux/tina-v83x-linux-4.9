/*
 * Remote processor messaging - sample client driver
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 * Copyright (C) 2011 Google, Inc.
 *
 * Ohad Ben-Cohen <ohad@wizery.com>
 * Brian Swetland <swetland@google.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/rpmsg.h>
#include <linux/workqueue.h>

#define MSG		"hello world!"
#define MSG_LIMIT	100

struct instance_data {
	int rx_count;
};

static struct delayed_work work;
static struct rpmsg_device *rd;
static int cnt;

static void work_func(struct work_struct *work)
{
	int ret;
	char buf[50];

	sprintf(buf, "send cnt%d", cnt++);
	printf("start send\n");
	/* send a message to our remote processor */
	ret = rpmsg_send(rd->ept, buf, strlen(MSG));
	if (ret) {
		dev_err(&rd->dev, "rpmsg_send failed: %d\n", ret);
	}

	schedule_delayed_work(to_delayed_work(work), msecs_to_jiffies(300));
}


static int rpmsg_sample_cb(struct rpmsg_device *rpdev, void *data, int len,
						void *priv, u32 src)
{

	print_hex_dump(KERN_DEBUG, __func__, DUMP_PREFIX_NONE, 16, 1,
		       data, len,  true);

	return 0;
}

static int rpmsg_sample_probe(struct rpmsg_device *rpdev)
{
	struct instance_data *idata;

	rd = rpdev;

	INIT_DELAYED_WORK(&work, work_func);

	dev_info(&rpdev->dev, "new channel: 0x%x -> 0x%x!\n",
					rpdev->src, rpdev->dst);

	idata = devm_kzalloc(&rpdev->dev, sizeof(*idata), GFP_KERNEL);
	if (!idata)
		return -ENOMEM;

	dev_set_drvdata(&rpdev->dev, idata);

	schedule_delayed_work(&work, msecs_to_jiffies(300));

	return 0;
}

static void rpmsg_sample_remove(struct rpmsg_device *rpdev)
{
	dev_info(&rpdev->dev, "rpmsg sample client driver is removed\n");
}

static struct rpmsg_device_id rpmsg_driver_sample_id_table[] = {
	{ .name	= "sunxi,dsp0" },
	{ },
};
MODULE_DEVICE_TABLE(rpmsg, rpmsg_driver_sample_id_table);

static struct rpmsg_driver rpmsg_sample_client = {
	.drv.name	= KBUILD_MODNAME,
	.id_table	= rpmsg_driver_sample_id_table,
	.probe		= rpmsg_sample_probe,
	.callback	= rpmsg_sample_cb,
	.remove		= rpmsg_sample_remove,
};
module_rpmsg_driver(rpmsg_sample_client);

MODULE_DESCRIPTION("Remote processor messaging sample client driver");
MODULE_LICENSE("GPL v2");
