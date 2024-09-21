/*
============================================================================
Name : 8a.c
Author : Shashank Vyas
Description :  Write a separate program using signal system call to catch `SIGSEGV`
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

// Signal handler for SIGSEGV
void sigsegv_handler(int signum) {
    printf("Caught SIGSEGV (Segmentation Fault)\n");
    exit(1);
}

int main() {
    // Register SIGSEGV handler
    signal(SIGSEGV, sigsegv_handler);

    // Simulate a segmentation fault by dereferencing a NULL pointer
    int *ptr = NULL;
    *ptr = 42;

    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./8a
Caught SIGSEGV (Segmentation Fault)
*/