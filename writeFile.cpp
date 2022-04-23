#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>



int main(int argc, char * argv[])
{
    // argv[0] = name of file
    // argv[1] = buffer
    if (argc != 3)
    {
        exit(1);
    }
    printf("this is father or child.\n");
    int fd = 0;
    if ((fd = open("file.txt", O_WRONLY | O_APPEND)) == -1)
    {
        perror("open failed.\n");
        fprintf(stderr, "open failed.\n");
        abort();
    }
    char * buffer = argv[1];
    size_t w = 0;
    for(int i=0; i< 100; i++)
    {
         if ((w = write(fd, buffer, strlen(buffer + 1)) == -1))
        {
            perror("write failed.\n");
            fprintf(stderr, "write failed.");
            abort();
        }
        if (strcmp(argv[2], "f"))
        {
            printf("father %d, %zu \n", i, w);
        }
        else
        {
            printf("child %d, %zu \n", i, w);
        }
        
    }
   
    printf("%zu\n", w);
    close(fd);
    return 0;
}





