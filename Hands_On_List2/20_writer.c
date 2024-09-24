/*
============================================================================
Name : 20_writer.c
Author : Shashank Vyas
Description : Write two programs so that both can communicate by FIFO - Use one way communication.
Date: 21th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_FILE "/tmp/myfifo"

int main() {
    int fd;
    char message[] = "Message from writer to reader";

    // Create a named pipe (FIFO) if it doesn't exist
    if (mkfifo(FIFO_FILE, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // Open the FIFO for writing
    fd = open(FIFO_FILE, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write the message to the FIFO
    write(fd, message, sizeof(message));

    // Close the FIFO
    close(fd);

    printf("Message sent to FIFO.\n");
    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/HOL 2$ ./20_writer 
    hiv ibb
    Message sent to FIFO.
*/