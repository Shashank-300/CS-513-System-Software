/*
============================================================================
Name : 19.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to find out time taken to execute getpid system call. Use time stamp counter.
Date: 30th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

static __inline__ unsigned long long rdtsc(void) {
    unsigned int dst;
    __asm__ __volatile__ ("rdtsc" : "=A" (dst));
    return dst;
}

int main() {
    unsigned long long start, end;
    
    // Get the start timestamp
    start = rdtsc();
    
    int pid = getpid();
    
    // Get the end timestamp
    end = rdtsc();
    
    printf("PID: %d\n", pid);
    printf("Time taken to execute getpid(): %llu CPU cycles\n", (end - start));
    
    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ ./19
    PID: 31133
    Time taken to execute getpid(): 9366 CPU cycles
*/