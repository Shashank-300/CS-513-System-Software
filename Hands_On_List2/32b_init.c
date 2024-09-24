/*
============================================================================
Name        : 32record.c
Author      : SHASHANK VYAS
Description : C Program to Initialize Train Records in a File
Date        : 30th Aug, 2024.
============================================================================
*/


#include <unistd.h>    // For `close`, `read`, `write`, `lseek`
#include <fcntl.h>     // For `open`, `O_RDWR`, `F_SETLKW`
#include <sys/types.h> 
#include <sys/stat.h>  
#include <stdio.h>     // For `printf`, `perror`, `getchar`

int main() {
    int i, fd;
    struct {
        int trainnum;
        int ticketcount;
    } db[3];
    for (i=0; i<3; i++) {
        db[i].trainnum = i+1;
        db[i].ticketcount = 0;
    }
    // Writing all 3 records to test18.txt file
        fd = open("train.txt", O_RDWR | O_CREAT,0666);
        if(fd==0)
        {
            printf("Error");
        }
        write(fd, db, sizeof(db));
}