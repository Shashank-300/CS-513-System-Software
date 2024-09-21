/*
============================================================================
Name : 31b.c
Author : Shashank Vyas
Description : Write a program to create a semaphore and initialize value to the semaphore. - Create a counting semaphore
Date: 21th Sep, 2024.
============================================================================
*/


#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>

int main() {
    // Define a union to hold the semaphore value
    union semaphoreUnion {
        int value;
    } semValue;

    // Generate a unique key for the semaphore
    key_t uniqueKey = ftok(".", 'c');
    if (uniqueKey == -1) {
        perror("Error generating key");
        return 1;
    }

    // Get or create a semaphore set with one semaphore
    int semaphoreID = semget(uniqueKey, 1, IPC_CREAT | 0600);
    if (semaphoreID == -1) {
        perror("Error creating semaphore set");
        return 1;
    }

    // Initialize the semaphore value to 5
    semValue.value = 5;
    if (semctl(semaphoreID, 0, SETVAL, semValue) == -1) {
        perror("Error setting semaphore value");
        return 1;
    }

    // Define a sembuf structure for semaphore operations
    struct sembuf semBuffer = {0, -1, 0};  // Decrease semaphore (P operation)

    // Perform the semaphore "wait" operation (decrement the semaphore value)
    if (semop(semaphoreID, &semBuffer, 1) == -1) {
        perror("Error during semaphore wait operation");
        return 1;
    }

    // Change the operation to "signal" (increment the semaphore value)
    semBuffer.sem_op = 1;  // Increase semaphore (V operation)

    // Perform the semaphore "signal" operation (increment the semaphore value)
    if (semop(semaphoreID, &semBuffer, 1) == -1) {
        perror("Error during semaphore signal operation");
        return 1;
    }

    return 0;
}
/*
    ------ Semaphore Arrays --------
    key        semid      owner      perms      nsems     
    0x6109e1d8 0          shashank   600        1         
    0x6309e1d8 1          shashank   600        1    
*/