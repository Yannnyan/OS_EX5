#include "doctest.h"
#include "sources/Heap/heap_funcs.hpp"
#include "sources/Stack/Stack.hpp"
#include <string.h>
#include <vector>
using namespace ex4;
using namespace std;
TEST_CASE("Stack functionality")
{
    map_memory();
    Stack * stack = (Stack *)_malloc(sizeof(Stack));
    stack->_Stack();
    stack->set_fd(get_mapped_fd());
    vector<char *> strs{(char *)"HELLO WORLD", (char *)"NVIDIA 1050 TI", (char *)"12 GEN INTEL PROCESSORS", (char *)"160 CORES PC with 320 THREADS"};
    SUBCASE("PUSH")
    {
        for(int i=0; i< 4; i++)
        {
            CHECK_NOTHROW(stack->PUSH(strs[i]));
            CHECK(!strcmp(stack->TOP(), strs[i]));
            // puts(stack->TOP());
        }
    }
    // SUBCASE("POP")
    // {
        char * str;
        for(int i=0; i<4; i++)
        {
            CHECK_NOTHROW(str = stack->POP());
            // puts(str);
            CHECK(!strcmp(str, strs[3 - i]));
            free(str);
        }
    // }
    
    clean_mem();
}




