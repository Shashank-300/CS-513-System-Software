/*
============================================================================
Name : 16b.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to perform mandatory locking. 
    b. Implement read lock 
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
        printf("Pass the file name to be locked as the argument!\n");
    else
    {
        fd = open(argv[1], O_RDWR);
        if (fd == -1) {
            perror("Error opening file");
            return;
        }

        lock.l_type = F_RDLCK;    // Set the lock type to read lock
        lock.l_whence = SEEK_SET; // Base the lock offset on the start of the file
        lock.l_start = 0;         // Start the lock at the beginning of the file
        lock.l_len = 0;           // Lock the entire file
        lock.l_pid = getpid();    // Lock is associated with this process ID

        printf("Before entering into the critical section\n");
        // Applying the waiting read lock
        fcntl(fd, F_SETLKW, &lock);
        printf("Inside the critical section (read lock acquired)\n");
        printf("Press enter to unlock\n");
        
        // Wait for input to unlock the file
        getchar();

        printf("File unlocked\n");
        lock.l_type = F_UNLCK; //UNLOCK
        fcntl(fd, F_SETLK, &lock);
        printf("End\n");

        close(fd); 
    }
}

//Before pressing enter
/*
    Terminal 1
    shashank@ubuntu-22:~/Documents/SYS$ ./16b test3.txt
    Before entering into the critical section
    Inside the critical section (read lock acquired)
    Press enter to unlock
*/
/*
    Terminal 2
    shashank@ubuntu-22:~/Documents/SYS$ ./16b test3.txt
    Before entering into the critical section
    Inside the critical section (read lock acquired)
    Press enter to unlock
*/

// After pressing enter
/*
    Terminal 1
    shashank@ubuntu-22:~/Documents/SYS$ ./16b test3.txt
    Before entering into the critical section
    Inside the critical section (read lock acquired)
    Press enter to unlock

    File unlocked
    End
*/
/*
    Terminal 2
    shashank@ubuntu-22:~/Documents/SYS$ ./16b test3.txt
    Before entering into the critical section
    Inside the critical section (read lock acquired)
    Press enter to unlock

    File unlocked
    End
*/