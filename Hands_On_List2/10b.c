/*
============================================================================
Name : 10b.c
Author : Shashank Vyas
Description :  Write a separate program using sigaction system call to catch `SIGINT` signal
Date: 20th Sep, 2024.
============================================================================
*/


#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// Custom handler for SIGINT
void sigint_handler(int signum) {
    printf("\nCaught SIGINT (Signal %d). You pressed Ctrl+C!\n", signum);
    exit(1);
}

int main() {
    struct sigaction sig;
    sig.sa_handler = sigint_handler;  
    sig.sa_flags = 0;                 // No special flags
    sigemptyset(&sig.sa_mask);        // Clear the signal mask

    // Set up the SIGINT signal handler using sigaction
    if (sigaction(SIGINT, &sig, NULL) == -1) {
        perror("Error setting up sigaction for SIGINT");
        return 1;
    }

    // Infinite loop to keep the program running, waiting for Ctrl+C
    printf("Press Ctrl+C to trigger SIGINT (signal).\n");
    while (1) {
        printf("Running... (press Ctrl+C to catch SIGINT)\n");
        sleep(2);
    }

    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./10b
Press Ctrl+C to trigger SIGINT (signal).
Running... (press Ctrl+C to catch SIGINT)
Running... (press Ctrl+C to catch SIGINT)
Running... (press Ctrl+C to catch SIGINT)
^C
Caught SIGINT (Signal 2). You pressed Ctrl+C!
*/