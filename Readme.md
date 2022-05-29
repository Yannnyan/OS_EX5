
![](https://github.com/Yannnyan/OS_EX5/blob/main/projectDiagram.png)


# Overview
In this project we've implemented multi process mapping of memory that child processes can manipulate.
We've also implemented a Server that serves multiple clients in a multi process inviroment.
All the server child process hold a shared address of a Stack object we've implemented too, which we prepared it to be multi process safe.

# Testing
The testing was done with doctest.h, we've tested the functionallity of the stack and the memory mapping.


### the main system calls used in this excersise
1) mmap
2) fcntl
read, write, open, close ...

### some library functions
ftruncate