/*
============================================================================
Name : 9.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to print the following information about a given file. 
    1. Inode 
    2. Number of hard links 
    3. UID 
    4. GID 
    5. Size 
    6. Block size 
    7. Number of blocks 
    8. Time of last access 
    9. Time of last modification 
    10. Time of last change
Date: 30th Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
    struct stat fileStat;

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    if (stat(argv[1], &fileStat) < 0) {
        perror("Error retrieving file stats");
        return 1;
    }

    // 1. Inode
    printf("Inode: %ld\n", fileStat.st_ino);

    // 2. Number of hard links
    printf("Number of hard links: %ld\n", fileStat.st_nlink);

    // 3. UID (User ID of owner)
    printf("UID: %d\n", fileStat.st_uid);

    // 4. GID (Group ID of owner)
    printf("GID: %d\n", fileStat.st_gid);

    // 5. Size (in bytes)
    printf("Size: %ld bytes\n", fileStat.st_size);

    // 6. Block size (preferred I/O block size)
    printf("Block size: %ld bytes\n", fileStat.st_blksize);

    // 7. Number of blocks allocated
    printf("Number of blocks: %ld\n", fileStat.st_blocks);

    // 8. Time of last access
    printf("Last access time: %s", ctime(&fileStat.st_atime));

    // 9. Time of last modification
    printf("Last modification time: %s", ctime(&fileStat.st_mtime));

    // 10. Time of last change (status change)
    printf("Last change time: %s", ctime(&fileStat.st_ctime));

    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ ./9 test7.txt
    Inode: 1466466
    Number of hard links: 1
    UID: 1000
    GID: 1000
    Size: 40 bytes
    Block size: 4096 bytes
    Number of blocks: 8
    Last access time: Wed Aug 28 14:36:16 2024
    Last modification time: Wed Aug 28 14:36:09 2024
    Last change time: Wed Aug 28 14:36:09 2024
*/