# Circular Queue Kernel Module
this is Circular queue kernel module

## Installation and Usage

### Step 1: Compile the Kernel Module
```sh
make
```

### Step 2: Monitor Kernel Logs
```sh
sudo dmesg -W
```
This will show kernel messages in real-time.

### Step 3: Insert the Kernel Module
```sh
sudo insmod circuler_queue.ko
```
This loads the compiled kernel module into the Linux kernel.

### Step 4: Verify Module is Loaded
```sh
lsmod
```

### Step 5: Create Device Node
```sh
mknod /dev/Dhruv_patel_1 c <major_number> 0
```
Replace `<major_number>` with the major number assigned to the module, which can be found in the kernel logs (`dmesg`).

### Step 6: Compile User-Space Programs
Compile the `push`, `pop`, and `set_limit` programs that interact with the module:
```sh
gcc -o push push.c
gcc -o pop pop.c
gcc -o set_limit set_limit.c
```

### Step 7: Use Queue Functionalities
Execute the compiled programs to interact with the circular queue.
```sh
./set_limit
./push
./pop
```

### Step 8: Unload the Module
When done, remove the kernel module:
```sh
sudo rmmod circuler_queue
```

## Notes
- remove secure boot for load this module.



