/*
============================================================================
Name : 32a.c
Author : Shashank Vyas
Description : Write a program to implement semaphore to protect any critical section - Rewrite the ticket number creation program using semaphore
Date: 21th Sep, 2024.
============================================================================
*/


#include <sys/ipc.h>   // For `ftok`, `semget`, `semctl`
#include <sys/sem.h>   // For semaphore operations
#include <sys/types.h> // For file operations
#include <sys/stat.h>  // For file creation modes
#include <fcntl.h>     // For `open`
#include <unistd.h>    // For `write`, `lseek`, `read`, `_exit`
#include <stdio.h>     // For `perror` & `printf`

void main() {
    char *ticketFile = "./sample-files/ticket-file.txt"; // Ticket file path

    int fileDescriptor;            // File descriptor for ticket file
    ssize_t readBytes, writeBytes; // Bytes read/written to ticket file
    off_t lseekOffset;
    int data; // Ticket data

    key_t semKey;      // Semaphore key
    int semIdentifier; // Semaphore identifier
    int semctlStatus;  // Status for semaphore control
    int semopStatus;   // Status for semaphore operation

    // Create/Open ticket file
    fileDescriptor = open(ticketFile, O_CREAT | O_RDWR, S_IRWXU);
    if (fileDescriptor == -1) {
        perror("Error while creating/opening the ticket file!");
        _exit(0);
    }

    // Semaphore union structure
    union semun {
        int val;               // Semaphore value
        struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
        unsigned short *array; /* Array for GETALL, SETALL */
        struct seminfo *__buf; /* Buffer for IPC_INFO */
    } semSet;

    semKey = ftok(".", 331);
    if (semKey == -1) {
        perror("Error while computing key!");
        _exit(1);
    }

    semIdentifier = semget(semKey, 1, 0); // Get existing semaphore
    if (semIdentifier == -1) {
        semIdentifier = semget(semKey, 1, IPC_CREAT | 0700); // Create new semaphore 
        if (semIdentifier == -1) {
            perror("Error while creating semaphore!");
            _exit(1);
        }

        semSet.val = 1; // Initialize binary semaphore
        semctlStatus = semctl(semIdentifier, 0, SETVAL, semSet);
        if (semctlStatus == -1) {
            perror("Error while initializing a binary semaphore!");
            _exit(1);
        }
    }

    struct sembuf semOp; // Semaphore operation structure
    semOp.sem_num = 0;   // Semaphore number
    semOp.sem_flg = 0;   // No special flags

    printf("Press enter to obtain lock on the critical section\n");
    getchar();
    
    // Lock the critical section
    semOp.sem_op = -1; // P operation (wait)
    semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1) {
        perror("Error while operating on semaphore!");
        _exit(1);
    }
    
    printf("Obtained lock on critical section!\n");
    printf("Now entering critical section!\n");

    // =========== Start of Critical Section ===========

    readBytes = read(fileDescriptor, &data, sizeof(data));
    if (readBytes == -1) {
        perror("Error while reading from ticket file!");
        _exit(0);
    } else if (readBytes == 0) { // No data in file
        data = 1;
    } else {
        data += 1; // Increment ticket number
        lseekOffset = lseek(fileDescriptor, 0, SEEK_SET);
        if (lseekOffset == -1) {
            perror("Error while seeking!");
            _exit(0);
        }
    }

    writeBytes = write(fileDescriptor, &data, sizeof(data));
    if (writeBytes == -1) {
        perror("Error while writing to ticket file!");
        _exit(1);
    }

    printf("Your ticket number is - %d\n", data);

    printf("Press enter to exit from critical section!\n");
    getchar();

    // =========== End of Critical Section =============

    // Unlock the critical section
    semOp.sem_op = 1; // V operation (signal)
    semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1) {
        perror("Error while operating on semaphore!");
        _exit(1);
    }

    close(fileDescriptor); // Close the ticket file
}

/*
    shashank@ubuntu-22:~/Documents/HOL 2$ mkdir -p ./sample-files
    shashank@ubuntu-22:~/Documents/HOL 2$ gcc -o 32a 32a.c
    shashank@ubuntu-22:~/Documents/HOL 2$ ./32a
    Press enter to obtain lock on the critical section

    Obtained lock on critical section!
    Now entering critical section!
    Your ticket number is - 1
    Press enter to exit from critical section!

    shashank@ubuntu-22:~/Documents/HOL 2$ ./32a
    Press enter to obtain lock on the critical section

    Obtained lock on critical section!
    Now entering critical section!
    Your ticket number is - 2
    Press enter to exit from critical section!

*/