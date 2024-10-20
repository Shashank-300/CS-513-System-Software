#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 10

// Account structure
typedef struct {
    int account_id;
    char username[50];
    char password[50];
    double balance;
} Account;

#define ACCOUNT_FILE "accounts.dat"

// Function declarations
void *handle_client(void *socket_desc);
int login(int client_sock, const char* role);
void send_menu(int client_sock, const char* role);
void view_balance(int client_sock, int account_id);
void deposit_money(int client_sock, int account_id, double amount);

// Role-specific menus
void send_customer_menu(int client_sock);
void send_manager_menu(int client_sock);
void send_employee_menu(int client_sock);
void send_admin_menu(int client_sock);

void send_menu(int client_sock, const char* role) {
    char menu[256];
    if (strcmp(role, "1") == 0) {  // Assuming role "1" is Customer
        sprintf(menu, "Customer Menu:\n1. View Account Balance\n2. Deposit Money\n3. Withdraw Money\n4. Transfer Funds\n5. Apply for a Loan\n6. Change Password\n7. View Transaction History\n8. Logout\n9. Exit\n");
    } else if (strcmp(role, "2") == 0) {  // Employee
        sprintf(menu, "Employee Menu:\n1. Add New Customer\n2. Modify Customer Details\n3. Process Loan Applications\n4. View Customer Transactions\n5. Logout\n6. Exit\n");
    } else if (strcmp(role, "3") == 0) {  // Manager
        sprintf(menu, "Manager Menu:\n1. Activate/Deactivate Customer Accounts\n2. Assign Loan Application Processes to Employees\n3. Review Customer Feedback\n4. Logout\n5. Exit\n");
    } else if (strcmp(role, "4") == 0) {  // Administrator
        sprintf(menu, "Admin Menu:\n1. Add New Bank Employee\n2. Modify Customer/Employee Details\n3. Manage User Roles\n4. Logout\n5. Exit\n");
    }
    send(client_sock, menu, strlen(menu), 0);
}

void initialize_accounts() {
    Account initial_accounts[] = {
        {1, "customer1", "pass1", 1000.0}, // Customer
        {2, "employee1", "emp_pass1", 0.0}, // Employee
        {3, "manager1", "mgr_pass1", 0.0}   // Manager
    };

    int fd = open(ACCOUNT_FILE, O_RDWR | O_CREAT, 0666); // Create or open the file
    if (fd < 0) {
        perror("Failed to open account file");
        return;
    }

    // Write initial accounts to the file
    for (int i = 0; i < sizeof(initial_accounts) / sizeof(initial_accounts[0]); i++) {
        write(fd, &initial_accounts[i], sizeof(Account));
    }

    close(fd);
}

