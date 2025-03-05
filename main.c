#include <stdio.h>
#include "Vector.h"

int main() {
    Vector vector = Vector_Init(sizeof(int)); // Create vector
    int input = 0;
    do {
        scanf("%d", &input);
        Vector_Append(vector, &input); // Append to vector
    } while(input != 0);

    for (int i = 0; i < Vector_Size(vector); i++) {
        int value = *(int*)Vector_Get(vector, i); // Get value from vector
        printf("%d ", value);
    }
    printf("\n");
    int size = Vector_Size(vector);
    for (int i = 0; i < size / 2; i++) {
        Vector_Remove(vector, 0); // Remove from vector
    }

    for (int i = 0; i < Vector_Size(vector); i++) {
        int value = *(int*)Vector_Get(vector, i);
        printf("%d ", value);
    }
    printf("\n");

    Vector_Free(vector); // Free vector
}
