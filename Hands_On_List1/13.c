/* Name : SHASHANK VYAS
 * Roll No. : MT2024141
 * Question : Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to verify whether the data is available within 10 seconds or not (check in $man 2 select).
 */

#include <sys/time.h>  // Import for 'select' and 'struct timeval' system call
#include <sys/types.h> // Import for 'select' system call
#include <unistd.h>    // For STDIN_FILENO, STDOUT_FILENO
#include <stdio.h>     

int main() {
    fd_set readFDSet;
    struct timeval time;
    int returnValue;

    // Initializing the fd sets
    FD_ZERO(&readFDSet);

    // Add STDIN to the set of fd to read from
    FD_SET(STDIN_FILENO, &readFDSet);

    // Setting the time to wait to 10 seconds
    time.tv_sec = 10;
    time.tv_usec = 0;	//Milliseconds

    // Calling select to monitor the fd
    returnValue = select(1, &readFDSet, NULL, NULL, &time);

     if (returnValue == -1) {
        perror("ERROR");
    } else if (returnValue) {
        // Check if STDIN has data available
        if (FD_ISSET(STDIN_FILENO, &readFDSet)) {
            printf("Data is available on STDIN.\n");
        }
    } else {
        // Timeout occurred
        printf("No data was given for 10 seconds.\n");
    }
    return 0;
}

/*
    shashank@ubuntu-22:~/Documents/SYS$ ./13
    No data was given for 10 seconds.
    shashank@ubuntu-22:~/Documents/SYS$ ./13
    hi 
    Data is available on STDIN.
*/



