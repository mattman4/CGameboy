#include "cpu.h"

// https://gbdev.io/pandocs/Power_Up_Sequence.html#cpu-registers
// https://gbdev.io/pandocs/CPU_Registers_and_Flags.html

struct registers {
	unsigned char a; // accumulator
	unsigned char f; // flags

	unsigned char b;
	unsigned char c;

	unsigned char d;
	unsigned char e;

	unsigned char h;
	unsigned char l;

	unsigned char sp;
	unsigned char pc;
};

struct registers registers;

void reset() {
	registers.a = 0x01;
	registers.f = 0xB0;
	registers.b = 0x00;
	registers.c = 0x13;
	registers.d = 0x00;
	registers.e = 0xD8;
	registers.h = 0x01;
	registers.l = 0x4D;
	registers.pc = 0x100;
	registers.sp = 0xFFFE;
}