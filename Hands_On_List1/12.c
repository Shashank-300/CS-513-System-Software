/*
============================================================================
Name : 12.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to find out the opening mode of a file. Use fcntl.
Date: 30th Aug, 2024.
============================================================================
*/

#include <sys/types.h> // Import for `open` system call
#include <sys/stat.h>  // Import for `open` system call
#include <fcntl.h>     // Import for `open`, `fcntl` system call
#include <unistd.h>    // Import for `fcntl` system call
#include <stdio.h>     // Import required for `perror` & `printf` function
#include <stdlib.h>	

int main(int argc, char *argv[]) {
    int fd;
    int flags;

    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }

	//Testing purpose
    fd = open(argv[1], O_APPEND);
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    // Get the file status flags using fcntl and F_GETFL
    flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("Error getting file status flags");
        close(fd);
        exit(1);
    }

    // Determine and print the file opening mode
    switch (flags & O_ACCMODE) {
        case O_RDONLY:
            printf("File is opened in read-only mode\n");
            break;
        case O_WRONLY:
            printf("File is opened in write-only mode\n");
            break;
        case O_RDWR:
            printf("File is opened in read-write mode\n");
            break;
        default:
            printf("Unknown file opening mode\n");
    }

    // Check and print additional flags
    if (flags & O_APPEND) {
        printf("File is opened in append mode\n");
    }
    if (flags & O_NONBLOCK) {
        printf("File is opened in non-blocking mode\n");
    }
    if (flags & O_SYNC) {
        printf("File is opened in synchronous I/O mode\n");
    }

    close(fd);

    return 0;
}

/*
	shashank@ubuntu-22:~/Documents/SYS$ gcc -o 12 12.c
	shashank@ubuntu-22:~/Documents/SYS$ ./12 12.c
	File is opened in read-only mode
	File is opened in append mode
*/