
#include "heap_funcs.hpp"
#include <signal.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>

#define MB(x) ((size_t) (x) << 20)
#define BLOCK_SIZE sizeof(Block)

int fd = 0;
bool allocated_heap = false;
Block * head_block = nullptr;

/**
 * @brief check if we already gave 10 mb of memory
 *  if not then map memory and initialize the addressed necessary.
 * 
 */
void check_alocated_malloc()
{
    if(allocated_heap == false)
    {
        fd = open("file.txt", O_CREAT | O_RDWR);
        if(ftruncate(fd, MB(10)) == -1)
        {
            perror("ftruncate");
            raise(SIGABRT);
        }
        head_block = (Block *)mmap(0, MB(10), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        head_block->free = 1;
        head_block->next = nullptr;
        head_block->size = 0;
        allocated_heap = true;
    }
}
void check_alocated_free()
{
    if(allocated_heap == false)
    {
        perror("Cannot free memory, program didn't map any memory for it.");
        raise(SIGABRT);
    }
}
Block * find_free_block(size_t size)
{
    Block * current_block = head_block;
    while(current_block != nullptr)
    {
        if(current_block->size >= size && current_block->free == 1)
        {
            current_block->free = 0;
            return current_block + 1;
        }
        current_block = current_block->next;
    }
    if(head_block == nullptr)
    {
        return nullptr;
    }
    char * c = (char *) head_block;
    c += (BLOCK_SIZE + head_block->size);
    Block * addr = (Block *) c;
    addr->size = size;
    addr->free = 0;
    addr->next = head_block;
    head_block = addr;
    return addr;
}

Block * find_block_in(void * addr)
{
    Block * temp = head_block;
    while(temp != nullptr)
    {
        if( (temp + 1) == addr)
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}
void * malloc(size_t size)
{  
    check_alocated_malloc();
    Block * free_block = find_free_block(size);
    return free_block;
}
void free(void * addr)
{
    check_alocated_free();
    Block * block = find_block_in(addr);
    if(block == nullptr)
    {
        perror("Cannot free unallocated memory.");
        raise(SIGABRT);
    }
    else
    {
        block->free = 1;
    }
}


















