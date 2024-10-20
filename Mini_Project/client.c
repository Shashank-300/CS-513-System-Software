#include <stdio.h>      // Import for `printf` & `perror` functions
#include <errno.h>      // Import for `errno` variable
#include <fcntl.h>      // Import for `fcntl` functions
#include <unistd.h>     // Import for `fork`, `fcntl`, `read`, `write`, `lseek`, `_exit` functions
#include <sys/types.h>  // Import for `socket`, `bind`, `listen`, `connect`, `fork`, `lseek` functions
#include <sys/socket.h> // Import for `socket`, `bind`, `listen`, `connect` functions
#include <netinet/ip.h> // Import for `sockaddr_in` structure
#include <string.h>     // Import for string functions

void connection_handler(int sockFD); // Handles the read & write operations to the server

void main()
{
    int socketFileDescriptor, connectStatus;
    struct sockaddr_in serverAddress;

    socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == -1)
    {
        perror("Error while creating server socket!");
        _exit(0);
    }

    serverAddress.sin_family = AF_INET;                // IPv4
    serverAddress.sin_port = htons(8081);              // Server will listen to port 8081
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // Binds the socket to all interfaces

    connectStatus = connect(socketFileDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (connectStatus == -1)
    {
        perror("Error while connecting to server!");
        close(socketFileDescriptor);
        _exit(0);
    }

    connection_handler(socketFileDescriptor);
}

// Handles the read & write operations with the server
// Handles the read & write operations with the server
void connection_handler(int sockFD)
{
    char readBuffer[1000], writeBuffer[1000]; // A buffer used for reading from / writing to the server
    ssize_t readBytes, writeBytes;            // Number of bytes read/written
    int shouldContinue = 1;

    while (shouldContinue) {
        // Read the server message
        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(sockFD, readBuffer, sizeof(readBuffer));
        if (readBytes == 0) {
            printf("Server closed the connection.\n");
            break;
        }
        printf("%s", readBuffer);

        // Get user input and send it to the server
        bzero(writeBuffer, sizeof(writeBuffer));
        fgets(writeBuffer, sizeof(writeBuffer), stdin);
        writeBytes = write(sockFD, writeBuffer, strlen(writeBuffer));

        // Check if the user selected to log out
        if (strncmp(writeBuffer, "9", 1) == 0) {
            shouldContinue = 0; // User chose to logout
        }
    }

    printf("Closing the connection to the server now!\n");
    close(sockFD);
}
