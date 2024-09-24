#Name: Shashank Vyas
#Roll Number: MT2024141

#1a Soft link (symlink system call)
ln -s test1 softLink.txt

#1b Hard link (link system call) 
ln test1 hardLink.txt

#1c FIFO (mkfifo Library Function or mknod system call)
mkfifo myfifo