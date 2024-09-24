/*
============================================================================
Name : 25.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to create three child processes. The parent should wait for a particular child (use `waitpid` system call).
Date: 30th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3;
    pid_t childpid;
    
    // Create the first child process
    pid1 = fork();
    if (pid1 == 0) {
        printf("First child process (PID: %d) created.\n", getpid());
        sleep(2);  
        exit(0);   
    }

    //Second child 
    pid2 = fork();
    if (pid2 == 0) {
        printf("Second child process (PID: %d) created.\n", getpid());
        sleep(4);  
        exit(0);   
    }

    //Third child 
    pid3 = fork();
    if (pid3 == 0) {
        printf("Third child process (PID: %d) created.\n", getpid());
        sleep(6);
        exit(0);   
    }

    // Parent process waits for a particular child
    childpid = pid2;  // Test wait for the second child
    waitpid(childpid, NULL, 0);
    printf("Parent process waited for child with PID: %d.\n", childpid);
    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ ./25
    First child process (PID: 5304) created.
    Third child process (PID: 5306) created.
    Second child process (PID: 5305) created.
    Parent process waited for child with PID: 5305.
*/