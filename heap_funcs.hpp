#include <stdio.h>

typedef struct Block
{
    // the size of the actual block in memory
    size_t size;
    // is the block is free to use or not
    bool free;
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
void * malloc(size_t size);
/**
 * @brief free currently used block for use
 * 
 * @param address 
 */
void free(void * address);






