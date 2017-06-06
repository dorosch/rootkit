/*
 * This is the main file of the rootkit. Two functions are 
 * declared here: module initialization and module unloading.
 */
#include <linux/init.h>
#include <linux/module.h>

#include "header/proc.h"



/*
 * Declare meta information about the module. The license 
 * of the module is also important, since some licenses 
 * do not allow to use all the features of the kernel module.
 */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Doroshenko Andrey");
MODULE_DESCRIPTION("\"rootkit\" module");
MODULE_VERSION("0.06");


/*
 * Module initialization function at startup.
 */
static int __init rootkit_module_init(void) {
    printk("rootkit: module init\n");

    if (!create_proc_file()) {
        printk("rootkit: can't create \"/proc/rootkit\" file\n");
        return -ENOMEM;
    }
    else {
        printk("rootkit: create \"/proc/rootkit\" file\n");
    }

    return 0;
}


/*
 * The function called when the module is unloaded.
 */
static void __exit rootkit_module_exit(void) {
    printk("rootkit: module exit\n");

    remove_proc_file();
}


/* Set the module initialization and unloading functions. */
module_init(rootkit_module_init);
module_exit(rootkit_module_exit);