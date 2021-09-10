// gcc -Wall -Wextra -Werror -Wpedantic -g3 gettersAndSetters.c -o gettersAndSetters

#include "helpers.h"


// 0b10000000
// n = 0 -> data[0] & (1 << (8-(0+1)) -> data[(n/8)] & (1 << (8-((n%8)+1)))
// n = 1 -> data[0] & (1 << (8-(1+1))
// n = 2 -> data[0] & (1 << (8-(2+1)))
// n = 7 -> data[0] & (1 << (8-(7+1)))
// n = 8 -> data[1] & (1 << (8-(0+1)))

uint8_t ft_getbit(uint8_t *data, int n){
	// printf("%x\n", data[(n/8)]);

	uint8_t bit = data[(n/8)] & (1 << (8 - ((n % 8) + 1))) ? 1 : 0;

	return bit;
}


void ft_setbit(uint8_t *data, int n, uint8_t val){
	if(val){
		data[(n/8)] |= (1 << (8 - ((n % 8) + 1)));
	}else{
		data[(n/8)] &= (0 << (8 - ((n % 8) + 1)));
	}
}

void ft_togglebit(uint8_t *data , int n){
	data[(n/8)] ^= (1 << (8 - ((n % 8) + 1)));

}


void ft_cpybit(uint8_t *dst, uint8_t dst_start, uint8_t *src, uint8_t src_start, int n){
	// uint8_t mask = 0b10000000;
	uint8_t mask = 0x80;
	for(int i = 0; i < (n-1); i++){
		mask = (mask >> 1) | (0x80);
	}
	printf("mask = %x\n", mask);
	uint8_t copied_bits = (*src & (mask >> src_start));
	printf("copied_bits = %x\n", copied_bits);
	copied_bits = copied_bits >> (8 - n - src_start);
	printf("shifted copied_bits = %x\n", copied_bits);
	uint8_t masked_dst = copied_bits << (8 - dst_start - n);
	printf("masked_dst = %x\n", masked_dst);
	uint8_t dst_mask = ~(mask >> dst_start);
	printf("dst_mask = %x\n", dst_mask);
	*dst &= dst_mask;
	printf("dst = %x\n", *dst);
	*dst |= masked_dst;
	printf("dst after copying = %x\n", *dst);

}
