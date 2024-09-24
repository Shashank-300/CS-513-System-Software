/*
============================================================================
Name : 28.c
Author : Shashank Vyas
Description : Write a program to change the exiting message queue permission. (Use `msqid_ds` structure)
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
    int msgid;  // Message queue identifier
    struct msqid_ds queueInfo;  // Structure to hold message queue metadata
    int status;

    // Generate a unique key for the message queue
    key_t key = ftok(".", 1);
    if (key == -1) {
        perror("Error generating key!");
        exit(EXIT_FAILURE);
    }

    // Create a message queue with read-write permissions for the owner
    msgid = msgget(key, IPC_CREAT | 0700);
    if (msgid == -1) {
        perror("Error creating message queue!");
        exit(EXIT_FAILURE);
    }

    printf("Key: %d\n", key);
    printf("Message Queue ID: %d\n\n", msgid);

    // Retrieve current metadata for the message queue
    status = msgctl(msgid, IPC_STAT, &queueInfo);
    if (status == -1) {
        perror("Error retrieving message queue info!");
        exit(EXIT_FAILURE);
    }

    // Display the current access permissions
    printf("Current access permissions: %o\n", queueInfo.msg_perm.mode);

    // Wait for the user to press Enter to continue
    printf("Press Enter to modify permissions...");
    getchar();

    // Change access permissions
    queueInfo.msg_perm.mode = 0644;  // Set new permissions (read-write for owner, read-only for group and others)

    // Apply the updated permissions to the message queue
    status = msgctl(msgid, IPC_SET, &queueInfo);
    if (status == -1) {
        perror("Error setting new permissions!");
        exit(EXIT_FAILURE);
    }

    // Display updated permissions
    printf("Updated access permissions: %o\n", queueInfo.msg_perm.mode);

    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/HOL 2$ ./28
    Key: 17424856
    Message Queue ID: 0

    Current access permissions: 700
    Press Enter to modify permissions...
    Updated access permissions: 644
*/