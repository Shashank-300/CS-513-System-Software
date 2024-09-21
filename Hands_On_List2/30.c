/*
============================================================================
Name : 30.c
Author : Shashank Vyas
Description : Write a program to create a shared memory. 
    1. Write some data to the shared memory
    2. Attach with `O_RDONLY` and check whether you are able to overwrite. 
    3. Detach the shared memory 
    4. Remove the shared memory
Date: 21th Sep, 2024.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHARED_MEM_SIZE 100  // Define the size of the shared memory segment

int main() {
    int sharedMemID;  // Variable to hold shared memory identifier
    key_t uniqueKey;  // Variable to hold generated key
    char *sharedMemPtr;  // Pointer to access shared memory

    // Generate a unique key for shared memory
    uniqueKey = ftok(".", 'b');
    printf("Generated Key: %d\n", uniqueKey);

    // Allocate shared memory
    sharedMemID = shmget(uniqueKey, SHARED_MEM_SIZE, IPC_CREAT | 0666);
    if (sharedMemID == -1) {
        perror("Error creating shared memory with shmget");
        return EXIT_FAILURE;
    }

    // Attach the shared memory segment to the process's address space
    sharedMemPtr = shmat(sharedMemID, NULL, 0);
    if (sharedMemPtr == (char *)-1) {
        perror("Error attaching shared memory with shmat");
        return EXIT_FAILURE;
    }

    // Take user input to write to the shared memory
    char inputBuffer[SHARED_MEM_SIZE];
    printf("Enter text to store in shared memory:\n");
    scanf("%[^\n]", inputBuffer);
    strcpy(sharedMemPtr, inputBuffer);  // Copy input to shared memory

    // Detach the shared memory segment from the process
    if (shmdt(sharedMemPtr) == -1) {
        perror("Error detaching shared memory with shmdt");
        return EXIT_FAILURE;
    }

    // Reattach the shared memory in read-only mode to verify content
    sharedMemPtr = shmat(sharedMemID, NULL, SHM_RDONLY);
    if (sharedMemPtr == (char *)-1) {
        perror("Error reattaching shared memory with shmat (read-only)");
        return EXIT_FAILURE;
    }

    // Display contents of shared memory
    printf("Data in shared memory: %s\n", sharedMemPtr);

    // Detach again after reading the memory
    if (shmdt(sharedMemPtr) == -1) {
        perror("Error detaching shared memory after reading");
        return EXIT_FAILURE;
    }

    // Mark the shared memory segment for deletion
    if (shmctl(sharedMemID, IPC_RMID, NULL) == -1) {
        perror("Error removing shared memory with shmctl");
        return EXIT_FAILURE;
    }

    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/HOL 2$ ./30
    Generated Key: 1644814808
    Enter text to store in shared memory:
    hi i am shashank
    Data in shared memory: hi i am shashank
*/