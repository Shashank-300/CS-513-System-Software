/*
============================================================================
Name : 14.c
Author : Shashank Vyas
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
Date: 20th Sep, 2024.
============================================================================
*/


#include <unistd.h> // Import for `pipe`, `write` & `read` system call
#include <stdio.h>  // Import for `perror` and `printf`

void main()
{
    // File descriptor used for pipe operations
    int pipfd[2];                // pipefd[0] -> read, pipefd[1] -> write
    char *writeBuff = "Hi i am from pipe!!"; // Data sent through the pipe
    char *readBuff;
    int pipeStat;            // Variable used to determine success of `pipe` call
    int rBytes, wBytes; // Number of bytes written using `write` & read using `read`

    // Creating a pipe
    pipeStat = pipe(pipfd);

    if (pipeStat == -1)
        perror("Error while creating the pipe! ");
    else
    {
        printf("Write on the pipe!\n");
        wBytes = write(pipfd[1], &writeBuff, sizeof(writeBuff));
        if (wBytes == -1)
            perror("Error while writing to pipe!");
        else
        {
            printf("Read from the pipe!\n");
            rBytes = read(pipfd[0], &readBuff, wBytes);
            if (rBytes == -1)
                perror("Error while reading from pipe!");
            else
                printf("Data from pipe: %s\n", readBuff);
        }
    }
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./14
Write on the pipe!
Read from the pipe!
Data from pipe: Hi i am from pipe!!
*/