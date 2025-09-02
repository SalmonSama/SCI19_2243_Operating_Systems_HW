#include <stdio.h>

void passByValue(int argv) {
        argv += 1;
        printf("During pass-by-value: %d\n", argv);
}
void passByReference(int *argv) {
        *argv += 1;
        printf("During pass-by-reference: %d\n", *argv);
}
void swap(char *argv1, char *argv2) {
        char tmp = *argv1;
        *argv1 = *argv2;
        *argv2 = tmp;
}
void passByArray(int argv[]) {
        argv[0] = 999;
}
void main() {
        int num = 10;
        printf("Before pass-by-value: %d\n", num);
        passByValue(num);
        printf("After pass-by-value: %d\n\n", num);
        printf("Before pass-by-reference: %d\n", num);
        passByReference(&num);
        printf("After pass-by-reference: %d\n\n", num);
        char var1 = 'a'; char var2 = 'b';
        printf("Before swap: var1 = %c, var2 = %c\n", var1, var2);
        swap(&var1, &var2);
        printf("After swap: var1 = %c, var2 = %c\n\n", var1, var2);
        int arr[] = {777, 888};
        printf("Before pass:\t {%d, %d}\n", arr[0], arr[1]);
        passByArray(arr);
        printf("After pass:\t {%d, %d}\n", arr[0], arr[1]);
}
