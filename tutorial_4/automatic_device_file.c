#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/device.h>

dev_t dev = 0;                  // Device number
static struct class *dev_class; // Device class

// Module initialization function
static int __init auto_device_init(void)
{
    // Allocate a device number
    if ((alloc_chrdev_region(&dev, 0, 1, "new_device")) < 0)
    {
        pr_err("Failed to allocate device number\n");
        return -1;
    }
    printk(KERN_INFO "Major = %d Minor = %d", MAJOR(dev), MINOR(dev));

    // Create device class
    dev_class = class_create(THIS_MODULE, "device_class");
    if (IS_ERR(dev_class))
    {
        pr_err("Failed to register device class\n");
        goto r_class;
    }

    // Create the device
    if ((device_create(dev_class, NULL, dev, NULL, "new_device")) < 0)
    {
        pr_err("Failed to create device\n");
        goto r_device;
    }
    printk(KERN_INFO "Device created\n");
    return 0;

    // Error handling: cleanup resources on failure
r_device:
    class_destroy(dev_class);
r_class:
    unregister_chrdev_region(dev, 1);
    return -1;
}

// Module exit function
static void __exit auto_device_exit(void)
{
    device_destroy(dev_class, dev);   // Remove device
    class_destroy(dev_class);         // Destroy class
    unregister_chrdev_region(dev, 1); // Release device number
    printk(KERN_INFO "Device removed\n");
}

module_init(auto_device_init); // Register init function
module_exit(auto_device_exit); // Register exit function

MODULE_LICENSE("GPL");
MODULE_AUTHOR("thedeveloperyug@gmail.com");
MODULE_VERSION("1.0");
