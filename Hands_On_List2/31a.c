/*
============================================================================
Name : 31a.c
Author : Shashank Vyas
Description : Write a program to create a semaphore and initialize value to the semaphore - Create a binary semaphore
Date: 21th Sep, 2024.
============================================================================
*/


#include<unistd.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdio.h>

int main(void) {
    union semun {
        int val;
    } arg;
    
    key_t key = ftok(".", 'a');
    int semid = semget(key, 1, IPC_CREAT | 0600);

    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);

    struct sembuf buff = {0, -1, 0};

    semop(semid, &buff, 1);
    buff.sem_op = 1;
    semop(semid, &buff, 1);

    return 0;
}

