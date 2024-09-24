/*
============================================================================
Name        : 18a.c
Author      : SHASHANK VYAS
Description : Write a C, ANSI-style program to perform Record locking. 
              a. Implement write lock 
Date        : 30th Aug, 2024.
============================================================================
*/

#include <unistd.h>    // For `close`, `read`, `write`, `lseek`
#include <fcntl.h>     // For `open`, `O_RDWR`, `F_SETLKW`
#include <sys/types.h> 
#include <sys/stat.h>  
#include <stdlib.h>
#include <stdio.h>     // For `printf`, `perror`, `getchar`

struct database {
    int trainnum;
    int ticketcount;
};

int main() {
    int fd, input;
    struct database db;

    fd = open("test18.txt", O_RDWR);
   
    printf("Select train number: 1, 2, 3\n");
    scanf("%d", &input);

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;

    // Lock start point based on the train number
    lock.l_start = (input - 1) * sizeof(struct database);
    lock.l_len = sizeof(struct database);
    lock.l_pid = getpid();

    // Value of ticket number
    lseek(fd, (input - 1) * sizeof(struct database), SEEK_SET);
    read(fd, &db, sizeof(struct database));

    printf("Before entering critical section\n");

    // Write lock
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Error setting lock");
        exit(0);
    }

    printf("Current ticket count: %d\n", db.ticketcount);
    db.ticketcount++;

    // Moving the file pointer to the start of the current record
    lseek(fd, -1 * sizeof(struct database), SEEK_CUR);
    write(fd, &db, sizeof(struct database));

    printf("To book ticket, press enter\n");
    getchar();
    getchar();

    // Unlock the record
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Error unlocking");
        close(fd);
        exit(0);
    }

    printf("Ticket booked with number %d\n", db.ticketcount);
    close(fd);
    return 0;
}
