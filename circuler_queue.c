#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/device.h>
#include <linux/fs.h>

static struct data {
    int length;
    char *data;
};

#define SET_SIZE_OF_QUEUE _IOW('a', 'a', int *)
#define PUSH_DATA _IOW('a', 'b', struct data *)
#define POP_DATA _IOR('a', 'c', struct data *)

static int major_number;
static spinlock_t lock;

static struct circuler_queue{
    int front, rear,size, capacity;
    struct data *buffer;
};

static struct circuler_queue queue;

static long int c_dev_ioctl(struct file *file, unsigned int cmd, unsigned long arg){

    struct data user_queue_data, kernel_queue_data;

    spin_lock(&lock);

    switch (cmd)
    {
    case SET_SIZE_OF_QUEUE:
        if(copy_from_user(&queue.capacity, (int *)arg, sizeof(int))){
            pr_info("error occure\n");
            spin_unlock(&lock);
            return -1;
        }
        queue.buffer = kmalloc(queue.capacity* sizeof(struct data), GFP_KERNEL);
        pr_info("set size %d\n", queue.capacity);
        queue.front = queue.rear = queue.size = 0;
        break;

    case PUSH_DATA:
        if(queue.size >= queue.capacity){
            pr_info("overflow\n");
            spin_unlock(&lock);
            return -1;
        }

        pr_info("push data.\n");
        if(copy_from_user(&user_queue_data, (struct data *)arg, sizeof(struct data))){
            pr_info("error occure\n");
            spin_unlock(&lock);
            return -1;
        }
        
        kernel_queue_data.length = user_queue_data.length;
        kernel_queue_data.data = kmalloc(kernel_queue_data.length, GFP_KERNEL);

        // copy data from user mode *data
        if(copy_from_user(kernel_queue_data.data, user_queue_data.data, kernel_queue_data.length)){
            pr_info("error occure\n");
            spin_unlock(&lock);
            return -1;
        }

        queue.rear = (queue.front + queue.size) % queue.capacity;
        *(queue.buffer + queue.rear) = kernel_queue_data;
        queue.size += 1;
        pr_info("push_done front = %d, rear = %d, size = %d\n", queue.front, queue.rear, queue.size);
        break;

    case POP_DATA:

        if(queue.size <= 0){
            pr_info("underflow\n");
            spin_unlock(&lock);
            return -1;
        }

        pr_info("pop data.\n");

        struct data content = *(queue.buffer + queue.front);

        if(copy_from_user(&user_queue_data, (struct data *)arg, sizeof(struct data))){
            pr_info("error occure\n");
            spin_unlock(&lock);
            return -1;
        }
        // copy data into user space * data.
        if(copy_to_user(user_queue_data.data, content.data, user_queue_data.length)){
            pr_info("error occure\n");
            spin_unlock(&lock);
            return -1;
        }

        queue.front = (queue.front + 1) % queue.capacity;
        queue.size -= 1;
        pr_info("push_done front = %d, rear = %d, size = %d\n", queue.front, queue.rear, queue.size);
        break;

    default:
        break;
    }

    spin_unlock(&lock);
    return 0;
}

static int c_dev_open(struct inode *inode, struct file *file){
    pr_info("file open\n");
    return 0;
}

static int c_dev_release(struct inode *inode, struct file *file){
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
    spin_lock_init(&lock);
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