/*
============================================================================
Name : 8e.c
Author : Shashank Vyas
Description :  Write a separate program using signal system call to catch `SIGALRM` (use `setitimer` system call)
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

// Signal handler for SIGALRM
void sigalrm_handler(int signum) {
    printf("Caught SIGALRM (Timer Expired)\n");
}

int main() {
    // Register the SIGALRM signal handler
    signal(SIGALRM, sigalrm_handler);

    // Declare a timer
    struct itimerval timer;

    // Configure the timer to expire after 2 seconds
    timer.it_value.tv_sec = 2;       // First expiration (2 seconds)
    timer.it_value.tv_usec = 0;      // Microseconds part (0)
    
    // Configure the timer to reset every 0 seconds after the initial expiration (one-time timer)
    timer.it_interval.tv_sec = 0;    // Interval (0 seconds means it doesn't repeat)
    timer.it_interval.tv_usec = 0;   // Microseconds part (0)

    // Set the timer to send SIGALRM when it expires
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("Error setting timer");
        return 1;
    }

    // Pause and wait for the signal to be caught
    printf("Waiting for SIGALRM...\n");
    pause();

    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./8d
Caught SIGALRM (Alarm)
*/