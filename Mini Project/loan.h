struct Loan {
    int customerID;       // ID of the customer requesting the loan
    int loanID;           // Unique loan ID
    int assignedEmployee; // ID of the employee assigned to handle the loan (0 if unassigned)
    double amount;        // Loan amount
    int accountID;        // Account ID associated with the loan
    int isAccepted; 
};
