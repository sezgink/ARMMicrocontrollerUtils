#include "memory_pool.h"
#include <assert.h>
#include <stdio.h>

void test_init_memory_pool() {
    MemoryPool pool;
    size_t block_size = 16;
    size_t block_count = 10;

    init_memory_pool(&pool, block_size, block_count);

    // Assert the pool was initialized correctly
    assert(pool.block_size >= block_size); // Block size aligned
    assert(pool.block_count == block_count);
    assert(pool.memory != NULL);          // Memory allocated
    assert(pool.block_list != NULL);      // Block list initialized

    destroy_memory_pool(&pool);
    printf("test_init_memory_pool passed.\n");
}

void test_allocate_from_pool() {
    MemoryPool pool;
    size_t block_size = 16;
    size_t block_count = 10;

    init_memory_pool(&pool, block_size, block_count);

    void* block = allocate_from_pool(&pool);
    assert(block != NULL); // Allocation should be successful
    assert(pool.block_list != (MemoryBlock*)block); // Block list should update

    destroy_memory_pool(&pool);
    printf("test_allocate_from_pool passed.\n");
}

void test_release_to_pool() {
    MemoryPool pool;
    size_t block_size = 16;
    size_t block_count = 10;

    init_memory_pool(&pool, block_size, block_count);

    void* block = allocate_from_pool(&pool);
    assert(block != NULL);

    int release_status = release_to_pool(&pool, block);
    assert(release_status == 0);           // Release should succeed
    assert(pool.block_list == (MemoryBlock*)block); // Block list should update

    destroy_memory_pool(&pool);
    printf("test_release_to_pool passed.\n");
}

void test_pool_exhaustion() {
    MemoryPool pool;
    size_t block_size = 16;
    size_t block_count = 2;

    init_memory_pool(&pool, block_size, block_count);

    void* block1 = allocate_from_pool(&pool);
    void* block2 = allocate_from_pool(&pool);
    void* block3 = allocate_from_pool(&pool); // Should fail due to exhaustion

    assert(block1 != NULL);
    assert(block2 != NULL);
    assert(block3 == NULL); //Should be null due to null return from pool

    destroy_memory_pool(&pool);
    printf("test_pool_exhaustion passed.\n");
}

int main(){
    test_init_memory_pool();
    test_allocate_from_pool();
    test_release_to_pool();
    test_pool_exhaustion();
    return 0;
}