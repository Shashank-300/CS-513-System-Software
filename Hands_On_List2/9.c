/*
============================================================================
Name : 9.c
Author : Shashank Vyas
Description :  Write a program to ignore a `SIGINT` signal then reset the default action of the `SIGINT` signal - Use `signal` system call.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    // Initially, ignore the SIGINT signal
    signal(SIGINT, SIG_IGN);
    printf("SIGINT signal is currently ignored. Press Ctrl+C to test.\n");

    sleep(5);

    // After 5 seconds, reseting SIGINT to its default action
    printf("Now resetting SIGINT to default behavior...\n");
    signal(SIGINT, SIG_DFL);

    // Sleep for another 5 seconds, during which SIGINT can reset to default
    printf("Press Ctrl+C now, and it will reset the behavior.\n");
    sleep(5);

    printf("Program finished.\n");
    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./9
SIGINT signal is currently ignored. Press Ctrl+C to test.
^C^C
Now resetting SIGINT to default behavior...
Press Ctrl+C now, and it will reset the behavior.
^C
*/