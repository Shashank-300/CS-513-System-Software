/*
============================================================================
Name : 11a.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to open a file, duplicate the file descriptor and append the file with both the descriptors and check whether the file is updated properly or not using `dup`
Date: 30th Aug, 2024.
============================================================================
*/

#include <sys/types.h> // Import for `open` system call
#include <sys/stat.h>  // Import for `open` system call
#include <fcntl.h>     // Import for `open`, `fcntl` system call
#include <unistd.h>    // Import for `fcntl` system call
#include <stdio.h>     // Import for `perror` & `printf` function
#include <string.h>    // Import for strlen function
#include <stdlib.h>    // Import for exit function

void main(int argc,char *argv[])
{
    int fd, fd_dup;
    int wbyte;
    char data1[] = "Data for original FD\n";
    char data2[] = "Data for duplicated FD\n";
    char *fname;

    // Opening the file in read-write modem,and append mode
    fd = open(argv[1], O_RDWR | O_APPEND | O_CREAT, 0666);
    if (fd == -1) {
        perror("Error opening the file");
        exit(0);
    }

    // Duplicate file descriptor
    fd_dup = dup(fd);
    if (fd_dup == -1) {
        perror("Error duplicating the file descriptor");
        close(fd);
        exit(0);
    }

    // Append data using the original file descriptor
    wbyte = write(fd, data1, strlen(data1));
    if (wbyte== -1) {
        perror("Error writing with the original file descriptor");
        close(fd);
        exit(0);
    }

    // Append data using the duplicated file descriptor
    wbyte = write(fd_dup, data2, strlen(data2));
    if (wbyte == -1) {
        perror("Error writing with the duplicated file descriptor");
        close(fd_dup);
        exit(0);
    }

    // Close both file descriptors
    close(fd);
    close(fd_dup);
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ cat test11.txt 
    Data for original FD
    Data for duplicated FD
*/