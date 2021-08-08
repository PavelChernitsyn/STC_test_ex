obj-m += my_dummy_device.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
test:
	sudo dmesg -C
	sudo insmod my_dummy_device.ko
	lsmod | grep "my_dummy_device"
	sudo rmmod my_dummy_device
	sudo dmesg
