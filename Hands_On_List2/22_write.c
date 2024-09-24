/*
============================================================================
Name : 22_write.c
Author : Shashank Vyas
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use `select` system call with FIFO.
Date: 21th Sep, 2024.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("22_fifo", O_WRONLY);
    
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buffer[100];
    

    printf("Enter text: ");
    scanf(" %[^\n]", buffer); // Note the space before %[^\n] to skip leading whitespace

    ssize_t bytesWritten = write(fd, buffer, sizeof(buffer));

    if (bytesWritten == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);
    
    printf("Data written to FIFO: %s\n", buffer);

    return 0;
}

/*
    ./22_write
    Enter text: hi
    Data written to FIFO: hi
*/