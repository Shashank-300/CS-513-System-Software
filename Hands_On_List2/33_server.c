/*
============================================================================
Name : 33_server.c
Author : Shashank Vyas
Description : Write a program to communicate between two machines using socket.
Date: 21th Sep, 2024.
============================================================================
*/


#include <sys/types.h>    // For system data types
#include <sys/socket.h>   // For socket system calls
#include <netinet/ip.h>   // For IP address family structures (IPv4)
#include <stdio.h>        // For standard I/O functions like printf, perror
#include <unistd.h>       // For system calls like close
#include <stdlib.h>       // For exit function

int main() {
    int server_socket, client_socket;         // Socket descriptors for server and client
    int bind_status, listen_status;           // Status for bind and listen operations
    socklen_t client_len;                     // To store size of client structure
    struct sockaddr_in server_addr, client_addr;  // Structures for server and client addresses

    ssize_t bytes_read, bytes_written;        // Variables to store number of bytes read/written
    char client_message[100];                 // Buffer for reading client message

    // 1. Create server-side socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);  // Create a TCP socket
    if (server_socket == -1) {
        perror("Failed to create server socket");
        exit(EXIT_FAILURE);  // Use exit with failure code for better error handling
    }
    printf("Server socket created successfully!\n");

    // 2. Set up server address configuration
    server_addr.sin_family = AF_INET;                 // IPv4 protocol
    server_addr.sin_port = htons(8000);               // Port number (convert to network byte order)
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // Bind to any available interface

    // 3. Bind socket to the address
    bind_status = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bind_status == -1) {
        perror("Failed to bind socket to the address");
        close(server_socket);  // Ensure socket is closed in case of error
        exit(EXIT_FAILURE);
    }
    printf("Socket successfully bound to address!\n");

    // 4. Start listening for incoming connections
    listen_status = listen(server_socket, 1);  // Listen with a backlog of 1 connection
    if (listen_status == -1) {
        perror("Failed to listen for connections");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("Server is now listening for incoming connections...\n");

    // 5. Accept incoming client connection
    client_len = sizeof(client_addr);  // Set the length of the client address structure
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
    if (client_socket == -1) {
        perror("Failed to accept client connection");
    } else {
        // 6. Send a message to the client
        const char *server_message = "Hello from server!";
        bytes_written = write(client_socket, server_message, 17);  // Send message to client
        if (bytes_written == -1) {
            perror("Failed to send message to client");
        } else {
            printf("Message sent to client.\n");
        }

        // 7. Read data from the client
        bytes_read = read(client_socket, client_message, sizeof(client_message) - 1);  // Read client message
        if (bytes_read == -1) {
            perror("Failed to read data from client");
        } else {
            client_message[bytes_read] = '\0';  // Null-terminate the string
            printf("Received message from client: %s\n", client_message);
        }

        close(client_socket);
        printf("Client connection closed.\n");
    }

    close(server_socket);
    printf("Server socket closed.\n");

    return 0;  
}

/*
    shashank@ubuntu-22:~/Documents/HOL 2$ ./33_server 
    Server socket created successfully!
    Socket successfully bound to address!
    Server is now listening for incoming connections...
    Message sent to client.
    Received message from client: Hello fr
    Client connection closed.
    Server socket closed.

*/