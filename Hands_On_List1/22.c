/*
============================================================================
Name : 22.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program,open a file, call fork, and then write to the file by both the child as well as the parent processes. Check output of the file.
Date: 30th Aug, 2024.
============================================================================
*/

#include <unistd.h>    // Import for `fork` system call
#include <sys/types.h> // Import for `open`, `fork` system call
#include <sys/stat.h>  // Import for `open` system call
#include <fcntl.h>     // Import for `open` system call
#include <stdio.h>     // Import for `printf`
#include <sys/wait.h>  // Import for `wait`
#include <stdlib.h>    // Import for `exit`
#include <string.h>    // Import for `strlen`

int main(int argc,char *argv[]) {
    int fd;
    int pid,cpid;

    if(argc!=2)
    {
        printf("Enter the filename !! \n");
        exit(0);
    }
    fd = open(argv[1], O_CREAT | O_WRONLY | O_APPEND, 0644);

    pid = fork();

    if (pid == 0) {
        // Child process
        const char *childmessage="This is the child process writing.\n";
        write(fd,childmessage,strlen(childmessage));
    } else {
        // Parent process
        const char *parentmessage="This is the parent process writing.\n";
        write(fd,parentmessage,strlen(parentmessage));
        wait(NULL);
    }

    printf("Both parent and child have written to the file.\n");
    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ gcc -o 22 22.c
    shashank@ubuntu-22:~/Documents/SYS$ ./22 test22.txt
    Both parent and child have written to the file.
    Both parent and child have written to the file.
    shashank@ubuntu-22:~/Documents/SYS$ cat test22.txt
    This is the parent process writing.
    This is the child process writing.
*/