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
    // char * sendbuffer = (char *)malloc(BUFFERSIZE);
    while(1)
    {
        printf("[SERVER] Reading message\n");
        memset(buffer, 0 , BUFFERSIZE);
        if(recv(conn_fd, buffer, BUFFERSIZE, 0) == -1)
        {
            printf("error\n");
            break;

        }
        printf("[SERVER] Got message: %s\n", buffer);
        process_input(buffer, conn_fd, stack);
    }
    // free(sendbuffer);
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
        if(send(conn_fd, buf, strlen(buf) + 1, 0) == -1)
        {
            printf("ERROR: cannot send message. POP");
            close(conn_fd);
            exit(1);
        }
        free(buf);
        return;
    }
    if(startsWith(buffer, (char *)"TOP"))
    {
        char * buf = stack->TOP();
        if(send(conn_fd, buf, strlen(buf) + 1, 0) == -1)
        {
            printf("ERROR: cannot send message. TOP");
            close(conn_fd);
            exit(1);
        }
        // free(buf);
        return;
    }
    if(startsWith(buffer, (char *)"PUSH"))
    {
        char * arg; 
        buffer[strlen(buffer)] = '\0';
        arg = getArg(buffer);
        arg[strlen(arg)] = '\0';
        stack->PUSH( arg );
        char * prompt = (char *)"Pushed into stack.";
        free(arg);
        if(send(conn_fd, prompt, strlen(prompt) + 1, 0) == -1)
        {
            printf("ERROR: cannot send message. PUSH");
            close(conn_fd);
            exit(1);
        }
        puts("[SERVER] Sent message to client.\n");
        return;
    }
    else
    {
        perror("ERROR: INSTRUCTION DOESN'T MATCH.");
        perror(buffer);
        char * prompt = (char *)"ERROR: INSTRUCTION DOESN'T MATCH.";
        if(send(conn_fd, prompt, strlen(prompt) + 1, 0) == -1)
        {
            printf("ERROR: cannot send message.");
            close(conn_fd);
            exit(1);
        }
        return;
    }

}




