#ifndef USER_H
#define USER_H

#include <stdbool.h>

struct User {
    int userID;           // Unique user ID for login
    char name[100];       // User's name
    char password[50];    // User's password
    bool isManager;       // Role identifier: true for Manager, false for Employee
    bool isLoggedIn; 
};

// Function prototypes
// Function Prototypes
// void employee_menu(int connFD, int employeeID);
// void add_new_customer(int connFD);
// void modify_customer_details(int connFD);
// void process_loan_applications(int connFD);
// void approve_reject_loans(int connFD);
// void view_assigned_loans(int connFD);
// void view_customer_transactions(int connFD);
// void change_employee_password(int connFD,int employeeID);
#endif
