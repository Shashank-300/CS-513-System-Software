/*
============================================================================
Name : 20.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to find out the priority of your running program. Modify the priority with nice command.
Date: 30th Aug, 2024.
============================================================================
*/

#include <stdio.h>      // For printf()
#include <unistd.h>     // For getpid() and nice()
#include <sys/types.h>  // For pid_t
#include <sys/time.h>   // For getpriority()
#include <sys/resource.h> // For getpriority()

int main() {
    pid_t pid = getpid(); // Get the current process ID
    int prior;

    // Get the current priority (niceness) of the process
    prior = getpriority(PRIO_PROCESS, pid);

    printf("Current priority of process with pid %d: %d\n", pid, prior);

    // Set a new priority using nice()
    prior=nice(10);
    printf("New priority of process with pid %d: %d\n", pid, prior);

    return 0;
}
/*
    shashank@ubuntu-22:~/Documents/SYS$ ./20
    Current priority of process with pid 30875: 0
    New priority of process with pid 30875: 10
*/