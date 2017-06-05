#ifndef __PROC_H__
#define __PROC_H__

#include <linux/proc_fs.h>
#include <linux/string.h>

#define PROC_FILE_NAME "rootkit"


int create_proc_file(void);
void remove_proc_file(void);

#endif