#include<stdio.h>

typedef struct
{
    char c;
    int i;
}structSize;

int main(){
    structSize s;
    printf("%lu", sizeof(s));
}
