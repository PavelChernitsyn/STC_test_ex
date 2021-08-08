#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pavel Chernitsyn");
MODULE_VERSION("0.01");
static int __init my_dummy_device_init(void) {
 printk(KERN_INFO "MY_DUMMY_DEVICE -- INIT!\n");
 return 0;
}
static void __exit my_dummy_device_exit(void) {
 printk(KERN_INFO "MY_DUMMY_DEVICE -- REMOVE!\n");
}
module_init(my_dummy_device_init);
module_exit(my_dummy_device_exit);
