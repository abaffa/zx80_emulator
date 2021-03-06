#ifndef Z80_H
#define Z80_H

#include "config.h"
#include "zx80_memory.h"
#include "z80_registers.h"
#include <stddef.h>




using namespace std;
                               /* LoopZ80() may return:      */
#define INT_RST00   0x00C7     /* RST 00h                    */
#define INT_RST08   0x00CF     /* RST 08h                    */
#define INT_RST10   0x00D7     /* RST 10h                    */
#define INT_RST18   0x00DF     /* RST 18h                    */
#define INT_RST20   0x00E7     /* RST 20h                    */
#define INT_RST28   0x00EF     /* RST 28h                    */
#define INT_RST30   0x00F7     /* RST 30h                    */
#define INT_RST38   0x00FF     /* RST 38h                    */
#define INT_IRQ     INT_RST38  /* Default IRQ opcode is FFh  */
#define INT_NMI     0xFFFD     /* Non-maskable interrupt     */
#define INT_NONE    0xFFFF     /* No interrupt required      */
#define INT_QUIT    0xFFFE     /* Exit the emulation         */

                               /* Bits in Z80 F register:    */
#define S_FLAG      0x80       /* 1: Result negative         */
#define Z_FLAG      0x40       /* 1: Result is zero          */
#define X2_FLAG     0x20       /* UNUSED BITS    */
#define H_FLAG      0x10       /* 1: Halfcarry/Halfborrow    */
#define X1_FLAG     0x08       /* UNUSED BITS    */
#define P_FLAG      0x04       /* 1: Result is even          */
#define V_FLAG      0x04       /* 1: Overflow occured        */
#define N_FLAG      0x02       /* 1: Subtraction occured     */
#define C_FLAG      0x01       /* 1: Carry/Borrow occured    */

#define IFF_1       0x01       /* IFF1 flip-flop             */
#define IFF_IM1     0x02       /* 1: IM1 mode                */
#define IFF_IM2     0x04       /* 1: IM2 mode                */
#define IFF_2       0x08       /* IFF2 flip-flop             */
#define IFF_EI      0x20       /* 1: EI pending              */
#define IFF_HALT    0x80       /* 1: CPU HALTed              */

class Z80
{
public:
    //struct zx80_memory memory;
    struct z80_registers registers;

	short IPeriod,ICount; /* Set IPeriod to number of CPU cycles */
                    /* between calls to LoopZ80()          */
	short IBackup;        /* Private, don't touch                */
    unsigned short IRequest;      /* Set to address of pending IRQ       */
    unsigned char IAutoReset;    /* Set to 1 to autom. reset IRequest   */
    unsigned char TrapBadOps;    /* Set to 1 to warn of illegal opcodes */
    unsigned short Trap;          /* Set Trap to address to trace from   */
    unsigned char Trace;         /* Set Trace=1 to start tracing        */
    long User;         /* Arbitrary user data (ID,RAM*,etc.)  */

    char last_op_desc[512];

    unsigned char PORT_FEFEh;// = 0x0;
    unsigned char PORT_FDFEh;// = 0x0;
    unsigned char PORT_FBFEh;// = 0x0;
    unsigned char PORT_F7FEh;// = 0x0;
    unsigned char PORT_EFFEh;// = 0x0;
    unsigned char PORT_DFFEh;// = 0x0;
    unsigned char PORT_BFFEh;// = 0x0;
    unsigned char PORT_7FFEh;// = 0x0;

	struct zx80_memory *zx80_memory;

	void z80_init();
	void z80_exec(struct zx80_memory* zx80_memory);
	void z80_reset();

	unsigned char RdZ80(struct zx80_memory* zx80_memory, unsigned short Address);
	void WrZ80(struct zx80_memory* zx80_memory, unsigned short Address, unsigned char V);

	void IntZ80(struct zx80_memory* zx80_memory, unsigned short Vector);
	void JumpZ80(unsigned short PC);

	unsigned char InZ80(unsigned short Port);

	//void OutZ80(unsigned short Port, unsigned char Value);
	void OutZ80(struct zx80_memory* zx80_memory, unsigned short Port, unsigned char Value);

private:
	unsigned char OpZ80(struct zx80_memory* zx80_memory, unsigned short A);
	unsigned short LoopZ80();

	void debug_opcode(char *op, char *desc);
	void debug_opcode_reg_word(struct zx80_memory* zx80_memory, char *op, char *desc);
	void debug_opcode_reg_byte(struct zx80_memory* zx80_memory, char *op, char *desc);
	void debug_opcode_reg_byte_byte(struct zx80_memory* zx80_memory, char *op, char *desc);
	void disassembly_current_opcode(struct zx80_memory* zx80_memory, unsigned char current_opcode);


	void z80_exec_main_code(unsigned char opcode, struct zx80_memory* zx80_memory);
	void z80_exec_extended_CB(struct zx80_memory* zx80_memory);
	void z80_exec_extended_DD(struct zx80_memory* zx80_memory);
	void z80_exec_extended_ED(struct zx80_memory* zx80_memory);
	void z80_exec_extended_FD(struct zx80_memory* zx80_memory);

	void z80_exec_extended_DDCB(struct zx80_memory* zx80_memory);
	void z80_exec_extended_FDCB(struct zx80_memory* zx80_memory);
};






#endif