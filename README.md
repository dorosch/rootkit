# Linux Rootkit

This project is a Linux rootkit for hiding its work and 
hiding the work of the custom malware.


### Assembly

To build, you need the tools from the package `module-assistant` 
in Debian or `kernel-devel` in Fedora. After installation, 
assemble the module:

```Bash
$ make
```

For debugging, messages are sent to the kernel level. To 
view them use `dmesg`. Next, you need to load a module:

```Bash
$ make install
$ dmesg | tail
```

After the test, unload the module:

```Bash
$ make uninstall
$ dmesg | tail
```

And clean up the working directory:

```Bash
$ make clean
```