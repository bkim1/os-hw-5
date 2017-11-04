#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/time.h>

#include "timeInfo.h"

typedef struct myTime {
    int sec;
    int min;
    int hour;
    int month;
    int day;
    int year;
} myTime;


asmlinkage long sys_listTimeInfo(void **user, int size) {
    struct timeval now;
    struct tm tm_val;

    printk("Starting syscall: listTimeInfo!\n");

    do_gettimeofday(&now);
    time_to_tm(now.tv_sec, 0, &tm_val);
    
    unsigned long get_time;
    get_time = now.tv_sec;
    int tmp = get_time / 60;
    int tmp2 = tmp / 60;

    myTime t_val = { get_time % 60,
                          tmp % 60,
                          (tmp2 % 24) - 4,
                          tm_val.tm_mon + 1,
                          tm_val.tm_mday,
                          tm_val.tm_year + 1900
                        };
    
    printk("About to send to user!\n");
    printk("time: %d:%d:%d\n", t_val.hour, t_val.min, t_val.sec);
    printk("date: %d/%d/%d\n", t_val.month, t_val.day, t_val.year);
    
    int ret = copy_to_user(user, (void *)&t_val, sizeof(struct myTime));
    if (ret != 0) {
        printk("Error! %d\n", ret);
    }
    return 0;
}