#ifndef ACCOUNT_H
#define ACCOUNT_H

#define MAX_TRANSACTIONS 10
#define MAX_TRANSACTION_LEN 256

// Structure for Account Information
struct Account {
    int accountID;               // Unique account ID (primary key for accounts)
    float balance;               // Account balance
    int transactionCount;        // Number of transactions
    char transactions[MAX_TRANSACTIONS][MAX_TRANSACTION_LEN]; // Transaction history
};

#endif