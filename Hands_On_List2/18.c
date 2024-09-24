/*
============================================================================
Name : 18.c
Author : Shashank Vyas
Description : Write a program to find out total number of directories on the `pwd`. Execute `ls -l | grep ^d | wc`. Use only `dup2`.
Date: 20th Sep, 2024.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];  // Pipe to communicate between parent and child

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the child process to run `ls -l`
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process (to run `ls -l`)
        // Redirect stdout to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);

        // Close the unused file descriptors
        close(pipefd[0]);  // Close read end of the pipe in the child
        close(pipefd[1]);  // Close the original write end after duplication

        // Execute `ls -l`
        execl("/bin/ls", "ls", "-l", (char *)NULL);

        // If execl fails
        perror("execl ls");
        exit(EXIT_FAILURE);
    } else {  // Parent process
        // Close the write end of the pipe
        close(pipefd[1]);

        // Redirect stdin to the read end of the pipe for the next commands
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        // Execute `grep ^d | wc` in a combined fashion
        execlp("sh", "sh", "-c", "grep ^d | wc -l", (char *)NULL);

        // If execlp fails
        perror("execlp grep wc");
        exit(EXIT_FAILURE);
    }

    // Wait for the child process to complete
    wait(NULL);
    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./18
2
*/