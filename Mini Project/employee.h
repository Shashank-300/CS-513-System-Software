#ifndef EMPLOYEE_H
#define EMPLOYEE_H

// Declare all the employee-related functions that you have defined in the employee.c file.
// These are the functions that other modules (like main.c, client.c) can call.

// Employee authentication and login-related functions
int is_user_logged_in(int userID);
void add_user_to_session(int userID);
void remove_user_from_session(int userID);
int authenticate_employee(int connFD, int userID, const char *password);
int employee_login(int connFD);

// Employee actions
void employee_menu(int connFD, int employeeID);
void add_new_customer(int connFD);
void modify_customer_details(int connFD);
void approve_reject_loans(int connFD,int employeeID);
void view_assigned_loans(int connFD,int employeeID);
void change_employee_password(int connFD, int userID);
// void view_customer_transactions(int connFD);

#endif
