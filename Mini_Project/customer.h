#ifndef CUSTOMER_H
#define CUSTOMER_H
#define MAX_PASSWORD_LENGTH 10
#include "account.h"

// Structure for Customer Information
struct Customer {
    int userID;          // Unique customer ID for login
    char password[50];   // Password for login
    char name[100];      // Customer's name
    int accountID;       // Link to account structure
    char feedback[500];  // Feedback from the customer
    int isActive;        // Activation status: 1 for active, 0 for deactivated
}__attribute__((packed));;


// Function Prototypes
void customer_login(int connFD);
void customer_menu(int connFD,int userID);
void view_account_balance(int connFD,int userID);
void deposit_money(int connFD,int userID);
void withdraw_money(int connFD,int userID);
void transfer_funds(int connFD,int userID);
void apply_for_loan(int connFD,int userID);
void change_password(int connFD,int userID);
void add_customer_feedback(int connFD,int userID);
void view_transaction(int connFD,int userID);

// Helper function
int authenticate_customer(int userID, const char *password);
#endif