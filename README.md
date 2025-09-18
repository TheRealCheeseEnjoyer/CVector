
# CVector
A simple dynamic array in C90

## Implementation

                    ⬇ pointer exposed to user
     |______________|______________________________________|
      header space      items space
      -size
      -capacity
      -item size
This allows to retrieve items like

    item = vec[10];
   instead of having a `vec_get` method


## Installation
1. Drop Vector.h and Vector.c in your project
2. ????
3. Profit

## Example usage

    #include <Vector.h>
    #include <stdio.h>
    
    typedef struct {
      int a;
    } test;

    
    int main() {
      test* vec = vec_init(sizeof(test));
      test item = {42};

      vec_append(&vec, &item);
      printf("%d\n", vec[0].a);
      
      vec_free(vec);
    }
## Documentation
Default capacity is 16, defined in Vector.c

void* vec_init(size_t itemSize):
   
+ itemSize: the size in bytes of the items

+ returns pointer to a vector of items 

void* vec_init_cap(size_t itemSize, size_t capacity): 

+ same as `vec_init()` but with custom initial capacity

int vec_append(void* vec, void* item):
  
+ vec: pointer to vector returned by `vec_init`

+ item: pointer to item to append

+ returns 1 on success and 0 on failure

WARNING: due to possible relocations the value of the pointer may change and any other pointer to that same memory may be pointing to invalid memory after an append.

        test* vec = vec_init(sizeof(text));
        test* vec1 = vec;
        while (vec_size(vec) < 100)
	        vec_append(&vec, &item);
        printf("%d\n", vec1[0].a); // vec1 may be pointing to invalid memory if a relocation occurred
size_t vec_capacity(void* vec):

+ returns the vector's capacity
  
size_t vec_size(void* vec):
+ returns the size of the vector
  
void vec_clear(void* vec):
+ clears a vector
  
+ NOTE: this does not release memory, it just sets the size to 0

void vec_free(void* vec):
+ frees the vector

