#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include <chrono>
#ifdef __linux__
#include <time.h>
#include <pthread.h> 
#endif

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"

#include "z80.h"
#include "zx80_keyboard.h"
#include "zx80_memory.h"

#if SERVER_WEB == 1
#include "hw_web.h"
#endif


#if defined(_MSC_VER) || defined(__MINGW32__)
#include <windows.h>
#endif


#define DEBUG_CYCLES 1

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


const unsigned int keyboard_map[ZX80_TOTAL_KEYS] = {
	SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, SDLK_6, SDLK_7, SDLK_8, SDLK_9, SDLK_0,
	SDLK_q, SDLK_w, SDLK_e, SDLK_r, SDLK_t, SDLK_y, SDLK_u, SDLK_i, SDLK_o, SDLK_p,
	SDLK_a, SDLK_s, SDLK_d, SDLK_f, SDLK_g, SDLK_h, SDLK_j, SDLK_k, SDLK_l, SDLK_RETURN,
	SDLK_LSHIFT, SDLK_z, SDLK_x, SDLK_c, SDLK_v, SDLK_b, SDLK_n, SDLK_m, SDLK_PERIOD, SDLK_SPACE,
	SDLK_BACKSPACE
};

typedef enum zx_keyboard {
	zxkey_n1, zxkey_n2, zxkey_n3, zxkey_n4, zxkey_n5, zxkey_n6, zxkey_n7, zxkey_n8, zxkey_n9, zxkey_n0,
	zxkey_q, zxkey_w, zxkey_e, zxkey_r, zxkey_t, zxkey_y, zxkey_u, zxkey_i, zxkey_o, zxkey_p,
	zxkey_a, zxkey_s, zxkey_d, zxkey_f, zxkey_g, zxkey_h, zxkey_j, zxkey_k, zxkey_l, zxkey_ret,
	zxkey_shift, zxkey_z, zxkey_x, zxkey_c, zxkey_v, zxkey_b, zxkey_n, zxkey_m, zxkey_period, zxkey_space,
	zxkey_backspace
} ZX_Keyboard;


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

void draw_bitmap(SDL_Renderer* renderer, int x, int y, unsigned char bitmap, int bit_y) {

	unsigned short bit_x = 0;

	for (bit_x = 0; bit_x < 8; bit_x++) {

		if (((bitmap << bit_x) & 0x80) == 0x80) {
			SDL_Rect r;
			r.x = ((x * 8 * ZX80_WINDOW_MULTIPLIER) + (bit_x * ZX80_WINDOW_MULTIPLIER)) + ZX80_BORDER;
			r.y = (y * 8 * ZX80_WINDOW_MULTIPLIER + bit_y * ZX80_WINDOW_MULTIPLIER) + ZX80_BORDER;
			r.w = ZX80_WINDOW_MULTIPLIER;
			r.h = ZX80_WINDOW_MULTIPLIER;
			SDL_RenderFillRect(renderer, &r);
		}
	}
}



void cls(HANDLE hConsole)
{
	COORD coordScreen = { 0, 0 };    // home for the cursor
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	// Get the number of character cells in the current buffer.
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill the entire screen with blanks.
	if (!FillConsoleOutputCharacter(hConsole,        // Handle to console screen buffer
		(TCHAR)' ',      // Character to write to the buffer
		dwConSize,       // Number of cells to write
		coordScreen,     // Coordinates of first cell
		&cCharsWritten)) // Receive number of characters written
	{
		return;
	}

	// Get the current text attribute.
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}

	// Set the buffer's attributes accordingly.
	if (!FillConsoleOutputAttribute(hConsole,         // Handle to console screen buffer
		csbi.wAttributes, // Character attributes to use
		dwConSize,        // Number of cells to set attribute
		coordScreen,      // Coordinates of first cell
		&cCharsWritten))  // Receive number of characters written
	{
		return;
	}

	// Put the cursor at its home coordinates.
	SetConsoleCursorPosition(hConsole, coordScreen);
}

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
		getch();
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
	zx80_keyboard_set_map(&zx80_keyboard, keyboard_map);
	z80.zx80_memory = &zx80_memory;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow(
		EMULATOR_WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		(ZX80_WIDTH * ZX80_WINDOW_MULTIPLIER) + (ZX80_BORDER * 2),
		(ZX80_HEIGHT * ZX80_WINDOW_MULTIPLIER) + (ZX80_BORDER * 2),
		SDL_WINDOW_SHOWN
	);

	//TTF_Init();
	//TTF_Font* sans = TTF_OpenFont("arial.ttf", 24); //this opens a font style and sets a size

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;


#if defined(_MSC_VER) || defined(__MINGW32__)        
	DWORD tid;
	HANDLE myHandle = CreateThread(0, 0, run_thread, reinterpret_cast<void*>(&z80), 0, &tid);
#else
	pthread_t tid;
	pthread_create(&tid, NULL, run_thread, (void *)&zx80_computer);
