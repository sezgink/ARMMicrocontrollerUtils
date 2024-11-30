#pragma once
#include <stdlib.h>

// Struct for linked list node, holding next available memory
typedef struct MemoryBlock {
    struct MemoryBlock* next;
} MemoryBlock;

// Memory pool structure
typedef struct {
    size_t block_size;
    size_t block_count;
    void* memory;        // Memory begin location of pool
    MemoryBlock* block_list; // Available blocks list
} MemoryPool;

// Methods
void init_memory_pool(MemoryPool* memPool, size_t block_size, size_t block_count);
void* allocate_from_pool(MemoryPool* memPool);
int release_to_pool(MemoryPool* memPool, void* ptr);
void destroy_memory_pool(MemoryPool* memPool);
