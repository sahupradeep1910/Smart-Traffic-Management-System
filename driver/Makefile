obj-m += traffic_signal_driver.o

KDIR := /lib/modules/7.0.0-14-generic/build

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
