#include "user.h"
#include "customer.h"
#include "loan.h"
#include "feedback.h"
#include "manager.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For read and write

// Function prototypes
void assign_loan_to_employee(int connFD);
void view_unassigned_loans(int connFD); // Update this if view_unassigned_loans takes parameters

// Your other includes and definitions...

// The rest of your manager.c implementation...

// Function to authenticate a manager with a single session per user
int authenticate_manager(int connFD, int userID, const char *password) {
    struct User user;
    FILE *file = fopen("users.txt", "r+");
    if (file == NULL) {
        write(connFD, "Error opening users file.\n", 26);
        return 0;
    }

    // Iterate through the file to find the user
    while (fread(&user, sizeof(struct User), 1, file)) {
        if (user.userID == userID && strcmp(user.password, password) == 0) {
            if (!user.isManager) {
                write(connFD, "Access Denied: Not a manager.\n", 30);
                fclose(file);
                return 0; // Not a manager
            }

            if (user.isLoggedIn) {
                write(connFD, "Error: Manager is already logged in.\n", 37);
                fclose(file);
                return 0; // Already logged in
            }

            // Update the user to logged in
            user.isLoggedIn = true;
            fseek(file, -sizeof(struct User), SEEK_CUR); // Move back to overwrite the user
            fwrite(&user, sizeof(struct User), 1, file);
            fflush(file); // Ensure data is written to the file
            fclose(file);
            return 1; // Authentication successful
        }
    }

    fclose(file);
    write(connFD, "Invalid credentials.\n", 21);
    return 0; // Authentication failed
}

// Function to logout and set isLoggedIn to false
void logout_manager(int userID) {
    struct User user;
    FILE *file = fopen("users.txt", "r+");
    if (file == NULL) {
        printf("Error opening users file.\n");
        return;
    }

    // Iterate through the file to find the user
    while (fread(&user, sizeof(struct User), 1, file)) {
        if (user.userID == userID) {
            // Set the user as logged out
            user.isLoggedIn = false;
            fseek(file, -sizeof(struct User), SEEK_CUR); // Move back to overwrite the user
            fwrite(&user, sizeof(struct User), 1, file);
            fflush(file); // Ensure data is written to the file
            break;
        }
    }

    fclose(file);
}

// Function to display the manager menu after successful login
void manager_menu(int connFD, int userID) {
    char buffer[1000];
    int choice;

    while (1) {
        // Display manager menu options
        strcpy(buffer, "\nManager Menu:\n1. Activate/Deactivate Customer\n2. Assign Loan Process\n3. Review Feedback\n4. Change Password\n5. View Unassigned loans\n6. Logout\nEnter your choice : ");
        fflush(stdout);
        write(connFD, buffer, strlen(buffer));
        
        // Get user's choice
        bzero(buffer, sizeof(buffer));
        read(connFD, buffer, sizeof(buffer));  // Read user's input
        buffer[strcspn(buffer, "\n")] = 0;     // Remove any newline characters
        choice = atoi(buffer);                 // Convert choice to integer
        
        switch (choice) {
            case 1:
                // Activate/Deactivate customer function
                activate_deactivate_customer(connFD);
                break;
            case 2:
                // Assign loan process function
                assign_loan_to_employee(connFD);
                break;
            case 3:
                // Review feedback function
                review_feedback(connFD);
                break;
            case 4:
                change_manager_password(connFD,userID);
                break;
            case 5:
                view_unassigned_loans(connFD);
                break;
            case 6:
                // Logout and set isLoggedIn to false
                logout_manager(userID);
                write(connFD, "Logging out...\n", 15);
                return;
            default:
                write(connFD, "Invalid option.\n", 16);
        }
    }
}

