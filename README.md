# Circular-Queue-kernel-module
this is Circular queue kernel module

step 1: make
step 2: sudo dmesg -W                                 (for kernel log and -W for show new logs)
step 3: sudo insmod circuler_queue.ko                 (.ko kernel object file)
step 4: lsmod                                         (list kernel module form /proc/modules)
step 5: mknod /dev/Dhruv_patel_1 c major_number 0     (see mejor number in kernel logs)
step 6: compile pop, push and set_limit file.
step 7: use these functionality
step 8: sudo rmmod circuler_queue                      (remove module)

