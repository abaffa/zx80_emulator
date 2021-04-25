#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "z80.h"
#include "zx80_keyboard.h"

int state = 0;
unsigned short mem_offset = 0x0000;
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


unsigned int toInt(char c)
{
  if (c >= '0' && c <= '9') return      c - '0';
  if (c >= 'A' && c <= 'F') return 10 + c - 'A';
  if (c >= 'a' && c <= 'f') return 10 + c - 'a';
  return -1;
}

int run = 0;

int main(int argc, char** argv)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cls(hConsole);
    struct zx80_keyboard zx80_keyboard; 
    struct z80 z80;
    z80_init(&z80);
    z80_reset(&z80);

    int j = 0;
    for(j = 0; j < Z80_MEMORY_SIZE; j++){
        z80.memory.memory[j] = 0x07;
    }
    //z80.memory.memory[Z80_MEMORY_SIZE-1] = 0x76;    


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

    //z80_load(&z80, buf, size, 0x0000);
    


    cpu_print(&z80);

    while(1){
        char *input = (char*)malloc(sizeof(char)*257);
        

        printf(">> ");
        scanf("%s", input);
        
        if(input[0] != 'n' && input[0] != 'N' &&
            input[0] != 'r' && input[0] != 'R'){
            size_t numdigits = strlen(input) / 2;
            size_t i;
            for (i = 0; i != numdigits; ++i)
            {
                unsigned char output = 16 * toInt(input[2*i]) + toInt(input[2*i+1]);
                z80.memory.memory[i] = output;
                //printf("%x\n", output[i]);
            }


            z80.registers.PC = 0;
        }
        else if(input[0] == 'r' || input[0] == 'R'){
            run = 1;
        }
        free(input);

        do{    
            cls(hConsole);

            COORD pos = {0, 0};
            SetConsoleCursorPosition(hConsole, pos);

            cpu_exec(&z80);
            printf("%s", z80.last_op_desc);
            cpu_print(&z80);
            usleep(100 * 1000);
            //sleep(1);
        }while(((z80.registers.IFF & IFF_HALT) != IFF_HALT) && run);

        run = 0;
    }

}