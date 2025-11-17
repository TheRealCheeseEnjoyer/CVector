#include "Vector.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFAULT_CAPACITY 16
#define DEFAULT_MULTIPLIER 2

typedef struct {
    size_t itemSize;
    size_t size;
    size_t capacity;
    size_t padding; // pad structure to a multiple of 16 bytes
} head;

void* vec_init(size_t itemSize) {
    return vec_init_cap(itemSize, DEFAULT_CAPACITY);
}

void* vec_init_cap(size_t itemSize, size_t capacity) {
    head* memory = malloc(sizeof(head) + itemSize * capacity);
    if (memory == NULL) {
        return NULL;
    }

    memory->itemSize = itemSize;
    memory->size = 0;
    memory->capacity = DEFAULT_CAPACITY;
    return memory + 1;
}

int vec_append(void* vec, void* item) {
    void** v = vec;
    head* h = *v - sizeof(head);
    if (h->size + 1 > h->capacity) {
        size_t newCapacity = h->capacity * DEFAULT_MULTIPLIER;
        head* newMemory = realloc(h, sizeof(head) + newCapacity * h->itemSize);
        if (newMemory == NULL) {
            printf("vec_append: realloc failed\n");
            return 0;
        }
        h = newMemory;
        h->capacity = newCapacity;
        *v = h + 1;
    }
    memcpy(*v + h->itemSize * h->size, item, h->itemSize);
    h->size += 1;
    return 1;
}

int vec_append_empty(void* vec) {
    void** v = vec;
    head* h = *v - sizeof(head);
    if (h->size + 1 > h->capacity) {
        size_t newCapacity = h->capacity * DEFAULT_MULTIPLIER;
        head* newMemory = realloc(h, sizeof(head) + newCapacity * h->itemSize);
        if (newMemory == NULL) {
            printf("vec_append: realloc failed\n");
            return 0;
        }
        h = newMemory;
        h->capacity = newCapacity;
        *v = h + 1;
    }
    memset(*v + h->itemSize * h->size, 0, h->itemSize);
    h->size += 1;
    return 1;
}

void vec_reserve(void* vec, size_t capacity) {
    void** v = vec;
    head* h = vec - sizeof(head);
    size_t newCapacity = capacity;
    while (capacity > h->capacity) {
        newCapacity *= DEFAULT_MULTIPLIER;
    }
    head* newMemory = realloc(h, sizeof(head) + newCapacity * h->itemSize);
    if (newMemory == NULL) {
        printf("vec_reserve: realloc failed\n");
        return;
    }
    h = newMemory;
    h->capacity = newCapacity;
    *v = h + 1;
}

int vec_insert(void* vec, void* item, size_t index) {

    void** v = vec;
    head* h = *v - sizeof(head);
    if (index > h->capacity) {
        vec_reserve(*v, index);
    }
    if (h->size + 1 > h->capacity) {
        size_t newCapacity = h->capacity * DEFAULT_MULTIPLIER;
        head* newMemory = realloc(h, sizeof(head) + newCapacity * h->itemSize);
        if (newMemory == NULL) {
            printf("vec_append: realloc failed\n");
            return 0;
        }
        h = newMemory;
        h->capacity = newCapacity;
        *v = h + 1;
    }
    memmove(*v + h->itemSize * (index + 1), *v + h->itemSize * index, h->itemSize * (h->size - index));
    memcpy(*v + h->itemSize * index, item, h->itemSize);
    h->size += 1;
}

size_t vec_capacity(void *vec) {
    if (vec == NULL)
        return 0;
    head* h = vec - sizeof(head);
    return h->capacity;
}

size_t vec_size(void *vec) {
    if (vec == NULL)
        return 0;
    head* h = vec - sizeof(head);
    return h->size;
}

void vec_clear(void *vec) {
    if (vec == NULL)
        return;
    head* h = vec - sizeof(head);
    h->size = 0;
}

void vec_free(void* vec) {
    if (vec == NULL)
        return;
    head* h = vec - sizeof(head);
    free(h);
}
