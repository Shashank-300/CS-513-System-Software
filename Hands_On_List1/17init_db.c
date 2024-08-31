/*
============================================================================
Name : 17init_db.c
Author : SHASHANK VYAS
Description : Write a program to open a file, store a ticket number, and exit.
Date: 30th Aug, 2024.
============================================================================
*/

#include <unistd.h>    // For `close`
#include <fcntl.h>     // For `open`, `O_CREAT`, `O_RDWR`
#include <sys/types.h> // For `open`
#include <sys/stat.h>  // For `open`
#include <stdio.h>     // For `printf`

int main() {
    int fd;
    struct {
        int ticket_no;
    } db;

    db.ticket_no = 10;
    fd = open("db", O_CREAT | O_RDWR, 0744);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Writing the initial ticket number to the file
    write(fd, &db, sizeof(db));
    close(fd);

    fd = open("db", O_RDONLY);

    // Read the ticket number
    read(fd, &db, sizeof(db));
    printf("Ticket no: %d\n", db.ticket_no); 
    close(fd);
    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ ./17init_db 
    Ticket no: 10
*/
