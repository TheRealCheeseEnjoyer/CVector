#ifndef VECTOR_H
#define VECTOR_H
#include <stddef.h>

typedef struct vector_t* Vector;

Vector Vector_Init(size_t typeSize);
Vector Vector_InitC(size_t typeSize, size_t capacity);

void Vector_Resize(Vector v);
void* Vector_Append(Vector v, void* item);
void* Vector_Get(Vector v, size_t index);
void Vector_Remove(Vector v, size_t index);
void Vector_Clear(Vector v);

size_t Vector_Size(Vector v);
size_t Vector_Capacity(Vector v);

void Vector_Free(Vector v);

#endif
