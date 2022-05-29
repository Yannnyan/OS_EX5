/*
** server.c -- a stream socket server demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include "../Process/process.hpp"
#include "../Heap/heap_funcs.hpp"
#include "../Stack/Stack.hpp"


#define PORT "3490"  // the port users will be connecting to

#define BACKLOG 10   // how many pending connections queue will hold

int sockfd;
int conn_sockets[10]; 
void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}

void sig_abrt_handler(int s)
{
    clean_mem();
    for(int i=0; i < 10 && conn_sockets[i] != 0; i++)
    {
        close(conn_sockets[i]);
    }
    close(sockfd);
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
    int conn_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;    
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;
    map_memory();
    ex4::Stack * stack = (ex4::Stack *)_malloc(sizeof(ex4::Stack));
    stack->_Stack();
    memset(&hints, 0, sizeof hints);
    // giving a signal handler for cntrl c SIGQUIT or cntrl z SISTP
    signal(SIGSTOP, sig_abrt_handler);
    signal(SIGTSTP, sig_abrt_handler);
    signal(SIGINT, sig_abrt_handler);
    memset(conn_sockets, 0, sizeof(int) * 10);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("[SERVER]: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("[SERVER]: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)  {
        fprintf(stderr, "[SERVER]: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("[SERVER]: waiting for connections...\n");
    int i=0;
    while(1) {  // main accept() loop
        sin_size = sizeof(their_addr);
        conn_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        conn_sockets[(i++) % 10] = conn_fd;
        if (conn_fd == -1) {
            perror("accept");
            break;
        }

        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof(s));
        printf("[SERVER]: got connection from %s\n", s);

        if (!fork()) { // this is the child process
            close(sockfd); // child doesn't need the listener
            // the child runs in infinite loop listening to the client he received.
            process_function(conn_fd, stack);
            exit(0);
        }
    }
    // clean_mem();

    return 0;
}