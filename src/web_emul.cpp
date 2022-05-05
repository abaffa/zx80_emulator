#include <stdio.h>
#include <stdlib.h>

#include <chrono>
#ifdef __linux__
#include <time.h>
#include <pthread.h> 
#endif

#include "z80.h"
#include "zx80_keyboard.h"
#include "zx80_memory.h"

#include "hw_web.h"


#if defined(_MSC_VER) || defined(__MINGW32__)
#include <windows.h>
#endif


#define DEBUG_CYCLES 0

//////////////////////////////////

using namespace std;
#include <string>
#include <iostream>
using std::cout;
#include <fstream>
using std::ifstream;
using std::getline;
using std::string;


using namespace std::chrono;



char state = 0;
unsigned short mem_offset = 0;
int mem_follow = 0;
char running = 1;

#if SERVER_WEB == 1
#include <queue>
queue<struct client_key> keyboard_queue;

HW_WEB hw_web;
#endif


unsigned char screenmap[25][32][8];


#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 


void cpu_exec(Z80& z80, struct zx80_memory* zx80_memory) {
	z80.z80_exec(zx80_memory);
}

#define LSB(w) ((w) & 0xff)
#define MSB(w) (((w) >> 8) & 0xff)
#define WORD(l, h) (((h)<<8) | (l))
void cpu_print(Z80& z80, struct zx80_memory* zx80_memory) {

	printf("\t ""%c%c%c%c%c%c%c%c""\n", BYTE_TO_BINARY(MSB(z80.registers.AF)));

	printf("  AF  |  BC  |  DE  |  HL  || S | Z | H | P | V | N | C |\n");
	printf(" %04x |", z80.registers.AF);
	printf(" %04x |", z80.registers.BC);
	printf(" %04x |", z80.registers.DE);
	printf(" %04x ||", z80.registers.HL);
	printf(" %01x |", (z80.registers.AF & S_FLAG) >> 7);
	printf(" %01x |", (z80.registers.AF & Z_FLAG) >> 6);
	printf(" %01x |", (z80.registers.AF & H_FLAG) >> 4);
	printf(" %01x |", (z80.registers.AF & P_FLAG) >> 2);
	printf(" %01x |", (z80.registers.AF & V_FLAG) >> 2);
	printf(" %01x |", (z80.registers.AF & N_FLAG) >> 1);
	printf(" %01x |", (z80.registers.AF & C_FLAG));
	printf("FLAGS ""%c%c%c%c%c%c%c%c", BYTE_TO_BINARY(LSB(z80.registers.AF)));
	printf("\n\n");

	printf("  AF' |  BC' |  DE' |  HL' ||  PC  |  SP  ||  IX  |  IY  || I  | R  |\n");
	printf(" %04x |", z80.registers.AFl);
	printf(" %04x |", z80.registers.BCl);
	printf(" %04x |", z80.registers.DEl);
	printf(" %04x ||", z80.registers.HLl);
	printf(" %04x |", z80.registers.PC);
	printf(" %04x ||", z80.registers.SP);
	printf(" %04x |", z80.registers.IX);
	printf(" %04x ||", z80.registers.IY);
	printf(" %02x |", z80.registers.I);
	printf(" %02x |", z80.registers.R);
	printf("\n\n");
	printf("IFF ""%c%c%c%c%c%c%c%c", BYTE_TO_BINARY(z80.registers.IFF));
	printf("\n\n");

	if (mem_follow)
		mem_offset = (z80.registers.PC / 0x10) * 0x10;

	int i = 0;
	printf("offset: %04x\n", mem_offset);
	printf("        ");
	for (i = 0; i < 16; i++)
		printf("%02x ", i);
	printf("\n\n %04x ", mem_offset);

	for (i = 0 + mem_offset; i < 256 + mem_offset; i++) {
		if (i % 16 == 0)
			if (z80.registers.PC == i)
				printf(" #");
			else
				printf("  ");
		if (z80.registers.PC == i || z80.registers.PC - 1 == i)
			printf("%02x#", z80.RdZ80(zx80_memory, i));
		else
			printf("%02x ", z80.RdZ80(zx80_memory, i));

		if ((i + 1) % 16 == 0 && i < 255 + mem_offset)
			printf("\n %04x ", i + 1);
	}
	printf("\n\n");
	printf("Stack:");
	for (i = 0; i < 16; i += 2) {
		if (i % 2 == 0) printf("  ");
		printf("%02x", z80.RdZ80(zx80_memory, z80.registers.SP + i + 1));
		printf("%02x", z80.RdZ80(zx80_memory, z80.registers.SP + i));
	}

	printf("\n\n");

}


