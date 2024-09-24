/*
============================================================================
Name : 21b.c
Author : Shashank Vyas
Description : Write two programs so that both can communicate by FIFO - Use two way communications.
Date: 21th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main() {
    int fd_read, fd_write;
    char write_msg[100], read_msg[100];

    // Open FIFOs
    fd_read = open(FIFO1, O_RDONLY);
    fd_write = open(FIFO2, O_WRONLY);

    while(1) {
        // Read message from Program 1
        read(fd_read, read_msg, sizeof(read_msg));
        printf("Program 2: Received message: %s\n", read_msg);

        // Write response to Program 1
        printf("Program 2: Enter message to send: ");
        fgets(write_msg, 100, stdin);
        write(fd_write, write_msg, strlen(write_msg) + 1);
    }

    close(fd_read);
    close(fd_write);

    return 0;
}


/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./21b
Program 2: Received message: hi

Program 2: Enter message to send: hi
Program 2: Received message: how are you

Program 2: Enter message to send: fine
Program 2: Received message: fine

Program 2: Enter message to send: 
*/