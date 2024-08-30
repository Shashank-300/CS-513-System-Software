/*
============================================================================
Name : 27d.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to execute `ls -Rl` by the following system calls 
    d. `execv` 
Date: 30th Aug, 2024.
============================================================================
*/

#include <stdio.h>  // For `printf`
#include <unistd.h> // For `execl`
#include <stdlib.h> // For `exit`

int main() {
    printf("Executing `ls -Rl` using execl...\n");

    char *args[] = {"/bin/ls", "-Rl",NULL, NULL}; 
    // Using execv to execute the command `ls -Rl`
    if (execv(args[0], args));
    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ ./27d
    Executing `ls -Rl` using execl...
    .:
    total 896
    -rwxrwxr-x 1 shashank shashank 16256 Aug 26 18:28 10
    -rw-rw-r-- 1 shashank shashank  2252 Aug 30 20:09 10.c
    -rwxrwxr-x 1 shashank shashank 16248 Aug 26 19:03 11
    -rwxrwxr-x 1 shashank shashank 16256 Aug 28 15:26 11a
    -rw-rw-r-- 1 shashank shashank  2050 Aug 30 20:11 11a.c
    -rwxrwxr-x 1 shashank shashank 16296 Aug 28 15:35 11b
    -rw-rw-r-- 1 shashank shashank  2259 Aug 30 20:12 11b.c
    -rw-rw-r-- 1 shashank shashank    44 Aug 28 15:36 11b.txt
    -rwxrwxr-x 1 shashank shashank 16336 Aug 28 15:43 11c
    -rw-rw-r-- 1 shashank shashank  2486 Aug 30 20:15 11c.c
    -rw-rw-r-- 1 shashank shashank    44 Aug 28 15:43 11c.txt
    -rwxrwxr-x 1 shashank shashank 16200 Aug 28 16:34 12
    -rw-rw-r-- 1 shashank shashank  2112 Aug 30 20:21 12.c
    -rwxrwxr-x 1 shashank shashank 16088 Aug 30 20:22 13
    -rw-rw-r-- 1 shashank shashank  1630 Aug 30 20:23 13.c
    -rwxrwxr-x 1 shashank shashank 16168 Aug 28 19:40 14
    -rw-rw-r-- 1 shashank shashank  1956 Aug 30 20:26 14.c
    -rwxrwxr-x 1 shashank shashank 16016 Aug 28 21:16 15
    -rw-rw-r-- 1 shashank shashank  5244 Aug 30 20:29 15.c
    -rwxrwxr-x 1 shashank shashank 16216 Aug 27 12:47 16a
    -rw-rw-r-- 1 shashank shashank  2060 Aug 30 20:30 16a.c
    -rwxrwxr-x 1 shashank shashank 16256 Aug 27 13:03 16b
    -rw-rw-r-- 1 shashank shashank  2519 Aug 30 20:30 16b.c
    -rwxrwxr-x 1 shashank shashank 16424 Aug 27 13:44 17
    -rw-rw-r-- 1 shashank shashank  2180 Aug 30 21:25 17.c
    -rwxrwxr-x 1 shashank shashank 16216 Aug 27 13:43 17init_db
    -rw-rw-r-- 1 shashank shashank  1271 Aug 30 14:57 17init_db.c
    -rw-rw-r-- 1 shashank shashank  2215 Aug 30 21:27 18.c
    -rw-rw-r-- 1 shashank shashank   555 Aug 29 08:16 18init.c
    -rwxrwxr-x 1 shashank shashank 16024 Aug 29 08:47 19
    -rw-rw-r-- 1 shashank shashank   867 Aug 30 21:29 19.c
    -rwxrwxr-x 1 shashank shashank 15992 Aug 28 08:56 1a
    -rw-rw-r-- 1 shashank shashank   677 Aug 30 19:23 1a.c
    -rwxrwxr-x 1 shashank shashank 15992 Aug 28 09:03 1b
    -rw-rw-r-- 1 shashank shashank   659 Aug 30 19:24 1b.c
    -rwxrwxr-x 1 shashank shashank 16080 Aug 28 09:08 1c
    -rw-rw-r-- 1 shashank shashank  1510 Aug 30 19:24 1c.c
    -rwxrwxr-x 1 shashank shashank 15768 Aug 28 09:10 2
    -rwxrwxr-x 1 shashank shashank 16080 Aug 29 08:40 20
    -rw-rw-r-- 1 shashank shashank  1027 Aug 30 22:47 20.c
    -rwxrwxr-x 1 shashank shashank 16032 Aug 29 08:50 21
    -rw-rw-r-- 1 shashank shashank   731 Aug 30 21:45 21.c
    -rwxrwxr-x 1 shashank shashank 16200 Aug 29 10:43 22
    -rw-rw-r-- 1 shashank shashank  1841 Aug 30 21:46 22.c
    -rwxrwxr-x 1 shashank shashank 16160 Aug 29 11:00 23
    -rw-rw-r-- 1 shashank shashank  1325 Aug 30 21:48 23.c
    -rwxrwxr-x 1 shashank shashank 16160 Aug 29 13:55 24
    -rw-rw-r-- 1 shashank shashank   974 Aug 30 21:49 24.c
    -rwxrwxr-x 1 shashank shashank 16160 Aug 29 21:59 25
    -rw-rw-r-- 1 shashank shashank  1555 Aug 30 21:50 25.c
    -rwxrwxr-x 1 shashank shashank 16080 Aug 29 22:44 26
    -rw-rw-r-- 1 shashank shashank  1009 Aug 30 21:52 26.c
    -rwxrwxr-x 1 shashank shashank 16080 Aug 30 00:40 27a
    -rw-rw-r-- 1 shashank shashank   682 Aug 30 21:55 27a.c
    -rwxrwxr-x 1 shashank shashank 16080 Aug 30 00:41 27b
    -rw-rw-r-- 1 shashank shashank   685 Aug 30 21:55 27b.c
    -rwxrwxr-x 1 shashank shashank 16080 Aug 30 00:42 27c
    -rw-rw-r-- 1 shashank shashank   690 Aug 30 22:46 27c.c
    -rwxrwxr-x 1 shashank shashank 16040 Aug 30 23:47 27d
    -rw-rw-r-- 1 shashank shashank   650 Aug 30 22:46 27d.c
    -rwxrwxr-x 1 shashank shashank 16048 Aug 30 23:45 27e
    -rw-rw-r-- 1 shashank shashank  7954 Aug 30 23:46 27e.c
    -rwxrwxr-x 1 shashank shashank 16152 Aug 30 09:59 28
    -rw-rw-r-- 1 shashank shashank  1090 Aug 30 23:43 28.c
    -rwxrwxr-x 1 shashank shashank 16240 Aug 30 11:34 29
    -rw-rw-r-- 1 shashank shashank  2342 Aug 30 23:44 29.c
    -rw-rw-r-- 1 shashank shashank   628 Aug 30 19:26 2.c
    -rwxrwxr-x 1 shashank shashank 16032 Aug 28 09:17 3
    -rwxrwxr-x 1 shashank shashank 16248 Aug 30 14:40 30
    -rw-rw-r-- 1 shashank shashank   954 Aug 30 23:45 30.c
    -rw-rw-r-- 1 shashank shashank   754 Aug 30 20:11 3.c
    -rwxrwxr-x 1 shashank shashank 16072 Aug 20 10:36 4
    -rw-rw-r-- 1 shashank shashank  1168 Aug 30 19:27 4.c
    -rwxrwxr-x 1 shashank shashank 15952 Aug 28 09:32 5
    -rw-rw-r-- 1 shashank shashank  1212 Aug 30 20:03 5.c
    -rwxrwxr-x 1 shashank shashank 16088 Aug 28 14:06 6
    -rw-rw-r-- 1 shashank shashank   643 Aug 30 20:05 6.c
    -rwxrwxr-x 1 shashank shashank 16248 Aug 28 14:35 7
    -rw-rw-r-- 1 shashank shashank  2195 Aug 30 20:06 7.c
    -rwxrwxr-x 1 shashank shashank 16248 Aug 29 10:21 8
    -rw-rw-r-- 1 shashank shashank  1401 Aug 30 20:07 8.c
    -rwxrwxr-x 1 shashank shashank 16128 Aug 20 15:59 9
    -rw-rw-r-- 1 shashank shashank  2177 Aug 30 20:08 9.c
    drwxrwxr-x 3 shashank shashank  4096 Aug 29 09:07 CS-513-System-Software
    -rwxrwxr-x 1 shashank shashank 16208 Aug 27 18:41 db
    -rw-rw-r-- 2 shashank shashank     0 Aug 21 23:00 file
    drwxrwxr-x 4 shashank shashank  4096 Aug 29 09:15 Hands_On_List1
    -rwxrwxr-x 1 shashank shashank 15952 Aug  8 08:59 hardlink
    -rw-rw-r-- 1 shashank shashank   140 Aug 28 08:58 hardlink.c
    prw-rw-r-- 1 shashank shashank     0 Aug 22 08:46 head
    -rw-rw-r-- 2 shashank shashank     0 Aug 21 23:00 hlink
    -rw-rw-r-- 2 shashank shashank     0 Aug 28 08:55 hlinktest
    prw-rw-r-- 1 shashank shashank     0 Aug 22 08:45 ll
    drwxrwxr-x 2 shashank shashank  4096 Aug 20 10:48 loopfile
    -rw-rw-r-- 1 shashank shashank    86 Aug  8 08:31 lseek.c
    prw-rw-r-- 1 shashank shashank     0 Aug 28 09:09 mkfifo
    prw-rw-r-- 1 shashank shashank     0 Aug 28 09:09 mknodfifo
    prwx------ 1 shashank shashank     0 Aug 11 17:21 mymkfifo
    prwx------ 1 shashank shashank     0 Aug 11 17:21 mymknod-fifo
    lrwxrwxrwx 1 shashank shashank     5 Aug 28 08:56 slinktest -> test1
    -rw-rw-r-- 2 shashank shashank     0 Aug 28 08:55 test1
    -rw-rw-r-- 1 shashank shashank    30 Aug 26 18:31 test10.txt
    -rw-rw-r-- 1 shashank shashank    88 Aug 28 15:26 test11.txt
    -rw-r--r-- 1 shashank shashank    71 Aug 29 10:44 test22.txt
    -rwx------ 1 shashank shashank     0 Aug  8 09:11 test3
    -rw-r--r-- 1 shashank shashank    40 Aug 28 14:24 test3.txt
    -rw------- 1 shashank shashank    40 Aug 28 14:36 test7.txt

    ./CS-513-System-Software:
    total 16
    -rw-rw-r-- 1 shashank shashank 11357 Aug 29 09:07 LICENSE
    -rw-rw-r-- 1 shashank shashank    24 Aug 29 09:07 README.md

    ./Hands_On_List1:
    total 8
    drwxrwxr-x 3 shashank shashank 4096 Aug 29 09:15 CS-513-System-Software
    -rw-rw-r-- 1 shashank shashank   40 Aug 29 09:12 Readme.md

    ./Hands_On_List1/CS-513-System-Software:
    total 16
    -rw-rw-r-- 1 shashank shashank 11357 Aug 29 09:15 LICENSE
    -rw-rw-r-- 1 shashank shashank    24 Aug 29 09:15 README.md

    ./loopfile:
    total 0
    -rw-r--r-- 1 shashank shashank 0 Aug 28 13:59 1
    -rw-r--r-- 1 shashank shashank 0 Aug 28 13:59 2
    -rw-r--r-- 1 shashank shashank 0 Aug 28 13:59 3
    -rw-r--r-- 1 shashank shashank 0 Aug 28 13:59 4
    -rw-r--r-- 1 shashank shashank 0 Aug 28 13:59 5
*/