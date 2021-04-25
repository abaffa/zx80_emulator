#ifndef Z80MEMORY_H
#define Z80MEMORY_H

#include "config.h"
struct z80_memory
{
    unsigned char* memory; //[z80_MEMORY_SIZE];
};

void z80_memory_set(struct z80_memory* memory, int index, unsigned char val);
unsigned char z80_memory_get(struct z80_memory* memory,int index);
unsigned short z80_memory_get_short(struct z80_memory* memory,int index);

#endif