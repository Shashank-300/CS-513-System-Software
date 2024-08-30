/*
============================================================================
Name : 3.c
Author : SHASHANK VYAS
Description : Write a C program,to create a file and print the file descriptor value. Use creat() system call
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>     
int main()
{
	char *name="test3.txt";
	int fd=creat(name,0644);
	if (fd == -1) {
        perror("creat didn't execute successfully!!");
        return 1;
    	} else {
        printf("File created successfully with the following file descriptor: %d\n", fd);
    }	
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ ./3
    File created successfully with the following file descriptor: 3

*/