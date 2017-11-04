#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>


typedef struct myTime {
    int sec;
    int min;
    int hour;
    int month;
    int day;
    int year;
} myTime;

int main() {
    myTime **from_kernel = malloc(sizeof(struct myTime *));
    long int ret_status = syscall(327, (void *)from_kernel, sizeof(struct myTime *));

    if(ret_status == 0) {
        myTime *t_val = (struct myTime *)from_kernel;
        printf("time: %02d:%02d:%02d\n", t_val->hour, t_val->min, t_val->sec);
        printf("day: %02d\n", t_val->day);
        printf("month: %02d\n", t_val->month);
        printf("year: %d\n", t_val->year);
    }
    else 
        printf("System call 'listTimeInfo' did not execute as expected %d\n",ret_status);

    return 0;
}