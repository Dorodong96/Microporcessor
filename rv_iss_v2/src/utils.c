#include <stdio.h>
#include <stdint.h>

#include "utils.h"

uint32_t byte_to_word(uint8_t data[])
{
	uint32_t result = 0;

	result = data[0];
	result |= data[1] << 8; //input value (no matter for +=)
	result |= data[2] << 16;
	result |= data[3] << 24;
	
	return result;
}

void display_reg()
{
	printf("==========================Registers===========================\n");
	for (uint32_t index1 = 0; index1 < 8; index1++) {
		for (uint32_t index2 = 0; index2 < 4; index2++) {
			printf("X[%2d] = %6d  ", index1*4 + index2, x_reg[index1*4 + index2]);
		}
		printf("\n");
	}
	printf("==============================================================\n");
}

void display_memory(uint32_t start, uint32_t size)
{
	uint8_t mem_value = 0;

	printf("===========================Memory=============================\n");
	for (uint32_t index3 = 0; index3 < size; index3++) {
		mem_value = memory[start];
		printf("memory[%d] = %6d (0x%x) \n", start, mem_value, mem_value);
		start++;
	}
	printf("==============================================================\n");
		
}
