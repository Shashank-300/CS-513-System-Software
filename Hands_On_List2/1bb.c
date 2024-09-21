/*
============================================================================
Name : 1bb.c
Author : Shashank Vyas
Description : Write a C, Ansi-style program to set a interval timer in 10s and 10ms 
                a. ITIMER_VIRTUAL
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void timer_handler(int signum) {
    printf("Virtual Timer expired \nSignal received\n");
}

void main() {
    struct itimerval timer;

    signal(SIGVTALRM, timer_handler);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 10;

    setitimer(ITIMER_VIRTUAL, &timer, NULL);
    while(1);
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./1bb
Virtual Timer expired 
Signal received
*/