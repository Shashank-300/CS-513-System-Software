#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "admin.h"
#include "customer.h"
#include "user.h"

int predefined_adminID = 0;
const char* predefined_password = "admin1";
// Function to authenticate the admin using hardcoded credentials (adminID = 0, password = "admin1")
int authenticate_admin(int adminID, const char* password) {
    // Hardcoded admin credentials
    
    // Print entered values for debugging
    printf("Entered Admin ID: %d\n", adminID);
    printf("Entered Password: %s\n", password);

    // Compare input credentials with predefined ones
    if (adminID == predefined_adminID && strcmp(password, predefined_password) == 0) {
        return 1;  // Authentication successful
    }

    return 0;  // Authentication failed
}

// Admin Login System
void admin_login(int connFD) {
    char buffer[1000], adminID_str[100], password[50];
    int adminID;

    // Ask for admin ID
    strcpy(buffer, "Enter Admin ID: ");
    write(connFD, buffer, strlen(buffer));
    bzero(adminID_str, sizeof(adminID_str));
    read(connFD, adminID_str, sizeof(adminID_str));
    adminID = atoi(adminID_str);

    // Ask for password
    // Ask for password
    strcpy(buffer, "Enter Password: ");
    write(connFD, buffer, strlen(buffer));
    bzero(password, sizeof(password));
    read(connFD, password, sizeof(password));

    // Remove trailing newline if present
    password[strcspn(password, "\n")] = 0;


    // Debug: Print the values to check
    printf("Admin ID received: %d\n", adminID);
    printf("Password received: %s\n", password);

    // Validate admin credentials
    if (authenticate_admin(adminID, password)) {
        admin_menu(connFD);
        return ;
    } else {
        strcpy(buffer, "Invalid Admin ID or Password.\n");
        write(connFD, buffer, strlen(buffer));
        return ;
    }
}
// Admin Menu Function
void admin_menu(int connFD) {
    char buffer[1000];
    int choice;

    while (1) {
        // Display the menu
        sprintf(buffer, "\nAdmin Menu:\n1. Add New Bank Employee\n2. Modify Customer/Employee Details\n3. Manage User Roles\n4. Change Password\n5. Logout\nEnter your choice: ");
        write(connFD, buffer, strlen(buffer));
        bzero(buffer, sizeof(buffer));
        // Read the choice from the admin
        read(connFD, buffer, sizeof(buffer));
        choice = atoi(buffer);

        switch (choice) {
            case 1:
                add_new_employee(connFD);
                break;
            case 2:
                modify_customer_employee_details(connFD);
                break;
            case 3:
                manage_user_roles(connFD);
                break;
            case 4:
                admin_change_password(connFD);
                break;
            case 5:
                admin_logout(connFD);
                return;
            default:
                strcpy(buffer, "Invalid choice, try again.\n");
                write(connFD, buffer, strlen(buffer));
        }
    }
}
// Function to logout the admin
void admin_logout(int connFD) {

    // Send confirmation message to admin
    char buffer[100];
    strcpy(buffer, "Admin successfully logged out.\n");
    write(connFD, buffer, strlen(buffer));

    // Close the connection for the admin
    close(connFD);
}

//add new employee
void add_new_employee(int connFD) {
    char buffer[1000], emp_name[50], emp_password[50];
    int empID;
    struct User newUser;
    bzero(buffer, sizeof(buffer)); // For zeroing out the buffer
    
    // Ask for employee ID
    strcpy(buffer, "Enter New Employee ID: ");
    write(connFD, buffer, strlen(buffer));
    read(connFD, buffer, sizeof(buffer));
    empID = atoi(buffer);
    
    // Ask for employee name
    strcpy(buffer, "Enter Employee Name: ");
    write(connFD, buffer, strlen(buffer));
    read(connFD, emp_name, sizeof(emp_name));
    
    // Ask for employee password
    strcpy(buffer, "Enter Employee Password: ");
    write(connFD, buffer, strlen(buffer));
    read(connFD, emp_password, sizeof(emp_password));

    // Set the new employee's details
    newUser.userID = empID;
    strcpy(newUser.name, emp_name);
    strcpy(newUser.password, emp_password);
    newUser.isManager = 0;  // Since this is an employee, not a manager

    // Open the users.txt file and append the new employee details
    FILE *file = fopen("users.txt", "ab");  // Using binary mode to append structures
    if (file != NULL) {
        fwrite(&newUser, sizeof(struct User), 1, file);
        fclose(file);
        strcpy(buffer, "New employee added successfully.\n");
    } else {
        strcpy(buffer, "Error adding new employee.\n");
    }

    // Send feedback to the client
    write(connFD, buffer, strlen(buffer));
}

