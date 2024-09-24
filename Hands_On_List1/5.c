/*
============================================================================
Name : 5.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to create five new files with an infinite loop. Execute the program in the background and check the file descriptor table at /proc/pid/fd.
Date: 30th Aug, 2024.
============================================================================
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

void main(){

	while(1){
		
		creat("./loopfile/1",0644);
		creat("./loopfile/2",0644);
		creat("./loopfile/3",0644);
		creat("./loopfile/4",0644);
		creat("./loopfile/5",0644);
		// printf("file created"); //Testing purpose
	}

}

/*
	l-wx------ 1 shashank shashank 64 Aug 28 14:03 116772 -> /home/shashank/Documents/SYS/loopfile/1
	l-wx------ 1 shashank shashank 64 Aug 28 14:03 116773 -> /home/shashank/Documents/SYS/loopfile/2
	l-wx------ 1 shashank shashank 64 Aug 28 14:03 116774 -> /home/shashank/Documents/SYS/loopfile/3
	l-wx------ 1 shashank shashank 64 Aug 28 14:03 116775 -> /home/shashank/Documents/SYS/loopfile/4
	l-wx------ 1 shashank shashank 64 Aug 28 14:03 116776 -> /home/shashank/Documents/SYS/loopfile/5
*/
