/*
============================================================================
Name : 26.c
Author : SHASHANK VYAS
Description : Write a C ,Ansi-style program to execute an executable program. 
    a. Use some executable program 
    b. Pass some input to an executable program. (for example execute an executable of `$./a.out name`)
Date: 30th Aug, 2024.
============================================================================
*/

#include <stdio.h>  // Import for `printf`
#include <unistd.h> // Import for `execlp`
#include <stdlib.h> // Import for `exit`

int main() {
    // Define the name of the executable program and its arguments
    char *program = "./9"; 
    char *arg1 = "test3.txt";      

    // Display a message before execution
    printf("Executing the program: %s with argument: %s\n", program, arg1);

    // Execute the program using execlp
    if (execlp(program, program, arg1, NULL) == -1) {
        perror("Error executing the program");
        exit(0);
    }
    return 0;
}
