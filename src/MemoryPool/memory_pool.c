#include "memory_pool.h"

void init_memory_pool(MemoryPool* memPool,size_t block_size,size_t block_count){

     // Align block size to the size of a pointer if it is smaller
    if (block_size < sizeof(void*)) {
        block_size = sizeof(void*);
    }
    
    memPool->block_size = block_size;
    memPool->block_count = block_count;
    memPool->memory = malloc(block_count*block_size);

    size_t i;
    memPool->block_list = (MemoryBlock*)memPool->memory;
    MemoryBlock* current= memPool->block_list;

    //Fill available blocks list inside of memory pool for memory efficiency
    for (i = 0; i < block_count-1; i++)
    {
        current->next = (MemoryBlock*)((char*)current+block_size);
        current = current->next;
    }
    current->next = NULL;
}
void* allocate_from_pool(MemoryPool* memPool){
    MemoryBlock* current = memPool->block_list;
    if(current==NULL){
        //Not any available block
        return NULL;
    }
    
    memPool->block_list = current->next; //Prepeare next available vlock for allocating
    return (void*)current;
}

int release_to_pool(MemoryPool* memPool,void* ptr){
    if(ptr==NULL){
        //Not avilable adress
        return 1; //Release error
    }

    MemoryBlock* current = (MemoryBlock*)ptr;
    current->next = memPool->block_list;
    memPool->block_list = current;
    
    return 0; //Release without problem
}

//Relase all memory hold by memory pool
void destroy_memory_pool(MemoryPool* memPool){
    free(memPool->memory);
    memPool->memory = NULL;
    memPool->block_list = NULL;
}

