/***************************************************************************/ /**
 * @file first_driver.c
 * @author Yogesh (thedeveloperyug@gmail.com)
 * @brief Sample kernel module
 * @version 0.1
 * @date 2024-09-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
//******************************************************************************/
 
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>


// module init function
static int __init firstDriver_init(void){
    printk(KERN_INFO "First kernel module inserted successfully");
    return 0;
}

// module exit function
static void __exit firstDriver_exit(void)
{
    printk(KERN_INFO "First kernel module removed successfully");
}



// function call for loading the kernal module
module_init(firstDriver_init);
// function call for unloading the kernal module
module_exit(firstDriver_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yogesh <thedeveloperyug@gmail.com>");
MODULE_DESCRIPTION("A simple hello world driver");
MODULE_VERSION("2:1.0");