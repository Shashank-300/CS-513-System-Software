/*
============================================================================
Name : 17a.c
Author : Shashank Vyas
Description : Write a program to execute `ls -l | wc`. Use `dup`
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    // File descriptor used for pipe operations
    int pipefd[2];  // pipefd[0] -> read, pipefd[1] -> write
    int pipeStatus; // // Variable used to determine success of `pipe` call
    pid_t childPid;

    pipeStatus = pipe(pipefd);

    if (pipeStatus == -1)
        perror("Error while creating the file!");
    else
    {
        childPid = fork();

        if (childPid == -1)
            perror("Error while forking child!");
        else if (childPid == 0)
        {
            // Child will enter this branch
            close(STDIN_FILENO);
            dup(pipefd[0]); // STDIN will be reassigned to pipefdp[0]
            close(pipefd[1]);
            execl("/usr/bin/wc", "wc", NULL);
        }
        else
        {
            // Parent will enter this branch
            close(STDOUT_FILENO);
            dup(pipefd[1]); // STDOUT will be reassigned to pipefd[1]
            close(pipefd[0]);
            execl("/usr/bin/ls", "ls -l", "-l", NULL);
        }
    }
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./17a
    142    1271    7878
*/