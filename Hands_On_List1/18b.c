/*
============================================================================
Name        : 18b.c
Author      : SHASHANK VYAS
Description : Write a C, ANSI-style program to perform Record locking. 
              b. Implement read lock 
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
    int ticket_count;
};

int main() {
    int fd, input;
    struct database db;

    fd = open("test18.txt", O_RDWR);

    printf("Select train number: 1, 2, 3\n");
    scanf("%d", &input);

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;

    // Lock start point based on the selected train number
    lock.l_start = (input - 1) * sizeof(struct database);
    lock.l_len = sizeof(struct database);
    lock.l_pid = getpid();

    // Read lock
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Error setting read lock");
        close(fd);
        return 1;
    }

    // Reading the value of the selected record
    lseek(fd, (input - 1) * sizeof(struct database), SEEK_SET);
    if (read(fd, &db, sizeof(struct database)) != sizeof(struct database)) {
        perror("Error reading record");
        close(fd);
        exit(0);
    }

    printf("Current ticket count for train %d: %d\n", db.trainnum, db.ticket_count);

    printf("To release the read lock, press enter\n");
    getchar();
    getchar();

    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Error unlocking");
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}
