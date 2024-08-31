/*
============================================================================
Name : 4.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to open an existing file with read write mode. Try O_EXCL flag also.
Date: 30th Aug, 2024.
============================================================================
*/


#include <sys/types.h> 
#include <sys/stat.h>  
#include <fcntl.h>     
#include <stdio.h>     

void main(int argc, char *argv[])
{

    char *fname;
    int fd;

    fname=argv[1];

    if (argc != 2)
        printf("Provide a filename as a argument\n");
    
    else
    {
	    fd = open(fname, O_RDWR | O_EXCL);

        if (fd == -1)
            perror("Error opening the file!");
        else
            printf("File '%s' opened successfully with O_RDWR | O_EXCL\n", fname);
    }
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ ./4 test4
    Error opening the file!: No such file or directory
    
    shashank@ubuntu-22:~/Documents/SYS$ ./4 test3.txt
    File 'test3.txt' opened successfully with O_RDWR | O_EXCL
    shashank@ubuntu-22:~/Documents/SYS$ 
*/
