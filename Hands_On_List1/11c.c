/* Name : SHASHANK VYAS
 * Roll No. : MT2024141
 * Question : Write a program to open a file, duplicate the file descriptor using `fcntl`, and append the file with both descriptors. Check whether the file is updated properly or not.
 */

#include <sys/types.h> // Import for `open` system call
#include <sys/stat.h>  // Import for `open` system call
#include <fcntl.h>     // Import for `open`, `fcntl` system call
#include <unistd.h>    // Import for `write`, `close` system calls
#include <stdio.h>     // Import for `perror` and `printf` functions
#include <string.h>    // Import for `strlen` function
#include <stdlib.h>    // Import for `exit` function

int main(int argc, char *argv[]) {
    int fd, fd_dup;
    int wbyte;
    char data1[] = "Data for original FD\n";
    char data2[] = "Data for duplicated FD\n";

    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }

    // Open the file in read-write and append mode
    fd = open(argv[1], O_RDWR | O_APPEND | O_CREAT, 0666);
    if (fd == -1) {
        perror("Error opening the file");
        exit(1);
    }

    // Duplicate the file descriptor using `fcntl`
    fd_dup = fcntl(fd, F_DUPFD, 0);
    if (fd_dup == -1) {
        perror("Error duplicating the file descriptor");
        close(fd);
        exit(1);
    }

    // Append data using the original file descriptor
    wbyte = write(fd, data1, strlen(data1));
    if (wbyte == -1) {
        perror("Error writing with the original file descriptor");
        close(fd);
        close(fd_dup);
        exit(1);
    }

    // Append data using the duplicated file descriptor
    wbyte = write(fd_dup, data2, strlen(data2));
    if (wbyte == -1) {
        perror("Error writing with the duplicated file descriptor");
        close(fd);
        close(fd_dup);
        exit(1);
    }

    // Close both file descriptors
    close(fd);
    close(fd_dup);

    printf("Data has been successfully written using both file descriptors.\n");

    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ gcc -o 11c 11c.c
    shashank@ubuntu-22:~/Documents/SYS$ ./11c 11c.txt
    Data has been successfully written using both file descriptors.
    shashank@ubuntu-22:~/Documents/SYS$ cat 11c.txt 
    Data for original FD
    Data for duplicated FD
*/
