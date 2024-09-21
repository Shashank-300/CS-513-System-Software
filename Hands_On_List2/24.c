/*
============================================================================
Name : 24.c
Author : Shashank Vyas
Description : Write a program to create a message queue and print the key and message queue id.
Date: 21th Sep, 2024.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    int key = ftok("/home/shashank/Documents/HOL 2/", 'a');
    int msgid = msgget(key, IPC_CREAT | 0744);

    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Key=0x%0x\nmsgid=%d\n", key, msgid);

    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/HOL 2$ ./24
    Key=0xffffffff
    msgid=0
*/
