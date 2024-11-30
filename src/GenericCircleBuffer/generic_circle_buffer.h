#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // For memcpy

typedef struct {
    void* buffer;         // Pointer to the data buffer
    size_t element_size;  // Size of each element in bytes
    size_t capacity;      // Max number of elements the buffer
    size_t mask;          // Size of mask for using and operator instead of modulus
    size_t head;          // Index of the write position
    size_t tail;          // Index of the read position
    bool is_full;         // Flag to indicate if the buffer is full
} GenericCircleBuffer;

// Function declarations
bool gb_init(GenericCircleBuffer* gb, size_t element_size, size_t capacity);
void gb_free(GenericCircleBuffer* gb);
bool gb_push(GenericCircleBuffer* gb, const void* data);
bool gb_pop(GenericCircleBuffer* gb, void* data);
bool gb_is_empty(const GenericCircleBuffer* gb);
bool gb_is_full(const GenericCircleBuffer* gb);
