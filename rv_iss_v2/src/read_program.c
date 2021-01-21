#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

extern uint8_t memory[1024]; // extern : 'memory' is declared in other file

uint32_t hex_to_decimal(char data[]);

int read_program(char* file)
{
	FILE	*fp;
	char	buf[128];
	char	address[9];
	char	program[9];
	uint32_t	prgr;
	uint32_t	addr;

	fp = fopen(file, "r");
	
	while (fgets(buf, 128, fp) != NULL) {
		if (strlen(buf) < 18)
			continue;

		printf("Program : %s", buf);
		
		strncpy(address, buf, 8);
		strncpy(program, buf+9, 8);
		
		addr = atoi(address); // ASCII to integer
		prgr = hex_to_decimal(program);
		
		memory[addr] = prgr & 0xff;       // put data by each 1Byte
		memory[addr+1] = prgr>>8 & 0xff;  // shift 1Byte & mask1
		memory[addr+2] = prgr>>16 & 0xff;
		memory[addr+3] = prgr>>24 & 0xff;

		//printf("Address : %s, Program : %s \n"
	}

	fclose(fp);

	return 0;
}

uint32_t hex_to_decimal(char data[])
{
	uint32_t	result = 0;
	
	for (int i=0; i<8; i++) {
		if (data[i] >= '0' && data[i] <= '9')
			result += (data[i] - '0');
		else if (data[i] >= 'A' && data[i] <= 'F')
			result += (10 + data[i] - 'A');
		else if (data[i] >= 'a' && data[i] <= 'f')
			result += (10 + data[i] - 'a');
		else
			printf("Error -  hex_to_decimal_ : Unknown hex code %c\n", data[i]);
		if (i < 7)
			result <<= 4; // result = result * 16;
	}
	return result;
}
