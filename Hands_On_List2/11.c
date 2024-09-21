/*
============================================================================
Name : 11.c
Author : Shashank Vyas
Description : Write a program to ignore a `SIGINT` signal then reset the default action of the `SIGINT` signal - use `sigaction` system call.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Custom handler to catch SIGINT (this won't be used in this case)
void sigint_handler(int signum) {
    printf("\nCaught SIGINT (Signal %d)\n", signum);
}

int main() {
    struct sigaction sig_ignore, sig_default;

    // Set up the sigaction struct to ignore SIGINT
    sig_ignore.sa_handler = SIG_IGN;  // Ignore SIGINT
    sig_ignore.sa_flags = 0;
    sigemptyset(&sig_ignore.sa_mask); // No signals are blocked during handling

    // Apply the ignore action for SIGINT
    if (sigaction(SIGINT, &sig_ignore, NULL) == -1) {
        perror("Error ignoring SIGINT");
        return 1;
    }

    printf("SIGINT will be ignored for 5 seconds. Try pressing Ctrl+C...\n");
    sleep(5); // Sleep for 5 seconds to allow user to press Ctrl+C

    // Set up the sigaction struct to reset the default action of SIGINT
    sig_default.sa_handler = SIG_DFL;  // Reset to default action
    sig_default.sa_flags = 0;
    sigemptyset(&sig_default.sa_mask); // No signals are blocked during handling

    // Apply the default action for SIGINT
    if (sigaction(SIGINT, &sig_default, NULL) == -1) {
        perror("Error resetting SIGINT to default");
        return 1;
    }

    printf("SIGINT behavior reset to default. Now press Ctrl+C to terminate.\n");
    sleep(5); // Sleep again for user to press Ctrl+C

    printf("Program finished without receiving SIGINT.\n");
    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./11
SIGINT will be ignored for 5 seconds. Try pressing Ctrl+C...
SIGINT behavior reset to default. Now press Ctrl+C to terminate.
^C
*/