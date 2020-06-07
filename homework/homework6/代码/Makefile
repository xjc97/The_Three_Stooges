#sample driver module
obj-m := scull1.o scull2.o scull3.o
KDIR = /root/linux-2.6.36.4/
PWD:=$(shell pwd)
INSTALLDIR=$(PWD)
modules:
	$(MAKE) -C /lib/modules/`uname -r`/build M=`pwd` modules
clean:
	rm -f *.mod.c *.mod.o *.ko *.o *.tmp_versions
.PHONY:modules clean
