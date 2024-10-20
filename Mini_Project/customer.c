#include <stdio.h>
#include <string.h>
#include <unistd.h>    // For read, write, close functions
#include <stdlib.h>
#include "customer.h"  // Include the header file with declarations
#include "account.h"
#include <fcntl.h>
#include "feedback.h"
#include "loan.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"  // Ensure this header includes the Account structure

// Function to save transaction for a customer
void save_transaction(int accountID, const char *transactionType, float amount) {
    char transaction[MAX_TRANSACTION_LEN];
    struct Account account; // Temporary variable to hold account data
    FILE *accountFile;

    // Open the account file in read/write mode
    accountFile = fopen("account.txt", "r+b");
    if (accountFile == NULL) {
        printf("Error opening account.txt file.\n");
        return;
    }

    // Format the transaction message
    snprintf(transaction, sizeof(transaction), "%s %.2f", transactionType, amount);

    // Read through the accounts to find the matching accountID
    while (fread(&account, sizeof(struct Account), 1, accountFile) == 1) {
        if (account.accountID == accountID) {
            // Check if there is space for a new transaction
            if (account.transactionCount < MAX_TRANSACTIONS) {
                // Add the new transaction to the account's transaction history
                strncpy(account.transactions[account.transactionCount], transaction, sizeof(account.transactions[0]) - 1);
                account.transactions[account.transactionCount][sizeof(account.transactions[0]) - 1] = '\0'; // Ensure null-termination
                account.transactionCount++; // Increment the transaction count

                // Move the file pointer back to the position of the current account
                fseek(accountFile, -sizeof(struct Account), SEEK_CUR);
                // Write the updated account back to the file
                fwrite(&account, sizeof(struct Account), 1, accountFile);
                printf("Transaction saved: %s\n", transaction);
            } else {
                printf("Transaction history full. Unable to save transaction.\n");
            }
            break; // Exit loop after processing the correct account
        }
    }

    fclose(accountFile); // Close the account file
}


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

// Function to lock the file for read/write operations
void lock_file(int fd, short lock_type) {
    struct flock lock;
    lock.l_type = lock_type;   // F_RDLCK for read, F_WRLCK for write
    lock.l_whence = SEEK_SET;  // Start of the file
    lock.l_start = 0;          // Offset from the start
    lock.l_len = 0;            // Lock the whole file (0 means entire file)
    lock.l_pid = getpid();     // Process ID

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Error locking file");
        exit(EXIT_FAILURE);
    }
}

// Function to unlock the file after the operation
void unlock_file(int fd) {
    struct flock lock;
    lock.l_type = F_UNLCK;    // Unlock the file
    lock.l_whence = SEEK_SET; // Start of the file
    lock.l_start = 0;         // Offset from the start
    lock.l_len = 0;           // Unlock the whole file

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Error unlocking file");
        exit(EXIT_FAILURE);
    }
}

int authenticate_customer(int userID, const char *password) {
    struct Customer customer;
    
    // Open the file where customer credentials are stored
    FILE *file = fopen("customer.txt", "rb");
    if (file == NULL) {
        // If the file doesn't exist, initialize it
        initialize_customers();
        
        // After initializifunctions/account.txtng, reopen the file for reading
        file = fopen("customer.txt", "rb+");
        if (file == NULL) {
            printf("Error opening customer.txt file for reading.\n");
            return 0;
        }
    }

    // Read each customer record from the file and check for matching credentials
    while (fread(&customer, sizeof(struct Customer), 1, file)) {
        if (customer.userID == userID && strcmp(customer.password, password) == 0) {
            fclose(file);
            return 1;  // Authentication successful
        }
    }
    fclose(file);
    return 0;  // Authentication failed
}

// Function to retrieve account details based on accountID
struct Account* get_account_by_id(int accountID) {
    FILE *file = fopen("account.txt", "rw");
    if (file == NULL) {
        printf("Error opening account.txt file.\n");
        return NULL;
    }

    struct Account *account = (struct Account*)malloc(sizeof(struct Account));

