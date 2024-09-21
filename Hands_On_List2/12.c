/*
============================================================================
Name : 12.c
Author : Shashank Vyas
Description :  Write a program to create an orphan process. Use `kill` system call to send `SIGKILL` signal to the parent process from the child process.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main() {
    pid_t pid = fork(); // Create a new process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) { 
        // Child process
        printf("Child process created with PID: %d\n", getpid());
        sleep(2);  // Give the parent time to execute

        // Send SIGKILL to parent (kill the parent process)
        printf("Child sending SIGKILL to parent process (PID: %d)\n", getppid());
        kill(getppid(), SIGKILL);

        printf("Parent killed. Child process is now orphan.\n");
        sleep(2);
        printf("Child process (PID: %d) has been adopted by 'init' (PID : %d).\n", getpid(),getppid());
    } 
    else {
        // Parent process
        printf("Parent process (PID: %d) is running.\n", getpid());
        sleep(3);
    }

    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./12
Parent process (PID: 17110) is running.
Child process created with PID: 17111
Child sending SIGKILL to parent process (PID: 17110)
Parent killed. Child process is now orphan.
Killed
shashank@ubuntu-22:~/Documents/HOL 2$ Child process (PID: 17111) has been adopted by 'init' (PID : 1648).
*/