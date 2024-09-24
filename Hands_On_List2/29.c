/*
============================================================================
Name : 29.c
Author : Shashank Vyas
Description : Write a program to remove the message queue.
Date: 21th Sep, 2024.
============================================================================
*/


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int queueIdentifier;
    struct msqid_ds metadata;
    int msgctlStatus;

    key_t key = ftok("/home/shashank/Documents/HOL 2/24", 'a');

    if (key == -1) {
        perror("Error while computing key!");
        exit(0);
    }

    queueIdentifier = msgget(key, 0);
    if (queueIdentifier == -1) {
        perror("Error while creating Message Queue!");
        exit(0);
    }

    printf("Key: %d\n", key);
    printf("Message Queue Identifier: %d\n\n", queueIdentifier);

    msgctlStatus = msgctl(queueIdentifier, IPC_RMID, NULL);

    if (msgctlStatus == -1) {
        perror("Error while getting Message Queue info!");
        exit(0);
    }

   return 0;
}

/*
    shashank@ubuntu-22:~/Documents/HOL 2$ ./29
    Key: 1627988821
    Message Queue Identifier: 3
*/