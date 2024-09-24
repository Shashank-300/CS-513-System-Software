/*
============================================================================
Name : 8f.c
Author : Shashank Vyas
Description :  Write a separate program using signal system call to catch `SIGVTALRM` (use `setitimer` system call)
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

// Signal handler for SIGVTALRM
void sigvtalrm_handler(int signum) {
    printf("Caught SIGVTALRM (Virtual Timer Expired)\n");
}

int main() {
    // Register the SIGVTALRM signal handler
    signal(SIGVTALRM, sigvtalrm_handler);

    // Declare a timer
    struct itimerval timer;

    // Configure the timer to expire after 2 seconds of CPU time
    timer.it_value.tv_sec = 2;       // First expiration (2 seconds of CPU time)
    timer.it_value.tv_usec = 0;      // Microseconds part (0)

    // Configure the timer to not reset (non-repeating timer)
    timer.it_interval.tv_sec = 0;    // Interval (0 means no repetition)
    timer.it_interval.tv_usec = 0;   // Microseconds part (0)

    // Set the virtual timer to send SIGVTALRM when it expires
    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("Error setting timer");
        return 1;
    }

    // Simulate some CPU-bound work to trigger the timer
     // Catch the SIGALRM signal
    int signalStatus = signal(SIGVTALRM, sigvtalrm_handler);
    if (signalStatus == SIG_ERR)
        perror("Error while catching signal!");
    else
        while (1);

    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./8f
Caught SIGVTALRM (Virtual Timer Expired)
*/