#endif

	while (1) {

		/*
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency() );
		*/

		SDL_Event event;
		while (SDL_PollEvent(&event)) {

			switch (event.type) {


			case SDL_QUIT:
				running = 0;
				goto out;
				break;

#if SERVER_WEB == 0
			case SDL_KEYDOWN: {
				int key = event.key.keysym.sym;

				int vkey = zx80_keyboard_map(&zx80_keyboard, key);
				if (vkey != -1) {
					zx80_keyboard_down(&zx80_keyboard, vkey);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_z))
						z80.PORT_FEFEh = ~(z80.PORT_FEFEh & 0x02);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_x))
						z80.PORT_FEFEh = ~(z80.PORT_FEFEh & 0x04);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_c))
						z80.PORT_FEFEh = ~(z80.PORT_FEFEh & 0x08);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_v))
						z80.PORT_FEFEh = ~(z80.PORT_FEFEh & 0x10);


					//

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_a))
						z80.PORT_FDFEh = ~(z80.PORT_FEFEh & 0x01);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_s))
						z80.PORT_FDFEh = ~(z80.PORT_FEFEh & 0x02);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_d))
						z80.PORT_FDFEh = ~(z80.PORT_FEFEh & 0x04);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_f))
						z80.PORT_FDFEh = ~(z80.PORT_FEFEh & 0x08);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_g))
						z80.PORT_FDFEh = ~(z80.PORT_FEFEh & 0x10);


					//
					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_q))
						z80.PORT_FBFEh = ~(z80.PORT_FEFEh & 0x01);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_w))
						z80.PORT_FBFEh = ~(z80.PORT_FEFEh & 0x02);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_e))
						z80.PORT_FBFEh = ~(z80.PORT_FEFEh & 0x04);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_r))
						z80.PORT_FBFEh = ~(z80.PORT_FEFEh & 0x08);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_t))
						z80.PORT_FBFEh = ~(z80.PORT_FEFEh & 0x10);

					//
					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n1))
						z80.PORT_F7FEh = ~(z80.PORT_FEFEh & 0x01);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n2))
						z80.PORT_F7FEh = ~(z80.PORT_FEFEh & 0x02);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n3))
						z80.PORT_F7FEh = ~(z80.PORT_FEFEh & 0x04);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n4))
						z80.PORT_F7FEh = ~(z80.PORT_FEFEh & 0x08);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n5))
						z80.PORT_F7FEh = ~(z80.PORT_FEFEh & 0x10);

					//
					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n0))
						z80.PORT_EFFEh = ~(z80.PORT_FEFEh & 0x01);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n9))
						z80.PORT_EFFEh = ~(z80.PORT_FEFEh & 0x02);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n8))
						z80.PORT_EFFEh = ~(z80.PORT_FEFEh & 0x04);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n7))
						z80.PORT_EFFEh = ~(z80.PORT_FEFEh & 0x08);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n6))
						z80.PORT_EFFEh = ~(z80.PORT_FEFEh & 0x10);

					//
					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_p))
						z80.PORT_DFFEh = ~(z80.PORT_FEFEh & 0x01);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_o))
						z80.PORT_DFFEh = ~(z80.PORT_FEFEh & 0x02);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_i))
						z80.PORT_DFFEh = ~(z80.PORT_FEFEh & 0x04);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_u))
						z80.PORT_DFFEh = ~(z80.PORT_FEFEh & 0x08);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_y))
						z80.PORT_DFFEh = ~(z80.PORT_FEFEh & 0x10);

					//
					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_ret))
						z80.PORT_BFFEh = ~(z80.PORT_FEFEh & 0x01);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_l))
						z80.PORT_BFFEh = ~(z80.PORT_FEFEh & 0x02);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_k))
						z80.PORT_BFFEh = ~(z80.PORT_FEFEh & 0x04);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_j))
						z80.PORT_BFFEh = ~(z80.PORT_FEFEh & 0x08);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_h))
						z80.PORT_BFFEh = ~(z80.PORT_FEFEh & 0x10);

					//
					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_space))
						z80.PORT_7FFEh = ~(z80.PORT_FEFEh & 0x01);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_period))
						z80.PORT_7FFEh = ~(z80.PORT_FEFEh & 0x02);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_m))
						z80.PORT_7FFEh = ~(z80.PORT_FEFEh & 0x04);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n))
						z80.PORT_7FFEh = ~(z80.PORT_FEFEh & 0x08);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_b))
						z80.PORT_7FFEh = ~(z80.PORT_FEFEh & 0x10);

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_shift))
						z80.PORT_FEFEh = z80.PORT_FEFEh & 0xFE;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_backspace)) {
						z80.PORT_EFFEh = ~(z80.PORT_FEFEh & 0x01);
						z80.PORT_FEFEh = z80.PORT_FEFEh & 0xFE;
					}


					//printf("key_down %x\t%x\n",z80.PORT_FEFEh);

				}
			}
							  break;

			case SDL_KEYUP: {
				int key = event.key.keysym.sym;
				int vkey = zx80_keyboard_map(&zx80_keyboard, key);
				if (vkey != -1) {


					//n1,n2,n3,n4,n5,n6,n7,n8,n9,n0,
					//q,w,e,r,tt,y,u,i,o,p,
					//a,s,d,f,g,h,j,k,l,ret,
					//shift,z,x,c,v,b,n,m,period, space

					/*
					HEX  1    2    4    8    10
					Port____Line____Bit__0____1____2____3____4__
					FEFEh  0  (A8)     SHIFT  Z    X    C    V
					FDFEh  1  (A9)       A    S    D    F    G
					FBFEh  2  (A10)      Q    W    E    R    T
					F7FEh  3  (A11)      1    2    3    4    5
					EFFEh  4  (A12)      0    9    8    7    6
					DFFEh  5  (A13)      P    O    I    U    Y
					BFFEh  6  (A14)    ENTER  L    K    J    H
					7FFEh  7  (A15)     SPC   .    M    N    B
					*/

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_shift))
						z80.PORT_FEFEh |= 0x01;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_z))
						z80.PORT_FEFEh |= 0x02;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_x))
						z80.PORT_FEFEh |= 0x04;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_c))
						z80.PORT_FEFEh |= 0x08;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_v))
						z80.PORT_FEFEh |= 0x10;

					//

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_a))
						z80.PORT_FDFEh |= 0x01;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_s))
						z80.PORT_FDFEh |= 0x02;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_d))
						z80.PORT_FDFEh |= 0x04;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_f))
						z80.PORT_FDFEh |= 0x08;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_g))
						z80.PORT_FDFEh |= 0x10;

					//
					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_q))
						z80.PORT_FBFEh |= 0x01;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_w))
						z80.PORT_FBFEh |= 0x02;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_e))
						z80.PORT_FBFEh |= 0x04;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_r))
						z80.PORT_FBFEh |= 0x08;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_t))
						z80.PORT_FBFEh |= 0x10;

					//
					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n1))
						z80.PORT_F7FEh |= 0x01;



					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n2))
						z80.PORT_F7FEh |= 0x02;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n3))
						z80.PORT_F7FEh |= 0x04;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n4))
						z80.PORT_F7FEh |= 0x08;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n5))
						z80.PORT_F7FEh |= 0x10;

					//
					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n0))
						z80.PORT_EFFEh |= 0x01;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n9))
						z80.PORT_EFFEh |= 0x02;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n8))
						z80.PORT_EFFEh |= 0x04;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n7))
						z80.PORT_EFFEh |= 0x08;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n6))
						z80.PORT_EFFEh |= 0x10;

					//
					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_p))
						z80.PORT_DFFEh |= 0x01;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_o))
						z80.PORT_DFFEh |= 0x02;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_i))
						z80.PORT_DFFEh |= 0x04;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_u))
						z80.PORT_DFFEh |= 0x08;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_y))
						z80.PORT_DFFEh |= 0x10;

					//
					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_ret))
						z80.PORT_BFFEh |= 0x01;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_l))
						z80.PORT_BFFEh |= 0x02;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_k))
						z80.PORT_BFFEh |= 0x04;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_j))
						z80.PORT_BFFEh |= 0x08;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_h))
						z80.PORT_BFFEh |= 0x10;

					//
					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_space))
						z80.PORT_7FFEh |= 0x01;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_period))
						z80.PORT_7FFEh |= 0x02;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_m))
						z80.PORT_7FFEh |= 0x04;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_n))
						z80.PORT_7FFEh |= 0x08;

					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_b))
						z80.PORT_7FFEh |= 0x10;


					if (zx80_keyboard_is_down(&zx80_keyboard, zxkey_backspace)) {
						z80.PORT_EFFEh |= 0x01;
						z80.PORT_FEFEh |= 0x01;

					}


					//printf("key_up %x\n",z80.PORT_FEFEh);

					if (zx80_keyboard_is_down(&zx80_keyboard, 2)) {
						if (mem_offset < ZX80_MEMORY_SIZE)
							mem_offset += 0xF;
					}
					if (zx80_keyboard_is_down(&zx80_keyboard, 1)) {
						if (mem_offset > 0)
							mem_offset -= 0xF;
					}
					if (zx80_keyboard_is_down(&zx80_keyboard, 3)) {
						if (mem_offset < ZX80_MEMORY_SIZE)
							mem_offset += 0xF0;
					}
					if (zx80_keyboard_is_down(&zx80_keyboard, 4)) {
						if (mem_offset > 0)
							mem_offset -= 0xF0;
					}

					if (zx80_keyboard_is_down(&zx80_keyboard, 5)) {
						mem_follow = !mem_follow;
					}

					zx80_keyboard_up(&zx80_keyboard, vkey);

					state = !state;
				}
			}
							break;

#endif
			}

		}

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


		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

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

					draw_bitmap(renderer, x, y, bitmap, bit_y);

					refresh |= (screenmap[y][x][bit_y] != bitmap);
					screenmap[y][x][bit_y] = bitmap;

					bit_y++;
				}

				vram++;
			}
			if (x < 32) memset(screenmap[y][x], 0, sizeof(unsigned char) * (32 - x) * 8);

			vram++;
		}

		SDL_RenderPresent(renderer);

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


out:
	SDL_DestroyWindow(window);

	return 0;
}
