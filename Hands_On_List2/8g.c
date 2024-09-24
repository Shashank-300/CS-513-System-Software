/*
============================================================================
Name : 8g.c
Author : Shashank Vyas
Description :   Write a separate program using signal system call to catch `SIGPROF` (use `setitimer` system call)
Date: 20th Sep, 2024.
============================================================================
*/


#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

// Signal handler for SIGPROF
void sigprof_handler(int signum) {
    printf("Caught SIGPROF (Profiling Timer Alarm)\n");
}

int main() {
    // Register SIGPROF handler
    signal(SIGPROF, sigprof_handler);

    // Set profiling timer to go off after 2 seconds
    struct itimerval timer;
    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_PROF, &timer, NULL);

    // Infinite loop to allow the timer to trigger
    while (1);

    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./8g
Caught SIGPROF (Profiling Timer Alarm)
*/