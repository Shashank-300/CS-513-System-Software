/*
============================================================================
Name : 24.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to create an orphan process.
Date: 30th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0) 
    {
        perror("Fork failed");
        exit(0);
    } 
    else if (pid > 0) 
    {
        // Parent process
        printf("Parent process PID : %d \n",getpid());
        exit(0);
    } 
    else 
    {
        // Child process
        sleep(5);  
        printf("Orphan child process is adopted by init PID : %d \n", getpid());
    }
    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ ./24
    Parent process PID : 10003 
    shashank@ubuntu-22:~/Documents/SYS$ Orphan child process is adopted by init PID : 10004 
*/