#if defined(_MSC_VER) || defined(__MINGW32__)
DWORD WINAPI run_thread(void *vargp)
#else
void *run_thread(void *vargp)
#endif
{

	Z80 *z80 = (Z80*)vargp;

	while (running) {


		if ((z80->registers.IFF & IFF_HALT) == 0x0) {
			cpu_exec(*z80, z80->zx80_memory);
		}
		else if (z80->registers.IFF & IFF_HALT) {
		}


		if (z80->registers.IFF & IFF_HALT) {
			z80->IntZ80(z80->zx80_memory, INT_IRQ);
			z80->registers.IFF |= IFF_1;
			z80->IntZ80(z80->zx80_memory, INT_IRQ);
		}
	}

	return NULL;
}



int main(int argc, char** argv)
{

	const char* filename;
	if (argc < 2)
	{
		printf("Loading Default Rom\n");
		//return -1;
		filename = "zx80rom.bin";
		//filename = "zx81rom.bin";
	}
	else
		filename = argv[1];

	printf("The filename to load is: %s\n", filename);

	FILE* f = fopen(filename, "rb");
	if (!f)
	{
		printf("Failed to open the file\n");
		printf("Press any key to continue");
		return -1;
	}

	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	fseek(f, 0, SEEK_SET);

	char* buf = (char*)malloc(size * sizeof(char));

	int res = fread(buf, size, 1, f);
	if (res != 1)
	{
		printf("Failed to read from file");
		return -1;
	}

#if SERVER_WEB == 1
	hw_web.start_server(&keyboard_queue);
#endif

	struct zx80_keyboard zx80_keyboard;
	struct zx80_memory zx80_memory;
	Z80 z80;
	z80.z80_init();

	///////////////////////////////////////////////////////////////////////////
	zx80_memory.memory = (unsigned char*)malloc(ZX80_MEMORY_SIZE * sizeof(unsigned char));
	//memcpy(z80->memory.memory, z80_default_character_set, sizeof(z80_default_character_set));

	int j = 0;
	for (j = 0; j < ZX80_MEMORY_SIZE; j++) {
		zx80_memory.memory[j] = 0x07;
	}

	//assert(size + Z80_PROGRAM_LOAD_ADDRESS < Z80_MEMORY_SIZE);
	//memcpy(&z80->memory.memory[Z80_PROGRAM_LOAD_ADDRESS], buf, size);

	//memcpy(z80->memory.memory, buf, size);
	memcpy(&zx80_memory.memory[0], buf, size);
	///////////////////////////////////////////////////////////////////////////

	z80.z80_reset();
	
	z80.zx80_memory = &zx80_memory;

	

#if defined(_MSC_VER) || defined(__MINGW32__)    
	DWORD tid;
	HANDLE myHandle = CreateThread(0, 0, run_thread, reinterpret_cast<void*>(&z80), 0, &tid);
#else
	pthread_t tid;
	pthread_create(&tid, NULL, run_thread, (void *)&z80);
#endif




	while (1) {

		/*
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency() );
		*/

#if SERVER_WEB == 1

		if (!keyboard_queue.empty()) {
			struct client_key k = keyboard_queue.front();
			keyboard_queue.pop();

			if (k.key == 'z')
				z80.PORT_FEFEh = ~(z80.PORT_FEFEh & 0x02);

			if (k.key == 'x')
				z80.PORT_FEFEh = ~(z80.PORT_FEFEh & 0x04);

			if (k.key == 'c')
				z80.PORT_FEFEh = ~(z80.PORT_FEFEh & 0x08);

			if (k.key == 'v')
				z80.PORT_FEFEh = ~(z80.PORT_FEFEh & 0x10);


			//

			if (k.key == 'a')
				z80.PORT_FDFEh = ~(z80.PORT_FEFEh & 0x01);

			if (k.key == 's')
				z80.PORT_FDFEh = ~(z80.PORT_FEFEh & 0x02);

			if (k.key == 'd')
				z80.PORT_FDFEh = ~(z80.PORT_FEFEh & 0x04);

			if (k.key == 'f')
				z80.PORT_FDFEh = ~(z80.PORT_FEFEh & 0x08);

			if (k.key == 'g')
				z80.PORT_FDFEh = ~(z80.PORT_FEFEh & 0x10);


			//
			if (k.key == 'q')
				z80.PORT_FBFEh = ~(z80.PORT_FEFEh & 0x01);

			if (k.key == 'w')
				z80.PORT_FBFEh = ~(z80.PORT_FEFEh & 0x02);

			if (k.key == 'e')
				z80.PORT_FBFEh = ~(z80.PORT_FEFEh & 0x04);

			if (k.key == 'r')
				z80.PORT_FBFEh = ~(z80.PORT_FEFEh & 0x08);

			if (k.key == 't')
				z80.PORT_FBFEh = ~(z80.PORT_FEFEh & 0x10);

			//
			if (k.key == '1')
				z80.PORT_F7FEh = ~(z80.PORT_FEFEh & 0x01);

			if (k.key == '2')
				z80.PORT_F7FEh = ~(z80.PORT_FEFEh & 0x02);

			if (k.key == '3')
				z80.PORT_F7FEh = ~(z80.PORT_FEFEh & 0x04);

			if (k.key == '4')
				z80.PORT_F7FEh = ~(z80.PORT_FEFEh & 0x08);

			if (k.key == '5')
				z80.PORT_F7FEh = ~(z80.PORT_FEFEh & 0x10);

			//
			if (k.key == '0')
				z80.PORT_EFFEh = ~(z80.PORT_FEFEh & 0x01);

			if (k.key == '9')
				z80.PORT_EFFEh = ~(z80.PORT_FEFEh & 0x02);

			if (k.key == '8')
				z80.PORT_EFFEh = ~(z80.PORT_FEFEh & 0x04);

			if (k.key == '7')
				z80.PORT_EFFEh = ~(z80.PORT_FEFEh & 0x08);

			if (k.key == '6')
				z80.PORT_EFFEh = ~(z80.PORT_FEFEh & 0x10);

			//
			if (k.key == 'p')
				z80.PORT_DFFEh = ~(z80.PORT_FEFEh & 0x01);

			if (k.key == 'o')
				z80.PORT_DFFEh = ~(z80.PORT_FEFEh & 0x02);

			if (k.key == 'i')
				z80.PORT_DFFEh = ~(z80.PORT_FEFEh & 0x04);

			if (k.key == 'u')
				z80.PORT_DFFEh = ~(z80.PORT_FEFEh & 0x08);

			if (k.key == 'y')
				z80.PORT_DFFEh = ~(z80.PORT_FEFEh & 0x10);

			//
			if (k.key == '\n' || k.key == '\r')
				z80.PORT_BFFEh = ~(z80.PORT_FEFEh & 0x01);

			if (k.key == 'l')
				z80.PORT_BFFEh = ~(z80.PORT_FEFEh & 0x02);

			if (k.key == 'k')
				z80.PORT_BFFEh = ~(z80.PORT_FEFEh & 0x04);

			if (k.key == 'j')
				z80.PORT_BFFEh = ~(z80.PORT_FEFEh & 0x08);

			if (k.key == 'h')
				z80.PORT_BFFEh = ~(z80.PORT_FEFEh & 0x10);

			//
			if (k.key == ' ')
				z80.PORT_7FFEh = ~(z80.PORT_FEFEh & 0x01);

			if (k.key == '.')
				z80.PORT_7FFEh = ~(z80.PORT_FEFEh & 0x02);

			if (k.key == 'm')
				z80.PORT_7FFEh = ~(z80.PORT_FEFEh & 0x04);

			if (k.key == 'n')
				z80.PORT_7FFEh = ~(z80.PORT_FEFEh & 0x08);

			if (k.key == 'b')
				z80.PORT_7FFEh = ~(z80.PORT_FEFEh & 0x10);

			if (k.shift == 1)
				z80.PORT_FEFEh = z80.PORT_FEFEh & 0xFE;

			if (k.key == (char)8) {
				z80.PORT_EFFEh = ~(z80.PORT_FEFEh & 0x01);
				z80.PORT_FEFEh = z80.PORT_FEFEh & 0xFE;
			}


			//printf("key_down %x\t%x\n",z80.PORT_FEFEh);


		}
#endif


		unsigned short x;
		unsigned short y;
		unsigned short bit_y;
		unsigned short  ka;

		unsigned short vram = 0x400C;
		unsigned short char_pixel_base = 0x0E00;

		vram = WORD(z80.RdZ80(&zx80_memory, vram), z80.RdZ80(&zx80_memory, vram + 1));

		bool refresh = false;

		for (y = 0; y < 25; y++) {

			for (x = 0; x < 32 && z80.RdZ80(&zx80_memory, vram) != 0x76; x++) {


				unsigned char keymap_code = z80.RdZ80(&zx80_memory, vram);
				unsigned char is_inversed = (keymap_code & 0x80) != 0;
				unsigned short keymap_address = char_pixel_base + (keymap_code & 0x7F) * 8;

				bit_y = 0;

				for (ka = keymap_address; ka < keymap_address + 8; ka++) {

					unsigned char bm = z80.RdZ80(&zx80_memory, ka);
					unsigned char bitmap = !is_inversed ? bm & 0xFF : (~bm) & 0xFF;

					refresh |= (screenmap[y][x][bit_y] != bitmap);
					screenmap[y][x][bit_y] = bitmap;

					bit_y++;
				}

				vram++;
			}
			if (x < 32) memset(screenmap[y][x], 0, sizeof(unsigned char) * (32 - x) * 8);

			vram++;
		}

#if SERVER_WEB == 1
		if (refresh) {
			string str = "";
			for (y = 0; y < 25; y++) {
				int bit_y = 0;
				for (bit_y = 0; bit_y < 8; bit_y++) {
					for (x = 0; x < 32; x++) {

						if (screenmap[y][x][bit_y] > 0)
							str.append("[" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(bit_y) + "," + std::to_string((unsigned int)screenmap[y][x][bit_y]) + "],");
					}
				}
			}


			if (str.size() > 0) {
				str.pop_back();

				hw_web.line(str, 0);
			}
		}
#endif

	}

	return 0;
}
