#include "process.hpp"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "../Auxilary/functions.hpp"
#include "../Stack/Stack.hpp"


// the conn_fd is the socket connection with the client
// the target_fd is the socket connection with the target file, that the server reads from.
void process_function(int conn_fd, ex4::Stack * stack)
{
    char * buffer = nullptr;
    while(1)
    {
        buffer = read_message(conn_fd, BUFFERSIZE-1);
        process_input(buffer, conn_fd, stack);
        free(buffer);
    }
}

// this function receives a message
// then it processes the message and checks if it is valid
// then it writes the message to the target_fd
void process_input(char * buffer, int conn_fd, ex4::Stack * stack)
{
    if(startsWith(buffer, (char *)"POP"))
    {
        string str = stack->POP();
        char * buf = convert_string_to_array(str);
        write_message(conn_fd, buf, str.size());
        free(buf);
        return;
    }
    if(startsWith(buffer, (char *)"TOP"))
    {
        string str = stack->TOP();
        char * buf = convert_string_to_array(str);
        write_message(conn_fd, buf, str.size());
        free(buf);
        return;
    }
    if(startsWith(buffer, (char *)"PUSH"))
    {
        char * inp = getArg(buffer);
        stack->PUSH( convertArrToString(inp));
        free(inp);
        char * prompt = (char *)"Pushed into stack.";
        write_message(conn_fd, prompt, sizeof(prompt));
        return;
    }
    else
    {
        perror("ERROR: INSTRUCTION DOESN'T MATCH.");
        perror(buffer);
        char * prompt = (char *)"ERROR: INSTRUCTION DOESN'T MATCH.";
        write_message(conn_fd, prompt, sizeof(prompt));
        return;
    }

}

void write_message(int conn_fd, char * message, size_t size)
{
    if ((write(conn_fd, message, size)) == -1 )
    {
        perror("write failed.");
        return;
    }
}
char * read_message(int conn_fd, size_t num_bytes)
{
    char * buffer = (char *)malloc(num_bytes+1);
    if ((read(conn_fd, buffer ,num_bytes)) == -1)
    {
        perror("read failed.");
        return (char*)"";
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







