#include "zx80_memory.h"
#include <assert.h>
#include <stdio.h>

static void zx80_is_memory_in_bounds(int index)
{
    assert(index >= 0 && index < ZX80_MEMORY_SIZE);
}

void zx80_memory_set(struct zx80_memory* zx80_memory, int index, unsigned char val)
{
    zx80_is_memory_in_bounds(index);
	zx80_memory->memory[index] = val;
}

unsigned char zx80_memory_get(struct zx80_memory* zx80_memory, int index)
{
    zx80_is_memory_in_bounds(index);
    return zx80_memory->memory[index];
}

unsigned short zx80_memory_get_short(struct zx80_memory* zx80_memory, int index)
{
    unsigned char byte1 = zx80_memory_get(zx80_memory, index);
    unsigned char byte2 = zx80_memory_get(zx80_memory, index + 1);

    return byte1 << 8 | byte2;
}


unsigned char RdZ80(struct zx80_memory* zx80_memory, unsigned short Address) {
	unsigned short A = Address;
	if (A >= 0x8000)
		A = A - 0x8000;
	if (A >= 0x4000)
		A = ((A - 0x4000) % 0x400) + 0x4000;

	return zx80_memory->memory[A];  //(RAM[A>>13][A&0x1FFF]); 
}

void WrZ80(struct zx80_memory* zx80_memory, unsigned short Address, unsigned char V)
{
	unsigned short A = Address;
	if (A >= 0x8000)
		A = A - 0x8000;
	if (A >= 0x4000)
		A = ((A - 0x4000) % 0x400) + 0x4000;
	zx80_memory->memory[A] = V;
}