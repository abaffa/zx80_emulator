#ifndef CONFIG_H
#define CONFIG_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EMULATOR_WINDOW_TITLE "ZX80 Emulator"

#define SERVER_WEB 1

#define DEBUG_OPCODE 0
#define DEBUG_LOG 0


#define ZX80_MEMORY_SIZE 0xFFFF //0x100
#define Z80_PROGRAM_LOAD_ADDRESS 0X000
#define ZX80_WIDTH 256 //32 x 8
#define ZX80_HEIGHT 200 // 25 x 8
#define ZX80_BORDER 40
#define ZX80_WINDOW_MULTIPLIER 2


#define Z80_TOTAL_DATA_REGISTERS 16
#define Z80_TOTAL_STACK_DEPTH 16
#define ZX80_TOTAL_KEYS 41
#define Z80_CHARACTER_SET_LOAD_ADDRESS 0x00
#define Z80_DEFAULT_SPRITE_HEIGHT 5

#endif


