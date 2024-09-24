/*
============================================================================
Name : 30.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to run a script at a specific time using a Daemon process.
Date: 31th Aug, 2024.
============================================================================
*/

#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void daemon() {
    int pid;
    pid = fork();
    if (pid < 0) {
        exit(1);
    }
    if (pid > 0) {
        exit(0);
    }
    // Set file permissions to be readable/writable by the daemon
    umask(0);
    // Create a new SID for the child process
    if (setsid() < 0) {
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        exit(1);
    }

    // Parse target time
    int target_hour = atoi(argv[1]);
    int target_minute = atoi(argv[2]);
    int target_second = (argc > 3) ? atoi(argv[3]) : 0;
    char *script_run = argv[4];

    // Calculating deadline time
    time_t curr_epoch, deadline_epoch;
    struct tm *deadline_tm;

    time(&curr_epoch);
    deadline_tm = localtime(&curr_epoch);

    deadline_tm->tm_hour = target_hour;
    deadline_tm->tm_min = target_minute;
    deadline_tm->tm_sec = target_second;

    deadline_epoch = mktime(deadline_tm);

    if (deadline_epoch == -1) {
        perror("Error converting deadline to epoch");
        exit(1);
    }
    daemon();

    // Wait until the target time
    while (1) {
        time(&curr_epoch);
        if (difftime(deadline_epoch, curr_epoch) <= 0) {
            printf("Runing the script %s",script_run);
            execl(script_run, script_run, (char *)NULL); // Run the script
            exit(0);  // Exit after running the script
        }
        sleep(1); // Check every 1 seconds
    }

    exit(0);
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ gcc -o 30 30.c
    shashank@ubuntu-22:~/Documents/SYS$ ./30 17 27 30 ./3
    shashank@ubuntu-22:~/Documents/SYS$ File created successfully with the following file descriptor: 3
*/