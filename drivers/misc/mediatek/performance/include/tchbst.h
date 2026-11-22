/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
 */


#ifndef _TCHBST_H
#define _TCHBST_H

#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/string.h>
#include <linux/notifier.h>
#include <linux/hrtimer.h>
#include <linux/workqueue.h>


#include <mt-plat/cpu_ctrl.h>
#include <mt-plat/eas_ctrl.h>
#include "perf_ioctl.h"

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/*tchbst 100 ms*/
#define TOUCH_TIMEOUT_NSEC 100000000
/*
 * Lowered from the stock 80 to trim the uclamp-min floor applied on every
 * touch (less CPU ramp / heat / battery drain per tap). Left well above the
 * 30% background cap so foreground UI work still gets clear priority.
 * TOUCH_BOOST_OPP intentionally left untouched: it indexes the raw OPP
 * frequency table, and changing it without that table in front of you risks
 * picking a floor frequency that causes visible touch lag.
 */
#define TOUCH_BOOST_EAS 65
#define TOUCH_BOOST_OPP 2
#define TOUCH_FSTB_ACTIVE_US 100000
#define TOUCH_TIME_TO_LAST_TOUCH_MS 600000

/*touch boost parent*/
int init_tchbst(struct proc_dir_entry *parent);

/*user*/
void switch_usrtch(int enable);
long usrtch_ioctl(unsigned int cmd, unsigned long arg);
int init_utch(struct proc_dir_entry *parent);
int notify_touch(int action);

/*kernel*/
int init_ktch(struct proc_dir_entry *parent);
int ktch_suspend(void);


#endif /* _TCHBST_H */
