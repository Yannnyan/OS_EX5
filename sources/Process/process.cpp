#include "process.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "../Heap/heap_funcs.hpp"
#include "../Auxilary/functions.hpp"
#include "../Stack/Stack.hpp"
#include <sys/socket.h>
#include <sys/types.h>

// the conn_fd is the socket connection with the client
// the target_fd is the socket connection with the target file, that the server reads from.
void process_function(int conn_fd, ex4::Stack * stack)
{
    char buffer[BUFFERSIZE];
    char * sendbuffer = (char *)malloc(BUFFERSIZE);
    while(1)
    {
        printf("reading message\n");
        if(recv(conn_fd, buffer, BUFFERSIZE, 0) == -1)
        {
            printf("error");
            break;

        }
        printf("[SERVER] Got message: %s", buffer);
        process_input(buffer, conn_fd, stack);
    }
    free(sendbuffer);
    printf("out\n");
}

// this function receives a message
// then it processes the message and checks if it is valid
// then it writes the message to the target_fd
void process_input(char * buffer, int conn_fd, ex4::Stack * stack)
{
    if(startsWith(buffer, (char *)"POP"))
    {
        char * buf = stack->POP();
        write_message(conn_fd, buf, strlen(buf) +1);
        free(buf);
        return;
    }
    if(startsWith(buffer, (char *)"TOP"))
    {
        char * buf = stack->TOP();
        write_message(conn_fd, buf, strlen(buf) +1);
        // free(buf);
        return;
    }
    if(startsWith(buffer, (char *)"PUSH"))
    {
        char garbage[BUFFERSIZE];
        char arg[BUFFERSIZE]; 
        memset(garbage,0 , BUFFERSIZE);
        memset(arg,0, BUFFERSIZE);
        sscanf(buffer, "%s %1024[^\n]", garbage, arg);
        arg[strlen(arg)] = '\0';
        stack->PUSH( arg );
        char * prompt = (char *)"Pushed into stack.\0";
        write_message(conn_fd, prompt, sizeof(prompt) + 1);
        return;
    }
    else
    {
        perror("ERROR: INSTRUCTION DOESN'T MATCH.");
        perror(buffer);
        char * prompt = (char *)"ERROR: INSTRUCTION DOESN'T MATCH.";
        write_message(conn_fd, prompt, sizeof(prompt) + 1);
        return;
    }

}

void write_message(int conn_fd, char * message, size_t size)
{
    printf("sending message\n");
    if ((send(conn_fd, message, size, 0)) == -1 )
    {
        printf("send failed.\n");
        perror("send failed.");
        return;
    }
}
char * read_message(int conn_fd, char * buffer,  size_t num_bytes)
{
    char * buf[BUFFERSIZE];
    memset(buffer, 0, BUFFERSIZE);
    int r = 0;
    if ((r = recv(conn_fd, buf ,BUFFERSIZE, 0)) == -1)
    {
        printf("recv failed.\n");
        perror("recv failed.\n");
        return (char*)"";
    }
    buffer[r] = '\0';
    printf("received %d bytes\n", r);
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







