#include <stdio.h>
#include <assert.h>
#include "generic_circle_buffer.h"

int main() {
    GenericCircleBuffer gb;
    int capacity = 8; // Must be a power of 2
    size_t element_size = sizeof(int);

    if (!gb_init(&gb, element_size, capacity)) {
        printf("Failed to initialize buffer.\n");
        assert(gb.buffer != NULL);
        return -1;
    }

    // Push elements into the buffer
    for (int i = 0; i < 10; i++) {
        if (gb_push(&gb, &i)) {
            printf("Pushed: %d\n", i);
            assert(i<capacity);
        } else {
            printf("Buffer is full, cannot push: %d\n", i);
            assert(i>=capacity);
        }
    }

    // Pop elements from the buffer
    int value;
    for(int i=0;i<=capacity;i++){

        if(gb_pop(&gb, &value)){
            printf("Popped: %d\n", value);
            assert(value==i);
            assert(i<capacity);

        } else {
            assert(i>=capacity); //If i exeeds capacity, pop should be return null
        }
        
    }

    // Clean up
    gb_free(&gb);
    

    return 0;
}