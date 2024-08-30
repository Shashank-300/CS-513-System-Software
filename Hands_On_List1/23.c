/*
============================================================================
Name : 23.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program,to create a Zombie state of the running program.
Date: 30th Aug, 2024.
============================================================================
*/

#include <stdio.h>      // Import for `printf` function for output
#include <stdlib.h>     // Import for `exit` function for terminating a process
#include <unistd.h>     // Import for `fork`, `getpid`, and `sleep` functions
#include <sys/types.h>  // Import for pid_t
#include <sys/wait.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid == 0) {
        //Child process
        printf("Child process PID: %d \n", getpid());
        exit(EXIT_SUCCESS);  // Terminate child process
    } 
    else {
        //Parent process
        printf("Parent process PID: %d \n", getpid());    
        sleep(30);
        printf("Parent process exit.\n");
    }

    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ ./23
    Parent process PID: 12941 
    Child process PID: 12942 

    shashank@ubuntu-22:~/Documents/SYS$ ps aux | grep Z
    USER         PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
    shashank   12942  0.0  0.0      0     0 pts/0    Z+   11:12   0:00 [23] <defunct>
*/
