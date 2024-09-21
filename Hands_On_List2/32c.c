/*
============================================================================
Name : 32c.c
Author : Shashank Vyas
Description : Write a program to implement semaphore to protect any critical section - Protect multiple pseudo resources (may be two) using counting semaphore 
Date: 21th Sep, 2024.
============================================================================
*/


#include <unistd.h>    // For system calls like `getchar`
#include <sys/ipc.h>   // For `ftok`
#include <sys/sem.h>   // For semaphore operations
#include <stdio.h>     // For `printf`, `perror`

int main(void) {
    // Define a union to set semaphore values
    union semun {
        int semaphoreValue;  // Value of the semaphore
    } semaphoreControl;

    // Generate a unique key for the semaphore using `ftok`
    key_t semaphoreKey = ftok(".", 42);  // Changed the character for uniqueness
    if (semaphoreKey == -1) {
        perror("Error generating semaphore key");
        return 1;
    }

    // Create or access the semaphore set
    int semaphoreId = semget(semaphoreKey, 1, IPC_CREAT | IPC_EXCL | 0600);  // Exclusive creation with permissions
    if (semaphoreId != -1) {
        // If the semaphore set was successfully created, initialize the value
        semaphoreControl.semaphoreValue = 2;  // Set the initial semaphore value to 2 (binary semaphore)
        if (semctl(semaphoreId, 0, SETVAL, semaphoreControl) == -1) {
            perror("Error initializing semaphore value");
            return 1;
        }
    } else {
        // If the semaphore set already exists, access it
        semaphoreId = semget(semaphoreKey, 1, 0600);
        if (semaphoreId == -1) {
            perror("Error accessing existing semaphore");
            return 1;
        }
    }

    printf("Before entering the critical section\n");

    // Define a sembuf structure for the semaphore operation (P operation)
    struct sembuf semaphoreBuffer = {0, -1, 0};  // Decrement semaphore to lock (enter critical section)

    // Perform the semaphore wait operation
    if (semop(semaphoreId, &semaphoreBuffer, 1) == -1) {
        perror("Error performing semaphore wait operation (P)");
        return 1;
    }

    // Critical section
    printf("Inside the critical section\n");

    // Wait for user input to leave the critical section
    printf("Press any key to exit the critical section\n");
    getchar();

    // Set semaphore operation for signaling (V operation)
    semaphoreBuffer.sem_op = 1;  // Increment semaphore to unlock (exit critical section)

    // Perform the semaphore signal operation
    if (semop(semaphoreId, &semaphoreBuffer, 1) == -1) {
        perror("Error performing semaphore signal operation (V)");
        return 1;
    }

    printf("Outside the critical section\n");

    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/HOL 2$ ./32c
    Before entering the critical section
    Inside the critical section
    Press any key to exit the critical section

    Outside the critical section
*/