#ifndef ZX80MEMORY_H
#define ZX80MEMORY_H

#include "config.h"
struct zx80_memory
{
    unsigned char* memory; //[zx80_MEMORY_SIZE];
};

void zx80_memory_set(struct zx80_memory* memory, int index, unsigned char val);
unsigned char zx80_memory_get(struct zx80_memory* memory,int index);
unsigned short zx80_memory_get_short(struct zx80_memory* memory,int index);

unsigned char RdZ80(struct zx80_memory* zx80_memory, unsigned short Address);
void WrZ80(struct zx80_memory* zx80_memory, unsigned short Address, unsigned char V);
#endif