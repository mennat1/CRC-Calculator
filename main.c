/*

$ make
$ ./main test.txt

*/


#include "bit.h"

int main(int argc,char* argv[]){

	if(argc > 1){

		char *test_file = argv[1];
		// printf("%s\n", test_file);
		FILE *fp;
		fp = fopen(test_file, "r");
		if (fp == NULL)
        	exit(EXIT_FAILURE);
		
		char line[60];
		char *line_ptr = NULL;
		uint8_t passed_test = 1;
		while((line_ptr = fgets (line, 60, fp))!= NULL){
			char *data_str = strtok(line_ptr," ");
			// printf ("data_str = %s\n",data_str);
			// uint16_t data = (uint16_t)strtol(data_str, NULL, 16);
			uint32_t data = (uint32_t)strtol(data_str, NULL, 16);
			printf("data = %x\n", data);


			char *poly_type_str = strtok(NULL, " ");
			// printf ("poly_type_str = %s\n",poly_type_str);
			uint8_t poly_type = (uint8_t)atoi(poly_type_str);
			printf("poly_type = %d\n", poly_type);

			char *crc_result_str = strtok(NULL, " ");
			// printf ("crc_result_str = %s\n",crc_result_str);
			uint32_t crc_result = (uint32_t)strtol(crc_result_str, NULL, 16);
			// crc_result = SHIFT_TO_BIG_ENDIAN_32_BIT(crc_result);
			printf("Correct crc_msg = %x\n\n", crc_result);
			uint8_t *crc_result_ptr = (uint8_t *)&crc_result;

			// data = SHIFT_TO_BIG_ENDIAN_16_BIT(data);
			data = SHIFT_TO_BIG_ENDIAN_32_BIT(data);
			uint8_t *ptr = (uint8_t *)&data;
			uint8_t *crc_msg = NULL;
			int msg_byte_len = sizeof(data);
			crc_gen(ptr, msg_byte_len, &crc_msg, poly_type);
			// for(int i=0; i<(int)sizeof(data); i++){
			// 	printf("%x\n", ptr[i]);
			// }

			uint8_t crc_nBytes_arr[4] = {POLY0_CRC_nBYTES, POLY1_CRC_nBYTES, POLY2_CRC_nBYTES, POLY3_CRC_nBYTES};
			uint8_t crc_nBytes = crc_nBytes_arr[poly_type];
			// printf("CRC BYTES:\n");
			uint8_t equal = 1;
			for(uint8_t i = 0; i < crc_nBytes; i++){
				// printf("Calculated crc_msg byte %d = %x\n", i, crc_msg[i]);
				// printf("Correct crc_msg byte %d = %x\n", i, crc_result_ptr[crc_nBytes-1-i]);
				if(crc_msg[i] != crc_result_ptr[crc_nBytes-1-i]){
					equal = 0;
					passed_test = 0;
				}
			}
			printf("\nPassed this test = %s\n", equal? "true":"false");
			printf("\n****************************\n\n");

		}
		printf("Passed ALL Tests: %s\n", passed_test? "true":"false");
		
		
  		fclose(fp);
	}else{
		printf("Please insert path to test file");
	}


	return 0;

}