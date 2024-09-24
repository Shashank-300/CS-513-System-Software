/*
============================================================================
Name : 10c.c
Author : Shashank Vyas
Description :   Write a separate program using sigaction system call to catch `SIGFPE` signal
Date: 20th Sep, 2024.
============================================================================
*/


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

// Custom handler for SIGFPE (Floating Point Exception)
void sigfpe_handler(int signum) {
    printf("Caught SIGFPE (Signal %d): Floating Point Exception (e.g., division by zero)\n", signum);
    exit(EXIT_FAILURE);  // Exit the program after catching the signal
}

int main() {
    struct sigaction sig;

    // Set up the sigaction struct
    sig.sa_handler = sigfpe_handler;  // Assign the handler function
    sig.sa_flags = 0;                 // No special flags
    sigemptyset(&sig.sa_mask);        // Clear the signal mask

    // Set up the SIGFPE signal handler
    if (sigaction(SIGFPE, &sig, NULL) == -1) {
        perror("Error setting up sigaction for SIGFPE");
        return 1;
    }

    // Force a floating-point exception by dividing by zero
    int x = 5, y = 0;
    printf("Forcing division by zero...\n");
    int result = x / y;  // This will raise SIGFPE

    // The program will not reach here due to the SIGFPE being raised
    printf("Result of division: %d\n", result);

    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./10c
Forcing division by zero...
Caught SIGFPE (Signal 8): Floating Point Exception (e.g., division by zero)
*/