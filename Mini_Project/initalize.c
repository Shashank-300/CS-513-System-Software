#include <stdio.h>
#include <string.h>
#include <unistd.h>    // For read, write, close functions
#include <stdlib.h>
#include "customer.h"
#include "account.h" 

void initialize_customers() {
    FILE *file;
    struct Customer customers[3] = {
        {1, "password1", "Alice", 1001, ""},
        {2, "password2", "Bob", 1002, ""},
        {3, "password3", "Charlie", 1003, ""}
    };

    // Open the file in write mode (binary)
    file = fopen("customer.txt", "wb");
    if (file == NULL) {
        printf("Error opening customer.txt file.\n");
        return;
    }

    // Write the customer records to the file
    fwrite(customers, sizeof(struct Customer), 3, file);

    fclose(file);
    printf("Initialized customer.txt with dummy data.\n");
}


// Function to initialize account data
void initialize_accounts() {
    FILE *file = fopen("account.txt", "wb");
    if (file == NULL) {
        printf("Error opening account.txt file for initialization.\n");
        return;
    }

    // Create some dummy account data
    struct Account accounts[3] = {
        {1001, 5000.00, 0, {{0}}},  // Account 1 with $5000 balance
        {1002, 10000.00, 0, {{0}}}, // Account 2 with $10000 balance
        {1003, 7500.00, 0, {{0}}}   // Account 3 with $7500 balance
    };

    // Write the accounts array to the file
    fwrite(accounts, sizeof(struct Account), 3, file);

    fclose(file);
    printf("Accounts initialized successfully!\n");
}

// Function to print the accounts (for verification)
void print_accounts() {
    struct Account account;
    FILE *file = fopen("account.txt", "rb");
    if (file == NULL) {
        printf("Error opening account.txt file for reading.\n");
        return;
    }

    printf("Account Details:\n");
    while (fread(&account, sizeof(struct Account), 1, file)) {
        printf("Account ID: %d\n", account.accountID);
        printf("Balance: $%.2f\n", account.balance);
        printf("Number of Transactions: %d\n", account.transactionCount);
        printf("-------------------------------\n");
    }

    fclose(file);
}

int main() {
    // Run the initialization only once
    initialize_accounts();

    // Print the account data to verify
    print_accounts();

    return 0;
}
