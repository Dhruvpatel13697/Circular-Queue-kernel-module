obj-m += circuler_queue.o 

PWD := $(CURDIR)
module_dir := /lib/modules/$(shell uname -r)/build

all:
	make -C $(module_dir) M=$(PWD) modules

clean:

	make -C $(module_dir) M=$(PWD) clean