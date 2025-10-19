#ifndef CPU_H_
#define CPU_H_

extern struct registers {
	unsigned char a; // accumulator
	unsigned char f; // flags

	unsigned char b;
	unsigned char c;

	unsigned char d;
	unsigned char e;

	unsigned char h;
	unsigned char l;

	unsigned short sp;
	unsigned short pc;
} registers;

void resetCPU(void);

// Instructions!
// i = indirect addressing

void unimplemented(void);

// 0x
void NOP(void);
void LD_BC_n16(unsigned short);
void LD_BCi_A(void);
void INC_BC(void);
void INC_B(void);
void DEC_B(void);
void LD_B_n8(unsigned char);
void RLCA(void);
void LD_a16i_SP(unsigned short);
void ADD_HL_BC(void);
void LD_A_BCi(void);
void DEC_BC(void);
void INC_C(void);
void DEC_C(void);
void LD_C_n8(unsigned char);
void RRCA(void);

// 1x
// 2x
// 3x
// 4x
// 5x
// 6x
// 7x
// 8x
// 9x
// Ax
// Bx
// Cx
// Dx
// Ex
// Fx

#endif