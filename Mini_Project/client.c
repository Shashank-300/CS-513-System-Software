#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock;
    struct sockaddr_in server;
    char server_reply[2000];
    char username[50], password[50];
    int choice;
    double amount;
    char role[20];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Could not create socket");
        return 1;
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connection failed");
        return 1;
    }

    // Receive and display role selection prompt
    memset(server_reply, 0, sizeof(server_reply));  // Clear buffer
    recv(sock, server_reply, sizeof(server_reply), 0);
    printf("%s", server_reply);

    // Send role selection
    printf("Enter role (1-4): ");
    scanf("%s", role);
    send(sock, role, strlen(role), 0);

    // Receive login prompt for username
    memset(server_reply, 0, sizeof(server_reply));  // Clear buffer
    recv(sock, server_reply, sizeof(server_reply), 0);
    printf("%s", server_reply);

    // Send username
    printf("Enter username: ");
    scanf("%s", username);
    send(sock, username, strlen(username), 0);

    // Receive password prompt
    memset(server_reply, 0, sizeof(server_reply));  // Clear buffer
    recv(sock, server_reply, sizeof(server_reply), 0);
    printf("%s", server_reply);

    // Send password
    printf("Enter password: ");
    scanf("%s", password);
    send(sock, password, strlen(password), 0);

    // Receive login response
    memset(server_reply, 0, sizeof(server_reply));  // Clear buffer
    recv(sock, server_reply, sizeof(server_reply), 0);
    printf("%s", server_reply);

    // If login is successful, receive the appropriate menu
    if (strstr(server_reply, "Login successful")) {
        memset(server_reply, 0, sizeof(server_reply));  // Clear buffer
        recv(sock, server_reply, sizeof(server_reply), 0);
        printf("%s", server_reply);

        // Loop for user input based on menu options
        while (1) {
            printf("Enter choice: ");
            scanf("%d", &choice);
            send(sock, &choice, sizeof(choice), 0);

            if (choice == 2) {  // Example for deposit option
                printf("Enter amount to deposit: ");
                scanf("%lf", &amount);
                send(sock, &amount, sizeof(amount), 0);
            }

            // Receive server's response after operation
            memset(server_reply, 0, sizeof(server_reply));  // Clear buffer
            recv(sock, server_reply, sizeof(server_reply), 0);
            printf("%s", server_reply);

            if (choice == 3) {  // Exit option
                break;
            }
        }
    }

    close(sock);
    return 0;
}