    // Read through the file and find the account with the matching accountID
    while (fread(account, sizeof(struct Account), 1, file)) {
        if (account->accountID == accountID) {
            fclose(file);
            return account;
        }
    }

    fclose(file);
    free(account);
    return NULL; // Account not found
}

// Function to update the account in the file after changes
void update_account(struct Account *account) {
    FILE *file = fopen("account.txt", "rw");
    if (file == NULL) {
        printf("Error opening account.txt file.\n");
        return;
    }

    struct Account temp;
    
    // Update the correct account by searching for matching accountID
    while (fread(&temp, sizeof(struct Account), 1, file)) {
        if (temp.accountID == account->accountID) {
            fseek(file, -sizeof(struct Account), SEEK_CUR); // Move file pointer back to overwrite
            fwrite(account, sizeof(struct Account), 1, file);
            break;
        }
    }

    fclose(file);
}

void customer_login(int connFD) {
    char buffer[1024], input[50];
    int userID;
    char password[MAX_PASSWORD_LENGTH];
    
    // Prompt for userID
    bzero(buffer, sizeof(buffer));
    strcpy(buffer, "Enter User ID: ");
    write(connFD, buffer, strlen(buffer));
    bzero(input, sizeof(input));
    read(connFD, input, sizeof(input));
    input[strcspn(input, "\n")] = 0;  // Remove newline character
    userID = atoi(input);

    // Prompt for password
    bzero(buffer, sizeof(buffer));
    strcpy(buffer, "Enter Password: ");
    write(connFD, buffer, strlen(buffer));
    bzero(password, sizeof(password));
    read(connFD, password, sizeof(password));
    password[strcspn(password, "\n")] = 0;  // Remove newline character

    // Authenticate customer
    if (authenticate_customer(userID, password)) {
        // Call customer_menu with userID
        customer_menu(connFD, userID);
    } else {
        strcpy(buffer, "Login failed. Invalid User ID or password.\n");
        write(connFD, buffer, strlen(buffer));
    }
}

void customer_menu(int connFD, int userID) {
    char buffer[1000];
    int choice;
    
    do {
        // Display menu
        strcpy(buffer, "\nCustomer Menu:\n1. View Account Balance\n2. Deposit Money\n3. Withdraw Money\n4. Transfer Funds\n5. Apply for Loan\n6. Change Password\n7. Add Feedback\n8. View Transaction History\n9. Logout\nEnter your choice: ");
        fflush(stdout);
        write(connFD, buffer, strlen(buffer));
        
        // Get user's choice
        bzero(buffer, sizeof(buffer));
        read(connFD, buffer, sizeof(buffer));  // Read user's input
        buffer[strcspn(buffer, "\n")] = 0;     // Remove any newline characters
        choice = atoi(buffer);                 // Convert choice to integer
        
        switch(choice) {
            case 1:
                view_account_balance(connFD, userID);
                break;
            case 2:
                deposit_money(connFD,userID);
                break;
            case 3:
                withdraw_money(connFD,userID);
                break;
            case 4:
                transfer_funds(connFD,userID);
                break;
            case 5:
                apply_for_loan(connFD,userID);
                break;
            case 6:
                change_password(connFD,userID);
                break;
            case 7:
                add_customer_feedback(connFD,userID);
                break;
            case 8:
                view_transaction(connFD,userID);
                break;
            case 9:
                strcpy(buffer, "Logout successful!\n");
                write(connFD, buffer, strlen(buffer));
                break;
            default:
                strcpy(buffer, "Invalid choice! Please try again.\n");
                write(connFD, buffer, strlen(buffer));
                fflush(stdout); 
        }
    } while (choice != 9);  // Stay in the loop until the user chooses to log out

    // After logout, close the connection
    strcpy(buffer, "Closing the connection to the server now!\n");
    write(connFD, buffer, strlen(buffer));
    close(connFD);
}

