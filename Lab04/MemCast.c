#include <stdio.h>

int main() {
	int i;
	int four_ints[4];
	char* four_c;

	for(i = 0; i < 4; i++)
        four_ints[i] = 2;

	printf("%x\n", four_ints[0]);
	
    four_c = (char*)four_ints;

	for(i = 0; i < 4; i++)
        four_c[i] = 'A' + i; // ASCII value of 'A' is 65 or 0x41 in Hex.
    
    // Add your code for the exercises here:
	printf("%x\n", four_ints[0]);
	printf("%x\n", four_ints[1]);

	printf("%p\n", &four_ints[0]);
	printf("%p\n", &four_c[0]);

	for(int i = 0; i < 4; i++)
	{
		printf("%x at %x\n", four_ints[i], &four_ints[i]);
	}

	// 44434241 at 837993b0
	// 2 at 837993b4
	// 2 at 837993b8
	// 2 at 837993bc

	for(int i = 0; i < 4; i++)
	{
		printf("%x at %x\n", four_c[i], &four_c[i]);
	}

	// 41 at 837993b0
	// 42 at 837993b1
	// 43 at 837993b2
	// 44 at 837993b3
	
	return 0;
}