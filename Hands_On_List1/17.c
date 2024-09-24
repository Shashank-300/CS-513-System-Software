/*
============================================================================
Name : 17.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to simulate online ticket reservations. Implement a write lock.  
    Write a program to open a file, store a ticket number, and exit.  Write a separate program, to open the file,  
    implement write lock, read the ticket number, increment the number, and print the new ticket number then close the file.
Date: 30th Aug, 2024.
============================================================================
*/

#include <unistd.h>    // For `close`, `read`, `write`, `lseek`
#include <fcntl.h>     // For `open`, `O_RDWR`, `F_SETLKW`
#include <sys/types.h> 
#include <sys/stat.h>  
#include <stdio.h>     // For `printf`, `perror`, `getchar`

int main() {
    struct flock lock;
    int fd;
    struct {
        int ticket_no;
    } db;

    // Open the file "db" in read/write mode
    fd = open("17init_db", O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Initialize the lock structure for a write lock
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET; 
    lock.l_start = 0;
    lock.l_len = 0; 
    lock.l_pid = getpid();

    printf("Before entering into critical section\n");

    //write lock
    fcntl(fd, F_SETLKW, &lock);
    printf("Inside the critical section\n");

    //current ticket number
    read(fd, &db, sizeof(db));
    printf("Current ticket number: %d\n", db.ticket_no);
    db.ticket_no++;
    // Reposition the file pointer to the beginning of the file
    lseek(fd, 0, SEEK_SET);
    write(fd, &db, sizeof(db));

    printf("New ticket number: %d\n", db.ticket_no);

    printf("Press enter to unlock\n");
    getchar(); //user input for unlock

    // Unlock the file
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    printf("Exited critical section\n");
    close(fd); 
    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ ./17
    Before entering into critical section
    Inside the critical section
    Current ticket number: 10
    New ticket number: 11
    Press enter to unlock

    Exited critical section
*/
