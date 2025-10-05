#ifndef MEMORY_H_
#define MEMORY_H_

extern unsigned char rom[0x8000];

unsigned char readMem(unsigned short);
int writeMem(unsigned short, unsigned char);
void resetMem(void);

#endif