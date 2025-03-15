#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>


static int start_module(void){
    pr_info("start module ....\n");
    return 0;
}

static void exit_module(void){
    pr_info("exit module ....\n");
}

module_init(start_module);
module_exit(exit_module);

MODULE_LICENSE("GPL");