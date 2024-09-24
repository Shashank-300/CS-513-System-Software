/*
============================================================================
Name : 33_client.c
Author : Shashank Vyas
Description : Write a program to communicate between two machines using socket.
Date: 21th Sep, 2024.
============================================================================
*/


#include <sys/types.h>    // For data types
#include <sys/socket.h>   // For socket system calls
#include <netinet/ip.h>   // For IP address structures (IPv4)
#include <stdio.h>        // For standard I/O functions like printf, perror
#include <unistd.h>       // For close, read, and write system calls
#include <stdlib.h>       // For exit function

int main()
{
    int socket_fd;                    // File descriptor for the socket
    int connection_status;            // Status for connection attempt
    struct sockaddr_in server_address; // Structure to hold server address details

    ssize_t bytes_read, bytes_written; // Bytes read/written over the socket
    char server_message[100];          // Buffer to hold the server's message

    // 1. Create a socket
    socket_fd = socket(AF_INET, SOCK_STREAM, 0); // SOCK_STREAM for TCP connection
    if (socket_fd == -1)
    {
        perror("Failed to create client socket");
        exit(EXIT_FAILURE); // Use EXIT_FAILURE for more clarity in exit codes
    }
    printf("Client socket created successfully!\n");

    // 2. Configure server address settings
    server_address.sin_family = AF_INET; // Use IPv4 address family
    server_address.sin_port = htons(8000); // Set server port (convert to network byte order)
    server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // Use loopback address (127.0.0.1)

    // 3. Connect to the server
    connection_status = connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address));
    if (connection_status == -1)
    {
        perror("Connection to the server failed");
        close(socket_fd); // Ensure socket is closed before exiting
        exit(EXIT_FAILURE);
    }
    printf("Successfully connected to the server.\n");

    // 4. Read data from the server
    bytes_read = read(socket_fd, server_message, sizeof(server_message) - 1); // Read server data
    if (bytes_read == -1)
    {
        perror("Failed to read data from the server");
    }
    else
    {
        server_message[bytes_read] = '\0'; // Null-terminate the string
        printf("Message from server: %s\n", server_message);
    }

    // 5. Write data to the server
    const char *client_message = "Hello from client"; 
    bytes_written = write(socket_fd, client_message, sizeof(client_message));
    if (bytes_written == -1)
    {
        perror("Failed to send data to the server");
    }
    else
    {
        printf("Client message sent to the server.\n");
    }

    close(socket_fd);
    printf("Connection closed.\n");

    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/HOL 2$ ./33_client 
    Client socket created successfully!
    Successfully connected to the server.
    Message from server: Hello from server
    Client message sent to the server.
    Connection closed.
*/