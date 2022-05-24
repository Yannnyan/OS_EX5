#ifndef PROCESS_HPP_
#define PROCESS_HPP_

#include <stdlib.h>
#include "../Stack/Stack.hpp"

// struct flock lock;
// this function writes a message into the file descriptor specified.
void write_message(int conn_fd, char * message, size_t size);
// reads num_bytes bytes from conn_fd 
char * read_message(int conn_fd, size_t num_bytes);
// the function that a process runs upon
void process_function(int conn_fd, ex4::Stack * stack);
// open a file and returns a file descriptor for the open file.
// if failed destroys the program.
int open_file(char * filename);
// close a file and destroy program if fails
void close_file(int open_fd);
// receives a buffer and processes the input
void process_input(char * buffer, int conn_fd, ex4::Stack * stack);

#endif

