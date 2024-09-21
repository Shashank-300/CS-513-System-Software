/*
============================================================================
Name : 5.c
Author : Shashank Vyas
Description : Write a program to print the system limitation of 
    1. Maximum length of the arguments to the exec family of functions. 
    2. Maximum number of simultaneous process per user id. 
    3. Number of clock ticks (jiffy) per second. 
    4. Maximum number of open files 
    5. Size of a page 
    6. Total number of pages in the physical memory 
    7. Number of  currently available pages in the physical memory.
Date: 20th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/sysinfo.h>

int main() {
    // 1. Maximum length of the arguments to the exec family of functions
    long arg_max = sysconf(_SC_ARG_MAX);
    printf("1. Maximum length of the arguments to the exec family of functions: %ld\n", arg_max);

    // 2. Maximum number of simultaneous processes per user ID
    long max_processes = sysconf(_SC_CHILD_MAX);
    printf("2. Maximum number of simultaneous processes per user id: %ld\n", max_processes);

    // 3. Number of clock ticks (jiffies) per second
    long clock_ticks = sysconf(_SC_CLK_TCK);
    printf("3. Number of clock ticks (jiffy) per second: %ld\n", clock_ticks);

    // 4. Maximum number of open files
    struct rlimit file_limit;
    if (getrlimit(RLIMIT_NOFILE, &file_limit) == 0) {
        printf("4. Maximum number of open files: soft limit = %ld, hard limit = %ld\n", 
                (long)file_limit.rlim_cur, (long)file_limit.rlim_max);
    } else {
        perror("Error getting file limit");
    }

    // 5. Size of a page
    long page_size = sysconf(_SC_PAGESIZE);
    printf("5. Size of a page: %ld bytes\n", page_size);

    // 6. Total number of pages in physical memory
    long total_pages = sysconf(_SC_PHYS_PAGES);
    printf("6. Total number of pages in physical memory: %ld\n", total_pages);

    // 7. Number of currently available pages in physical memory
    long available_pages = sysconf(_SC_AVPHYS_PAGES);
    printf("7. Number of currently available pages in physical memory: %ld\n", available_pages);

    return 0;
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./5
1. Maximum length of the arguments to the exec family of functions: 2097152
2. Maximum number of simultaneous processes per user id: 29023
3. Number of clock ticks (jiffy) per second: 100
4. Maximum number of open files: soft limit = 1048576, hard limit = 1048576
5. Size of a page: 4096 bytes
6. Total number of pages in physical memory: 1876801
7. Number of currently available pages in physical memory: 48920
*/
