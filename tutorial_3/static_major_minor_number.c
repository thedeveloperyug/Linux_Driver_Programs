/***************************************************************************/
/**
 * @file major_minor_number.c
 * @author Yogesh
 * @brief Static Allocation for major and minor number
 * @version 1.0
 * @copyright Copyright (c) 2024
 *
 */
//******************************************************************************/

#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include <linux/fs.h>

//creating the dev with our custom major and minor number
dev_t dev = MKDEV(201, 0);

/*
** Module Init function
*/
static int __init static_major_minor_init(void)
{
    register_chrdev_region(dev, 1, "Static_Driver");
    printk(KERN_INFO "Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
    printk(KERN_INFO "Kernel Module Inserted Successfully...\n");
    return 0;
}

/*
** Module exit function
*/
static void __exit static_major_minor_exit(void)
{
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "Kernel Module Removed Successfully...\n");
}
 
module_init(static_major_minor_init);
module_exit(static_major_minor_exit);
 

// Module metadata
MODULE_AUTHOR("thedevloperyug"); // Author of the module
MODULE_VERSION("1.0");           // Version of the module
MODULE_LICENSE("GPL");           // License under which the module is distributed (GPL)
