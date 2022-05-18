#include "process.hpp"
#include <stdio.h>
#include <unistd.h>
#include "functions.hpp"
#include <string.h>
#include <fcntl.h>

size_t BUFFERSIZE = 1024;
// the conn_fd is the socket connection with the client
// the target_fd is the socket connection with the target file, that the server reads from.
void process_function(int conn_fd, int target_fd)
{
    char * buffer;
    while(1)
    {
        buffer = read_message(conn_fd, BUFFERSIZE-1);
        process_input(buffer, target_fd);
        free(buffer);
    }
}

// this function receives a message
// then it processes the message and checks if it is valid
// then it writes the message to the target_fd
void process_input(char * buffer, int target_fd)
{
    if (!startsWith(buffer, "POP") || !startsWith(buffer, "PUSH ") || !startsWith(buffer, "TOP"))
    {
        perror("ERROR: INSTRUCTION DOESN'T MATCH.");
        return;
    }
    write_message(target_fd, buffer, strlen(buffer) + 1);
}

void write_message(int conn_fd, char * message, size_t size)
{
    
    int w = 0;
    if ((w = write(conn_fd, message, size)) == -1 )
    {
        perror("write failed.");
        exit(1);
    }
}
char * read_message(int conn_fd, size_t num_bytes)
{
    int r = 0;
    char * buffer = (char *)malloc(num_bytes+1);
    if ((r = read(conn_fd, buffer ,num_bytes)) == -1)
    {
        perror("read failed.");
        exit(1);
    }
    return buffer;
}

int open_file(char * filename, int flags)
{
    int fd =0;
    if ((fd =open(filename, flags)) == -1)
    {
        perror("failed to open file.");
        exit(1);
    }
    return fd;
}

void close_file(int open_fd)
{
    if (close(open_fd) == -1)
    {
        perror("failed to close the file.");
        exit(1);
    }
}







