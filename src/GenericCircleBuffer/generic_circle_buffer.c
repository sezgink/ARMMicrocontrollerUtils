#include "generic_circle_buffer.h"


// Initialize the generic circle buffer
bool gb_init(GenericCircleBuffer* gb, size_t element_size, size_t capacity) {
    if((capacity & (capacity - 1)) != 0)
        return false; //Not capasity with power of 2, which problem for using AND operator for modulus

    gb->buffer = malloc(element_size * capacity); // Allocate buffer memory
    gb->element_size = element_size;
    gb->capacity = capacity;
    gb->mask = capacity-1;
    gb->head = 0;
    gb->tail = 0;
    gb->is_full = false;
    return true;
}

// Free the generic circle buffer memory
void gb_free(GenericCircleBuffer* gb) {
    if (!gb || !gb->buffer)
        return false; // Handle Null buffer
    free(gb->buffer);
    gb->buffer = NULL;
    gb->element_size = 0;
    gb->capacity = 0;
    gb->head = 0;
    gb->tail = 0;
    gb->is_full = false;
}

// Push data into the buffer
bool gb_push(GenericCircleBuffer* gb, const void* data) {
    if (gb->is_full) {
        return false; // Buffer is full
    }

    // Copy data into the buffer at the current head position
    memcpy((char*)gb->buffer + (gb->head * gb->element_size), data, gb->element_size);

    // Move head to the next position, use AND operator for faster modulus
    gb->head = (gb->head + 1) & gb->mask;

    // If the head catches up to the tail, the buffer is now full
    gb->is_full = (gb->head == gb->tail);

    return true;
}

// Pop data from the buffer
bool gb_pop(GenericCircleBuffer* gb, void* data) {
    if (gb_is_empty(gb)) {
        return false; // Buffer is empty
    }

    // Copy data from the buffer at the current tail position
    memcpy(data, (char*)gb->buffer + (gb->tail * gb->element_size), gb->element_size);

    // Move tail to the next position, use AND operator for faster modulus
    gb->tail = (gb->tail + 1) & gb->mask;

    // Buffer is no longer full
    gb->is_full = false;

    return true;
}

// Check if the buffer is empty
bool gb_is_empty(const GenericCircleBuffer* gb) {
    return (!gb->is_full && (gb->head == gb->tail));
}

// Check if the buffer is full
bool gb_is_full(const GenericCircleBuffer* gb) {
    return gb->is_full;
}
