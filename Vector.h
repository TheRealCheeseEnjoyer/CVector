#ifndef VECTOR_H
#define VECTOR_H
#include <stddef.h>

typedef struct vector_t* Vector;

Vector Vec_Init(size_t typeSize);
Vector Vec_InitC(size_t typeSize, size_t capacity);

void Vec_Resize(Vector v);
void* Vec_Append(Vector v, void* item);
void* Vec_Get(Vector v, size_t index);
void Vec_Remove(Vector v, size_t index);
void Vec_Clear(Vector v);

size_t Vec_Size(Vector v);
size_t Vec_Capacity(Vector v);

void Vec_Free(Vector v);

#endif
