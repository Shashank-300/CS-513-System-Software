/*
============================================================================
Name : 30.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to run a script at a specific time using a Daemon process.
Date: 30th Aug, 2024.
============================================================================
*/

#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    if(!fork()) {
        setsid();
        chdir("/");
        umask(0);

        while(1) {
            sleep(5);
            printf("Daemon process still running (PID : %d)\n", getpid());
        }
    }   
    else 
        exit(0);
}       

/*
    shashank@ubuntu-22:~/Documents/SYS$ Daemon process still running (PID : 46256)
    Daemon process still running (PID : 46256)

    shashank@ubuntu-22:~/Documents/SYS$ ps aux | grep 48325
    shashank   48325  0.0  0.0   2624    96 ?        Ss   14:53   0:00 ./30

    kill -9 48325
*/