/* Name : SHASHANK VYAS
 * Roll No. : MT2024141
 * Question : Write a program to open a file in read only mode, read line by line and display each line as it is read. Close the file when end of file is reached.
 */

#include <sys/types.h> // Import for `open` system call.
#include <sys/stat.h>  // Import for `open` system call.
#include <fcntl.h>     // Import for `open` system call.
#include <unistd.h>    // Import for `read` and `write` system call
#include <stdio.h>     // Import for `perrro` and `printf` functions
#include <stdlib.h>

void main(int argc,char *argv[]){
	
	char *fname;
	int fd;
	char *buffer;
	
	if (argc != 2) {
        	printf("Usage: %s filename\n", argv[0]);
        	exit(1);
    	}

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
    	perror("Error opening file");
        exit(0);
    }	
	
	
	while ((read(fd, buffer, 1)) > 0) {
        	if (buffer[0] == '\n') {
            		getchar();
        	} 
		else {
            		write(STDOUT_FILENO, buffer, 1);
        	}
    	}

	close(fd);
}

/*
	shashank@ubuntu-22:~/Documents/SYS$ cat test3.txt
	Hi i am Shashank Vyas
	This is program 3
	shashank@ubuntu-22:~/Documents/SYS$ ./8 test3.txt 
	Hi i am Shashank Vyas
	This is program 3
*/