// Manager login function
int manager_login(int connFD) {
    char buffer[1000], userID_str[100], password[50];
    int userID;

    // Ask for manager ID
    strcpy(buffer, "Enter Manager ID: ");
    write(connFD, buffer, strlen(buffer));
    bzero(userID_str, sizeof(userID_str));
    read(connFD, userID_str, sizeof(userID_str));
    userID = atoi(userID_str);

    // Ask for password
    strcpy(buffer, "Enter Password: ");
    write(connFD, buffer, strlen(buffer));
    bzero(password, sizeof(password));
    read(connFD, password, sizeof(password));

    // Validate manager credentials
    if (authenticate_manager(connFD, userID, password)) {
        manager_menu(connFD, userID);
        return 1;
    } else {
        strcpy(buffer, "Invalid Manager ID or Password.\n");
        write(connFD, buffer, strlen(buffer));
        return 0;
    }
}

void change_manager_password(int connFD, int managerID) {
    char buffer[1000], new_password[50];
    struct User user;
    int found = 0;

    // Ask for new password
    strcpy(buffer, "Enter new password: ");
    write(connFD, buffer, strlen(buffer));
    bzero(new_password, sizeof(new_password));
    read(connFD, new_password, sizeof(new_password));

    // Open the users.txt file to read/write
    FILE *file = fopen("users.txt", "rb+");  // Open in read/write binary mode
    if (file == NULL) {
        strcpy(buffer, "Error opening users.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Search for the manager by userID
    while (fread(&user, sizeof(struct User), 1, file)) {
        if (user.userID == managerID && user.isManager == 1) {
            found = 1;
            // Update the password
            strcpy(user.password, new_password);

            // Go back to the position of this user in the file
            fseek(file, -sizeof(struct User), SEEK_CUR);
            // Write the updated record
            fwrite(&user, sizeof(struct User), 1, file);
            fclose(file);

            strcpy(buffer, "Password changed successfully.\n");
            write(connFD, buffer, strlen(buffer));
            return;
        }
    }

    fclose(file);
    if (!found) {
        strcpy(buffer, "Manager not found.\n");
        write(connFD, buffer, strlen(buffer));
    }
}


void activate_deactivate_customer(int connFD) {
    char buffer[1000], customerID_str[50];
    int customerID, found = 0;
    struct Customer customer;

    // Ask for the customer ID to be activated or deactivated
    strcpy(buffer, "Enter Customer ID to activate/deactivate: ");
    write(connFD, buffer, strlen(buffer));

    // Clear the buffer for customer ID
    bzero(customerID_str, sizeof(customerID_str));
    
    // Read customer ID
    ssize_t bytesRead = read(connFD, customerID_str, sizeof(customerID_str) - 1);
    if (bytesRead > 0) {
        customerID_str[bytesRead] = '\0'; // Ensure null-termination
        customerID_str[strcspn(customerID_str, "\n")] = '\0'; // Remove newline character
        customerID = atoi(customerID_str); // Convert to integer
    } else {
        strcpy(buffer, "Failed to read Customer ID.\n");
        write(connFD, buffer, strlen(buffer));
        return; // Exit if read fails
    }

    // Open the customers file in read/write mode
    FILE *file = fopen("customer.txt", "rb+");
    if (!file) {
        strcpy(buffer, "Error opening customer.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Search for the customer by customerID
    while (fread(&customer, sizeof(struct Customer), 1, file)) {
        if (customer.userID == customerID) {
            found = 1;

            // Toggle the activation status
            customer.isActive = !customer.isActive; // Toggle between 0 and 1
            sprintf(buffer, "Customer account %s successfully.\n",
                    customer.isActive ? "activated" : "deactivated");

            // Move the file pointer back to the start of this record
            fseek(file, -sizeof(struct Customer), SEEK_CUR);

            // Update the customer record in the file
            fwrite(&customer, sizeof(struct Customer), 1, file);
            fclose(file);

            // Inform the manager of the change
            write(connFD, buffer, strlen(buffer));
            return;
        }
    }

    fclose(file);

    if (!found) {
        strcpy(buffer, "Customer not found.\n");
        write(connFD, buffer, strlen(buffer));
    }
}

void review_feedback(int connFD) {
    char buffer[1000];
    struct Feedback feedback;
    int found = 0;

    // Open feedback.txt to read the feedback
    FILE *file = fopen("feedback.txt", "rb");
    if (file == NULL) {
        snprintf(buffer, sizeof(buffer), "Error opening feedback.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Notify the manager that feedback will be listed
    strcpy(buffer, "Customer Feedback:\n");
    write(connFD, buffer, strlen(buffer));

    // Read through all feedback entries and send them to the manager
    while (fread(&feedback, sizeof(struct Feedback), 1, file)) {
        found = 1;
        snprintf(buffer, sizeof(buffer), "Customer ID: %d\nFeedback: %s\n\n", feedback.userID, feedback.feedbackText);
        write(connFD, buffer, strlen(buffer));
    }

    fclose(file);

    // Check if any feedback was found
    if (!found) {
        strcpy(buffer, "No feedback available.\n");
        write(connFD, buffer, strlen(buffer));
    }
}

void assign_loan_to_employee(int connFD) {
    char buffer[1000], loanID_str[50], employeeID_str[50];
    struct Loan loan;
    int loanID, employeeID;
    bool loanFound = false; // Flag to check if loan is found

    // Prompt user for Loan ID
    strcpy(buffer, "Enter Loan ID to assign: ");
    write(connFD, buffer, strlen(buffer));
    
    // Clear the buffer for loan ID input
    bzero(loanID_str, sizeof(loanID_str));
    read(connFD, loanID_str, sizeof(loanID_str));
    loanID = atoi(loanID_str); // Convert to integer

    // Prompt user for Employee ID
    strcpy(buffer, "Enter Employee ID to assign the loan to: ");
    write(connFD, buffer, strlen(buffer));
    
    // Clear the buffer for employee ID input
    bzero(employeeID_str, sizeof(employeeID_str));
    read(connFD, employeeID_str, sizeof(employeeID_str));
    employeeID = atoi(employeeID_str); // Convert to integer

    // Open the loans file in read/write mode
    FILE *file = fopen("loan.txt", "r+b");
    if (file == NULL) {
        strcpy(buffer, "Error opening loan.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Search for the loan by loanID
    while (fread(&loan, sizeof(struct Loan), 1, file)) {
        if (loan.loanID == loanID) {
            loanFound = true;
            loan.assignedEmployee = employeeID; // Assign the employee ID

            // Move the file pointer back to overwrite the record
            fseek(file, -sizeof(struct Loan), SEEK_CUR);
            fwrite(&loan, sizeof(struct Loan), 1, file);
            
            // Inform the manager of the successful assignment
            sprintf(buffer, "LoanID %d has been assigned to EmployeeID %d.\n", loanID, employeeID);
            write(connFD, buffer, strlen(buffer));
            break;
        }
    }

    if (!loanFound) {
        sprintf(buffer, "LoanID %d not found.\n", loanID);
        write(connFD, buffer, strlen(buffer));
    }

    fclose(file);
}
// Function to view unassigned loans
void view_unassigned_loans(int connFD) {
    struct Loan loan;
    FILE *file = fopen("loan.txt", "r");
    if (file == NULL) {
        char *errorMsg = "Error opening loan.txt file.\n";
        write(connFD, errorMsg, strlen(errorMsg));
        return;
    }

    char buffer[1000];
    int bytesWritten;

    // Header message
    char *headerMsg = "Loans not assigned to any employee:\n";
    write(connFD, headerMsg, strlen(headerMsg));

    bool hasLoans = false;

    // Read the loan data from file and display unassigned loans
    while (fread(&loan, sizeof(struct Loan), 1, file)) {
        if (loan.assignedEmployee == 0) { // Check if the loan is unassigned
            hasLoans = true;
            // Prepare the loan information message
            bytesWritten = snprintf(buffer, sizeof(buffer), 
                "LoanID: %d, CustomerID: %d, Amount: %.2f, AccountID: %d\n",
                loan.loanID, loan.customerID, loan.amount, loan.accountID);
            write(connFD, buffer, bytesWritten);
        }
    }

    if (!hasLoans) {
        char *noLoansMsg = "No unassigned loans found.\n";
        write(connFD, noLoansMsg, strlen(noLoansMsg));
    }

    fclose(file);
}

