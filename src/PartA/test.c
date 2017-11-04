#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>
#define __NR_list_64 326 //64 bit
static inline long mysys_syscall(void) { 
     return syscall(__NR_list_64,NULL); 
}
int main(int argc, char**argv)
{ 
    printf("Invoking 'listProcessInfo' system call");
    // long int ret_status = syscall(__NR_list_64); // 326 is the syscall number 64 bit
    long int ret_status = mysys_syscall();
    if(ret_status == 0) 
        printf("System call 'listProcessInfo' executed correctly. Use dmesg to check processInfo\n");
    else 
        printf("System call 'listProcessInfo' did not execute as expected %d\n",ret_status);
    return 0;
}