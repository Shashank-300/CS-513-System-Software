/* Name - SHASHANK VYAS
 * Roll No. - MT2024141
 * Question: Write a program to create a file and print the file descriptor value. Use creat() system call
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