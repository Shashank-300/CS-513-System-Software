/*
============================================================================
Name : 13b.c
Author : Shashank Vyas
Description : Write two programs: first program is waiting to catch `SIGSTOP` signal, the second program will send the signal (using `kill` system call). Find out whether the first  program is able to catch the signal or not.
Date: 20th Sep, 2024.
============================================================================
*/


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    int pid = atoi(argv[1]);

    // Sending SIGSTOP signal to the process
    kill(pid, SIGSTOP);
    printf("SIGSTOP sent to process %d\n", pid);

    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./13b 17978
SIGSTOP sent to process 17978
*/