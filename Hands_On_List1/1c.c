/*
============================================================================
Name : 1c.c
Author : SHASHANK VYAS
Description : Write a C,Create a FIFO file using the `mkfifo` library function or `mknod` system call
Date: 30th Aug, 2024.
============================================================================
*/

#include <sys/types.h> 
#include <sys/stat.h>  
#include <fcntl.h>     
#include <unistd.h>    
#include <stdio.h>     
#include <stdio.h>
#include <errno.h>

int main() {
    char *mkfifoName = "./mkfifo";    
    char *mknodName = "./mknodfifo"; 

    int mkfifo_rvalue; 
    int mknod_rvalue; 

    // Using `mkfifo` library function
    mkfifo_rvalue = mkfifo(mkfifoName, 0666);

    if (mkfifo_rvalue == -1)
        perror("Error in creating FIFO file using mkfifo. !");
    else
        printf("Successfully created FIFO file using mkfifo. !\n");

    // Using `mknod` system call
    mknod_rvalue = mknod(mknodName, __S_IFIFO | 0666, 0);

    if (mknod_rvalue == -1)
        perror("Error in creating FIFO file using mknod. !");
    else
        printf("Successfully created FIFO file using mknod. !\n");

    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ ./1c
    Successfully created FIFO file using mkfifo. !
    Successfully created FIFO file using mknod. !
    shashank@ubuntu-22:~/Documents/SYS$ ./1c
    Error in creating FIFO file using mkfifo. !: File exists
    Error in creating FIFO file using mknod. !: File exists
    shashank@ubuntu-22:~/Documents/SYS$ 
*/

