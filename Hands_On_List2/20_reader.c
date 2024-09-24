/*
============================================================================
Name : 20_reader.c
Author : Shashank Vyas
Description : Write two programs so that both can communicate by FIFO - Use one way communication.
Date: 21th Sep, 2024.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_FILE "/tmp/myfifo"

int main() {
    int fd;
    char buffer[100];

    // Open the FIFO for reading
    fd = open(FIFO_FILE, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read the data from the FIFO
    read(fd, buffer, sizeof(buffer));

    // Print the message received from the writer
    printf("Received message: %s\n", buffer);

    // Close the FIFO
    close(fd);

    return 0;
}

/*
    ./20_reader 
    Received message: Message from writer to reader
*/
