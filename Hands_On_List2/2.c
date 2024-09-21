/*
============================================================================
Name : 2.c
Author : Shashank Vyas
Description : Write a C, Ansi-style program to print the system resource limits. Use getrlimit system call.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>

void main() {
    struct rlimit limit;
    int resource;
    getrlimit(RLIMIT_CPU,&limit);
    printf("Current limits: soft=%ld; hard=%ld\n", (long)limit.rlim_cur, (long)limit.rlim_max);
    
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./2
Current limits: soft=-1; hard=-1
*/