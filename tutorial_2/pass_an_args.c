#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/moduleparam.h>


int value, arr_value[4];
char *name;
int cb_value=0;



module_param(value,int,S_IRUSR | S_IWUSR);   //int value
module_param(name,charp, S_IRUSR | S_IWUSR);  // String
module_param_array(arr_value, int, NULL, S_IRUSR | S_IWUSR); //Array Of integer



// Module_param_callback
int notify_param(const char* value, const struct kernel_param *kp){
    int res = param_set_int(value,kp);
    if(res==0){
        printk(KERN_INFO "New value of cb_value = %d\n ", cb_value);
        return 0;
    }
    return -1;

}

const struct kernel_param_ops my_param_ops = {
    .set = &notify_param,
    .get = &param_get_int,
};

module_param_cb(cb_value,&my_param_ops,&cb_value, S_IRUGO | S_IWUSR);


static int __init pass_an_args_init(void){
    int i;
    int size = sizeof(arr_value)/sizeof(int); 
    printk(KERN_INFO "Value = %d\n",value);
    printk(KERN_INFO "CB_Value = %d\n",cb_value);
    printk(KERN_INFO "Name  = %s  \n",name);


    for(i=0; i<size; i++){
        printk(KERN_INFO " Arr_Value[%d] = %d\n",i, arr_value[i]);
    }

    printk(KERN_INFO " kERNEL MODULE LOADED SUCCESSFULLY...\n");
    return 0;
}   



static void __exit pass_an_args_exit(void){
 printk(KERN_INFO " kERNAL MODULE Removed SUCCESSFULLY...\n");
    
}

module_init(pass_an_args_init);
module_exit(pass_an_args_exit);



MODULE_LICENSE("GPL");
MODULE_AUTHOR("thedeveloperyug");
MODULE_VERSION("1.0");