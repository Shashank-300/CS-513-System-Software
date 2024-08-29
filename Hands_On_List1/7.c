/* Name : SHASHANK VYAS
 * Roll No. : MT2024141
 * Question : Write a program to copy file1 into file2 ($cp file1 file2).
 */

#include <sys/types.h> // Import for `open`  system call.
#include <sys/stat.h>  // Import for `open` system call.
#include <fcntl.h>     // Import for `open`  system call.
#include <unistd.h>    // Import for `read` and `write` system call
#include <stdio.h>     // Import for `perrro` and `printf` functions
#include <stdlib.h>    // Import for `exit` function.

int main(int argc,char *argv[]) {
	
	int S_fd, D_fd;		// The file descriptors of the source and destination files
    int rbytes, wbytes;	// Number of bytes read and write into the buffer respectively.
    char *buffer[1024];	// Buffer to store contents of the source file
	char *S_fname;
	char *D_fname; 

	if (argc != 3) {
        	printf("%s file1 file2\n",argv[0]);
        	exit(1);
    	}

	S_fname=argv[1];
	D_fname=argv[2];
	
	S_fd=open(S_fname, O_RDONLY);
	D_fd=open(D_fname, O_CREAT | O_WRONLY | O_EXCL , 0600);

	if(S_fd==-1 ){
		perror("Error in opening Source file!!");
	}

	if(D_fd==-1 ){           
                  perror("Error in opening Destination file!!");            
        }

	// Copy contents from the source file to the destination file.
	while ((rbytes = read(S_fd, buffer, 100)) > 0)
	{
            wbytes = write(D_fd, buffer, rbytes);
            if (wbytes == -1)
                printf("Error in writing to file %s",D_fname);
        }

	 // Checking if there was an error during reading.
    if (rbytes == -1) {
        perror("Error reading source file");
    } else {
        // If no error, print success message.
        printf("Successfully copied content from file %s to file %s!\n", S_fname, D_fname);
    }
		
	close(S_fd);
	close(D_fd);

	return 0;
}

/*
	shashank@ubuntu-22:~/Documents/SYS$ ./7 test3.txt test7.txt
	Successfully copied content from file test3.txt to file test7.txt!
	shashank@ubuntu-22:~/Documents/SYS$ cat test7.txt 
	Hi i am Shashank Vyas
	This is program 3
*/
