/*
============================================================================
Name : 17b.c
Author : Shashank Vyas
Description : Write a program to execute `ls -l | wc`. Use `dup2`
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];  // File descriptors for the pipe
    pid_t child1, child2;

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("Error creating pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the first child to run `ls -l`
    child1 = fork();

    if (child1 == -1) {
        perror("Fork failed for first child");
        exit(EXIT_FAILURE);
    }

    if (child1 == 0) {  // In first child process (for `ls -l`)
        close(pipefd[0]);  // Close the read end of the pipe

        // Redirect stdout to the pipe's write end using `dup2()`
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("Error duplicating file descriptor for stdout");
            exit(EXIT_FAILURE);
        }

        // Close the write end of the pipe as it's already duplicated
        close(pipefd[1]);

        // Execute `ls -l` using `execl()`
        execl("/bin/ls", "ls", "-l", (char *)NULL);

        // If execl() fails, handle error
        perror("Error executing ls -l");
        exit(EXIT_FAILURE);
    }

    // Fork the second child to run `wc`
    child2 = fork();

    if (child2 == -1) {
        perror("Fork failed for second child");
        exit(EXIT_FAILURE);
    }

    if (child2 == 0) {  // In second child process (for `wc`)
        close(pipefd[1]);  // Close the write end of the pipe

        // Redirect stdin to the pipe's read end using `dup2()`
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("Error duplicating file descriptor for stdin");
            exit(EXIT_FAILURE);
        }

        // Close the read end of the pipe as it's already duplicated
        close(pipefd[0]);

        // Execute `wc` using `execl()`
        execl("/usr/bin/wc", "wc", (char *)NULL);

        // If execl() fails, handle error
        perror("Error executing wc");
        exit(EXIT_FAILURE);
    }

    // Parent process closes both ends of the pipe
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both child processes to finish
    wait(NULL);  // Wait for the first child (`ls -l`)
    wait(NULL);  // Wait for the second child (`wc`)

    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./17b
    142    1271    7878
*/