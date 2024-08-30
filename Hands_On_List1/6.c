/*
============================================================================
Name : 6.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to take input from STDIN and display on STDOUT. Use only read/write system calls
Date: 30th Aug, 2024.
============================================================================
*/

#include <unistd.h> 
#include <stdio.h>  

int main(){

	char* buff[50];
	int rbyte;

	rbyte=read(STDIN_FILENO,buff,sizeof(buff)-1);

	if(rbyte==-1){
		perror("Error while reading!!");
	}

	write(STDOUT_FILENO,buff,rbyte);

}

/*
	shashank@ubuntu-22:~/Documents/SYS$ ./6
	hi i am 6.c 
	hi i am 6.c
*/
