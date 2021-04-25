#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#include "z80.h"
#include "zx80_keyboard.h"


const char keyboard_map[ZX80_TOTAL_KEYS] = {
    (int)'0',(int)'1',(int)'2',(int)'3',(int)'4',(int)'5',(int)'6',(int)'7',(int)'8',(int)'9',
    (int)'A',(int)'B',(int)'C',(int)'D',(int)'E',(int)'F'};

char state = 0;
unsigned short mem_offset = 0;
int mem_follow = 0;

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


void cpu_exec(struct z80 *z80){
    z80_exec(z80);
}

#define LSB(w) ((w) & 0xff)
#define MSB(w) (((w) >> 8) & 0xff)
void cpu_print(struct z80 *z80){

            
            printf("\t "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(MSB(z80->registers.AF)));

            //if(state == 0){
            printf("  AF  |  BC  |  DE  |  HL  || S | Z | H | P | V | N | C |\n");
            printf(" %04x |", z80->registers.AF);
            printf(" %04x |", z80->registers.BC);
            printf(" %04x |", z80->registers.DE);
            printf(" %04x ||", z80->registers.HL);
            printf(" %01x |", (z80->registers.AF & S_FLAG) >> 7);
            printf(" %01x |", (z80->registers.AF & Z_FLAG) >> 6);
            printf(" %01x |", (z80->registers.AF & H_FLAG) >> 4);
            printf(" %01x |", (z80->registers.AF & P_FLAG) >> 2);
            printf(" %01x |", (z80->registers.AF & V_FLAG) >> 2);
            printf(" %01x |", (z80->registers.AF & N_FLAG) >> 1);
            printf(" %01x |", (z80->registers.AF & C_FLAG));
            printf("FLAGS "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(LSB(z80->registers.AF)));
            printf("\n\n");

            printf("  AF' |  BC' |  DE' |  HL' ||  PC  |  SP  ||  IX  |  IY  || I  | R  |\n");
            printf(" %04x |", z80->registers.AFl);
            printf(" %04x |", z80->registers.BCl);
            printf(" %04x |", z80->registers.DEl);
            printf(" %04x ||", z80->registers.HLl);
            printf(" %04x |", z80->registers.PC);
            printf(" %04x ||", z80->registers.SP);
            printf(" %04x |", z80->registers.IX);
            printf(" %04x ||", z80->registers.IY);
            printf(" %02x |", z80->registers.I);
            printf(" %02x |", z80->registers.R);
            printf("\n\n");
            printf("IFF "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(z80->registers.IFF));
            printf("\n\n");
            /*
             printf(" MEM > ");
            int i = 0; 
            for(i = 0; i< 10; i++)
                printf("%02x", z80->memory.memory[z80->registers.PC + i]);
            printf("\n\n");
            }
            else if(state == 1){
            
                printf("  PC  |  SP  ||  IX  |  IY  || I  | R  || S | Z | H | P | V | N | C |\n");
            
                printf(" %04x |", z80->registers.PC);
                printf(" %04x ||", z80->registers.SP);
                printf(" %04x |", z80->registers.IX);
                printf(" %04x ||", z80->registers.IY);
                printf(" %02x |", z80->registers.I);
                printf(" %02x ||", z80->registers.R);
                
            printf(" %01x |", (z80->registers.AF & S_FLAG) >> 7);
            printf(" %01x |", (z80->registers.AF & Z_FLAG) >> 6);
            printf(" %01x |", (z80->registers.AF & H_FLAG) >> 4);
            printf(" %01x |", (z80->registers.AF & P_FLAG) >> 2);
            printf(" %01x |", (z80->registers.AF & V_FLAG) >> 2);
            printf(" %01x |", (z80->registers.AF & N_FLAG) >> 1);
            printf(" %01x |", (z80->registers.AF & C_FLAG));
   
                printf("\n\n");
                */

                printf("%x", mem_follow);
                if(mem_follow)
                    mem_offset  = (z80->registers.PC / 0x10) * 0x10;
                
                int i = 0;
                printf("offset: %04x\n", mem_offset);
                printf("        ");
                for(i = 0; i < 16; i++)
                    printf("%02x ", i);
                printf("\n\n %04x ", mem_offset);

                for(i = 0 + mem_offset; i < 256 + mem_offset; i++){
                    if(i % 16 == 0)
                        if(z80->registers.PC == i)
                            printf(" #");
                        else
                            printf("  ");
                    if(z80->registers.PC == i || z80->registers.PC-1 == i)
                        printf("%02x#", RdZ80(z80, i));
                    else
                        printf("%02x ", RdZ80(z80, i));
                    
                    if((i+1) % 16 == 0 && i < 255+ mem_offset)
                        printf("\n %04x ", i+1);
                }
                printf("\n\n");
            //}
}



