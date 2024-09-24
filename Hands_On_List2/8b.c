/*
============================================================================
Name : 8b.c
Author : Shashank Vyas
Description :  Write a separate program using signal system call to catch `SIGINT`
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>

// Signal handler for SIGINT
void sigint_handler(int signum) {
    printf("Caught SIGINT (Interrupt)\n");
}

int main() {
    // Register SIGINT handler
    signal(SIGINT, sigint_handler);

    // Wait for Ctrl+C (SIGINT)
    printf("Press Ctrl+C to trigger SIGINT...\n");
    while (1);  // Infinite loop to keep the program running

    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/HOL 2$ ./8b
    Press Ctrl+C to trigger SIGINT...
    ^CCaught SIGINT (Interrupt)
    ^CCaught SIGINT (Interrupt)
    ^CCaught SIGINT (Interrupt)
    ^Z
    [1]+  Stopped                 ./8b
*/