#include "sources/Heap/heap_funcs.hpp"
#include "sources/Stack/Stack.hpp"
#include "sources/Auxilary/functions.hpp"
#include <sys/mman.h>
#include <unistd.h>
#include <wait.h>
#include <iostream>
#include <string.h>

using namespace std;
using namespace ex4;


int somefunc(char * buffer)
{
    return startsWith(buffer, (char *) "PUSH"); 
}
int main()
{
    char * buffer = "PUSH HELLO WORLD";
    printf("%d %ld\n", somefunc(buffer),strlen(buffer));
}









