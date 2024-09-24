/*
============================================================================
Name : 26.c
Author : Shashank Vyas
Description : Write a program to send messages to the message queue. Check `ipcs -q`
Date: 21th Sep, 2024.
============================================================================
*/


#include <sys/types.h> // Import for `ftok` `msgget` & `msgsnd`
#include <sys/ipc.h>   // Import for `ftok` `msgget` & `msgsnd`
#include <sys/msg.h>   // Import for `msgget` & `msgsnd`
#include <stdio.h>     // Import for `perror` & `printf`
#include <unistd.h>    // Import for `_exit`
#include <errno.h>     // Import for `errno`

void main()
{
    key_t queueKey;        // IPC (Message Queue) key
    int queueIdentifier;   // IPC (Message Queue) identifier
    int messageSendStatus; // Determines success of `msgsnd` call

    struct msgbuf
    {
        long mtype;     // Used to identify message type - should be > 0
        int someNumber; // Integer data
    } data;

    queueKey = ftok("/home/shashank/Documents/HOL 2/", 'a');

    if (queueKey == -1)
    {
        perror("Error while computing key!");
        _exit(0);
    }

    queueIdentifier = msgget(queueKey, IPC_CREAT | 0700);

    if (queueIdentifier == -1)
    {
        perror("Error while creating message queue!");
        _exit(0);
    }

    data.mtype = 1;
    data.someNumber = 100;

    messageSendStatus = msgsnd(queueIdentifier, &data, sizeof(data), 0);

    if (messageSendStatus == -1)
    {
        perror("Error while sending message via Message Queue!");
        _exit(0);
    }

    printf("Message sent! Check using `ipcs -q`\n");
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./26
Message sent! Check using `ipcs -q`
shashank@ubuntu-22:~/Documents/HOL 2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x6109e1d8 0          shashank   700        16           1       
*/