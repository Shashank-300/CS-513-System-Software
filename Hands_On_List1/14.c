/*
============================================================================
Name : 14.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to find the type of a file. 
    1. Input should be taken from command line. 
    2. Program should be able to identify any type of a file.
Date: 30th Aug, 2024.
============================================================================
*/

#include <sys/types.h> // Imports for using `stat` system call
#include <sys/stat.h>  // Imports for using `stat` system call
#include <unistd.h>    // Imports for using `stat` system call
#include <fcntl.h>     // Import for `O_RDONLY` flag
#include <stdio.h>     // Import for `printf`
#include <stdlib.h>

void main(int argc, char *argv[])
{
    struct stat filestat;
    int fd;

    if (argc != 2)
        printf("Give the file name/path !");
    else
    {
	fd=open(argv[1],O_RDONLY);
	
	if (fstat(fd, &filestat) == -1) 
    	{
        	perror("Error retrieving file status");
        	exit(0);
    	}
      	if (S_ISREG(filestat.st_mode)) {
        	printf("%s is a regular file.\n", argv[1]);
    	} 
	else if (S_ISDIR(filestat.st_mode)) {
        	printf("%s is a directory.\n", argv[1]);
    	} 
	else if (S_ISLNK(filestat.st_mode)) {
        	printf("%s is a symbolic link.\n", argv[1]);
    	} 
	else if (S_ISCHR(filestat.st_mode)) {
        	printf("%s is a character device.\n", argv[1]);
    	} 
	else if (S_ISBLK(filestat.st_mode)) {
        	printf("%s is a block device.\n", argv[1]);
	} 
	else if (S_ISFIFO(filestat.st_mode)) {
        	printf("%s is a FIFO (named pipe).\n", argv[1]);
    	} else if (S_ISSOCK(filestat.st_mode)) {
        	printf("%s is a socket.\n", argv[1]);
	} 
	else {
        	printf("%s is of an unknown file type.\n", argv[1]);
    	}
    }
}

/*
	shashank@ubuntu-22:~/Documents/SYS$ ./14 test3.txt
	test3.txt is a regular file.
	shashank@ubuntu-22:~/Documents/SYS$ ./14 loopfile/
	loopfile/ is a directory.
*/