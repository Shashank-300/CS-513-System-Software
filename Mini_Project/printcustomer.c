#include "customer.h"
#include "account.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void print_all_customers() {
    struct Customer customer;
    struct Account account;
    FILE *customerFile = fopen("customer.txt", "r");
    FILE *accountFile = fopen("account.txt", "r");
    
    if (customerFile == NULL || accountFile == NULL) {
        printf("Error opening customer.txt or account.txt file.\n");
        return;
    }

    printf("All Customers with Account Details:\n");
    while (fread(&customer, sizeof(struct Customer), 1, customerFile)) {
        // Print Customer Info
        printf("UserID: %d, Name: %s, AccountID: %d, IsActive: %d\n",
               customer.userID, customer.name, customer.accountID, customer.isActive);
        
        // Find and print corresponding Account Info
        rewind(accountFile);  // Reset file pointer to start of account.txt
        while (fread(&account, sizeof(struct Account), 1, accountFile)) {
            if (account.accountID == customer.accountID) {
                printf("  AccountID: %d, Balance: %.2f\n", account.accountID, account.balance);
                printf("  Transaction Count: %d\n", account.transactionCount);

                // Print transaction details
                if (account.transactionCount > 0) {
                    printf("  Transactions:\n");
                    for (int i = 0; i < account.transactionCount; i++) {
                        printf("    - %s\n", account.transactions[i]);
                    }
                } else {
                    printf("  No transactions found.\n");
                }
                break;
            }
        }
    }

    fclose(customerFile);
    fclose(accountFile);
}
#include "user.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void print_all_users() {
    struct User user;
    FILE *userFile = fopen("users.txt", "r");
    
    if (userFile == NULL) {
        printf("Error opening users.txt file.\n");
        return;
    }

    printf("All Employees and Managers:\n");
    while (fread(&user, sizeof(struct User), 1, userFile)) {
        if (user.isManager == 1) {
            printf("Manager - UserID: %d, Name: %s\n", user.userID, user.name);
        } else {
            printf("Employee - UserID: %d, Name: %s\n", user.userID, user.name);
        }
    }

    fclose(userFile);
}
void main() {
    // Print all customers with their account details
    print_all_customers();
    
    // Print all employees and managers
    print_all_users();
}
