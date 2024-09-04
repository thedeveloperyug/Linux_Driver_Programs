/***************************************************************************/ /**
 * @file pass_an_args.c
 * @author Yogesh (thedeveloperyug@gmail.com)
 * @brief passing arguments to the function by cmd_line 
 * @version 1.0
 * @copyright Copyright (c) 2024
 * 
 */
//******************************************************************************/



#include <linux/init.h>       
#include <linux/module.h>      
#include <linux/kernel.h>    
#include <linux/moduleparam.h> 

// Declare global module parameters
int value, arr_value[4]; // Integer and an array of integers
char *name;              // String for storing a name
int cb_value = 0;        // Integer parameter with a default value

// Define the parameters for the module

// Module parameter for an integer 'value' with read and write permissions for the user
module_param(value, int, S_IRUSR | S_IWUSR); // 'S_IRUSR' for read permission, 'S_IWUSR' for write permission

// Module parameter for a string 'name' with read and write permissions for the user
module_param(name, charp, S_IRUSR | S_IWUSR); // 'charp' type for string; 'S_IRUSR' and 'S_IWUSR' for read and write

// Module parameter for an array of integers 'arr_value' with read and write permissions for the user
module_param_array(arr_value, int, NULL, S_IRUSR | S_IWUSR); // 'NULL' indicates no maximum number of elements; 'S_IRUSR' and 'S_IWUSR' for read and write

// Callback function for handling changes to 'cb_value'
int notify_param(const char *value, const struct kernel_param *kp)
{
    int res = param_set_int(value, kp); // Set the parameter using the helper function for integers
    if (res == 0)
    {
        printk(KERN_INFO "New value of cb_value = %d\n", cb_value); // Log the new value
        return 0;                                                   // Success
    }
    return -1; // Failure
}

// Define operations for getting and setting the parameter
const struct kernel_param_ops my_param_ops = {
    .set = &notify_param,  // Use our custom setter function
    .get = &param_get_int, // Use the standard getter function for integers
};

// Register the callback function for 'cb_value' parameter
module_param_cb(cb_value, &my_param_ops, &cb_value, S_IRUGO | S_IWUSR); // 'S_IRUGO' for read permission for all users; 'S_IWUSR' for write permission for the user

// Initialization function for the module
static int __init pass_an_args_init(void)
{
    int i;
    int size = sizeof(arr_value) / sizeof(int);

    // Log the values of the module parameters
    printk(KERN_INFO "Value = %d\n", value);       
    printk(KERN_INFO "CB_Value = %d\n", cb_value); 
    printk(KERN_INFO "Name = %s\n", name);      

    // Print the elements of the integer array
    for (i = 0; i < size; i++)
    {
        printk(KERN_INFO "Arr_Value[%d] = %d\n", i, arr_value[i]); // Print each element in the array
    }

    // Log that the module has been loaded successfully
    printk(KERN_INFO "KERNEL MODULE LOADED SUCCESSFULLY...\n");
    return 0; 
}

// Cleanup function for the module
static void __exit pass_an_args_exit(void)
{
    // Log that the module has been removed successfully
    printk(KERN_INFO "KERNEL MODULE REMOVED SUCCESSFULLY...\n");
}

// Register the initialization and cleanup functions
module_init(pass_an_args_init); // Register the initialization function
module_exit(pass_an_args_exit); // Register the cleanup function

// Define module information
MODULE_LICENSE("GPL");           
MODULE_AUTHOR("thedeveloperyug"); 
MODULE_VERSION("1.0");          
