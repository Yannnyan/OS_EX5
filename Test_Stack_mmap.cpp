
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "Stack.hpp"
#include <string>
#include <wait.h>

using namespace ex4;
using namespace std;

int main()
{
    int fd = open("stack.txt", O_CREAT | O_RDWR);
    long size_page = sysconf(_SC_PAGE_SIZE);
    if(ftruncate(fd, size_page) == -1)
    {
        perror("ftruncate error");
        exit(1);
    }
    Stack * stack = (Stack *)mmap(0, size_page, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    stack->PUSH("HELLO WORLD");
    cout << stack->TOP() << endl;
    // int pid = fork();
    // if(pid == 0)
    // {
    //     stack->PUSH("1050 TI");
    //     cout << "child pushed to stack " + stack->TOP() << endl;
    // }
    // else
    // {
    //     wait(&pid);
    //     cout << stack->POP() << endl;
    //     cout << stack->POP() << endl;
    // }

    munmap(stack, size_page);
    close(fd);
    
}










