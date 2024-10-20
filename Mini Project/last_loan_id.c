#include <fcntl.h>
#include <unistd.h>

int generate_unique_loanID() {
    int fd, loanID = 1000;
    
    // Open the file to store the last used loan ID
    fd = open("last_loan_id.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening last_loan_id.txt");
        return loanID;  // Return default ID if file can't be opened
    }
    
    // Read the last used loan ID
    if (read(fd, &loanID, sizeof(int)) != sizeof(int)) {
        // If read fails or file is empty, start with default ID
        loanID = 1000;
    }
    
    // Increment the loan ID
    loanID++;
    
    // Move file pointer to the beginning
    lseek(fd, 0, SEEK_SET);
    
    // Write the new loan ID back to the file
    if (write(fd, &loanID, sizeof(int)) != sizeof(int)) {
        perror("Error writing to last_loan_id.txt");
    }
    
    close(fd);
    return loanID;
}