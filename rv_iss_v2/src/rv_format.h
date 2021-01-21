#ifndef RV_FORMAT_H
#define RV_FORMAT_H

typedef union { //gong yong chae

	uint32_t	instr; //Intruction
	struct {
		uint32_t	opcode:7; //parameter:bits
		uint32_t	rd:5;
		uint32_t	funct3:3;
		uint32_t	rs1:5;
		uint32_t	rs2:5;
		uint32_t	funct7:7;

	} r; //R-format

	struct {
		uint32_t	opcode:7;
		uint32_t	rd:5;
		uint32_t	funct3:3;
		uint32_t	rs1:5;
		int32_t	imm:12;
	} i; //I-format

	struct {
		uint32_t	opcode:7; 
		int32_t	imm1:5;
		uint32_t	funct3:3;
		uint32_t	rs1:5;
		uint32_t	rs2:5;
		int32_t	imm2:7;

	} sb; //S,B-format

	struct {
		uint32_t	opcode:7;
		uint32_t	rd:5;
		uint32_t	imm:20;
	} uj; // U,J-format

	
} rv_format;

#endif
