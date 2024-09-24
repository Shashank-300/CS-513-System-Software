/*
============================================================================
Name : 29.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to get the scheduling policy and modify the scheduling policy (SCHED_FIFO, SCHED_RR).
Date: 30th Aug, 2024.
============================================================================
*/

#include <sched.h>      // Import for `sched_getscheduler`, `sched_setscheduler`
#include <sys/types.h>  // Import for `getpid`
#include <unistd.h>     // Import for `getpid`
#include <stdio.h>      // Import for `perror`, `printf`

void print_schedulepolicy(int policy) {
    switch (policy) {
        case SCHED_FIFO:
            printf("Current policy is FIFO\n");
            break;
        case SCHED_RR:
            printf("Current policy is RR\n");
            break;
        case SCHED_OTHER:
            printf("Current policy is OTHER\n");
            break;
        default:
            printf("Unknown policy\n");
    }
}

int main() {
    int policy;
    pid_t pid;
    pid = getpid();

    policy = sched_getscheduler(pid);

    print_schedulepolicy(policy);

    struct sched_param priority;
    priority.sched_priority = 15; 
    switch (policy) {
        case SCHED_FIFO:
            printf("Switching to RR policy\n");
            if (sched_setscheduler(pid, SCHED_RR, &priority) == -1) {
                perror("Error while setting RR policy");
            }
            break;
        case SCHED_RR:
            printf("Switching to FIFO policy\n");
            if (sched_setscheduler(pid, SCHED_FIFO, &priority) == -1) {
                perror("Error while setting FIFO policy");
            }
            break;
        case SCHED_OTHER:
            printf("Switching to RR policy\n");
            if (sched_setscheduler(pid, SCHED_RR, &priority) == -1) {
                perror("Error while setting RR policy");
            }
            break;
        default:
            printf("Unknown policy\n");
        }

    policy = sched_getscheduler(pid);
    if (policy == -1) {
        perror("Error while getting new policy");
        return 1;
    }

    print_schedulepolicy(policy);
    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ sudo ./29
    [sudo] password for shashank: 
    Current policy is OTHER
    Switching to RR policy
    Current policy is RR
*/