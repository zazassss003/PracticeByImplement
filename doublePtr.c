#include<stdio.h>

int main(){
    int x = 100;
    int* p = &x;
    //int* p1 = &p; //warning
    int** p2 = &p;
    printf("x address = %p\n", p);
    printf("p address = %p\n\n", p2);
    printf("p data = %p\n\n", *p2);
    printf("%d\n\n", **p2);
    // **p2 = *(*p2) = *(p) = x 


}