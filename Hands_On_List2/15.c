/*
============================================================================
Name : 15.c
Author : Shashank Vyas
Description : Write a simple program to send some data from parent to the child process.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int pipfds[2];  // Array to store pipe file descriptors
    __pid_t pid;
    char w_msg[] = "Hi from parent process!";
    char r_msg[100];

    // Create a pipe
    if (pipe(pipfds) == -1) {
        perror("pipe");
        exit(1);
    }
    else 
        printf("Pipe creation was success!!\n");

    // Fork a child process
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    // Child process
    if (pid == 0) {
        // Close the write end of the pipe in the child
        close(pipfds[1]);

        // Read data from the pipe
        read(pipfds[0], r_msg, sizeof(r_msg));

        // Display the message received from parent
        printf("Child received: %s\n", r_msg);

        // Close the read end of the pipe
        close(pipfds[0]);
    } 
    // Parent process
    else {
        // Close the read end of the pipe in the parent
        close(pipfds[0]);

        // Write data to the pipe
        write(pipfds[1], w_msg, strlen(w_msg) + 1);

        // Close the write end of the pipe
        close(pipfds[1]);
    }

    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./15
Pipe creation was success!!
Child received: Hi from parent process!
*/