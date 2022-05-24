#include "doctest.h"
#include "sources/Heap/heap_funcs.hpp"
#include "signal.h"


TEST_CASE("malloc")
{
    map_memory();
    int * array = (int *)_malloc(sizeof(int) * 100);
    printf("array: %p\n", array);
    for(int i=0; i< 100; i++)
    {
        array[i] = i;
    }
    for(int i=0; i< 100; i++)
    {
        CHECK_EQ(array[i], i);
    }
    char ** chars = (char **)_malloc(sizeof(char *) * 10);
    printf("%p", chars);
    for(int i=0; i< 10; i++)
    {
        chars[i] = (char *)_malloc(sizeof(char));
    }
    for(int i=0; i< 10; i++)
    {
        chars[i][0] = 'a' + i;
    }
    for(int i=0; i< 10; i++)
    {
        CHECK_EQ(chars[i][0], 'a' + i); 
    }
    
}

TEST_CASE("free")
{
    int * array = (int *)_malloc(sizeof(int) * 100);
    for(int i=0; i< 100; i++)
    {
        array[i] = i;
    }
    _free(array);
    CHECK_THROWS(_free(array));
    clean_mem();
}











