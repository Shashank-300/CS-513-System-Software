/*
============================================================================
Name : 4.c
Author : Shashank Vyas
Description : Write a C, Ansi-style program to measure how much time is taken to execute 100 getppid() system call. Use time stamp counter.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

// Inline function to read Time Stamp Counter (TSC)
static inline uint64_t rdtsc(void) {
    unsigned int lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

int main() {
    uint64_t start, end;
    int ppid;

    // Record the start time using TSC
    start = rdtsc();

    // Perform 100 getppid() system calls
    for (int i = 0; i < 100; i++) {
        ppid = getppid();
    }

    // Record the end time using TSC
    end = rdtsc();

    // Calculate the number of CPU cycles taken
    uint64_t cycles_taken = end - start;

    // Print the result
    printf("Time taken for 100 getppid() calls: %lu CPU cycles\n", cycles_taken);

    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./4
Time taken for 100 getppid() calls: 64239 CPU cycles
*/