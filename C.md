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
