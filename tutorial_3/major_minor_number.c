/***************************************************************************/
/**
 * @file major_minor_number.c
 * @author Yogesh
 * @brief Dynamic Allocation for major and minor number
 * @version 1.0
 * @copyright Copyright (c) 2024
 *
 */
//******************************************************************************/

#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/init.h>  
#include <linux/fs.h>     

dev_t dev = 0; // dev_t type to hold major and minor numbers, initialized to 0 for dynamic allocation

// Function to be called when the module is inserted
static int __init major_minor_init(void)
{
    // Dynamically allocate a major number and minor number (0) for the device
    // "first_Device_Driver" is the name of the device, 1 is the number of minor devices
    int res = alloc_chrdev_region(&dev, 0, 1, "first_Device_Driver");

    // Check if the allocation was successful
    if (res < 0)
    {
        // If allocation failed, log an error message with the error code and return it
        printk(KERN_ERR "Failed to register the device, error code: %d\n", res);
        return res; // Return the error code to indicate failure
    }

    // Log the major and minor numbers allocated for the device
    printk(KERN_INFO "Registered first_Device_Driver: Major = %d, Minor = %d\n", MAJOR(dev), MINOR(dev));
    printk(KERN_INFO "Kernel Module Inserted Successfully....");
    return 0; // Return 0 to indicate success
}

// Function to be called when the module is removed
static void __exit major_minor_exit(void)
{
    // Unregister the device and release the major and minor numbers
    unregister_chrdev_region(dev, 1);

    // Log a message indicating that the kernel module has been removed successfully
    printk(KERN_INFO "Kernel Module Removed Successfully....");
}

// Macros to specify the initialization and exit functions of the module
module_init(major_minor_init);
module_exit(major_minor_exit);

// Module metadata
MODULE_AUTHOR("thedevloperyug"); // Author of the module
MODULE_VERSION("1.0");           // Version of the module
MODULE_LICENSE("GPL");           // License under which the module is distributed (GPL)
