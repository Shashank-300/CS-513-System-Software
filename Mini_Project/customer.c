#include "customer.h"

void send_customer_menu(int client_sock) {
    char menu[] = "\nCustomer Menu:\n1. View Balance\n2. Deposit Money\n3. Exit\n";
    send(client_sock, menu, sizeof(menu), 0);
}

void view_balance(int client_sock, int account_id) {
    int fd = open(ACCOUNT_FILE, O_RDONLY);
    Account acc;
    lseek(fd, account_id * sizeof(Account), SEEK_SET);
    read(fd, &acc, sizeof(Account));
    close(fd);

    char balance_message[100];
    sprintf(balance_message, "Account ID: %d\nBalance: $%.2f\n", acc.account_id, acc.balance);
    send(client_sock, balance_message, strlen(balance_message), 0);
}

void deposit_money(int client_sock, int account_id, double amount) {
    // Logic for depositing money
    // You can implement file handling, updating account balance, etc.
    
    // Example of sending a confirmation message back to the client
    char message[100];
    sprintf(message, "Amount %.2lf has been deposited to account %d\n", amount, account_id);
    send(client_sock, message, strlen(message), 0);
}
