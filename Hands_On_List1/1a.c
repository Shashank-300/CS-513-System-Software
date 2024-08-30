/*
============================================================================
Name : 1a.c
Author : SHASHANK VYAS
Description : Write a C, Ansi-style program to perform Soft link (symlink system call) .
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
int main()
{
	symlink("test1","slinktest");
//	printf("SoftLink"); //Testing purpose
	return 0;
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ ./1a
    SoftLinkshashank@ubuntu-22:~/Documents/SYS$ ll | grep "slinktest"
    lrwxrwxrwx 1 shashank shashank     5 Aug 28 08:56 slinktest -> test1
    shashank@ubuntu-22:~/Documents/SYS$ 
*/