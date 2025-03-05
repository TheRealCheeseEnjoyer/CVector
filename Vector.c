#include "Vector.h"
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 16
#define RESIZE_MULTIPLIER 2

struct vector_t {
    void* data;
    size_t typeSize;

    size_t size;
    size_t capacity;
};

/// Initialize a vector with default capacity
/// @param typeSize The size in bytes of the object the vector holds
/// @return A handle to the vector
Vector Vec_Init(const size_t typeSize) {
    return Vec_InitC(typeSize, DEFAULT_CAPACITY);
}

/// Initialize a vector with custom capacity
/// @param typeSize The size in bytes of the object the vector holds
/// @param capacity Custom initial capacity
/// @return A handle to the vector
Vector Vec_InitC(const size_t typeSize, const size_t capacity) {
    Vector v = malloc(sizeof(struct vector_t));
    v->capacity = capacity;
    v->size = 0;
    v->typeSize = typeSize;
    v->data = malloc(typeSize * capacity);
    return v;
}

/// Resizes the vector to trim excess space
/// @param v Handle to a vector
void Vec_Resize(Vector v) {
    void* newMem = realloc(v->data, v->size * v->typeSize);
    if (!newMem) return;
    v->data = newMem;
    v->capacity = v->size;
}

/// Appends a shallow copy (memcpy) of the object to the end of the vector
/// @param v A handle to the vector
/// @param item The item to copy into the vector
/// @return A pointer to the item's location
void* Vec_Append(Vector v, void* item) {
    if (v->size == v->capacity) {
        v->capacity *= RESIZE_MULTIPLIER;
        void* newData = realloc(v->data, v->capacity * v->typeSize);
        if (!newData) {
            return NULL;
        }
        v->data = newData;
    }

    void* newItemsPlace = v->data + v->size * v->typeSize;
    memcpy(newItemsPlace, item, v->typeSize);
    v->size++;
    return newItemsPlace;
}

/// Get an item from the vector
/// @param v A handle to the vector
/// @param index Index of the object to get
/// @return A pointer to the item's location, NULL if the index is out of bounds
void* Vec_Get(Vector v, const size_t index) {
    if (index >= v->size) {
        return NULL;
    }

    return v->data + index * v->typeSize;
}

/// Deletes an item from the vector
/// @param v A handle to the vector
/// @param index Index of the item to delete
void Vec_Remove(Vector v, size_t index) {
    void* target = Vec_Get(v, index);
    if (target == NULL) return;
    memmove(target, target + v->typeSize, (v->size - index - 1) * v->typeSize);
    v->size--;
}

/// Deletes all items from the vector
/// @param v Handle to a vector
void Vec_Clear(Vector v) {
    v->size = 0;
}

/// Get the size of the vector
/// @param v Handle to a vector
/// @return Size of the vector
size_t Vec_Size(Vector v) {
    return v->size;
}

/// Get the capacity of the vector
/// @param v Handle to a vector
/// @return Capacity of the vector
size_t Vec_Capacity(Vector v) {
    return v->capacity;
}

/// Frees the vector
/// @param v Handle to a vector
void Vec_Free(Vector v) {
    free(v->data);
    free(v);
}
