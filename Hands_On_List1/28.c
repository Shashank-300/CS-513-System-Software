/*
============================================================================
Name : 28.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to get maximum and minimum real time priority.
Date: 30th Aug, 2024.
============================================================================
*/

#include <stdio.h>    // For `printf`
#include <sched.h>    // For `sched_get_priority_max`, `sched_get_priority_min`
#include <stdlib.h>   // For `exit`

int main() {
    int max_prior, min_prior;

    // maximum real-time priority
    max_prior = sched_get_priority_max(SCHED_FIFO);
    if (max_prior == -1) {
        perror("Error !");
        exit(0);
    }

    // minimum real-time priority
    min_prior = sched_get_priority_min(SCHED_FIFO);
    if (min_prior == -1) {
        perror("Error !");
        exit(0);
    }
    printf("Maximum real-time priority: %d\n", max_prior);
    printf("Minimum real-time priority: %d\n", min_prior);

    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ ./28
    Maximum real-time priority: 99
    Minimum real-time priority: 1
*/