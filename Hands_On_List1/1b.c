/* Name - SHASHANK VYAS
 * Roll No. - MT2024141
 * Question: Hard link (link system call) 
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
