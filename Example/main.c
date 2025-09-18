#include <stdio.h>
#include "Vector.h"

int main() {
    char* vector = vec_init(sizeof(char)); // Create vector
    char input = 0;
    do {
        scanf("%c", &input);
        vec_append(&vector, &input); // Append to vector
    } while(input != '\n');
    char end = 0;
    vec_append(&vector, &end);

    printf("input: %s", vector);

    vec_free(vector); // Free vector
}
