/*
============================================================================
Name : 23.c
Author : Shashank Vyas
Description : Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer).
Date: 21th Sep, 2024.
============================================================================
*/

#include <unistd.h>    // For sysconf, pathconf
#include <sys/types.h> // For mkfifo
#include <sys/stat.h>  // For mkfifo
#include <stdio.h>     // For perror, printf
#include <errno.h>     // For errno

int main()
{
    int fifoStatus;      // Holds the status of mkfifo call
    long maxOpenFiles;   // Holds the maximum number of files a process can open
    long pipeBufferSize; // Holds the size of a FIFO pipe

    const char *fifoPath = "example_fifo"; // Name of the FIFO
    fifoStatus = mkfifo(fifoPath, S_IRWXU); // Create the FIFO with user permissions

    // Check for errors during FIFO creation
    if (fifoStatus == -1 && errno != EEXIST)
    {
        perror("Failed to create FIFO");
    }
    else
    {
        // Get the system limit on the maximum number of open files for a process
        maxOpenFiles = sysconf(_SC_OPEN_MAX);
        
        if (maxOpenFiles == -1)
        {
            perror("Failed to retrieve the maximum number of open files");
        }
        else
        {
            printf("The maximum number of files a process can open: %ld\n", maxOpenFiles);
        }

        // Get the size of the FIFO buffer using pathconf
        pipeBufferSize = pathconf(fifoPath, _PC_PIPE_BUF);

        if (pipeBufferSize == -1)
        {
            perror("Failed to retrieve the size of the pipe buffer");
        }
        else
        {
            printf("FIFO buffer size: %ld bytes\n", pipeBufferSize);
        }
    }

    return 0;
}

/*
    The maximum number of files a process can open: 1048576
    FIFO buffer size: 4096 bytes
*/