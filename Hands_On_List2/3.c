/*
============================================================================
Name : 3.c
Author : Shashank Vyas
Description : Write a C, Ansi-style program to set (any one) system resource limit. Use setrlimit system call.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    struct rlimit limit;

    // Get the current limit for the number of open files
    if (getrlimit(RLIMIT_NOFILE, &limit) == 0) {
        printf("Current limits: soft=%ld; hard=%ld\n", (long)limit.rlim_cur, (long)limit.rlim_max);
    } else {
        perror("Error getting limit");
        return 1;
    }

    // Set new soft limit (e.g., increase soft limit to 500)
    limit.rlim_cur = 500;
    
    // Attempt to set the new limits using setrlimit
    if (setrlimit(RLIMIT_NOFILE, &limit) == 0) {
        printf("New limits set successfully.\n");
    } else {
        perror("Error setting limit");
        return 1;
    }

    // Verify the new limits
    if (getrlimit(RLIMIT_NOFILE, &limit) == 0) {
        printf("Updated limits: soft=%ld; hard=%ld\n", (long)limit.rlim_cur, (long)limit.rlim_max);
    } else {
        perror("Error getting updated limit");
        return 1;
    }

    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./3
Current limits: soft=1048576; hard=1048576
New limits set successfully.
Updated limits: soft=500; hard=1048576
*/