
#include "heap_funcs.hpp"
#include <signal.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#define MB(x) ((size_t) (x) << 20)
#define BLOCK_SIZE sizeof(Block)

int fd = 0;
bool allocated_heap = false;
// The last block that was added to the list.
Block * head_block = nullptr;
// pointer to the start of the mmap location.
void * start_map = nullptr;
// pointer to where the cursor is currently pointing at in the mapped memory
char * current_addr = nullptr;
// a lock to the file descriptor.
struct flock fl;
struct flock check_fl;
int get_mapped_fd()
{
    if(fd != 0)
    {
        return fd;
    }
    throw("didn't map any memory yet");
}

void map_memory()
{
    if(allocated_heap)
    {
        throw("Cannot map more memory.");
    }
    fd = open("file.txt", O_CREAT | O_RDWR);
    if(ftruncate(fd, MB(10)) == -1)
    {
        perror("ftruncate");
        throw("cannot ftruncate");
    }
    start_map = mmap(NULL, MB(10), PROT_READ | PROT_WRITE, MAP_SHARED, fd , 0);
    current_addr = (char *)start_map;
    allocated_heap = true;
}


/**
 * @brief check if we already gave 10 mb of memory
 *  if not then map memory and initialize the addressed necessary.
 * 
 */
void check_mapped_memory()
{
    if(!allocated_heap)
    {
        throw("cannot use _malloc without mapping memory.");
    }
}

Block * find_free_block(size_t size)
{
    if(!head_block)
    {
        head_block = (Block *) current_addr;
        (head_block)->free = false;
        (head_block)->next = nullptr;
        (head_block)->size = size;
        current_addr += BLOCK_SIZE;
        current_addr += size;
        // printf("%p\n", (head_block));
        // printf("%p\n", (head_block)->next);
        return head_block + 1;
    }
    Block * prev_block = head_block;
    Block * current_block = head_block;
    while(current_block)
    {
        // printf("%p\n", current_block);
        // printf("%p\n", (current_block)->next);
        if( ((current_block)->size >= size) && ((current_block)->free == true))
        {
            (current_block)->free = false;
            return ((current_block) + 1);
        }
        prev_block = current_block;
        (current_block) = (current_block) -> next;
    }
    // not found good block of memory to re-use
    // allocate new memory
    current_addr = ((char *)prev_block) + prev_block->size + BLOCK_SIZE;
    Block * b = (Block *) current_addr;
    (b)->free = false;
    (b)->next = nullptr;
    (b)->size = size;
    prev_block->next = b;
    current_addr += BLOCK_SIZE;
    current_addr += size;
    return (b + 1);
}

Block * find_block_in(void * addr)
{
    Block * temp = head_block;
    while(temp)
    {
        if( (temp + 1) == addr)
        {
            return temp;
        }
        temp = (temp)->next;
    }
    return nullptr;
}
void * _malloc(size_t size)
{  
    check_mapped_memory();
    Block * free_block = find_free_block(size);
    return free_block;
}
void _free(void * addr)
{
    check_mapped_memory();
    Block * block = find_block_in(addr);
    if(block == nullptr)
    {
        perror("Cannot free unallocated memory.");
        throw("Cannot free unallocated memory");
    }
    if(block->free == true)
    {
        throw("Cannot free already freed memory.");
    }
    block->free = true;
}

void clean_mem()
{
    munmap(start_map, MB(10));
    close(fd);
    unlink("file.txt");
}

int num_bytes_untill_address(Block * addr)
{
    char * s = (char *) start_map;
    char * end = (char *) addr;
    int bytes_count = end - s;
    if(bytes_count < 0)
    {
        throw("cannot reach addr, it's not inside the mapped space of memory specified.");
    }
    return bytes_count;

}

bool lock_block_in_mappedmem(void * addr)
{
    // Block * block = ((Block *)addr) - 1;
    // int bytes = num_bytes_untill_address(block);
    fl.l_whence = SEEK_SET;
    fl.l_type = F_WRLCK;
    fl.l_len = 0;
    fl.l_start = 0;
    // this call should lock and wait if another process acquired the lock already.
    if(fcntl(fd, F_SETLKW, &fl) == -1)
    {
        // cannot lock for some reason.
        return false;
    }
    return true;
    
}

bool unlock_block_in_mappedmem(void * addr)
{
    // Block * block = ((Block *)addr) - 1;
    // int bytes = num_bytes_untill_address(block);
    fl.l_whence = SEEK_SET;
    fl.l_type = F_UNLCK;
    fl.l_len = 0;
    fl.l_start = 0;    
    if(fcntl(fd, F_SETLKW, &fl) == -1)
    {
        return false;
    }
    return true;
}














