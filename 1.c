#include <linux/init.h> 
#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/sched.h> 
#include <linux/string.h> 
#include <linux/sched/signal.h> 
#include <linux/uaccess.h> // Include for user mode helper #include <linux/errno.h> // Include for error codes 
MODULE_LICENSE("GPL"); 
MODULE_AUTHOR("Neha N); 
MODULE_DESCRIPTION("OS"); 
MODULE_ALIAS("pesu"); 

static void print_task(struct task_struct *task, int level); 
static int __init pesu_init(void) { 
 printk(KERN_INFO "Loading our module...\n");  char *user = "user";  
 char *argv[] = { user, NULL }; 
 static char *envp[] = { "HOME=/", "TERM=linux",  "PATH=/sbin:/bin:/usr/sbin:/usr/bin",  NULL };
 int ret = call_usermodehelper(user, argv, envp,  
UMH_WAIT_PROC); 
 if (ret != 0) { 
 printk(KERN_ERR "Failed to execute user mode helper. Error  code: %d\n", ret); 
 return -EINVAL;  
 } 
 print_task(&init_task, 0); 
 printk(KERN_INFO "Our Module loaded.\n"); 
 return 0; 
} 	

static void __exit pesu_exit(void)
{ 
 printk(KERN_INFO "Module removed.\n"); 
} 
static void print_task(struct task_struct *task, int level) {  struct task_struct *child_task; 
 struct list_head *list; 
 printk(KERN_INFO "%*s Process: %s [%d]\n", level * 2, "", task- >comm, task->pid); 
 list_for_each(list, &task->thread_group) { 
 child_task = list_entry(list, struct task_struct, thread_group);  printk(KERN_INFO "%*s Thread: %s [%d]\n", (level + 1) * 2, "",  child_task->comm, child_task->pid); 
 } 
 list_for_each(list, &task->children) { 
 child_task = list_entry(list, struct task_struct, sibling);  print_task(child_task, level + 1); 
 } 
} 
module_init(pesu_init);
module_exit(pesu_exit);

