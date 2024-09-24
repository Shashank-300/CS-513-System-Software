/*
============================================================================
Name : 6.c
Author : Shashank Vyas
Description : Write a simple program to create three threads.
Date: 20th Sep, 2024.
============================================================================
*/


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Function that each thread will execute
void* thread_function(void* arg) {
    int thread_num = *((int*)arg); // Get the thread number
    printf("Thread %d is running. Thread ID: %ld\n", thread_num, pthread_self());
    return NULL;
}

int main() {
    pthread_t threads[3];
    int thread_nums[3];

    // Create 3 threads
    for (int i=0;i<3;i++) {
        thread_nums[i] = i + 1; // Assign thread numbers starting from 1
        if (pthread_create(&threads[i], NULL, thread_function, &thread_nums[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }
    
    for(int i=0;i<3;i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf("All threads have finished execution.\n");

    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./6
Thread 2 is running. Thread ID: 140106566461120
Thread 1 is running. Thread ID: 140106574853824
Thread 3 is running. Thread ID: 140106558068416
All threads have finished execution.
*/