int main(int argc, char** argv)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cls(hConsole);

    const char* filename;
    if(argc < 2)
    {
        printf("Loading Default Rom\n");
        //return -1;
        filename = "zx80rom.bin";
    }
    else
        filename = argv[1];

    printf("The filename to load is: %s\n", filename);

    FILE* f = fopen(filename, "rb");
    if(!f)
    {
        printf("Failed to open the file");
        return -1;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* buf = (char*) malloc(size * sizeof(char));
    
    int res = fread(buf, size, 1, f);
    if(res != 1)
    {
        printf("Failed to read from file");
        return -1;
    }    
    cls(hConsole);


    struct zx80_keyboard zx80_keyboard; 
    struct z80 z80;
    z80_init(&z80);

    int j = 0;
    for(j = 0; j < Z80_MEMORY_SIZE; j++){
        z80.memory.memory[j] = 0x07;
    }

    z80_load(&z80, buf, size, 0x0000);
    //z80_load(&z80, buf, size, 0x2000);
    //z80_load(&z80, buf, size, 0x4000);
    //z80_load(&z80, buf, size, 0x8000);
    //z80_load(&z80, buf, size, 0xA000);
    //z80_load(&z80, buf, size, 0xC000);
    
    z80_reset(&z80);
    
    clock_t t1 = clock(), t2 = clock();
    double deltaTime = 0;
    double frame = 0;
    double cpu_clk = 0;
    double cpu = 0; 
    printf("0.0fMHz - 0\n");
    printf("Opcode: \n\n\n");
    cpu_print(&z80);
    int iii = 0;
    double speed =  3.0769230769231E-4;
                    //3.0769230769231E-7
    int do_steps = 0;
    int step = 0;
    
    int do_breakpoint = 0;
    unsigned short breakpoint = 0x161; //0x0150;

    struct timespec tstart={0,0}, tend={0,0};

    while(1){


		clock_gettime(GetTickCount(), &tend); //clock_gettime(CLOCK_MONOTONIC, &tend);
        deltaTime = ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
		clock_gettime(GetTickCount(), &tstart); // clock_gettime(CLOCK_MONOTONIC, &tstart);

        frame += deltaTime;
        cpu += deltaTime;
        cpu_clk += deltaTime;


        if((!do_steps && cpu >= speed) || (do_steps && step)){ 
            cpu_exec(&z80); iii++;
            cpu = 0;

            step = 0;

            if(do_breakpoint && z80.registers.PC == breakpoint)
                do_steps = 1;
        }

        if(frame >= 0.1){
                
             if(kbhit()){
                int key = getch();
            
                if(key == (int)'b'){
                    do_breakpoint = !do_breakpoint;
                }

                if(key == (int)'s'){
                    do_steps = !do_steps;
                }

                if(key == (int)'r'){
                    do_steps = 0;
                }
                
                if(key == (int)'n'){
                    step = 1;
                }

                if(key == (int)'2'){
                    if(mem_offset + 0x10 < Z80_MEMORY_SIZE)
                        mem_offset += 0x10; 
                }
                if(key == (int)'1'){
                    if(mem_offset - 0x10 > 0)
                        mem_offset -= 0x10; 
                }
                if(key == (int)'3'){
                    if(mem_offset + 0x100 < Z80_MEMORY_SIZE)
                        mem_offset += 0x100; 
                }
                if(key == (int)'4'){
                    if(mem_offset - 0x100 > 0)
                        mem_offset -= 0x100; 
                }
                if(key == (int)'5'){
                    if(mem_offset + 0x1000 < Z80_MEMORY_SIZE)
                        mem_offset += 0x1000; 
                }
                if(key == (int)'6'){
                    if(mem_offset - 0x1000 > 0)
                        mem_offset -= 0x1000; 
                }
                if(key == (int)'7'){
                    speed /= 10;
                }                        
                if(key == (int)'8'){
                    if(speed < 1)
                        speed *= 10;
                    else if(speed > 1) 
                        speed += 1;
                    
                    if(speed > 2)
                        speed = 2;
                }                        
                if(key == (int)'9'){
                    mem_follow = !mem_follow;
                }                        

                if(key == (int)'0')
                return ;
            }

            //cls(hConsole);

            COORD pos = {0, 0};
            SetConsoleCursorPosition(hConsole, pos);
            printf("                                                                                                                                                      \r\n");
            printf("                                                                                                                                                      \n");
            printf("                                                                                                                                                      \n");
            SetConsoleCursorPosition(hConsole, pos);
            printf("%.3fMHz - %g\n", ((float)iii)/1000000, speed);
            printf("%s", z80.last_op_desc);
            cpu_print(&z80);
            frame = 0;
            
        }

        if(cpu_clk >= 1){
            iii = 0;
            cpu_clk = 0;
        }

        if(z80.registers.IFF & IFF_HALT){
            do_steps = 1;
            z80.registers.IFF &= ~IFF_HALT;
            //printf("%s", z80.last_op_desc);
            //printf("HALT");
            //return;
            }

    }

    return 0;
} 
