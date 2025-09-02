#include <stdio.h>

void runner() {
        int num = 10;
        int *ptr; ptr = &num;
        int **dPtr; dPtr = &ptr;
        printf("Value at num = %d\n", num);
        printf("Address of num = %p\n\n", &num);
        printf("Value at ptr = %p\n", ptr);
        printf("Address of ptr = %p\n", &ptr);
        printf("Value at *ptr = %d\n\n", *ptr);
        printf("Value at dPtr = %p\n", dPtr);
        printf("Address of dPtr = %p\n", &dPtr);
        printf("Value at **dPtr = %d\n\n", **dPtr);
}

void main() {
        runner();
}
