/*
============================================================================
Name : 25.c
Author : Shashank Vyas
Description : Write a program to print a message queue's (use `msqid_ds` and `ipc_perm` structures)
    1. Access permission 
    2. `uid`, `gid` 
    3. Time of last message sent and received 
    4. Time of last change in the message queue
    5. Size of the queue 
    6. Number of messages in the queue
    7. Maximum number of bytes allowed
    8. PID of the `msgsnd` and `msgrcv`
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

    key_t key = ftok(".", 1);

    if (key == -1) {
        perror("Error while computing key!");
        exit(0);
    }

    queueIdentifier = msgget(key, IPC_CREAT | 0700);
    if (queueIdentifier == -1) {
        perror("Error while creating Message Queue!");
        exit(0);
    }

    printf("Key: %d\n", key);
    printf("Message Queue Identifier: %d\n\n", queueIdentifier);

    msgctlStatus = msgctl(queueIdentifier, IPC_STAT, &metadata);

    if (msgctlStatus == -1) {
        perror("Error while getting Message Queue info!");
        exit(0);
    }

    printf("Access Permission: %o\n", metadata.msg_perm.mode);
    printf("UID: %d\n", metadata.msg_perm.uid);
    printf("GID: %d\n", metadata.msg_perm.gid);
    printf("Time of last message sent: %ld\n", metadata.msg_stime);
    printf("Time of last message received: %ld\n", metadata.msg_rtime);
    printf("Size of queue: %ld\n", metadata.msg_cbytes);
    printf("Number of messages in the queue: %ld\n", metadata.msg_qnum);
    printf("Maximum number of bytes allowed in the queue: %ld\n", metadata.msg_qbytes);
    printf("PID of last sent message: %d\n", metadata.msg_lspid);
    printf("PID of last received message: %d\n", metadata.msg_lrpid);

    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/HOL 2$ ./25
    Key: 17424856
    Message Queue Identifier: 0

    Access Permission: 700
    UID: 1000
    GID: 1000
    Time of last message sent: 0
    Time of last message received: 0
    Size of queue: 0
    Number of messages in the queue: 0
    Maximum number of bytes allowed in the queue: 16384
    PID of last sent message: 0
    PID of last received message: 0
*/