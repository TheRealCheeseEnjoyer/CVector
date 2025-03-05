# CVector
A simple, cross-platform, thread unsafe dynamic array in C

## Implementation
This implementation uses a raw memory pool coupled with the size in bytes of the objects to store, granting the ability to store any type of data with a retrieval time complexity of O(1).

## Usage
Every function has the Vec_ Prefix.  
Default capacity and Resize multiplier are defined at the top of Vector.c and can be changed as needed

* Use Vec_Init to create a new vector with default capacity, or Vec_InitC for a custom initial capacity.
* Vec_Resize trims away unused memory
* Vec_Append appends an item to the end of the vector, resizes if needed and returns the location inside the memory pool, or NULL if insertion fails. (NOTE: this creates a SHALLOW COPY of the item using memcpy). If my calculations are correct, it should be O(1) time normally, and O(n) time if a reallocation occurs  
* Vec_Get returns a pointer to the object into the memory pool in O(1), NULL if the index is out of range
* Vec_Remove deletes the item in position in O(n) time (depending on the index)
* Vec_Clear clears the vector in O(1) time
* Vec_Size returns the size of the vector
* Vec_Capacity returns the capacity of the vector
* Vec_Free frees the vector
