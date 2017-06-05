/*
 * "rootkit" kernel module
 */

/*
 * The below are header files provided by the kernel which are
 * required for all modules.  They include things like the definition
 * of the module_init() macro.
 */
#include <linux/init.h>
#include <linux/module.h>


/*
 * MODULE_LICENSE() informs the kernel what license the module source
 * code is under, which affects which symbols it may access in the
 * main kernel.
 */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Doroshenko Andrey");
MODULE_DESCRIPTION("\"rootkit\" module");
MODULE_VERSION("0.01");


/*
 * This is the init function, which is run when the module is first
 * loaded.  The __init keyword tells the kernel that this code will
 * only be run once, when the module is loaded.
 */
static int __init rootkit_init(void) {
	printk("Hello from kernel rootkit!\n");
	return 0;
}


/*
 * Similary, the exit function is run once, upon module unloading, and
 * the module_exit() macro identifies which function is the exit
 * function.
 */
static void __exit rootkit_exit(void) {
	printk("Goodbye from kernel rootkit!\n");
}


/*
 * The below macro informs the kernel as to which function to use as
 * the init function.
 */
module_init(rootkit_init);
module_exit(rootkit_exit);