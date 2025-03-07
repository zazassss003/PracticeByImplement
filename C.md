What’s the output of the following program?
int main(void)
{
    	unsigned int org = 0x128a, mask = 0x30, val = 0x70;
    	unsigned int new = 0;
    	new = org & ~mask;
    	new |= val & mask;
    	printf("0x%x\n", new);
    	return 0;
}

org   = 0001 0010 1000 1010
mask  = 0000 0000 0011 0000
val   = 0000 0000 0111 0000 
~mask = 1111 1111 1100 1111
new   = 0001 0010 1000 1010

***

What’s the output of the following program running on 64-bit architecture platform?
typedef struct {
    char a;
    double b;
} _A;
#pragma pack(push)
#pragma pack(1)
typedef struct {
    char a;
    double b;
} _B;
#pragma pack(pop)
int main()
{
    printf("%d%d", sizeof(_A), sizeof(_B));
    return 0;
}

Concept : compiler alignment

char   = 1 byte
double = 8 byte

char must add 7 bytes to align double's 8 bytes
so sizeof(_A) = 16

and then, "#pragma pack(push)" disable alignment

so sizeof(_B) = 9

Ans: 169

***

What’s the output of the following program?
int main ()
{
const char str1[] = {'1','2','3','\0','4','5','6'};
char str2[16] = {0};
char str3[16] = {0};
strcpy(str2, str1);
memcpy(str3, str1, sizeof(str3));
printf("%s\n", str2);
printf("%c\n", str3[5]);
return 0;
}

Concept : strcpy copy string until '\0', memcpy cpoy all bytes from memory (i.e. whole string)

str2 = {'1', '2', '3', 0...0}
srt3 = {'1','2','3','\0','4','5','6', 0...0}

Ans: 123, 5

***

What’s the output of the following program?
int main ()
{
char str[10]="12345!";
int a = strlen(str); 
int b = sizeof(str);
printf("%d\n",a);
printf("%d\n",b);
return 0;
}

see size_of_datatype for detail

Ans: 6, 10

***

What’s the output of the following program?
int main ()
{
int a[]={1,2,3,4,5,6};
int *p = a; 
int i;
*(p++) += 10; 
*(++p) += 20; 
for(i = 0; i < 6; i ++)
printf("%d", a[i]);
return 0;
}

*(p++) += 10 -> *p += 10 then move to next position
*(++p) += 20 -> *p move to next postion and += 20

a = {11, 2, 23, 4, 5, 6}

Ans: 11223456

***

What’s the output of the following program?
int main ()
{
int a[5] = {1, 2, 3, 4, 5};
int i;
for (i = 0; i < 5; i++)
if (((char)a[i]) == '5')
printf("%d\n", a[i]);
return 0;
}

Typecasting int to char only keeps the lowest byte (LSB)
ASCII value of '5' is 53, which doesn't match any char casted from a[i]

int 1    = 0x0001
(char) 1 = 0x01 = 1
'5'      = 53

Ans: no output (see typecast.c for result)

***