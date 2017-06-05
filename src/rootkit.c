#include <linux/init.h>
#include <linux/module.h>

#include "include/proc.h"


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Doroshenko Andrey");
MODULE_DESCRIPTION("\"rootkit\" module");
MODULE_VERSION("0.05");


static int __init rootkit_module_init(void) {
    printk("rootkit: module init");

    if (!create_proc_file()) {
        printk("rootkit: can't create \"/proc/rootkit\" file");
        return -ENOMEM;
    }
    else {
        printk("rootkit: create \"/proc/rootkit\" file");
    }

    return 0;
}


static void __exit rootkit_module_exit(void) {
    printk("rootkit: module exit");

    remove_proc_file();
}


module_init(rootkit_module_init);
module_exit(rootkit_module_exit);