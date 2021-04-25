#include "z80_memory.h"
#include <assert.h>

static void z80_is_memory_in_bounds(int index)
{
    assert(index >= 0 && index < Z80_MEMORY_SIZE);
}

void z80_memory_set(struct z80_memory* memory, int index, unsigned char val)
{
    z80_is_memory_in_bounds(index);
    memory->memory[index] = val;
}

unsigned char z80_memory_get(struct z80_memory* memory, int index)
{
    z80_is_memory_in_bounds(index);
    return memory->memory[index];
}

unsigned short z80_memory_get_short(struct z80_memory* memory, int index)
{
    unsigned char byte1 = z80_memory_get(memory, index);
    unsigned char byte2 = z80_memory_get(memory, index + 1);

    return byte1 << 8 | byte2;
}