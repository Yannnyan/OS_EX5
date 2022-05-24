#include "doctest.h"
#include "sources/Heap/heap_funcs.hpp"
#include "sources/Stack/Stack.hpp"
#include <string>
#include <vector>
using namespace ex4;
using namespace std;
TEST_CASE("Stack functionality")
{
    map_memory();
    Stack * stack = (Stack *)_malloc(sizeof(Stack));
    stack->set_fd(get_mapped_fd());
    vector<string> strs{"HELLO WORLD", "NVIDIA 1050 TI", "12 GEN INTEL PROCESSORS", "160 CORES PC with 320 THREADS"};
    SUBCASE("PUSH")
    {
        for(int i=0; i< 4; i++)
        {
            CHECK_NOTHROW(stack->PUSH(strs[i]));
            CHECK_EQ(stack->TOP(), strs[i]);
        }
    }
    // SUBCASE("POP")
    // {
        for(int i=0; i<4; i++)
        {
            CHECK_EQ(stack->POP(), strs[3 - i]);
        }
    // }
    
    clean_mem();
}




