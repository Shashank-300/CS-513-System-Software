#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "employee.h"
#include "customer.h"
#include "user.h"
#include "loan.h"


// Path where the userID is stored
#define USER_ID_FILE "user_id.txt"

// Function to generate a unique user ID
int generate_unique_userID() {
    FILE *file;
    int userID = 1; // Starting value for user ID

    // Open the file that stores the last used user ID
    file = fopen(USER_ID_FILE, "r+");
    if (file == NULL) {
        // If file doesn't exist, create it and start with the base user ID
        file = fopen(USER_ID_FILE, "w");
        if (file == NULL) {
            printf("Error opening file!\n");
            exit(1);
        }
        fprintf(file, "%d", userID);
    } else {
        // If file exists, read the last used user ID
        fscanf(file, "%d", &userID);
        userID++; // Increment user ID to make it unique
    }

    // Write the updated user ID back to the file
    rewind(file); // Reset file pointer to the beginning
    fprintf(file, "%d", userID);
    fclose(file); // Close the file

    return userID;
}

// Path where the accountID is stored
#define ACCOUNT_ID_FILE "account_id.txt"

// Function to generate a unique account ID
int generate_unique_accountID() {
    FILE *file;
    int accountID = 1001; // Starting value for account ID

    // Open the file that stores the last used account ID
    file = fopen(ACCOUNT_ID_FILE, "r+");
    if (file == NULL) {
        // If file doesn't exist, create it and start with the base account ID
        file = fopen(ACCOUNT_ID_FILE, "w");
        if (file == NULL) {
            printf("Error opening file!\n");
            exit(1);
        }
        fprintf(file, "%d", accountID);
    } else {
        // If file exists, read the last used account ID
        fscanf(file, "%d", &accountID);
        accountID++; // Increment account ID to make it unique
    }

    // Write the updated account ID back to the file
    rewind(file); // Reset file pointer to the beginning
    fprintf(file, "%d", accountID);
    fclose(file); // Close the file

    return accountID;
}

// Function to check if user is already logged in (by checking session.txt)
int is_user_logged_in(int userID) {
    FILE *session_file = fopen("session.txt", "r");
    if (session_file == NULL) {
        return 0; // If session.txt doesn't exist, assume no one is logged in
    }

    int id;
    while (fscanf(session_file, "%d", &id) != EOF) {
        if (id == userID) {
            fclose(session_file);
            return 1; // User is already logged in
        }
    }

    fclose(session_file);
    return 0; // User is not logged in
}

// Function to add user to session.txt (indicating login)
void add_user_to_session(int userID) {
    FILE *session_file = fopen("session.txt", "a");
    if (session_file == NULL) {
        printf("Error opening session.txt\n");
        return;
    }

    fprintf(session_file, "%d\n", userID); // Add the userID to session.txt
    fclose(session_file);
}

// Function to remove user from session.txt (indicating logout)
void remove_user_from_session(int userID) {
    FILE *session_file = fopen("session.txt", "r");
    if (session_file == NULL) {
        printf("Error opening session.txt\n");
        return;
    }

    FILE *temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) {
        printf("Error creating temp file\n");
        fclose(session_file);
        return;
    }

    int id;
    while (fscanf(session_file, "%d", &id) != EOF) {
        if (id != userID) {
            fprintf(temp_file, "%d\n", id); // Copy all userIDs except the one to be removed
        }
        else 
            continue;
    }

    fclose(session_file);
    fclose(temp_file);
    remove("session.txt"); // Remove old session.txt
    rename("temp.txt", "session.txt"); // Rename temp.txt to session.txt
}


int authenticate_employee(int connFD, int userID, const char *password) {
    struct User user;
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        write(connFD, "Error opening users file.\n", 26);
        return 0;
    }

    // Check if user is already logged in
    if (is_user_logged_in(userID)) {
        write(connFD, "Error: Employee is already logged in.\n", 39);
        fclose(file);
        return 0;
    }

    // Iterate through the file to find the user
    while (fread(&user, sizeof(struct User), 1, file)) {
        if (user.userID == userID && strcmp(user.password, password) == 0) {
            if (user.isManager) {
                write(connFD, "Access Denied: Not an employee.\n", 33);
                fclose(file);
                return 0; // User is a manager, not an employee
            }

            // Add the user to the session.txt file (indicating login)
            add_user_to_session(userID);
            fclose(file);
            return 1; // Authentication successful
        }
    }

    fclose(file);
    write(connFD, "Invalid credentials.\n", 21);
    return 0; // Authentication failed
}

