#ifndef MANAGER_H
#define MANAGER_H

#include <stdio.h>
#include <string.h>

// Function prototypes for manager actions

// Authenticates the manager by checking userID and password in the users file.
// Returns 1 if authentication is successful, 0 otherwise.
int authenticate_manager(int connFD, int userID, const char *password);

// Logs out the manager by setting isLoggedIn to false in the users file.
void logout_manager(int userID);

// Displays the manager menu and handles manager choices such as activate/deactivate customer, 
// assign loan process, review feedback, change password, and logout.
void manager_menu(int connFD, int userID);

// Handles manager login process. Prompts the manager for userID and password and validates them.
// Calls `manager_menu` on successful login.
int manager_login(int connFD);

// Changes the manager's password by updating the user record in the users file.
void change_manager_password(int connFD, int managerID);

// Activates or deactivates a customer by toggling their `isActive` status in the customers file.
void activate_deactivate_customer(int connFD);

// Reviews customer feedback by reading feedback entries from the feedback file and displaying them.
void review_feedback(int connFD);

#endif
