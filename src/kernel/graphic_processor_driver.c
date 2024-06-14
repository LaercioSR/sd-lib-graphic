#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

/* Define memory address */
#define WBR         0x00
#define WSM         0x01
#define WBM         0x02
#define DP          0x03
#define DATA_A      0x80
#define DATA_B      0x70
#define LW_VIRTUAL  0xFF200000

/* Define device */
#define DEVICE_NAME "gpu_driver"
#define CLASS_NAME  "gpudriver_class"

/* Define device variables */
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Graphic Processor Driver");
MODULE_VERSION("0.1");
MODULE_AUTHOR("");

/* Define device variables */
static int major_number;
static struct class* gpu_class = NULL;
static struct device* gpu_device = NULL;
static struct cdev gpu_cdev;

volatile int* START_ptr;
volatile int* DATA_A_ptr;
volatile int* DATA_B_ptr;
void __iomem* LW_virtual;

/* Define device functions */
static int device_open(struct inode* inodep, struct file* filep);
static int device_release(struct inode* inodep, struct file* filep);
static ssize_t device_write(struct file* filep, const char* buffer, size_t len, loff_t* offset);

static struct file_operations fops = {
    .open = device_open,
    .release = device_release,
    .write = device_write,
};

/**
 * @brief Function to close device
 * 
 * @param code define which device will be closed
 *             1 - All Devices
 *             2 - Virtual Address
 *             3 - Device
 *             4 - Class
 *             5 - Major Number
 * 
 * @return int
 */
static int
close_device(int code) {
    switch (code) {
        case 1:
        case 2: iounmap(LW_virtual);
        case 3: device_destroy(gpu_class, MKDEV(major_number, 0));
        case 4: class_unregister(gpu_class); class_destroy(gpu_class);
        case 5: unregister_chrdev(major_number, DEVICE_NAME);
        default: break;
    }
    printk(KERN_INFO "Graphic Processor Driver closed\n");
    return 0;
}

/**
 * @brief WBR (Write in Bank of Registers) - Write in bank of register to change background color 
 */
void
wbr_background() {}

/**
 * @brief WBR (Write in Bank of Registers) - Write in bank of register to configure sprite 
 */
void
wbr_sprite() {}

/**
 * @brief WSM - Store or modify content in sprite memory 
 */
void
write_sprite_memory() {}

/**
 * @brief WBM - Store or modify content in background memory 
 */
void
write_background_memory() {}

/**
 * @brief DP - Modify content of coprocessor 
 */
void
define_polygon() {}

/**
 * @brief Function to init driver 
 */
static void __init
gpu_init() {
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "Graphic Processor Driver failed to register a major number\n");
        return major_number;
    }
    printk(KERN_INFO "Graphic Processor Driver registered correctly with major number %d\n", major_number);

    gpu_class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(gpu_class)) {
        close_device(5);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(gpu_class);
    }

    gpu_device = device_create(gpu_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
    if (IS_ERR(gpu_device)) {
        close_device(4);
        printk(KERN_ALERT "Failed to create the device\n");
        return PTR_ERR(gpu_device);
    }

    LW_virtual = ioremap(LW_VIRTUAL, 0x1000);
    if (LW_virtual == NULL) {
        close_device(4);
        printk(KERN_ALERT "Mapping virtual address failed\n");
        return -ENOMEM;
    }

    DATA_A_PTR = (volatile int*)(LW_virtual + DATA_A);
    DATA_B_PTR = (volatile int*)(LW_virtual + DATA_B);
    START_PTR = (volatile int*)(LW_virtual + START);

    printk(KERN_INFO "Graphic Processor Driver loaded\n");
}

/**
 * @brief Function to exit driver 
 */
static void __exit
gpu_exit() {
    close_device(1);
    printk(KERN_INFO "Graphic Processor Driver unloaded\n");
}

module_init(gpu_init);
module_exit(gpu_exit);