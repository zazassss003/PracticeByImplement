#include<stdio.h>


int main(){
    printf("Size of char:         %lu bytes\n", sizeof(char));
    printf("Size of short:        %lu bytes\n", sizeof(short));
    printf("Size of int:          %lu bytes\n", sizeof(int));
    printf("Size of unsigned int: %lu bytes\n", sizeof(unsigned int));
    printf("Size of float:        %lu bytes\n", sizeof(float));
    printf("Size of long:         %lu bytes\n", sizeof(long));
    printf("Size of double:       %lu bytes\n", sizeof(double));
    printf("Size of pointer:      %lu bytes\n", sizeof(void *));
    return 0;
}

// pointer size depends on the system, if it's 32-bit then * is 4 bytes (4*8 = 32-bit)
// if it is 64-bit system then it is 8 bytes (8*8 = 64-bit), rest of datatype all the same.