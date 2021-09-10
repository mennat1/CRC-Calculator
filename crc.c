// gcc -Wall -Wextra -Werror -Wpedantic -g3 crc.c -o crc


#include "helpers.h"

/*
poly_tpe:
0 -> 24 bit polynomial type A: D24 + D23 + D18 + D17 + D14 + D11 + D10 + D7 + D6 + D5 + D4 + D3 + D + 1
1 -> 24 bit polynomial type B:  D24 + D23 + D6 + D5 + D + 1
2 -> 16 bit polynomial:  D16 + D12 + D5 + 1
3 -> 8 bit polynomial: D8 + D7 + D4 + D3 + D + 1

0 -> 25 bits: 0b 1 10000110 01001100 11111011 = 0x 1 86 4C FB
1 -> 25 bits: 0b 1 10000000 00000000 01100011 = 0x 1 80 00 63
2 -> 17 bits: 0b 1 00010000 00100001 = 0x 1 10 21
3 -> 9 bits:  0b 1 10011011 = 0x 1 9B  

is_alloc:
0b100 - variable “msg” is already allocated and output data should be stored in that variable
0b010 - variable “crc_msg” is already allocated and output data should be stored in that variable
0b001 - variable “crc_msg” is not allocated and output data should be stored in that variable

NOTE - value is “0b100” “msg” variable will be allocated to length of data bit + parity bits,
but the “byte_len” variable will be equal to length of data bits


*/
/*
The modulo-2 division process is defined as follows:

- Call the uppermost c+1 bits of the message the remainder.
- Beginning with the most significant bit in the original message and for each bit 
  position that follows, look at the c+1 bit remainder:
	+ If the most significant bit of the remainder is a one, the divisor is said 
	  to divide into it. If that happens (just as in any other long division) 
	  it is necessary to indicate a successful division in the appropriate bit position
	  in the quotient and to compute the new remainder. 
	  In the case of modulo-2 binary division, we simply:
		1) Set the appropriate bit in the quotient to a one, and
		2) XOR the remainder with the divisor and store the result back into
		   the remainder
	
	+ Otherwise (if the first bit is not a one):
		1) Set the appropriate bit in the quotient to a zero, and
		2) XOR the remainder with zero (no effect)
	
	+ Left-shift the remainder, shifting in the next bit of the message. The bit that's shifted out will always be a zero, so no information is lost.
- The final value of the remainder is the CRC of the given message.

NB:
- The most significant bit of any generator polynomial is always a one.
- The uppermost bit of the XOR result is always zero and promptly shifted out of
  the remainder.
So -> Since we already have the information in the uppermost bit and we don't need it 
for the XOR, the polynomial can also be stored in an 8-, 16-, or 32-bit register. 
We can simply discard the most significant bit. The register size that we use will 
always be equal to the width of the CRC we're calculating.

*/




void crc_gen(uint8_t *msg, int msg_byte_len, uint8_t **crc_msg, uint8_t poly_type){
	uint32_t polynomial = 0;
	uint32_t crc_register = 0;
	uint8_t width_in_bits = 0;
	uint32_t mask = 0;
	uint8_t starting_byte = 0;

	// Try using a static array
	uint32_t polynomial_arr[4] = {POLY0, POLY1, POLY2, POLY3};
	uint8_t width_in_bits_arr[4] = {8*POLY0_CRC_nBYTES, 8*POLY1_CRC_nBYTES, 8*POLY2_CRC_nBYTES, 8*POLY3_CRC_nBYTES};
	uint32_t mask_arr[4] = {0x00FFFFFF, 0x00FFFFFF, 0x0000FFFF, 0x000000FF};
	uint8_t starting_byte_arr[4] = {1, 1, 2, 3};

	polynomial = polynomial_arr[poly_type];
	width_in_bits = width_in_bits_arr[poly_type];
	mask = mask_arr[poly_type];
	starting_byte = starting_byte_arr[poly_type];
	
	printf("Used Polynomial Genarator = 0x%x\n", polynomial);
	uint32_t msb = (1 << (width_in_bits - 1));
	uint8_t crc_nBytes = (width_in_bits/8);
	for(int byte = 0; byte < msg_byte_len; byte++){
		// printf("byte = %d\n", byte);
		// printf("crc_register = %x\n", crc_register);
		crc_register ^= (msg[byte] << (width_in_bits - 8));
		for(int bit = 0; bit < 8; bit++){
			// printf("bit = %d\n", bit);
			if(crc_register & msb){
				// printf("XORING\n");
				crc_register = ((crc_register << 1) ^ polynomial);
				// printf("crc_register = %x\n", crc_register);
			}else{
				crc_register = crc_register << 1;
				// printf("crc_register = %x\n", crc_register);
			}
		}
	}
	// printf("crc_register = %x\n", crc_register);
	crc_register &= mask;
	printf("Calculated crc_msg = %x\n\n", crc_register);
	crc_register = SHIFT_TO_BIG_ENDIAN_32_BIT(crc_register);
	// printf("crc_register = %x\n", crc_register);
	uint8_t *ptr = (uint8_t *)&crc_register;
	*crc_msg = (uint8_t *)malloc(crc_nBytes *sizeof(uint8_t));
	uint8_t j=0;
	for(uint8_t i = starting_byte; i<(starting_byte+crc_nBytes); i++, j++){
		*(*crc_msg + j) = ptr[i];
		// printf("+++++%x\n", *(*crc_msg + j) );
	}
	*(*crc_msg + j) = -1;
	// j = 0;


}
