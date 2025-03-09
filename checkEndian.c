#include<stdio.h>

int is_little_endian() {
    unsigned int x = 1;
    // Cast the address of x to a byte pointer and check the first byte
    printf("%p\n", &x);
    printf("%p\n", (char*)&x);
    printf("%d\n", *(char*)&x);
    return (*(char*)&x == 1);
}

int main() {
    if (is_little_endian()) {
        printf("Machine is Little-Endian\n");
    } else {
        printf("Machine is Big-Endian\n");
    }
    return 0;
}

// x = 0x0001
// (char*)&x -> typecast x addr to a char pinter, since it only look for first byte