int employee_login(int connFD) {
    char buffer[1000], userID_str[100], password[50];
    int userID;

    // Ask for employee ID
    strcpy(buffer, "Enter Employee ID: ");
    write(connFD, buffer, strlen(buffer));
    bzero(userID_str, sizeof(userID_str));
    read(connFD, userID_str, sizeof(userID_str));
    userID = atoi(userID_str);

    // Ask for password
    strcpy(buffer, "Enter Password: ");
    write(connFD, buffer, strlen(buffer));
    bzero(password, sizeof(password));
    read(connFD, password, sizeof(password));

    // Validate employee credentials
    if (authenticate_employee(connFD, userID, password)) {
        employee_menu(connFD, userID);
        return 1;
    } else {
        strcpy(buffer, "Invalid Employee ID or Password.\n");
        write(connFD, buffer, strlen(buffer));
        return 0;
    }
}


void add_new_customer(int connFD) {
    char buffer[1000], name[100], password[50];
    struct Customer newCustomer = {0}; // Initialize all fields to 0
    struct Account newAccount = {0};   // Initialize new account structure

    FILE *customerFile = fopen("customer.txt", "ab");
    if (customerFile == NULL) {
        strcpy(buffer, "Error opening customer.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    FILE *accountFile = fopen("account.txt", "ab");
    if (accountFile == NULL) {
        strcpy(buffer, "Error opening account.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        fclose(customerFile);
        return;
    }

    // Ask for customer name
    strcpy(buffer, "Enter Customer Name: ");
    write(connFD, buffer, strlen(buffer));
    bzero(name, sizeof(name));
    ssize_t bytesRead = read(connFD, name, sizeof(name) - 1);
    if (bytesRead > 0) {
        name[bytesRead] = '\0'; // Ensure null-termination
        name[strcspn(name, "\n")] = '\0'; // Remove newline character
        strncpy(newCustomer.name, name, sizeof(newCustomer.name) - 1);
        newCustomer.name[sizeof(newCustomer.name) - 1] = '\0'; // Ensure null-termination
    }

    // Ask for customer password
    strcpy(buffer, "Enter Password: ");
    write(connFD, buffer, strlen(buffer));
    bzero(password, sizeof(password));
    bytesRead = read(connFD, password, sizeof(password) - 1);
    if (bytesRead > 0) {
        password[bytesRead] = '\0'; // Ensure null-termination
        password[strcspn(password, "\n")] = '\0'; // Remove newline character
        strncpy(newCustomer.password, password, sizeof(newCustomer.password) - 1);
        newCustomer.password[sizeof(newCustomer.password) - 1] = '\0'; // Ensure null-termination
    }

    // Assign a unique userID and accountID
    newCustomer.userID = generate_unique_userID();
    newCustomer.accountID = generate_unique_accountID();

    // Set isActive to 1 (active)
    newCustomer.isActive = 1;

    // Initialize feedback as empty
    newCustomer.feedback[0] = '\0';

    // Save the new customer to customer.txt
    fwrite(&newCustomer, sizeof(struct Customer), 1, customerFile);

    // Create a new account for the customer
    newAccount.accountID = newCustomer.accountID;
    newAccount.balance = 0.0f; // Initial balance of 0.0
    newAccount.transactionCount = 0; // No transactions initially

    // Save the new account to account.txt
    fwrite(&newAccount, sizeof(struct Account), 1, accountFile);

    // Close both files
    fclose(customerFile);
    fclose(accountFile);

    // Notify the user that the new customer and account have been added
    snprintf(buffer, sizeof(buffer), "New customer added successfully with UserID: %d and AccountID: %d\n", 
             newCustomer.userID, newCustomer.accountID);
    write(connFD, buffer, strlen(buffer));
}


void modify_customer_details(int connFD) {
    char buffer[1000], userID_str[50], new_name[100], new_password[50];
    int userID;
    struct Customer customer;
    int found = 0;

    // Ask for customer ID
    strcpy(buffer, "Enter Customer UserID to modify: ");
    write(connFD, buffer, strlen(buffer));
    bzero(userID_str, sizeof(userID_str));
    read(connFD, userID_str, sizeof(userID_str));
    userID = atoi(userID_str);

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

            // Ask for new name
            strcpy(buffer, "Enter new name: ");
            write(connFD, buffer, strlen(buffer));
            bzero(new_name, sizeof(new_name));
            read(connFD, new_name, sizeof(new_name));
            strcpy(customer.name, new_name);

            // Ask for new password
            strcpy(buffer, "Enter new password: ");
            write(connFD, buffer, strlen(buffer));
            bzero(new_password, sizeof(new_password));
            read(connFD, new_password, sizeof(new_password));
            strcpy(customer.password, new_password);

            // Update the customer record in the file
            fseek(file, -sizeof(struct Customer), SEEK_CUR);
            fwrite(&customer, sizeof(struct Customer), 1, file);
            fclose(file);

            strcpy(buffer, "Customer details updated successfully.\n");
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

void approve_reject_loans(int connFD, int employeeID) {
    struct Loan loan;
    FILE *file = fopen("loan.txt", "r+b");
    char buffer[1000];
    
    if (file == NULL) {
        strcpy(buffer, "Error opening loan.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    int found = 0;
    // Go through each loan in the file
    while (fread(&loan, sizeof(struct Loan), 1, file)) {
        // Check if the loan is assigned to the current employee and is still pending
        if (loan.assignedEmployee == employeeID && loan.isAccepted == 0) {
            found = 1;
            snprintf(buffer, sizeof(buffer), 
                     "Loan ID: %d, Customer ID: %d, Amount: %.2f\n",
                     loan.loanID, loan.customerID, loan.amount);
            write(connFD, buffer, strlen(buffer));
            
            // Ask for acceptance or rejection
            strcpy(buffer, "Do you want to accept or reject this loan? (a/r): ");
            write(connFD, buffer, strlen(buffer));
            
            char response[10];
            bzero(response, sizeof(response));
            ssize_t bytesRead = read(connFD, response, sizeof(response) - 1);
            if (bytesRead > 0) {
                response[bytesRead] = '\0';
                response[strcspn(response, "\n")] = '\0'; // Remove newline character

                if (strcmp(response, "a") == 0) {
                    loan.isAccepted = 1; // Mark the loan as accepted
                    strcpy(buffer, "Loan accepted.\n");
                } else if (strcmp(response, "r") == 0) {
                    loan.isAccepted = -1; // Mark the loan as rejected
                    strcpy(buffer, "Loan rejected.\n");
                } else {
                    strcpy(buffer, "Invalid input. Skipping this loan.\n");
                }
                write(connFD, buffer, strlen(buffer));
                
                // Move the file pointer to the start of the current loan record
                fseek(file, -sizeof(struct Loan), SEEK_CUR);
                // Update the loan status in the file
                fwrite(&loan, sizeof(struct Loan), 1, file);
                fflush(file); // Ensure the write is immediately reflected
            }
        }
    }

    if (!found) {
        strcpy(buffer, "No pending loans assigned to you.\n");
        write(connFD, buffer, strlen(buffer));
    }

    fclose(file);
}

void change_employee_password(int connFD, int userID) {
    char buffer[1000], new_password[50];
    struct User user;
    int found = 0;

    // Ask for new password
    strcpy(buffer, "Enter new password: ");
    write(connFD, buffer, strlen(buffer));
    bzero(new_password, sizeof(new_password));
    read(connFD, new_password, sizeof(new_password));

    FILE *file = fopen("users.txt", "rb+");
    if (file == NULL) {
        strcpy(buffer, "Error opening users.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Search for the user by userID (both employees and managers are in this file)
    while (fread(&user, sizeof(struct User), 1, file)) {
        if (user.userID == userID) {
            found = 1;
            strcpy(user.password, new_password);  // Update the password field

            // Move the file pointer back to the beginning of the current record
            fseek(file, -sizeof(struct User), SEEK_CUR);

            // Write the updated user record back to the file
            fwrite(&user, sizeof(struct User), 1, file);
            fclose(file);

            strcpy(buffer, "Password changed successfully.\n");
            write(connFD, buffer, strlen(buffer));
            return;
        }
    }

    fclose(file);

    // If the userID was not found, inform the client
    if (!found) {
        strcpy(buffer, "User not found.\n");
        write(connFD, buffer, strlen(buffer));
    }
}

// :)))))))))
// :(((((((((
void view_customer_transactions(int connFD) {
    char buffer[1000], userID_str[50];
    int userID, accountID = -1;
    struct Customer customer;
    struct Account account;

    // Ask for the user ID
    strcpy(buffer, "Enter your Customer UserID: ");
    write(connFD, buffer, strlen(buffer));
    bzero(userID_str, sizeof(userID_str));
    read(connFD, userID_str, sizeof(userID_str));
    userID = atoi(userID_str); // Convert input to integer

    // Open the customer file to retrieve the accountID using the provided userID
    FILE *customer_file = fopen("customer.txt", "rb");
    if (customer_file == NULL) {
        strcpy(buffer, "Error opening customers.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    int found_customer = 0;

    // Search for the customer by userID
    while (fread(&customer, sizeof(struct Customer), 1, customer_file)) {
        if (customer.userID == userID) {
            accountID = customer.accountID; // Retrieve accountID from the customer
            found_customer = 1;
            break;
        }
    }

    fclose(customer_file);

    if (!found_customer) {
        strcpy(buffer, "Customer not found.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Now, retrieve the transaction history for the found accountID
    FILE *account_file = fopen("account.txt", "rb");
    if (account_file == NULL) {
        strcpy(buffer, "Error opening account.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    int found_account = 0;

    // Search for the account using the accountID
    while (fread(&account, sizeof(struct Account), 1, account_file)) {
        if (account.accountID == accountID) {
            found_account = 1;

            // Display transaction history
            snprintf(buffer, sizeof(buffer), "Transaction history for Account ID %d:\n", accountID);
            write(connFD, buffer, strlen(buffer));

            for (int i = 0; i < account.transactionCount; i++) {
                snprintf(buffer, sizeof(buffer), "%s\n", account.transactions[i]);
                write(connFD, buffer, strlen(buffer));
            }

            break;
        }
    }

    fclose(account_file);

    if (!found_account) {
        strcpy(buffer, "No transactions found for the specified account ID.\n");
        write(connFD, buffer, strlen(buffer));
    }
}


// Function to logout and set isLoggedIn to false
void logout_employee(int connFD, int userID) {
    remove_user_from_session(userID); // Remove from session.txt
    write(connFD, "Logging out...\n", 15);

    // Close the connection for the client after logging out
    close(connFD);
    printf("Employee (UserID: %d) logged out successfully and connection closed.\n", userID);
}


void employee_menu(int connFD, int employeeID) {
    char buffer[1000];
    int choice;

    while (1) {
        // Display menu options
        strcpy(buffer, "\n--- Employee Menu ---\n"
                       "1. Add New Customer\n"
                       "2. Modify Customer Details\n"
                       "3. Approve/Reject Loans\n"
                       "4. View Assigned Loan Applications\n"
                       "5. View Customer Transactions\n"
                       "6. Change Password\n"
                       "7. Logout\n"
                       "Enter your choice: ");
        write(connFD, buffer, strlen(buffer));

        // Get employee's choice
        bzero(buffer, sizeof(buffer));
        read(connFD, buffer, sizeof(buffer));
        choice = atoi(buffer);

        // Perform action based on choice
        switch (choice) {
            case 1:
                add_new_customer(connFD);
                break;
            case 2:
                modify_customer_details(connFD);
                break;
            case 3:
                approve_reject_loans(connFD,employeeID);
                break;
            case 4:
                view_assigned_loans(connFD);
                break;
            case 5:
                view_customer_transactions(connFD);
                break;
            case 6:
                change_employee_password(connFD,employeeID);
                break;
            case 7:
                logout_employee(connFD, employeeID);
                return;  // Exit the menu after logout
            default:
                strcpy(buffer, "Invalid choice. Please try again.\n");
                write(connFD, buffer, strlen(buffer));
        }
    }
}

void view_assigned_loans(int employeeID) {
    struct Loan loan;
    FILE *file = fopen("loan.txt", "r");
    if (file == NULL) {
        printf("Error opening loan.txt file.\n");
        return;
    }

    printf("Loans assigned to EmployeeID %d:\n", employeeID);
    bool hasLoans = false;
    while (fread(&loan, sizeof(struct Loan), 1, file)) {
        if (loan.assignedEmployee == employeeID) {
            hasLoans = true;
            printf("LoanID: %d, CustomerID: %d, Amount: %.2f, AccountID: %d\n",
                   loan.loanID, loan.customerID, loan.amount, loan.accountID);
        }
    }

    if (!hasLoans) {
        printf("No loans assigned to EmployeeID %d.\n", employeeID);
    }

    fclose(file);
}
