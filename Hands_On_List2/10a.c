/*
============================================================================
Name : 10a.c
Author : Shashank Vyas
Description :  Write a separate program using sigaction system call to catch `SIGSEGV` signal
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

// Custom handler for SIGSEGV
void sigsegv_handler(int signum) {
    printf("Caught SIGSEGV (Segmentation Fault)\n");
    exit(EXIT_FAILURE);  // Exit after catching the signal
}

int main() {
    struct sigaction sig;

    // Set up the sigaction struct
    sig.sa_handler = sigsegv_handler; // Assign the handler function
    sig.sa_flags = 0;                 // No special flags
    sigemptyset(&sig.sa_mask);         // Clear the signal mask

    // Set up the SIGSEGV signal handler
    if (sigaction(SIGSEGV, &sig, NULL) == -1) {
        perror("Error setting up sigaction");
        return 1;
    }

    // Force a segmentation fault by accessing invalid memory
    printf("Generating segmentation fault...\n");
    int *p = NULL;  // Null pointer
    *p = 42;        // Dereferencing the null pointer causes SIGSEGV

    // The program will not reach here since a SIGSEGV will occur above
    printf("This line will never be printed.\n");

    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./10a
Generating segmentation fault...
Caught SIGSEGV (Segmentation Fault)
*/
