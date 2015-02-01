obj-m := cryptage.o comm.o
KDIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

DRV := /dev/comm1 /dev/comm2

default: $(DRV)
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	cp *.ko /lib/modules/$(shell uname -r)/kernel
	depmod -a
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

$(DRV):
	@mknod /dev/comm1 c 150 0; chmod a+rw /dev/comm1
	@mknod /dev/comm2 c 150 1; chmod a+rw /dev/comm2

probe:
	@modprobe comm
#	@dmesg

rm:
	@rmmod comm
	@rmmod cryptage
