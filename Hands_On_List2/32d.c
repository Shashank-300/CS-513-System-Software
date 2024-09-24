/*
============================================================================
Name : 32d.c
Author : Shashank Vyas
Description : Write a program to implement semaphore to protect any critical section - Remove the created semaphore
Date: 21th Sep, 2024.
============================================================================
*/


#include <unistd.h>    // For various system calls
#include <sys/ipc.h>   // For IPC (Inter-Process Communication)
#include <sys/sem.h>   // For semaphore operations
#include <stdio.h>     // For standard I/O functions

int main(void) {
    // Define a union to hold semaphore values
    union semaphore_union {
        int value;  // Value of the semaphore
    } semaphore_arg;

    // Generate a unique key for the semaphore using `ftok`
    key_t semaphore_key = ftok(".", 'A');  // Changed the character for uniqueness
    if (semaphore_key == -1) {
        perror("Failed to generate semaphore key");
        return 1;
    }

    // Create a new semaphore set or access an existing one
    int semaphore_id = semget(semaphore_key, 1, IPC_CREAT | IPC_EXCL | 0600);
    if (semaphore_id != -1) {
        // If the semaphore set was created, initialize its value
        semaphore_arg.value = 1;  // Initial value for the semaphore
        if (semctl(semaphore_id, 0, SETVAL, semaphore_arg) == -1) {
            perror("Failed to initialize semaphore");
            return 1;
        }
    } else {
        // If the semaphore already exists, access it
        semaphore_id = semget(semaphore_key, 1, 0600);
        if (semaphore_id == -1) {
            perror("Failed to access existing semaphore");
            return 1;
        }
    }

    // Remove the semaphore from the system
    if (semctl(semaphore_id, 0, IPC_RMID) == -1) {
        perror("Failed to remove semaphore");
        return 1;
    }
    printf("Semaphore successfully removed.\n");
    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/HOL 2$ ./32d
    Semaphore successfully removed.
*/
