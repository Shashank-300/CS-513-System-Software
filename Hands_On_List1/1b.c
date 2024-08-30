/*
============================================================================
Name : 1b.c
Author : SHASHANK VYAS
Description : Write a C, Ansi-style program to perform Hard link (link system call).
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
int main()
{
	link("test1","hlinktest");
    printf("hardlink"); //Testing 
    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ ./1b
    hardlinkshashank@ubuntu-22:~/Documents/SYS$ ll | grep "hlinktest"
    -rw-rw-r-- 2 shashank shashank     0 Aug 28 08:55 hlinktest
    shashank@ubuntu-22:~/Documents/SYS$ 
*/
