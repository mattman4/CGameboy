#include "memory.h"

// https://gbdev.io/pandocs/Memory_Map.html

unsigned char rom[0x8000] = { 0 };
unsigned char vram[0x2000] = { 0 };
unsigned char eram[0x2000] = { 0 };
unsigned char wram[0x2000] = { 0 };
unsigned char hram[0x007F] = { 0 };
unsigned char oam[0x00A0] = { 0 };
unsigned char io[0x0010] = { 0 };

// we don't map echo ram
// todo: 0xA000 to 0xBFFF for external ram (rom saves)

// 8 bit value, 16 bit address

unsigned char readMem(unsigned short addr) {
	if (addr < 0x8000) return rom[addr];
	if (addr < 0xA000) return vram[addr - 0x8000];
	if (addr < 0xC000) return eram[addr - 0xA000];
	if (addr < 0xE000) return wram[addr - 0xC000];
	if (addr < 0xFE00) return 0; // echo ram - prohibited
	if (addr < 0xFEA0) return oam[addr - 0xFE00];
	if (addr < 0xFF00) return 0xFF; // not usable
	if (addr < 0xFF80) return io[addr - 0xFF00];
	if (addr < 0xFFFF) return hram[addr - 0xFF80];
	if (addr == 0xFFFF) return 0; // IE


	return 0;
}

int writeMem(unsigned short addr, unsigned char val) {
	if (addr < 0x8000) { rom[addr] = val; return; }
	if (addr < 0xA000) { vram[addr - 0x8000] = val; return; }
	if (addr < 0xC000) { eram[addr - 0xA000] = val; return; }
	if (addr < 0xE000) { wram[addr - 0xC000] = val; return; }
	if (addr < 0xFE00) return;
	if (addr < 0xFEA0) { oam[addr - 0xFE00] = val; return; }
	if (addr < 0xFF00) return;
	if (addr < 0xFF80) { io[addr - 0xFF00] = val; return; }
	if (addr < 0xFFFF) { hram[addr - 0xFF80] = val; return; }
	if (addr == 0xFFFF) return;


	return 0;
}

void reset() {
	memset(rom, 0, sizeof(rom));
	memset(vram, 0, sizeof(vram));
	memset(eram, 0, sizeof(eram));
	memset(wram, 0, sizeof(wram));
	memset(hram, 0, sizeof(hram));
	memset(oam, 0, sizeof(oam));
	memset(io, 0, sizeof(io));
}