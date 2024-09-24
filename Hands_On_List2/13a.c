/*
============================================================================
Name : 13a.c
Author : Shashank Vyas
Description :   Write two programs: first program is waiting to catch `SIGSTOP` signal, the second program will send the signal (using `kill` system call). Find out whether the first  program is able to catch the signal or not.
Date: 20th Sep, 2024.
============================================================================
*/


#include <stdio.h>
#include <signal.h>
#include <unistd.h>


int main() {
    printf("Process PID: %d\n", getpid());

    // Attempt to catch SIGSTOP (which will fail)
    if (signal(SIGSTOP, SIG_IGN) == SIG_ERR) {
        printf("Cannot catch SIGSTOP, it's non-catchable\n");
    }

    // Infinite loop waiting for signals
    while (1) {
        pause();  // Wait for a signal to arrive
    }

    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./13a
Process PID: 17978
Cannot catch SIGSTOP, it's non-catchable
     
[11]+  Stopped                 ./13a
*/