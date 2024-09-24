/*
============================================================================
Name : 21.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program ,call fork and print the parent and child process id.
Date: 30th Aug, 2024.
============================================================================
*/

#include <sys/types.h> // Import for `fork` & `getpid` system call
#include <unistd.h>    // Import for `fork` & `getpid` system call
#include <stdio.h>     // Import for printf function

void main()
{
    int cPid, pPid;

    pPid = getpid();

    printf("Parent's PID: %d\n", pPid);

    cPid = fork();

    if (cPid != 0)
        // Parent process
        printf("Child's PID: %d\n", cPid);
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ ./21
    Parent's PID: 30731
    Child's PID: 30732
*/