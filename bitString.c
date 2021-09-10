// Compile: gcc -Wall -Wextra -Werror -Wpedantic -g3 bitString.c -o bitString

#include "helpers.h"


uint8_t *ft_16bit2string(uint16_t data1){
	uint16_t data = SHIFT_TO_BIG_ENDIAN_16_BIT(data1);
	uint8_t *bytes_ptr = (uint8_t *)malloc(sizeof(data));
	uint8_t *data_ptr = (uint8_t*)&data;
	for(int i = 0; i < (int)sizeof(data); i++){
		bytes_ptr[i] = data_ptr[i];
	}
	return bytes_ptr;
}
uint8_t *ft_32bit2string(uint32_t data1){
	uint32_t data = SHIFT_TO_BIG_ENDIAN_32_BIT(data1);
	uint8_t *bytes_ptr = (uint8_t *)malloc(sizeof(data));
	uint8_t *data_ptr = (uint8_t*)&data;
	for(int i = 0; i < (int)sizeof(data); i++){
		bytes_ptr[i] = data_ptr[i];
	}
	return bytes_ptr;

}
uint8_t *ft_64bit2string(uint64_t data1){
	uint64_t data = SHIFT_TO_BIG_ENDIAN_64_BIT(data1);
	uint8_t *bytes_ptr = (uint8_t *)malloc(sizeof(data));
	uint8_t *data_ptr = (uint8_t*)&data;
	for(int i = 0; i < (int)sizeof(data); i++){
		bytes_ptr[i] = data_ptr[i];
	}
	return bytes_ptr;
}
