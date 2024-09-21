/*
============================================================================
Name : 1cb.c
Author : Shashank Vyas
Description : Write a C, Ansi-style program to set a interval timer in 10s and 10ms 
                c. ITIMER_PROF
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void timer_handler(int sig) {
    printf("SIGPROF Timer expired \nSignal received\n");
}

void main() {
    struct itimerval timer;

    signal(SIGPROF, timer_handler);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 10;

    setitimer(ITIMER_PROF, &timer, NULL);
    while(1);
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./1cb
SIGPROF Timer expired 
Signal received
*/