// View account balance
void view_account_balance(int connFD, int userID) {
    struct Customer customer;
    struct Account *account;
    FILE *file = fopen("customer.txt", "rb");

    // Find the customer by userID
    while (fread(&customer, sizeof(struct Customer), 1, file)) {
        if (customer.userID == userID) {
            fclose(file);
            account = get_account_by_id(customer.accountID); // Get associated account
            if (account != NULL) {
                char buffer[1000];
                snprintf(buffer, sizeof(buffer), "Your current account balance is $%.2f.\n", account->balance);
                write(connFD, buffer, strlen(buffer));
                free(account); // Free allocated memory for account
            } else {
                write(connFD, "Account not found.\n", 20);
            }
            return;
        }
    }
    fclose(file);
}
// Deposit money into account
void deposit_money(int connFD, int userID) {
    char buffer[1000], amount_str[100];
    double deposit_amount;
    struct Customer customer;
    struct Account account;
    int found = 0;

    // Ask for the amount to deposit
    strcpy(buffer, "Enter the amount to deposit: ");
    write(connFD, buffer, strlen(buffer));
    bzero(amount_str, sizeof(amount_str));
    read(connFD, amount_str, sizeof(amount_str));
    deposit_amount = atof(amount_str);

    // Validate deposit amount
    if (deposit_amount <= 0) {
        strcpy(buffer, "Invalid deposit amount. Must be greater than 0.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Open the customer file to find the account ID of the user
    FILE *customer_file = fopen("customer.txt", "rb");
    if (customer_file == NULL) {
        strcpy(buffer, "Error opening customer.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Find the customer by userID
    while (fread(&customer, sizeof(struct Customer), 1, customer_file)) {
        if (customer.userID == userID) {
            fclose(customer_file);

            // Open the account file in read/write mode
            FILE *account_file = fopen("account.txt", "rb+");
            if (account_file == NULL) {
                strcpy(buffer, "Error opening account.txt file.\n");
                write(connFD, buffer, strlen(buffer));
                return;
            }

            // Lock the file before performing the deposit
            int account_fd = fileno(account_file);
            lock_file(account_fd, F_WRLCK);  // Acquire write lock

            // Read the accounts and find the one with the matching accountID
            while (fread(&account, sizeof(struct Account), 1, account_file)) {
                if (account.accountID == customer.accountID) {
                    found = 1;

                    // Debugging: Show current account balance before the deposit
                    printf("Current balance before deposit: $%.2f\n", account.balance);

                    // Perform the deposit
                    account.balance += deposit_amount;

                    // Log the transaction
                    if (account.transactionCount < MAX_TRANSACTIONS) {
                        snprintf(account.transactions[account.transactionCount], MAX_TRANSACTION_LEN, "Deposit $%.2f", deposit_amount);
                        account.transactionCount++; // Increment transaction count
                    } else {
                        printf("Transaction log is full. Cannot log this deposit.\n");
                    }

                    // Debugging: Show new balance after the deposit
                    printf("New balance after deposit: $%.2f\n", account.balance);

                    // Move the file pointer back to the correct position
                    fseek(account_file, -sizeof(struct Account), SEEK_CUR);

                    // Write the updated account data back to the file
                    if (fwrite(&account, sizeof(struct Account), 1, account_file) != 1) {
                        printf("Error writing to account file.\n");
                    } else {
                        // Log the successful deposit
                        save_transaction(account.accountID, "Deposit", deposit_amount);
                        snprintf(buffer, sizeof(buffer), "Deposit successful! New balance: $%.2f\n", account.balance);
                        write(connFD, buffer, strlen(buffer));
                    }

                    break; // Exit the loop once the account is updated
                }
            }

            if (!found) {
                strcpy(buffer, "Account not found.\n");
                write(connFD, buffer, strlen(buffer));
            }

            // Unlock the file after the operation
            unlock_file(account_fd);
            fclose(account_file);
            return;
        }
    }

    fclose(customer_file);
    strcpy(buffer, "Customer not found.\n");
    write(connFD, buffer, strlen(buffer));
}


// Withdraw money from account
void withdraw_money(int connFD, int userID) {
    char buffer[1000], amount_str[100];
    double withdraw_amount;
    struct Customer customer;
    struct Account account;
    int found = 0;

    // Ask for the amount to withdraw
    strcpy(buffer, "Enter the amount to withdraw: ");
    write(connFD, buffer, strlen(buffer));
    bzero(amount_str, sizeof(amount_str));
    read(connFD, amount_str, sizeof(amount_str));
    withdraw_amount = atof(amount_str);

    // Open the customer file to find the account ID of the user
    FILE *customer_file = fopen("customer.txt", "rb");
    if (customer_file == NULL) {
        strcpy(buffer, "Error opening customer.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Find the customer by userID
    while (fread(&customer, sizeof(struct Customer), 1, customer_file)) {
        if (customer.userID == userID) {
            fclose(customer_file);

            // Open the account file in read/write mode
            FILE *account_file = fopen("account.txt", "rb+");
            if (account_file == NULL) {
                strcpy(buffer, "Error opening account.txt file.\n");
                write(connFD, buffer, strlen(buffer));
                return;
            }

            // Read the accounts and find the one with the matching accountID
            while (fread(&account, sizeof(struct Account), 1, account_file)) {
                if (account.accountID == customer.accountID) {
                    found = 1;

                    // Lock the file before performing the withdrawal
                    int account_fd = fileno(account_file);
                    lock_file(account_fd, F_WRLCK);  // Acquire write lock

                    // Check if there's enough balance for the withdrawal
                    if (account.balance >= withdraw_amount) {
                        // Perform the withdrawal
                        account.balance -= withdraw_amount;
                        snprintf(account.transactions[account.transactionCount], MAX_TRANSACTION_LEN, "Withdraw $%.2f", withdraw_amount);
    account.transactionCount++; // Increment transaction count

                        // Move the file pointer back to the correct position
                        fseek(account_file, -sizeof(struct Account), SEEK_CUR);

                        // Write the updated account data back to the file
                        fwrite(&account, sizeof(struct Account), 1, account_file);

                        // Check if the file write was successful
                        if (ferror(account_file)) {
                            printf("Error writing to account file.\n");
                        }

                        // Unlock the file after the operation
                        unlock_file(account_fd);

                        
                        snprintf(buffer, sizeof(buffer), "Withdrawal successful! New balance: $%.2f\n", account.balance);
                        save_transaction(account.accountID,"Withdraw",withdraw_amount);
                    } else {
                        snprintf(buffer, sizeof(buffer), "Insufficient balance for the withdrawal.\n");
                    }

                    fclose(account_file);
                    write(connFD, buffer, strlen(buffer));
                    return;  // Exit after successful withdrawal or balance check
                }
            }

            if (!found) {
                strcpy(buffer, "Account not found.\n");
                write(connFD, buffer, strlen(buffer));
            }
            return;  // Exit if customer found but account not found
        }
    }

    fclose(customer_file);
    strcpy(buffer, "Customer not found.\n");
    write(connFD, buffer, strlen(buffer));
}

// Transfer funds from the current user's account to another user's account
// Transfer funds from the current user's account to another user's account
void transfer_funds(int connFD, int senderID) {
    char buffer[1000], amount_str[100];
    double transfer_amount;
    struct Customer sender_customer, recipient_customer; // Declare both customers here
    struct Account sender_account, recipient_account;
    int found_sender = 0, found_recipient = 0;
    int recipientID;

    // Ask for the recipient User ID and the transfer amount
    strcpy(buffer, "Enter the User ID of the recipient: ");
    write(connFD, buffer, strlen(buffer));
    bzero(buffer, sizeof(buffer));
    read(connFD, buffer, sizeof(buffer));
    recipientID = atoi(buffer);

    strcpy(buffer, "Enter the amount to transfer: ");
    write(connFD, buffer, strlen(buffer));
    bzero(amount_str, sizeof(amount_str));
    read(connFD, amount_str, sizeof(amount_str));
    transfer_amount = atof(amount_str);

    // Open the customer file to find the sender's account ID
    FILE *customer_file = fopen("customer.txt", "rb");
    if (customer_file == NULL) {
        strcpy(buffer, "Error opening customer.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Find the sender customer by senderID
    while (fread(&sender_customer, sizeof(struct Customer), 1, customer_file)) {
        if (sender_customer.userID == senderID) {
            found_sender = 1;
            break;
        }
    }

    if (!found_sender) {
        strcpy(buffer, "Sender not found.\n");
        write(connFD, buffer, strlen(buffer));
        fclose(customer_file);
        return;
    }

    fclose(customer_file);

    // Open the account file to find the sender's account
    FILE *account_file = fopen("account.txt", "rb+");
    if (account_file == NULL) {
        strcpy(buffer, "Error opening account.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Find the sender's account based on the customer account ID
    while (fread(&sender_account, sizeof(struct Account), 1, account_file)) {
        if (sender_account.accountID == sender_customer.accountID) {
            found_sender = 1;
            break;
        }
    }

    if (!found_sender) {
        strcpy(buffer, "Sender account not found.\n");
        write(connFD, buffer, strlen(buffer));
        fclose(account_file);
        return;
    }

    // Now, find the recipient customer by recipientID
    FILE *recipient_customer_file = fopen("customer.txt", "rb");
    if (recipient_customer_file == NULL) {
        strcpy(buffer, "Error opening customer.txt file for recipient.\n");
        write(connFD, buffer, strlen(buffer));
        fclose(account_file);
        return;
    }

    // Find the recipient customer
    while (fread(&recipient_customer, sizeof(struct Customer), 1, recipient_customer_file)) {
        if (recipient_customer.userID == recipientID) {
            found_recipient = 1;
            break;
        }
    }

    fclose(recipient_customer_file); // Close the recipient customer file

    if (!found_recipient) {
        strcpy(buffer, "Recipient customer not found.\n");
        write(connFD, buffer, strlen(buffer));
        fclose(account_file);
        return;
    }

    // Now, find the recipient's account based on the recipient's account ID
    rewind(account_file);  // Reset the pointer to the beginning
    while (fread(&recipient_account, sizeof(struct Account), 1, account_file)) {
        if (recipient_account.accountID == recipient_customer.accountID) { // Compare with account ID
            found_recipient = 1;
            break;
        }
    }

    if (!found_recipient) {
        strcpy(buffer, "Recipient account not found.\n");
        write(connFD, buffer, strlen(buffer));
        fclose(account_file);
        return;
    }

    // Perform the transfer: deduct from sender and add to recipient
    if (sender_account.balance >= transfer_amount) {
        // Lock the file before performing the transactions
        int account_fd = fileno(account_file);
        lock_file(account_fd, F_WRLCK);  // Acquire write lock

        // Deduct from sender
        sender_account.balance -= transfer_amount;

        // Add to recipient
        recipient_account.balance += transfer_amount;

        // Move the file pointer to the correct positions for each account
        fseek(account_file, -sizeof(struct Account), SEEK_CUR); // Move back to sender's position
        fwrite(&sender_account, sizeof(struct Account), 1, account_file); // Update sender account

        // Move to recipient's position
        fseek(account_file, -sizeof(struct Account) * 2, SEEK_CUR); // Adjust to recipient's position
        fwrite(&recipient_account, sizeof(struct Account), 1, account_file); // Update recipient account

        // Unlock the file after the operation
        unlock_file(account_fd);

        snprintf(buffer, sizeof(buffer), "Transfer successful! New balance: $%.2f\n", sender_account.balance);
        write(connFD, buffer, strlen(buffer));
    } else {
        snprintf(buffer, sizeof(buffer), "Insufficient balance in sender account.\n");
        write(connFD, buffer, strlen(buffer));
    }

    fclose(account_file);
}


// // Path where the loanID is stored
// Path where the userID is stored
#define USER_ID_FILE "last_loan_id.txt"

// Function to generate a unique loan ID
int generate_unique_loanID() {
    FILE *file;
    int loanID = 1; // Starting value for loan ID

    // Open the file that stores the last used loan ID
    file = fopen(USER_ID_FILE, "r+");
    if (file == NULL) {
        // If file doesn't exist, create it and start with the base loan ID
        file = fopen(USER_ID_FILE, "w");
        if (file == NULL) {
            printf("Error opening file!\n");
            exit(1);
        }
        fprintf(file, "%d", loanID);
    } else {
        // If file exists, read the last used loan ID
        fscanf(file, "%d", &loanID);
        loanID++; // Increment loan ID to make it unique
    }

    // Write the updated loan ID back to the file
    rewind(file); // Reset file pointer to the beginning
    fprintf(file, "%d", loanID);
    fclose(file); // Close the file

    return loanID;
}

void apply_for_loan(int connFD, int customerID) {
    struct Customer customer;
    struct Loan new_loan;
    char buffer[100];
    int accountID = -1;

    // Open the customer file to retrieve the accountID
    FILE *customer_file = fopen("customer.txt", "rb");
    if (customer_file == NULL) {
        strcpy(buffer, "Error opening customers.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Search for the customer by customerID
    int found = 0;
    while (fread(&customer, sizeof(struct Customer), 1, customer_file)) {
        if (customer.userID == customerID) {
            found = 1;
            accountID = customer.accountID; // Retrieve the accountID from the customer structure
            break;
        }
    }
    fclose(customer_file);

    if (!found) {
        strcpy(buffer, "Customer not found.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Ask for the loan amount
    strcpy(buffer, "Enter the loan amount: ");
    write(connFD, buffer, strlen(buffer));
    bzero(buffer, sizeof(buffer));
    read(connFD, buffer, sizeof(buffer));
    new_loan.amount = atof(buffer); // Convert input to double

    // Fill in the loan details
    new_loan.customerID = customerID;
    new_loan.loanID = generate_unique_loanID(); // Generate unique loan ID
    new_loan.assignedEmployee = 0; // Initially unassigned
    new_loan.accountID = accountID; // Use retrieved accountID
    new_loan.isAccepted = 0; // Initially not accepted

    // Write the loan details to a file
    FILE *loan_file = fopen("loan.txt", "ab"); // Open for appending
    if (loan_file == NULL) {
        strcpy(buffer, "Error opening loan.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    fwrite(&new_loan, sizeof(struct Loan), 1, loan_file); // Write the loan structure
    fclose(loan_file);

    strcpy(buffer, "Loan application submitted successfully.\n");
    write(connFD, buffer, strlen(buffer));
}


// Function for customer to add feedback
void add_customer_feedback(int connFD, int userID) {
    char buffer[1000], feedbackText[500];
    struct Feedback feedback;

    // Ask for feedback
    strcpy(buffer, "Enter your feedback: ");
    write(connFD, buffer, strlen(buffer));
    bzero(feedbackText, sizeof(feedbackText));
    read(connFD, feedbackText, sizeof(feedbackText));

    // Fill feedback structure
    feedback.userID = userID;
    strcpy(feedback.feedbackText, feedbackText);

    // Append feedback to feedback.txt
    FILE *file = fopen("feedback.txt", "rw");
    if (file == NULL) {
        strcpy(buffer, "Error opening feedback.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    fwrite(&feedback, sizeof(struct Feedback), 1, file);
    fclose(file);

    strcpy(buffer, "Feedback submitted successfully.\n");
    write(connFD, buffer, strlen(buffer));
}

void view_transaction(int connFD, int userID) {
    char buffer[1000];
    struct Customer customer;
    struct Account account;
    int found = 0;

    // Open the customer file to find the account ID of the user
    FILE *customer_file = fopen("customer.txt", "rb");
    if (customer_file == NULL) {
        strcpy(buffer, "Error opening customer.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Find the customer by userID
    while (fread(&customer, sizeof(struct Customer), 1, customer_file)) {
        if (customer.userID == userID) {
            fclose(customer_file);

            // Open the account file in read mode
            FILE *account_file = fopen("account.txt", "rb");
            if (account_file == NULL) {
                strcpy(buffer, "Error opening account.txt file.\n");
                write(connFD, buffer, strlen(buffer));
                return;
            }

            // Read the accounts and find the one with the matching accountID
            while (fread(&account, sizeof(struct Account), 1, account_file)) {
                if (account.accountID == customer.accountID) {
                    found = 1;

                    // Prepare to send the transaction history
                    snprintf(buffer, sizeof(buffer), "Transaction History for Account ID %d:\n", account.accountID);
                    write(connFD, buffer, strlen(buffer));

                    // Display each transaction
                    for (int i = 0; i < account.transactionCount; i++) {
                        snprintf(buffer, sizeof(buffer), "%s\n", account.transactions[i]);
                        write(connFD, buffer, strlen(buffer));
                    }

                    if (account.transactionCount == 0) {
                        strcpy(buffer, "No transactions found.\n");
                        write(connFD, buffer, strlen(buffer));
                    }

                    fclose(account_file);
                    return; // Exit after processing the found account
                }
            }

            fclose(account_file);
            strcpy(buffer, "Account not found.\n");
            write(connFD, buffer, strlen(buffer));
            return; // Exit if no account was found
        }
    }

    fclose(customer_file);
    strcpy(buffer, "Customer not found.\n");
    write(connFD, buffer, strlen(buffer));
}


void change_password(int connFD, int userID) {
    char buffer[1024], old_password[MAX_PASSWORD_LENGTH], new_password[MAX_PASSWORD_LENGTH], confirm_password[MAX_PASSWORD_LENGTH];
    struct Customer customer;
    FILE *file;

    // Open the customer file
    file = fopen("customer.txt", "rb+");
    if (file == NULL) {
        strcpy(buffer, "Error opening customer.txt file.\n");
        write(connFD, buffer, strlen(buffer));
        return;
    }

    // Find the customer by userID
    int found = 0;
    while (fread(&customer, sizeof(struct Customer), 1, file)) {
        if (customer.userID == userID) {
            found = 1;
            break;
        }
    }

    if (!found) {
        strcpy(buffer, "Customer not found.\n");
        write(connFD, buffer, strlen(buffer));
        fclose(file);
        return;
    }

    // Prompt for old password
    bzero(buffer, sizeof(buffer));
    strcpy(buffer, "Enter your old password: ");
    write(connFD, buffer, strlen(buffer));
    bzero(old_password, sizeof(old_password));
    read(connFD, old_password, sizeof(old_password));
    old_password[strcspn(old_password, "\n")] = 0;  // Remove newline character

    // Check if the old password matches
    if (strcmp(customer.password, old_password) != 0) {
        strcpy(buffer, "Old password is incorrect.\n");
        write(connFD, buffer, strlen(buffer));
        fclose(file);
        return;
    }

    // Prompt for new password
    bzero(buffer, sizeof(buffer));
    strcpy(buffer, "Enter your new password: ");
    write(connFD, buffer, strlen(buffer));
    bzero(new_password, sizeof(new_password));
    read(connFD, new_password, sizeof(new_password));
    new_password[strcspn(new_password, "\n")] = 0;  // Remove newline character

    // Prompt to confirm the new password
    bzero(buffer, sizeof(buffer));
    strcpy(buffer, "Confirm your new password: ");
    write(connFD, buffer, strlen(buffer));
    bzero(confirm_password, sizeof(confirm_password));
    read(connFD, confirm_password, sizeof(confirm_password));
    confirm_password[strcspn(confirm_password, "\n")] = 0;  // Remove newline character

    // Check if new password and confirm password match
    if (strcmp(new_password, confirm_password) != 0) {
        strcpy(buffer, "New password and confirmation do not match.\n");
        write(connFD, buffer, strlen(buffer));
        fclose(file);
        return;
    }

    // Lock the file before modifying
    int fd = fileno(file);
    lock_file(fd, F_WRLCK);  // Lock for writing

    // Update the password in the customer structure
    strcpy(customer.password, new_password);

    // Move file pointer to the correct position and update the record
    fseek(file, -sizeof(struct Customer), SEEK_CUR);
    fwrite(&customer, sizeof(struct Customer), 1, file);

    // Unlock the file after writing
    unlock_file(fd);

    // Close the file
    fclose(file);

    // Inform the customer that their password has been changed
    strcpy(buffer, "Password changed successfully.\n");
    write(connFD, buffer, strlen(buffer));
}
