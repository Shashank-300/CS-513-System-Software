/*
============================================================================
Name : 10.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to open a file with read write mode, write 10 bytes, move the file pointer by 10 bytes (use lseek) and write again 10 bytes. 

    1. Check the return value of `lseek` 
    2. Open the file with `od` and check the empty spaces in between the data.
Date: 30th Aug, 2024.
============================================================================
*/

#include <sys/stat.h>  // Import for `open` system call
#include <fcntl.h>     // Import for `open` system call
#include <sys/types.h> // Import for `open`, `lseek` system call
#include <unistd.h>    // Import for `close`, `lseek` system call
#include <stdio.h>     // Import for `perror` and `printf` functions
#include <stdlib.h>    // Import for 'exit' system call

void main(int argc,char *argv[])
{
    int fd;
    int b_write;
    long int offset;
    char *fname;

    fname=argv[1];
    // Opening file in read-write mode (creating if it doesn't exist)
    fd = open(fname, O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("Error opening the file");
        exit(0);
    }

    // First 10 bytes to the file
    char data1[] = "1234567890";  // 10 bytes
    b_write = write(fd, data1, 10);
    if (b_write != 10) {
        perror("Error writing the first 10 bytes");
        close(fd);
        exit(0);
    }

    // Moving the file pointer by 10 bytes
    offset = lseek(fd, 10, SEEK_CUR);
    if (offset == -1) {
        perror("Error using lseek");
        close(fd);
        exit(0);
    } else {
        printf("lseek successful,current offset: %ld\n", offset);
    }

    //Next 10 bytes to the file
    char data2[] = "ABCDEFGHIJ";  
    b_write = write(fd, data2, 10);
    if (b_write != 10) {
        perror("Error writing the second 10 bytes");
        close(fd);
        exit(0);
    }
    close(fd);
}

/*
 Output
	shashank@ubuntu-22:~/Documents/SYS$ ./10 test10.txt
	lseek successful,current offset: 20
	shashank@ubuntu-22:~/Documents/SYS$ od -c test10.txt 
	0000000   1   2   3   4   5   6   7   8   9   0  \0  \0  \0  \0  \0  \0
	0000020  \0  \0  \0  \0   A   B   C   D   E   F   G   H   I   J
	0000036
*/