int main() {
    initialize_accounts();
    int server_fd, client_sock, c;
    struct sockaddr_in server, client;
    pthread_t thread_id;

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    listen(server_fd, MAX_CLIENTS);

    printf("Server is running and waiting for connections...\n");

    // Accept and handle incoming connections
    c = sizeof(struct sockaddr_in);
    while ((client_sock = accept(server_fd, (struct sockaddr *)&client, (socklen_t*)&c))) {
        printf("Client connected\n");

        // Create a thread for each client connection
        if (pthread_create(&thread_id, NULL, handle_client, (void*)&client_sock) < 0) {
            perror("Could not create thread");
            exit(EXIT_FAILURE);
        }
    }

    if (client_sock < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    close(server_fd);
    return 0;
}

void *handle_client(void *socket_desc) {
    int client_sock = *(int*)socket_desc;
    int account_id;
    char role[20];

    // Ask for the role (Customer, Manager, Employee, or Admin)
    char role_prompt[] = "Select Role:\n1. Customer\n2. Manager\n3. Employee\n4. Admin\n";
    send(client_sock, role_prompt, sizeof(role_prompt), 0);
    
    // Receive the role from the client
    recv(client_sock, role, sizeof(role), 0);
    
    // Handle login after role selection
    account_id = login(client_sock, role);
    if (account_id == -1) {
        printf("Login failed\n");
        close(client_sock);
        pthread_exit(NULL);
    }

    printf("Client logged in with account ID: %d and role: %s\n", account_id, role);

    // Send the appropriate menu based on the role
    send_menu(client_sock, role);

    // Handle the client's operations
    int choice;
    double amount;
    while (recv(client_sock, &choice, sizeof(choice), 0) > 0) {
        switch (choice) {
            case 1:
                view_balance(client_sock, account_id);
                break;
            case 2:
                recv(client_sock, &amount, sizeof(amount), 0);
                deposit_money(client_sock, account_id, amount);
                break;
            case 3:
                printf("Client disconnected.\n");
                close(client_sock);
                pthread_exit(NULL);
            default:
                printf("Invalid choice received.\n");
        }
        send_menu(client_sock, role);  // Send menu after each operation
    }

    close(client_sock);
    pthread_exit(NULL);
}

int login(int client_sock, const char* role) {
    char username[50], password[50];
    Account acc;
    int fd = open(ACCOUNT_FILE, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open account file");
        return -1;
    }

    // Receive username and password from client
    char login_prompt[] = "Enter username: ";
    send(client_sock, login_prompt, sizeof(login_prompt), 0);
    recv(client_sock, username, sizeof(username), 0);

    char password_prompt[] = "Enter password: ";
    send(client_sock, password_prompt, sizeof(password_prompt), 0);
    recv(client_sock, password, sizeof(password), 0);

    // Search for matching credentials
    while (read(fd, &acc, sizeof(Account)) == sizeof(Account)) {
        if (strcmp(acc.username, username) == 0 && strcmp(acc.password, password) == 0) {
            close(fd);
            send(client_sock, "Login successful\n", 17, 0);
            return acc.account_id;
        }
    }

    close(fd);
    send(client_sock, "Login failed\n", 13, 0);
    return -1;
}

// Role-specific menu functions
void send_customer_menu(int client_sock) {
    char menu[] = "\nCustomer Menu:\n1. View Balance\n2. Deposit Money\n3. Exit\n";
    send(client_sock, menu, sizeof(menu), 0);
}

void send_manager_menu(int client_sock) {
    char menu[] = "\nManager Menu:\n1. Activate/Deactivate Customer Accounts\n2. Exit\n";
    send(client_sock, menu, sizeof(menu), 0);
}

void send_employee_menu(int client_sock) {
    char menu[] = "\nEmployee Menu:\n1. Add New Customer\n2. Exit\n";
    send(client_sock, menu, sizeof(menu), 0);
}

void send_admin_menu(int client_sock) {
    char menu[] = "\nAdmin Menu:\n1. Add New Employee\n2. Exit\n";
    send(client_sock, menu, sizeof(menu), 0);
}

// Common functions (e.g., for customers)
void view_balance(int client_sock, int account_id) {
    Account acc;
    int fd = open(ACCOUNT_FILE, O_RDONLY);
    if (fd < 0) {
        perror("Error opening account file");
        return;
    }
    
    // Read account data at the correct position
    lseek(fd, (account_id - 1) * sizeof(Account), SEEK_SET);
    read(fd, &acc, sizeof(Account));
    close(fd);

    char balance_message[100];
    sprintf(balance_message, "Account ID: %d\nBalance: $%.2f\n", acc.account_id, acc.balance);
    send(client_sock, balance_message, strlen(balance_message), 0);
}

void deposit_money(int client_sock, int account_id, double amount) {
    Account acc;
    int fd = open(ACCOUNT_FILE, O_RDWR);
    if (fd < 0) {
        perror("Error opening account file");
        return;
    }
    
    // Read and update account data
    lseek(fd, (account_id - 1) * sizeof(Account), SEEK_SET);
    read(fd, &acc, sizeof(Account));
    acc.balance += amount;
    
    // Write updated account data back to file
    lseek(fd, (account_id - 1) * sizeof(Account), SEEK_SET);
    write(fd, &acc, sizeof(Account));
    close(fd);

    char success_message[100];
    sprintf(success_message, "Deposited $%.2f to account ID: %d\nNew Balance: $%.2f\n", amount, acc.account_id, acc.balance);
    send(client_sock, success_message, strlen(success_message), 0);
}
