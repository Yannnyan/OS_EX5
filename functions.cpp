#include <functions.hpp>
#include <string.h>
#include <stdlib.h>


int startsWith(char * target, char * prefix)
{
    size_t len = strlen(prefix);
    // the prefix is larger than the target
    if (strlen(target) < len)
    {
        return false;
    }
    for(int i=0; i<len; i++)
    {
        if (target[i] != prefix[i])
        {
            return 0;
        }
    }
    return 1;
}
char * getArg(char * target)
{
    // if the length is 0, this is invalid string
    size_t len = strlen(target);
    if (len == 0)
    {
        return NULL;
    }
    // iterate untill we found a space
    size_t i=0;
    while(target[i] != ' ')
    {
        if (target[i] == '\0' || target[i] == '\n')
        {
            return NULL;
        }
        i++;
    }
    i++;
    if(i > len)
    {
        return NULL;
    }
    char * arg = (char *) malloc(len + 1);
    size_t index_arg = 0;
    while(target[i] != '\0' && target[i] != '\n')
    {
        arg[index_arg] = target[i];
        index_arg++;
        i++;
    }
    return arg;
}







