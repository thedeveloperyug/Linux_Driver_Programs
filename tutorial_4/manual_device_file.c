/***************************************************************************/ /**
 * @file pass_an_args.c
 * @author Yogesh (thedeveloperyug@gmail.com)
 * @brief creating device file manually 
 * @version 1.0
 * @copyright Copyright (c) 2024
 * 
 */
//******************************************************************************/
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

dev_t dev = 0; // Variable to store the device number

// Module initialization function
static int __init manual_device_init(void)
{
    // Allocate a device number
    if ((alloc_chrdev_region(&dev, 0, 1, "manual_device_driver")) < 0)
    {
        printk(KERN_ALERT "Failed to allocate device number\n");
        return -1;
    }
    printk(KERN_INFO "Device number allocated\n");
    return 0;
}

// Module exit function
static void __exit manual_device_exit(void)
{
    // Release the allocated device number
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "Device number unregistered\n");
}

module_init(manual_device_init); // Register init function
module_exit(manual_device_exit); // Register exit function

MODULE_LICENSE("GPL");
MODULE_AUTHOR("thedeveloperyug@gmail.com");
MODULE_VERSION("1.0");

/* For creating manual_device_file:

1. Build the driver by using Makefile (sudo make)

2. Load the driver using sudo insmod
    Check the device file using ls -l /dev/. By this time device file is not created for your driver.
3. Create a device file using mknod and then check using ls -l /dev/.

4. linux@thedeveloperyug:/home/driver/driver$sudo mknod -m 666 /dev/manual_device c 246 0
5 . linux@thedeveloperyug:/home/driver/driver$ ls -l /dev/ | grep "manual_device"
    crw-rw-rw-  1  root root  246, 0  Aug 15  13:53  manual_device
    Now our device file has been created and registered with a major number and a minor number.

6. Unload the driver using sudo rmmod

*/