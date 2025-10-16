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

#endif