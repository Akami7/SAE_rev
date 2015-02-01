obj-m := cryptage.o comm.o
KDIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	cp *.ko /lib/modules/$(shell uname -r)/kernel
	depmod -a
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

probe:
	@modprobe comm
#	@dmesg

rm:
	@rmmod comm
	@rmmod cryptage
