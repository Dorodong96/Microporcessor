#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "rv_format.h"
#include "utils.h"

uint32_t	x_reg[32];
uint8_t		memory[4096];
uint32_t 	pc = 0;
uint32_t 	clock = 0;
uint32_t	m_start = 0;
uint32_t	s_size = 0;

int read_program(char*); //prototype of read_program.c

int main(int argc, char* argv[])
{
	char *program_file;
	rv_format a_instr;

	if (argc < 2) {
		printf("Usage : rv_iss [file name]\n");
		return 1; 
		//return 0 : main function close normally
		//return 1 : main function close with error
	} else {
		int ret;

		program_file = argv[1];
		printf("Program file name: %s\n", program_file);

		ret = read_program(program_file);

		if (ret != 0) {
			printf("Error : read program\n");
			return 1;
		}
	}
	
	//printf("memory[0] = 0x%x\n", byte_to_word(memory));
	//printf("memory[0] = 0x%x\n", byte_to_word(memory+4));
	printf("Start RISC-V Simulator...\n");
	
	while(1) {
		a_instr.instr = *(uint32_t*)(memory+pc);
		//an instruction, memory+pc:pointer(with 4Bytes)

		uint32_t opcode = a_instr.r.opcode;
		
		// R-Format
		if (opcode == 0x33) { 
			uint32_t rd = a_instr.r.rd;
			uint32_t funct3 = a_instr.r.funct3;
			uint32_t rs1 = a_instr.r.rs1;
			uint32_t rs2 = a_instr.r.rs2;
			uint32_t funct7 = a_instr.r.funct7;

			if (funct3 == 0x0) {
				if (funct7 == 0x0) { // add
					printf("PC:%6d add x%d, x%d, x%d\n", pc, rd, rs1, rs2);
					x_reg[rd] = x_reg[rs1] + x_reg[rs2];

				} else if (funct7 == 0x20) { // sub
					printf("PC:%6d sub x%d, x%d, x%d\n", pc, rd, rs1, rs2);
					x_reg[rd] = x_reg[rs1] - x_reg[rs2];

				} else {
					printf("Error : Unknown funct7 = 0x%x\n", funct7);
					exit(1);
				}
			} else if (funct3 == 0x1) { // sll
				printf("PC:%6d sll x%d, x%d, x%d\n", pc, rd, rs1, rs2);
				x_reg[rd] = x_reg[rs1] << x_reg[rs2];

			} else if (funct3 == 0x2) { // slt
				printf("PC:%6d slt x%d, x%d, x%d\n", pc, rd, rs1, rs2);
				x_reg[rd] = (x_reg[rs1] < x_reg[rs2]) ? 1 : 0;

			} else if (funct3 == 0x3) { // sltu
				printf("PC:%6d sltu x%d, x%d, x%d\n", pc, rd, rs1, rs2);
				x_reg[rd] = ((int32_t)x_reg[rs1] < (int32_t)x_reg[rs2]) ? 1 : 0;

			} else if (funct3 == 0x4) { // xor
				printf("PC:%6d xor x%d, x%d, x%d\n", pc, rd, rs1, rs2);
				x_reg[rd] = x_reg[rs1] ^ x_reg[rs2];

			} else if (funct3 == 0x5) { 
				if (funct7 == 0x0) { // srl
					printf("PC:%6d srl x%d, x%d, x%d\n", pc, rd, rs1, rs2);
					x_reg[rd] = x_reg[rs1] >> x_reg[rs2];

				} else if (funct7 == 0x20) { // sra
					printf("PC:%6d sra x%d, x%d, x%d\n", pc, rd, rs1, rs2);
					x_reg[rd] = (int32_t)x_reg[rs1] >> (int32_t)x_reg[rs2];

				} else {
					printf("Error : Unknown funct7 = 0x%x\n", funct7);
					exit(1);
				}

			} else if (funct3 == 0x6) { // or
				printf("PC:%6d or x%d, x%d, x%d\n", pc, rd, rs1, rs2);
				x_reg[rd] = x_reg[rs1] | x_reg[rs2];

			} else if (funct3 == 0x7) { // and
				printf("PC:%6d and x%d, x%d, x%d\n", pc, rd, rs1, rs2);
				x_reg[rd] = x_reg[rs1] & x_reg[rs2];

			} else {
				printf("Unknown Instruction\n");
			}
		
		// I-Fromat
		} else if (opcode == 0x03) { // lw, lh, lb...
			uint32_t funct3 = a_instr.i.funct3;
			uint32_t rd = a_instr.i.rd;
			uint32_t rs1 = a_instr.i.rs1;
			int32_t imm = a_instr.i.imm;
			
			if (funct3 == 0x0) { // lb
				x_reg[rd] = memory[x_reg[rs1] + imm];
				
				if ((x_reg[rd] >> 7) == 1) // Check MSB for sign extension
					x_reg[rd] |= 0xffffff00;
				printf("PC:%6d lb x%d, %d(x%d)\n", pc, rd, imm, rs1);

			} else if (funct3 == 0x1) { // lh 
				x_reg[rd] = memory[x_reg[rs1] + imm];
				x_reg[rd] |= memory[x_reg[rs1] + imm + 1] << 8;
				
				if ((x_reg[rd] >> 15) == 1)
					x_reg[rd] |= 0xffff0000;
				printf("PC:%6d lh x%d, %d(x%d)\n", pc, rd, imm, rs1);

			} else if (funct3 == 0x2) { // lw
				x_reg[rd] = memory[x_reg[rs1] + imm];
				x_reg[rd] |= memory[x_reg[rs1] + imm + 1] << 8;
				x_reg[rd] |= memory[x_reg[rs1] + imm + 2] << 16;
				x_reg[rd] |= memory[x_reg[rs1] + imm + 3] << 24;
				printf("PC:%6d lw x%d, %d(x%d)\n", pc, rd, imm, rs1);

			} else if (funct3 == 0x3) { // ld
				printf("This is 64-bit instruction : ld\n");

			} else if (funct3 == 0x4) { // lbu
				x_reg[rd] = memory[x_reg[rs1] + imm];
				printf("PC:%6d lbu x%d, %d(x%d)\n", pc, rd, imm, rs1);

			} else if (funct3 == 0x5) { // lhu
				x_reg[rd] = memory[x_reg[rs1] + imm];
				x_reg[rd] |= memory[x_reg[rs1] + imm + 3] << 24;
				printf("PC:%6d lhu x%d, %d(x%d)\n", pc, rd, imm, rs1);

			} else if (funct3 == 0x6) { // lwu
				
				printf("This is 64-bit instruction : lwu\n");
		/*		
				x_reg[rd] = memory[x_reg[rs1] + imm];
				x_reg[rd] |= memory[x_reg[rs1] + imm + 1] << 8;
				x_reg[rd] |= memory[x_reg[rs1] + imm + 2] << 16;
				x_reg[rd] |= memory[x_reg[rs1] + imm + 3] << 24;
				printf("PC:%6d lwu x%d, %d(x%d)\n", pc, rd, imm, rs1);
		 */
			} else {
				printf("Unknown instruction (Load)\n");
			}


		} else if (opcode == 0x13) { // addi, slli, slti...
			uint32_t funct3 = a_instr.i.funct3;
			uint32_t rd = a_instr.i.rd;
			uint32_t rs1 = a_instr.i.rs1;
			int32_t imm = a_instr.i.imm;
			uint32_t funct7 = a_instr.i.imm >> 5;
			uint32_t shamt = (a_instr.i.imm & 0x1f);

			if (funct3 == 0x0) { // addi
				x_reg[rd] = x_reg[rs1] + imm;
				printf("PC:%6d addi x%d, x%d, %d\n", pc, rd, rs1, imm);

			} else if (funct3 == 0x1) { // slli
				printf("PC:%6d slli x%d, x%d, %d\n", pc, rd, rs1, imm);
				x_reg[rd] = x_reg[rs1] << imm;

			} else if (funct3 == 0x2) { // slti
				printf("PC:%6d slti x%d, x%d, %d\n", pc, rd, rs1, imm);
				x_reg[rd] = (x_reg[rs1] < imm) ? 1 : 0;

			} else if (funct3 == 0x3) { // sltiu
				printf("PC:%6d slliu x%d, x%d, %d\n", pc, rd, rs1, imm);
				x_reg[rd] = ((int32_t)x_reg[rs1] < (int32_t)imm) ? 1 : 0;

			} else if (funct3 == 0x4) { // xori
				printf("PC:%6d xori x%d, x%d, %d\n", pc, rd, rs1, imm);
				x_reg[rd] = x_reg[rs1] ^ imm;

			} else if (funct3 == 0x5) { // srli,srai
				if (funct7 == 0x0) { // srli	
					printf("PC:%6d srli x%d, x%d, %d\n", pc, rd, rs1, shamt);
					x_reg[rd] = x_reg[rs1] >> shamt;

				} else if (funct7 == 0x20) { //srai
					printf("PC:%6d srai x%d, x%d, %d\n", pc, rd, rs1, shamt);
					x_reg[rd] = (int32_t)x_reg[rs1] >> (int32_t)shamt;

				} else {
					printf("Error : Unknown funct7 = 0x%x\n", funct7);
					exit(1);
				}

			} else if (funct3 == 0x6) { // ori
				printf("PC:%6d ori x%d, x%d, %d\n", pc, rd, rs1, imm);
				x_reg[rd] = x_reg[rs1] | (int32_t)imm;

			} else if (funct3 == 0x7) { // andi
				printf("PC:%6d andi x%d, x%d, %d\n", pc, rd, rs1, imm);
				x_reg[rd] = x_reg[rs1] & (int32_t)imm;

			} else {
				printf("Unknown Instruction (Immidiate)\n");
			}
		} else if (opcode == 0x23) { // S-Fromat : sb, sh, sw
			uint32_t funct3 = a_instr.sb.funct3;
			uint32_t rs1 = a_instr.sb.rs1;
			uint32_t rs2 = a_instr.sb.rs2;
			uint32_t imm;

			imm = a_instr.sb.imm1 | a_instr.sb.imm2 << 5;
			
			m_start = x_reg[rs1] + imm;

			if (funct3 == 0x0) { // sb
				s_size = 1;
				memory[m_start] = (uint8_t)(x_reg[rs2] & 0xff);
				printf("PC:%6d sb x%d, %d(x%d)\n", pc, rs1, imm, rs2);

			} else if (funct3 == 0x1) { // sh
				s_size = 2;
				memory[m_start] = (uint8_t)(x_reg[rs2] & 0xff);
				memory[m_start + 1] = (uint8_t)(x_reg[rs2] >> 8 & 0xff);
				printf("PC:%6d sh x%d, %d(x%d)\n", pc, rs1, imm, rs2);

			} else if (funct3 == 0x2) { // sw
				s_size = 4;
				memory[m_start] = (uint8_t)(x_reg[rs2] & 0xff);
				memory[m_start + 1] = (uint8_t)(x_reg[rs2] >> 8 & 0xff);
				memory[m_start + 2] = (uint8_t)(x_reg[rs2] >> 16 & 0xff);
				memory[m_start + 3] = (uint8_t)(x_reg[rs2] >> 24 & 0xff);
				printf("PC:%6d sw x%d, %d(x%d)\n", pc, rs1, imm, rs2);

			} else {
				printf("Unknown instruction (Store)\n");
			}

		} else if (opcode == 0x63) { //Branch
			uint32_t funct3 = a_instr.sb.funct3;
			uint32_t rs1 = a_instr.sb.rs1;
			uint32_t rs2 = a_instr.sb.rs2;
			int32_t imm = 0;

			imm = a_instr.sb.imm1 & 0x1e;
			imm |= (a_instr.sb.imm2 & 0x3f) << 5;
			imm |= (a_instr.sb.imm1 & 0x1) << 11; // 11th bit
			imm |= (a_instr.sb.imm2 >> 6) << 12;  // 12th bit (Warning! : << 5 X)

			if (funct3 == 0x0) { // beq
				if(x_reg[rs1] == x_reg[rs2]) {
					printf("PC:%6d beq x%d, x%d, %d\n", pc, rs1, rs2, imm);
					pc = pc + imm - 4; // -4 for pc counter below	
				}

			} else if (funct3 == 0x01) { // bne
				printf("PC:%6d bne x%d, x%d, %d\n", pc, rs1, rs2, imm);
				if (x_reg[rs1] != x_reg[rs2]) {
					pc = pc + imm - 4;
				}

			} else if (funct3 == 0x04) { // blt
				if ((int32_t)x_reg[rs1] < (int32_t)x_reg[rs2]) {
					pc = pc + imm - 4;
				}
			
			} else if (funct3 == 0x05) { // bge
				if ((int32_t)x_reg[rs1] >=  (int32_t)x_reg[rs2]) {
					pc = pc + imm - 4;
				}

			} else if (funct3 == 0x06) { // bltu
				if (x_reg[rs1] < x_reg[rs2]) {
					pc = pc + imm - 4;
				}
			} else if (funct3 == 0x07) { // bgeu
				if (x_reg[rs1] >= x_reg[rs2]) {
					pc = pc + imm - 4;
				}
			} else {
				printf("Unknown instruction\n");
			}
			
		} else if (opcode == 0x6f) { // jal (U-J)
			uint32_t rd = a_instr.uj.rd;
			uint32_t imm = 0;

			uint32_t tmp = a_instr.uj.imm;
			
			imm = ((tmp >> 9) & 0x3ff) << 1;
			imm |= ((tmp >> 8) & 0x1) << 11;
			imm |= (tmp & 0xff) << 12;
			imm |= (tmp >> 19) << 20;
		
			printf("PC:%6d jal x%d, %d\n", pc, rd, imm);
			
			x_reg[rd] = pc + 4;
			pc = pc + imm - 4;
		}
		x_reg[0] = 0;
		pc += 4;
		clock++;
		if (opcode == 0){
			printf("Opcode is 0x00\n");
			break;
		}
	}
	display_reg();
	display_memory(m_start, s_size);

	printf("End RISC-V Simulator. (Clock = %d)\n", clock);

	return 0;
}
