/*
============================================================================
Name : 16a.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to perform mandatory locking. 
    a. Implement write lock 
Date: 30th Aug, 2024.
============================================================================
*/

#include <unistd.h>   
#include <fcntl.h>    
#include <sys/types.h> 
#include <sys/stat.h>  
#include <stdio.h>  

void main(int argc, char *argv[])
{
    struct flock lock;
    int fd;

    if (argc != 2)
        printf("Pass the file name to be locked as the argument!");
    else
    {
        int fd;
        fd = open(argv[1], O_RDWR);
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = 0;
        lock.l_len = 0;
        lock.l_pid = getpid();
        printf("Before entering into critical section\n");
        fcntl(fd, F_SETLKW, &lock);
        printf("Inside the critical section\n");
        printf("Press enter to unlock");
        // This makes the program wait till an input is received on STDIN and so file remains locked, till that happens
        getchar();
        printf("File unlocked\n");
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        printf("End\n");
    }
}

//Before pressing enter
/*
    Terminal 1
    shashank@ubuntu-22:~/Documents/SYS$ ./16 test3.txt
    Before entering into critical section
    Inside the critical section
    Press enter to unlock
*/
/*
    Terminal 2
    shashank@ubuntu-22:~/Documents/SYS$ ./16 test3.txt
    Before entering into critical section
*/

// After pressing enter
/*
    Terminal 1
    shashank@ubuntu-22:~/Documents/SYS$ ./16 test3.txt
    Before entering into critical section
    Inside the critical section
    Press enter to unlock
    File unlocked
    End
    shashank@ubuntu-22:~/Documents/SYS$ 
*/
/*
    Terminal 2
    shashank@ubuntu-22:~/Documents/SYS$ ./16 test3.txt
    Before entering into critical section
    Inside the critical section
    Press enter to unlock
*/