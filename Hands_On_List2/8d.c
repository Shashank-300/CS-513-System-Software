/*
============================================================================
Name : 8d.c
Author : Shashank Vyas
Description :  Write a separate program using signal system call to catch `SIGFPE`
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Signal handler for SIGALRM
void sigalrm_handler(int signum) {
    printf("Caught SIGALRM (Alarm)\n");
}

int main() {
    // Register SIGALRM handler
    signal(SIGALRM, sigalrm_handler);

    // Trigger SIGALRM after 3 seconds
    alarm(3);

    // Pause and wait for the signal
    pause();

    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./8d
Caught SIGALRM (Alarm)
*/