#ifndef SERVER_CONSTANTS_H
#define SERVER_CONSTANTS_H


// ========== COMMON TEXT =============================

// LOGIN
#define LOGIN_ID "Enter your login ID"
#define PASSWORD "Enter your password \n# "
#define INVALID_LOGIN "The login ID specified doesn't exist!$"
#define INVALID_PASSWORD "The password specified doesn't match!$"
#define SALT_BAE "666"

// GET ACCOUNT DETAILS
#define GET_ACCOUNT_NUMBER "Enter the account number of the account you're searching for"
#define GET_CUSTOMER_ID "Enter the customer ID of the customer you're searching for"

#define ERRON_INPUT_FOR_NUMBER "It seems you have passed a sequence of alphabets when a number was expected or you have entered an invalid number!\nYou'll now be redirected to the main menu!^"

#define INVALID_MENU_CHOICE "It seems you've made an invalid menu choice\nYou'll now be redirected to the main menu!^"

#define CUSTOMER_ID_DOESNT_EXIT "No customer could be found for the given ID"
#define CUSTOMER_LOGIN_ID_DOESNT_EXIT "No customer could be found for the given login ID$"

#define ACCOUNT_ID_DOESNT_EXIT "No account could be found for the given account number"

#define TRANSACTIONS_NOT_FOUND "No transactions were performed on this account by the customer!^"

// ====================================================

// ========== ADMIN SPECIFIC TEXT =======================

// LOGIN WELCOME
#define ADMIN_LOGIN_WELCOME "Welcome dear admin! With great power comes great responsibility!\nEnter your credentials to unlock this power!"
#define ADMIN_LOGIN_SUCCESS "Welcome superman!"

// ADMIN MENU
#define ADMIN_MENU "1. Add New Bank Employee\n2. Modify Customer/Employee Details\n3. Manage User Roles\n4. Change Password\nPress any other key to logout"

// ADD EMPLOYEE
#define ADMIN_ADD_EMPLOYEE_NAME "Enter the employee's name"
#define ADMIN_ADD_EMPLOYEE_SUCCESS "Employee added successfully!"

#define ADMIN_LOGOUT "Logging you out now superman! Good bye!$"

// ====================================================

// ========== CUSTOMER SPECIFIC TEXT ====================

// LOGIN WELCOME
#define CUSTOMER_LOGIN_WELCOME "Welcome dear customer! Enter your credentials to gain access to your account!"
#define CUSTOMER_LOGIN_SUCCESS "Welcome beloved customer!"

#define CUSTOMER_LOGOUT "Logging you out now dear customer! Good bye!$"

// CUSTOMER MENU
#define CUSTOMER_MENU "1. View Account Balance\n2. Deposit Money\n3. Withdraw Money\n4. Transfer Funds\n5. Apply for a Loan\n6. View Transaction History\n7. Change Password\n8. Add Feedback\nPress any other key to logout"

#define ACCOUNT_DEACTIVATED "It seems your account has been deactivated!^"

// DEPOSIT/WITHDRAW/TRANSFER
#define DEPOSIT_AMOUNT "How much would you like to deposit?"
#define WITHDRAW_AMOUNT "How much would you like to withdraw?"
#define TRANSFER_FUNDS "Enter the account number to transfer funds to"
#define TRANSACTION_SUCCESS "Transaction successful!^"

// PASSWORD CHANGE
#define PASSWORD_CHANGE_SUCCESS "Password successfully changed!^"

// ====================================================

// ========== BANK EMPLOYEE SPECIFIC TEXT ================

// LOGIN WELCOME
#define EMPLOYEE_LOGIN_WELCOME "Welcome dear employee! Enter your credentials!"
#define EMPLOYEE_LOGIN_SUCCESS "Welcome onboard!"

// EMPLOYEE MENU
#define EMPLOYEE_MENU "1. Add New Customer\n2. Modify Customer Details\n3. Process Loan Applications\n4. Approve/Reject Loans\n5. View Assigned Loan Applications\n6. View Customer Transactions\n7. Change Password\nPress any other key to logout"

#define EMPLOYEE_LOGOUT "Logging you out now! Good bye!$"

// ADD/MODIFY CUSTOMER
#define EMPLOYEE_ADD_CUSTOMER "Enter customer details to add."
#define EMPLOYEE_MODIFY_CUSTOMER "Enter customer details to modify."

// LOAN PROCESSING
#define EMPLOYEE_LOAN_SUCCESS "Loan processed successfully!"
#define EMPLOYEE_LOAN_REJECT "Loan application rejected!"

// ====================================================

// ========== MANAGER SPECIFIC TEXT =====================

// LOGIN WELCOME
#define MANAGER_LOGIN_WELCOME "Welcome Manager! Enter your credentials."
#define MANAGER_LOGIN_SUCCESS "Welcome manager!"

// MANAGER MENU
#define MANAGER_MENU "1. Activate/Deactivate Customer Accounts\n2. Assign Loan Applications to Employees\n3. Review Customer Feedback\n4. Change Password\nPress any other key to logout"

#define MANAGER_LOGOUT "Logging you out now manager! Good bye!$"

// ASSIGN LOAN
#define MANAGER_ASSIGN_LOAN "Assign loan application to an employee."

// REVIEW FEEDBACK
#define MANAGER_REVIEW_FEEDBACK "Reviewing customer feedback."

// ====================================================

// ========== COMMON ACCOUNT MANAGEMENT =================

#define ACCOUNT_FILE "./records/account.bank"
#define CUSTOMER_FILE "./records/customer.bank"
#define EMPLOYEE_FILE "./records/employee.bank"
#define TRANSACTION_FILE "./records/transactions.bank"
#define FEEDBACK_FILE "./records/feedback.bank"

#endif
