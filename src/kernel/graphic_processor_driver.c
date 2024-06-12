#include <linux/device.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

/* Define memory address */
#define LW_VIRTUAL  0xFF200000
#define DATA_A      0x80
#define DATA_B      0x70

/* Define device */
#define DEVICE_NAME "gpu_driver"
#define CLASS_NAME  "gpudriver_class"

/* Define device variables */
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Graphic Processor Driver");
MODULE_VERSION("0.1");
MODULE_AUTHOR("");

/* Function to init driver */
static void __init
gpu_init() {
    printk(KERN_INFO "Graphic Processor Driver loaded\n");
}

/* Function to exit driver */
static void __exit
gpu_exit() {
    printk(KERN_INFO "Graphic Processor Driver unloaded\n");
}

module_init(gpu_init);
module_exit(gpu_exit);