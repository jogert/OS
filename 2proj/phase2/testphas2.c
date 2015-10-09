/* Ian J & Derek M */

#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "pinfo.h"

// These values MUST match the unistd_32.h modifications:

#define __NR_cs3013_syscall1 355 
#define __NR_cs3013_syscall2 356
#define __NR_cs3013_syscall3 357



long testCall1 ( void) {
        return (long) syscall(__NR_cs3013_syscall1);
}

long testCall2 (struct processinfo* info) {
        return (long) syscall(__NR_cs3013_syscall2, info);
}

long testCall3 ( void) {
        return (long) syscall(__NR_cs3013_syscall3);
}


/* Print Process Stats */
int main(){
    struct processinfo* info = (struct processinfo*) malloc(sizeof(struct processinfo));
    int pid = fork();
    int status;    
    
    if (pid !=0){
        printf("\tcs3013_syscall2: %ld\n", testCall2(info));
        printf("\t\tState          : %ld\n", info->state);
        printf("\t\tPid            : %d\n", info->pid);
        printf("\t\tParent  Pid    : %d\n", info->parent_pid);
        printf("\t\tYougest Kid Pid: %d\n", info->youngest_child);
        printf("\t\tYounger Sib Pid: %d\n", info->younger_sibling);
        printf("\t\tOlder   Sib Pid: %d\n", info->older_sibling);
        printf("\t\tUid            : %d\n\n", info->uid);
        printf("\tTimes:\n");
        printf("\t\tStart     : %lld\n", info->start_time);
        printf("\t\tUser      : %lld\n", info->user_time);
        printf("\t\tSystem    : %lld\n", info->sys_time);
        printf("\t\tKid User  : %lld\n", info->cutime);
        printf("\t\tKid system: %lld\n", info->cstime);
        waitpid(pid, &status, 0);
    }
    free(info);
    return 0;

}