// Function to modify customer details
void modify_customer_employee_details(int connFD) {
    char buffer[1000], input[100];
    int userID, found = 0;
    struct Customer customer;

    // Ask for the customer ID to modify
    strcpy(buffer, "Enter Customer User ID to modify: ");
    write(connFD, buffer, strlen(buffer));
    bzero(input, sizeof(input));
    read(connFD, input, sizeof(input));
    userID = atoi(input);

    // Open the customer file to find and modify the customer details
    FILE *file = fopen("customer.txt", "rb+");
    if (file == NULL) {
        strcpy(buffer, "Error opening customer.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Search for the customer by userID
    while (fread(&customer, sizeof(struct Customer), 1, file)) {
        if (customer.userID == userID) {
            found = 1;

            // Display the current details of the customer
            snprintf(buffer, sizeof(buffer),
                     "\nCurrent Customer Details:\n"
                     "User ID: %d\nName: %s\nPassword: %s\nAccount ID: %d\nFeedback: %s\n\n",
                     customer.userID, customer.name, customer.password, customer.accountID, customer.feedback);
            write(connFD, buffer, strlen(buffer));

            // Ask which field to modify
            strcpy(buffer, "What would you like to modify?\n1. Name\n2. Password\n3. Feedback\nEnter your choice: ");
            write(connFD, buffer, strlen(buffer));
            bzero(input, sizeof(input));
            read(connFD, input, sizeof(input));
            int choice = atoi(input);

            switch (choice) {
                case 1:
                    // Modify Name
                    strcpy(buffer, "Enter new Name: ");
                    write(connFD, buffer, strlen(buffer));
                    bzero(customer.name, sizeof(customer.name));
                    read(connFD, customer.name, sizeof(customer.name));
                    break;

                case 2:
                    // Modify Password
                    strcpy(buffer, "Enter new Password: ");
                    write(connFD, buffer, strlen(buffer));
                    bzero(customer.password, sizeof(customer.password));
                    read(connFD, customer.password, sizeof(customer.password));
                    break;

                case 3:
                    // Modify Feedback
                    strcpy(buffer, "Enter new Feedback: ");
                    write(connFD, buffer, strlen(buffer));
                    bzero(customer.feedback, sizeof(customer.feedback));
                    read(connFD, customer.feedback, sizeof(customer.feedback));
                    break;

                default:
                    strcpy(buffer, "Invalid choice.\n");
                    write(connFD, buffer, strlen(buffer));
                    fclose(file);
                    return;
            }

            // Move the file pointer back to the correct position
            fseek(file, -sizeof(struct Customer), SEEK_CUR);

            // Write the updated customer data back to the file
            fwrite(&customer, sizeof(struct Customer), 1, file);

            strcpy(buffer, "Customer details updated successfully.\n");
            write(connFD, buffer, strlen(buffer));
            break;
        }
    }

    if (!found) {
        strcpy(buffer, "Customer not found.\n");
        write(connFD, buffer, strlen(buffer));
    }

    fclose(file);
}


// Function to manage user roles
void manage_user_roles(int connFD) {
    struct User user;
    int userID;
    char buffer[1000];

    // Ask for the userID of the person whose role is to be changed
    strcpy(buffer, "Enter the userID of the person whose role you want to change: ");
    write(connFD, buffer, strlen(buffer));
    
    // Read userID input from the admin
    bzero(buffer, sizeof(buffer)); // Clear the buffer before reading new input
    read(connFD, buffer, sizeof(buffer));
    userID = atoi(buffer);  // Convert the input to integer (assuming userID is an integer)

    // Open the file containing user data
    FILE *file = fopen("users.txt", "rb+");
    if (!file) {
        write(connFD, "Error opening users file.\n", 26);
        return;
    }

    // Find the user by userID
    while (fread(&user, sizeof(struct User), 1, file)) {
        if (user.userID == userID) {
            // Toggle the role (switch between employee and manager)
            user.isManager = !user.isManager;

            // Move the file pointer back to the beginning of the current record
            fseek(file, -sizeof(struct User), SEEK_CUR);

            // Write the updated user record back to the file
            fwrite(&user, sizeof(struct User), 1, file);

            // Inform the admin that the role has been changed
            strcpy(buffer, "User role changed successfully.\n");
            write(connFD, buffer, strlen(buffer));

            fclose(file);
            return;
        }
    }

    // If the userID was not found, inform the admin
    fclose(file);
    strcpy(buffer, "User not found.\n");
    write(connFD, buffer, strlen(buffer));
}

// Function to change admin password
void admin_change_password(int connFD) {
    char buffer[1000], new_password[50], confirm_password[50];
    
    // Ask for new password
    strcpy(buffer, "Enter New Password: ");
    write(connFD, buffer, strlen(buffer));
    read(connFD, new_password, sizeof(new_password));

    // Confirm new password
    strcpy(buffer, "Confirm New Password: ");
    write(connFD, buffer, strlen(buffer));
    read(connFD, confirm_password, sizeof(confirm_password));

    if (strcmp(new_password, confirm_password) == 0) {
        predefined_password=confirm_password;
        strcpy(buffer, "Password changed successfully.\n");
    } else {
        strcpy(buffer, "Passwords do not match. Try again.\n");
    }
    write(connFD, buffer, strlen(buffer));
}
