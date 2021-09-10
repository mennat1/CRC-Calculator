//My machine is Little Endian, i.e, reads the from right to left (LSB first).


#include <stdio.h>

void checkEndianness(){
	unsigned int i = 1;
	char *c = (char*)&i;
	if (*c)	
		printf("Little endian"); //First Byte is 1
	else
		printf("Big endian"); //First Byte is 0
}
