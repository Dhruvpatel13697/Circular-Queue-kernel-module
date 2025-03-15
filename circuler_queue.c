#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/device.h>
#include <linux/fs.h>

struct data {
    int length;
    char *data;
};

#define SET_SIZE_OF_QUEUE __IOW('a', 'a', int * )
#define PUSH_DATA __IOW('a', 'b', struct data * )
#define POP_DATA _IOR('a', 'c', struct data * )

int  c_dev_open(struct inode *, struct file *);
int c_dev_release(struct inode *, struct file *);
int c_dev_ioctl(struct file *, unsigned int, unsigned long);

int major_number;

struct circuler_queue{
    int front, rear,size, capacity;
    struct data *buffer;
};

int c_dev_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
    return 0;
}

int c_dev_open(struct inode *inode, struct file *file){
    pr_info("file open\n");
    return 0;
}

int c_dev_release(struct inode *inode, struct file *file){
    pr_info("file release\n");
    return 0;
}


struct file_operations fops = {
    .open = c_dev_open,
    .release = c_dev_release,
    .unlocked_ioctl = c_dev_ioctl,
}; 

static int start_module(void){

    pr_info("start module ....\n");
    major_number = register_chrdev(0, "Dhruv_patel_1", &fops);
    pr_info("device ragistered major = %d\n", major_number);
    
    return 0;
}

static void exit_module(void){
    
    unregister_chrdev(major_number, "Dhruv_patel_1");
    pr_info("exit module ....\n");
}

module_init(start_module);
module_exit(exit_module);

MODULE_LICENSE("GPL");