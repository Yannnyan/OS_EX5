#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pid = fork();
    if (pid == 0) // child
    {
        char * buffer[] = {(char *)"writeFile", (char *)"cc", (char *)"c", NULL};
        execv((char *)"writeFile", buffer);
    }
    else // father
    {
        char * buffer[] = {(char *)"writeFile", (char *)"ff", (char *)"f", NULL};
        execv((char *)"writeFile", buffer);
    }
    
    return 0;

}