#include <stdio.h>

typedef struct Block
{
    // the size of the actual block in memory
    size_t size;
    // true - the block is free, false the block isn't free
    bool free;
    // the next block in the list.
    Block * next;

}Block;

/**
 * @brief finds the given block inside the linked list of the allocated memory
 * 
 * @param addr 
 * @return Block* 
 */
Block * find_block_in(void * addr);
/**
 * @brief finds a free block with enough size inside the linked list and returns it
 * if not found, then allocated block memory and set it's size, free, next values accordingly
 * next will be the head, free will be 0, and size will be size.
 * 
 * @param size 
 * @return Block* 
 */

Block * find_free_block(size_t size);



/**
 * @brief map size bytes into memory that could be share between child processes
 * 
 * @param size 
 * @return void* 
 */
void * _malloc(size_t size);
/**
 * @brief free currently used block for use
 * 
 * @param address 
 */
void _free(void * address);

/**
 * @brief unmaps the memory allocated at the first time and closes the file descriptor opened.
 * 
 */
void clean_mem();

/**
 * @brief Maps 10 mb of memory
 * The user must use this before using any operation including _malloc and _free.
 * 
 */
void map_memory();
/**
 * @brief throws exception if the memory wasn't mapped.
 * 
 */
void check_mapped_memory();
/**
 * @brief Get the mapped fd object
 * 
 * @return int 
 */
int get_mapped_fd();

/**
 * @brief locks the mapped memory given by addr in the file descriptor created.
 * 
 * @param addr - the address of the desired block to lock.
 */
bool lock_block_in_mappedmem(void * addr);
/**
 * @brief unlocks the mapped memory given by addr in the file descriptor created.
 * 
 * @param addr - the address of the desired block to unlock.
 */
bool unlock_block_in_mappedmem(void * addr);
