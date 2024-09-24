/*
============================================================================
Name : 21a.c
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
    int fd_write, fd_read;
    char write_msg[100], read_msg[100];

    // Create FIFOs if they don't exist
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    // Open FIFOs
    fd_write = open(FIFO1, O_WRONLY);
    fd_read = open(FIFO2, O_RDONLY);

    while(1) {
        // Write message to Program 2
        printf("Program 1: Enter message to send: ");
        fgets(write_msg, 100, stdin);
        write(fd_write, write_msg, strlen(write_msg) + 1);

        // Read response from Program 2
        read(fd_read, read_msg, sizeof(read_msg));
        printf("Program 1: Received message: %s\n", read_msg);
    }

    close(fd_write);
    close(fd_read);

    return 0;
}


/*
shashank@ubuntu-22:~/Documents/HOL 2$ gcc -o 21a 21a.c
shashank@ubuntu-22:~/Documents/HOL 2$ ./21a
Program 1: Enter message to send: hi
Program 1: Received message: hi

Program 1: Enter message to send: how are you 

Program 1: Received message: fine

Program 1: Enter message to send: 

*/