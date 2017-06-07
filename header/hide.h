#ifndef __HIDE_SHADOW_H__
#define __HIDE_SHADOW_H__

#include <linux/module.h>
#include <linux/export.h>
#include <linux/kobject.h>
#include <linux/list.h>


/* Function Signatures. */
void module_hide(void);
void module_show(void);

#endif