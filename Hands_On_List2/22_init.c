#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *fifoPath = "22_fifo"; // Specify the path for the FIFO

    // Create the FIFO with read and write permissions (0666)
    if (mkfifo(fifoPath, 0666) == -1) {
        perror("mkfifo");
        return 1;
    }

    printf("FIFO created successfully at path: %s\n", fifoPath);

    return 0;
}