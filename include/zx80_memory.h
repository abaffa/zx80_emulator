#ifndef zx80MEMORY_H
#define zx80MEMORY_H

#include "config.h"
struct zx80_memory
{
	unsigned char* memory; //[zx80_MEMORY_SIZE];
	//unsigned char* rom; //[zx80_MEMORY_SIZE];

	//char rom_page;
};

void zx80_memory_set(struct zx80_memory* memory, int index, unsigned char val);
unsigned char zx80_memory_get(struct zx80_memory* memory, int index);
unsigned short zx80_memory_get_short(struct zx80_memory* memory, int index);

#endif