#include<stdio.h>

//What’s the output of the following program?
int main ()
{
    int a[5] = {1, 2, 3, 4, 5};
    int i;
    for (i = 0; i < 5; i++)
    if (((char)a[i]) == '5')
    printf("%d\n", a[i]);
    return 0;
}
