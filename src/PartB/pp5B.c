#include <linux/sched.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>



void dfs(struct task_struct *task) {
    struct task_struct *child;
    struct list_head *list;

    list_for_each(list, &task->children) {
        child = list_entry(list, struct task_struct, sibling);
        dfs(child);

        printk("Process: %s\n", child->comm);
        printk("State: %ld\n", (long)child->state);
        printk("PID: %ld\n\n", (long)task_pid_nr(child));
    }
}

// Called when module is loaded/initialized
int pp5B_init(void) {
    printk("Loading module...\n");
    dfs(&init_task);

    return 0;
}


void pp5B_exit(void) {
    printk("Removing module...\n");
}

module_init(pp5B_init);
module_exit(pp5B_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PP5 Part B");
MODULE_AUTHOR("BKIM");