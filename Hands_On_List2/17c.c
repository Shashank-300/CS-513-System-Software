/*
============================================================================
Name : 17c.c
Author : Shashank Vyas
Description : Write a program to execute `ls -l | wc`. Use `fcntl`
Date: 20th Sep, 2024.
============================================================================
*/


#include <unistd.h>    // Import for `pipe``, `fork`, `execl` & `fcntl`
#include <sys/types.h> // Import `fork`
#include <fcntl.h>     // Import for `fcntl`
#include <stdio.h>     // Import for `perror` 

void main()
{
    // File descriptor used for pipe operations
    int pipefd[2];  // pipefd[0] -> read, pipefd[1] -> write
    int pipeStatus; // // Variable used to determine success of `pipe` call
    pid_t child1;

    pipeStatus = pipe(pipefd);

    if (pipeStatus == -1)
        perror("Error while creating the file!");
    else
    {
        child1 = fork();

        if (child1 == -1)
            perror("Error while forking child!");
        else if (child1 == 0)
        {
            // Child will enter this branch
            close(STDIN_FILENO);
            fcntl(pipefd[0], F_DUPFD, STDIN_FILENO); // STDIN will be reassigned to pipefdp[0]
            close(pipefd[1]);
            execl("/usr/bin/wc", "wc", NULL);
        }
        else
        {
            // Parent will enter this branch
            close(STDOUT_FILENO);
            fcntl(pipefd[1], F_DUPFD, STDOUT_FILENO); // STDOUT will be reassigned to pipefd[1]
            close(pipefd[0]);
            execl("/usr/bin/ls", "ls -l", "-l", NULL);
        }
    }
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./17c
    142    1271    7878
*/