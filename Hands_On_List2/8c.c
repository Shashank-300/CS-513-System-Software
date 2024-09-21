/*
============================================================================
Name : 8c.c
Author : Shashank Vyas
Description :  Write a separate program using signal system call to catch `SIGFPE`
Date: 20th Sep, 2024.
============================================================================
*/

#include <signal.h> // Import for `signal`, `raise`
#include <stdio.h>  // Import for `printf`, `scanf` & `perror`
#include <unistd.h> // Import for `_exit`

void callback()
{
    printf("Signal SIGFPE has been caught!\n");
    _exit(0);
}

void main()
{
    __sighandler_t signalStatus; // Determines the success of the `signal` call

    signalStatus = signal(SIGFPE, (void *)callback);
    if (signalStatus == SIG_ERR)
        perror("Error while assigning signal handler!");
    else
        raise(SIGFPE); // Send a signal associated with floating point error
}

/*
shashank@ubuntu-22:~/Documents/HOL 2$ ./8c
Signal SIGFPE has been caught!
*/