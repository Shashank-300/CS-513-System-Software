/*
============================================================================
Name : 32b.c
Author : Shashank Vyas
Description : Write a program to implement semaphore to protect any critical section - Protect shared memory from concurrent write access
Date: 21th Sep, 2024.
============================================================================
*/

#include <unistd.h>     // For system calls like `read`, `lseek`, `getchar`
#include <sys/ipc.h>    // For `ftok`
#include <sys/sem.h>    // For semaphore operations
#include <fcntl.h>      // For file operations like `open`
#include <stdio.h>      // For `printf`, `perror`

// Structure to store train ticket data
struct train_record {
    int train_number;
    int ticket_number;
};

int main(void) {
    int fileDescriptor = open("train.txt", O_RDWR);
    if (fileDescriptor == -1) {
        perror("Error opening file!");
        return 1;
    }

    struct train_record record;

    // Semaphore initialization
    union semun {
        int val;
    } semaphoreUnion;

    // Create a unique key for the semaphore
    key_t semaphoreKey = ftok(".", 65);
    if (semaphoreKey == -1) {
        perror("Error generating key with ftok");
        return 1;
    }

    int semaphoreId = semget(semaphoreKey, 1, IPC_CREAT | IPC_EXCL | 0600);
    if (semaphoreId != -1) {
        // If the semaphore set was created, initialize its value to 1 (binary semaphore)
        semaphoreUnion.val = 1;
        if (semctl(semaphoreId, 0, SETVAL, semaphoreUnion) == -1) {
            perror("Error initializing semaphore");
            return 1;
        }
    } else {
        // If the semaphore already exists, retrieve it
        semaphoreId = semget(semaphoreKey, 1, 0600);
        if (semaphoreId == -1) {
            perror("Error accessing existing semaphore");
            return 1;
        }
    }

    printf("Before entering critical section\n");

    // Define the semaphore operation for entering the critical section (P operation)
    struct sembuf semOpStruct = {0, -1, 0};  // Decrement semaphore to lock
    if (semop(semaphoreId, &semOpStruct, 1) == -1) {
        perror("Error while performing P operation");
        return 1;
    }

    printf("Inside critical section\n");
    if (read(fileDescriptor, &record, sizeof(record)) == -1) {
        perror("Error reading file");
        close(fileDescriptor);
        return 1;
    }

    // Adjust file pointer to correct position for writing back updated data
    if (lseek(fileDescriptor, -sizeof(record), SEEK_CUR) == -1) {
        perror("Error seeking in file");
        close(fileDescriptor);
        return 1;
    }

    record.ticket_number++;
    printf("Updated ticket number: %d\n", record.ticket_number);


    if (write(fileDescriptor, &record, sizeof(record)) == -1) {
        perror("Error writing to file");
        close(fileDescriptor);
        return 1;
    }
    close(fileDescriptor);

    
    semOpStruct.sem_op = 1;
    printf("Press any key to exit the critical section\n");
    getchar(); 

    // Perform the semaphore operation to leave the critical section
    if (semop(semaphoreId, &semOpStruct, 1) == -1) {
        perror("Error while performing V operation");
        return 1;
    }

    printf("Outside critical section\n");

    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/HOL 2$ gcc -o 32b 32b.c
    shashank@ubuntu-22:~/Documents/HOL 2$ ./32b
    Before entering critical section
    Inside critical section
    Updated ticket number: 2
    Press any key to exit the critical section

    Outside critical section
*/