/*
============================================================================
Name : 27a.c
Author : Shashank Vyas
Description : Write a program to receive messages from the message queue with `0` as a flag
Date: 21th Sep, 2024.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Define a structure for your message
struct MyMessage {
    long mtype;  // Used to identify message type (should be > 0)
    int data;    // Integer data to send
};

int main() {
    // Generate a unique key using ftok
    int key = ftok("/home/shashank/Documents/HOL 2/24", 'a');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create or get a message queue
    int msgid = msgget(key, IPC_CREAT | 0744);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    // Print the generated key and message queue ID
    printf("Key=0x%0x\nmsgid=%d\n", key, msgid);

    // Prepare your message
    struct MyMessage content;
    content.mtype = 1;  // Message type, must be > 0
    content.data = 100;  // Message content

    // Send the message
    if (msgsnd(msgid, &content, sizeof(content.data), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Message sent! Data = %d\n", content.data);

    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./27a
Key=0x61092355
msgid=1
Message sent! Data = 100
*/