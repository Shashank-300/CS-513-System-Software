/*
============================================================================
Name : 7.c
Author : Shashank Vyas
Description : Write a simple program to print the created thread IDs.
Date: 20th Sep, 2024.
============================================================================
*/


#include <stdio.h>
#include <pthread.h> // For pthreads

// Function that each thread will execute
void* thread_function(void* arg) {
    printf("Thread ID: %ld\n", pthread_self());
    return NULL;
}

int main() {
    pthread_t thread;

    // Create the thread
    if (pthread_create(&thread, NULL, thread_function, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }
    pthread_join(thread, NULL);

    printf("Thread has finished execution.\n");

    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./7
Thread ID: 140039377909440
Thread has finished execution.
*/