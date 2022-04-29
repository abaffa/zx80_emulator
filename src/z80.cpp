#include "z80.h"
#include "z80_opcodes.h"
#include "byte_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#include "tasm_opcode.h"
#include "utils.h"

#include <unordered_map>
using namespace std;
unordered_map<string, Tasm_Opcode> ht_opcodes;
FILE *fa;

// Z80 OPCODES
//https://clrhome.org/table/
//http://z80-heaven.wikidot.com/opcode-reference-chart

//Z80 REGISTERS
//https://link.springer.com/chapter/10.1007/978-1-349-06957-6_5
//http://www.z80.info/z80arki.htm
//https://onlinetoolz.net/bitshift#base=16&value=20&bits=8&steps=1&dir=l&type=rtc&carry=1&allsteps=1

//ZX80 REF
//https://k1.spdns.de/Develop/Projects/zxsp-osx/Info/nocash%20Sinclair%20ZX%20Specs.html
//https://en.wikipedia.org/wiki/ZX80_character_set

#include "z80_tables.h"
#define WORD(l, h) (((h)<<8) | (l))
#define LSB(w) ((w) & 0xff)
#define MSB(w) (((w) >> 8) & 0xff)
#define SET_LSB(Rg, l) Rg = ((Rg & 0xFF00) | ((l) & 0xff))
#define SET_MSB(Rg, h) Rg = ((h)<<8) | (Rg & 0x00FF)
#define SET_WORD(Rg, l, h) Rg = WORD(l, h)




void Z80::z80_init()
{
	//memset(z80, 0, sizeof(struct z80));

	this->registers.PC = 0;
	//this->registers.PC = Z80_PROGRAM_LOAD_ADDRESS;

	char str_out[255];
	char buff[255];
	//	char buff2[255];
	FILE *fp;

	fp = fopen("tasm80.tab", "r");

	if (fp == NULL)
	{
		printf("Could not found tasm80.tab file!");
		exit(1);
	}

	while (fscanf(fp, "%255[^\n]%*c\n", buff) != EOF) {


		char _desc[50];
		char _opcode[50];
		char __size[50];
		int _size = 0;

		int col = 0;


		char *token = strtok(buff, "*\t");
		while (token != NULL) {

			if (col == 0)
				sprintf(_desc, "%s", token);

			else if (col == 1)
				sprintf(_opcode, "%s", token);

			else if (col == 2) {
				sprintf(__size, "%s", token);
				_size = atoi(__size);
			}
			col++;
			token = strtok(NULL, "*\t");
		}

		if (_size >= 1) {
			ht_opcodes[strlower(_opcode)] = Tasm_Opcode(_opcode, _desc, _size);
		}
	}

	fclose(fp);



	fa = fopen("debug_trace.log", "w");
	if (fa == NULL) {
		printf("can not open debug file\n");
		exit(1);
	}




}

void Z80::z80_reset()
{
	this->registers.AF = 0x0000;
	this->registers.BC = 0x0000;
	this->registers.DE = 0x0000;
	this->registers.HL = 0x0000;

	this->registers.AFl = 0x0000;
	this->registers.BCl = 0x0000;
	this->registers.DEl = 0x0000;
	this->registers.HLl = 0x0000;

	this->registers.IX = 0x0000;
	this->registers.IY = 0x0000;
	this->registers.SP = 0x0000;
	//this->registers.SP     = 0xF000;
	//this->registers.SP     = 0x00F0;

	this->registers.I = 0x00;
	this->registers.R = 0x00;

	this->registers.PC = 0x0000;

	this->registers.IFF = 0x00;

	this->IPeriod = 0;

	this->ICount = this->IPeriod;
	this->IRequest = INT_NONE;
	this->IBackup = 0;

	this->JumpZ80(this->registers.PC);

	this->PORT_FEFEh = 0xFF;
	this->PORT_FDFEh = 0xFF;
	this->PORT_FBFEh = 0xFF;
	this->PORT_F7FEh = 0xFF;
	this->PORT_EFFEh = 0xFF;
	this->PORT_DFFEh = 0xFF;
	this->PORT_BFFEh = 0xFF;
	this->PORT_7FFEh = 0xFF;

}





////


/////
unsigned char Z80::OpZ80(struct zx80_memory* zx80_memory, unsigned short A)
{
	unsigned char b = this->RdZ80(zx80_memory, A);   //(RAM[A>>13][A&0x1FFF]); 
	this->registers.PC++;
	return b;
}


unsigned char Z80::RdZ80(struct zx80_memory* zx80_memory, unsigned short Address) {
	unsigned short A = Address;
	if (A >= 0x8000)
		A = A - 0x8000;
	if (A >= 0x4000)
		A = ((A - 0x4000) % 0x400) + 0x4000;

	return  zx80_memory->memory[A];  //(RAM[A>>13][A&0x1FFF]); 
}

void Z80::WrZ80(struct zx80_memory* zx80_memory, unsigned short Address, unsigned char V)
{
	unsigned short A = Address;
	if (A >= 0x8000)
		A = A - 0x8000;
	if (A >= 0x4000)
		A = ((A - 0x4000) % 0x400) + 0x4000;
	zx80_memory->memory[A] = V;
}


void Z80::OutZ80(struct zx80_memory* zx80_memory, unsigned short Port, unsigned char Value) {
}

int cPORT_FEFEh = 0;
int cPORT_FDFEh = 0;
int cPORT_FBFEh = 0;
int cPORT_F7FEh = 0;
int cPORT_EFFEh = 0;
int cPORT_DFFEh = 0;
int cPORT_BFFEh = 0;
int cPORT_7FFEh = 0;
int lim_key = 2;

unsigned char Z80::InZ80(unsigned short Port) {

	unsigned char c = 0x7F;

	if (Port == 0xFEFE) {
		c = this->PORT_FEFEh;

#if SERVER_WEB == 1
		if (c < 0xFF && cPORT_FEFEh < 5) {
			cPORT_FEFEh++;

		}
		else if (c < 0xFF) {
			this->PORT_FEFEh = 0xFF;
			cPORT_FEFEh = 0;
		}
#endif	
}
	if (Port == 0xFDFE) {
		c = this->PORT_FDFEh;

#if SERVER_WEB == 1
		if (c < 0xFF && cPORT_FDFEh < lim_key) {
			cPORT_FDFEh++;
			
		}
		else if (c < 0xFF) {
 			this->PORT_FDFEh = 0xFF;
			cPORT_FDFEh = 0;
		}
#endif
}
	if (Port == 0xFBFE) {
		c = this->PORT_FBFEh;
#if SERVER_WEB == 1
		if (c < 0xFF && cPORT_FBFEh < lim_key) {
			cPORT_FBFEh++;

		}
		else if (c < 0xFF) {
			this->PORT_FBFEh = 0xFF;
			cPORT_FBFEh = 0;
		}
#endif	
	}


	if (Port == 0xF7FE) {
		c = this->PORT_F7FEh;
#if SERVER_WEB == 1
		if (c < 0xFF && cPORT_F7FEh < lim_key) {
			cPORT_F7FEh++;

		}
		else if (c < 0xFF) {
			this->PORT_F7FEh = 0xFF;
			cPORT_F7FEh = 0;
		}
#endif	
	}


	if (Port == 0xEFFE) {
		c = this->PORT_EFFEh;
#if SERVER_WEB == 1
		if (c < 0xFF && cPORT_EFFEh < lim_key) {
			cPORT_EFFEh++;

		}
		else if (c < 0xFF) {
			this->PORT_EFFEh = 0xFF;
			cPORT_EFFEh = 0;
		}
#endif	
	}


	if (Port == 0xDFFE) {
		c = this->PORT_DFFEh;
#if SERVER_WEB == 1
		if (c < 0xFF && cPORT_DFFEh < lim_key) {
			cPORT_DFFEh++;

		}
		else if (c < 0xFF) {
			this->PORT_DFFEh = 0xFF;
			cPORT_DFFEh = 0;
		}
#endif	
	}

	
	if (Port == 0xBFFE) {
		c = this->PORT_BFFEh;
#if SERVER_WEB == 1
		if (c < 0xFF && cPORT_BFFEh < lim_key) {
			cPORT_BFFEh++;

		}
		else if (c < 0xFF) {
			this->PORT_BFFEh = 0xFF;
			cPORT_BFFEh = 0;
		}
#endif	
	}
	
	
	if (Port == 0x7FFE) {
		c = this->PORT_7FFEh;
#if SERVER_WEB == 1
		if (c < 0xFF && cPORT_7FFEh < lim_key) {
			cPORT_7FFEh++;

		}
		else if (c < 0xFF) {
			this->PORT_7FFEh = 0xFF;
			cPORT_7FFEh = 0;
		}
#endif	
	}

	return c;
}

// ALU


void Z80::JumpZ80(unsigned short PC) {}


unsigned short Z80::LoopZ80() { return INT_NONE; }


void Z80::IntZ80(struct zx80_memory* zx80_memory, unsigned short Vector)
{
	/* If HALTed, take CPU off HALT instruction */
	if (this->registers.IFF & IFF_HALT) { this->registers.PC++; this->registers.IFF &= ~IFF_HALT; }

	if ((this->registers.IFF & IFF_1) || (Vector == INT_NMI))
	{
		/* Save PC on stack */
		M_PUSH(this, zx80_memory, PC);

		/* Automatically reset IRequest if needed */
		if (this->IAutoReset && (Vector == this->IRequest)) this->IRequest = INT_NONE;

		/* If it is NMI... */
		if (Vector == INT_NMI)
		{
			/* Clear IFF1 */
			this->registers.IFF &= ~(IFF_1 | IFF_EI);
			/* Jump to hardwired NMI vector */
			this->registers.PC = 0x0066;
			this->JumpZ80(0x0066);
			/* Done */
			return;
		}

		/* Further interrupts off */
		this->registers.IFF &= ~(IFF_1 | IFF_2 | IFF_EI);

		/* If in IM2 mode... */
		if (this->registers.IFF & IFF_IM2)
		{
			/* Make up the vector address */
			Vector = (Vector & 0xFF) | ((unsigned short)(this->registers.I) << 8);
			/* Read the vector */
			SET_LSB(this->registers.PC, this->RdZ80(zx80_memory, Vector++));
			SET_MSB(this->registers.PC, this->RdZ80(zx80_memory, Vector));
			this->JumpZ80(this->registers.PC);
			/* Done */
			return;
		}

		/* If in IM1 mode, just jump to hardwired IRQ vector */
		if (this->registers.IFF & IFF_IM1) {
			this->registers.PC = 0x0038;
			this->JumpZ80(0x0038);
			return;
		}

		/* If in IM0 mode... */

		/* Jump to a vector */
		switch (Vector)
		{
		case INT_RST00: this->registers.PC = 0x0000; this->JumpZ80(0x0000); break;
		case INT_RST08: this->registers.PC = 0x0008; this->JumpZ80(0x0008); break;
		case INT_RST10: this->registers.PC = 0x0010; this->JumpZ80(0x0010); break;
		case INT_RST18: this->registers.PC = 0x0018; this->JumpZ80(0x0018); break;
		case INT_RST20: this->registers.PC = 0x0020; this->JumpZ80(0x0020); break;
		case INT_RST28: this->registers.PC = 0x0028; this->JumpZ80(0x0028); break;
		case INT_RST30: this->registers.PC = 0x0030; this->JumpZ80(0x0030); break;
		case INT_RST38: this->registers.PC = 0x0038; this->JumpZ80(0x0038); break;
		}
	}
}



void Z80::debug_opcode(char *op, char *desc) {
	if (DEBUG_OPCODE == 1) {
		sprintf(this->last_op_desc, "opcode: %s\n%s\n\n", op, desc);
		//printf("%s", this->last_op_desc);

		//printf("opcode: %s\n", op);
		//printf("%s\n\n", desc);
	}
}

void Z80::debug_opcode_reg_word(struct zx80_memory* zx80_memory, char *op, char *desc) {
	if (DEBUG_OPCODE == 1) {
		sprintf(this->last_op_desc, "opcode: %s_%04x\n%s\n\n", op,
			WORD(zx80_memory->memory[this->registers.PC], zx80_memory->memory[this->registers.PC + 1]),
			desc);
		//printf("%s", this->last_op_desc);

		//printf("opcode: %s_%02x\n", op, WORD(this->memory.zx80_memory->memory[this->registers.PC], this->memory.zx80_memory->memory[this->registers.PC+1]));
		//printf("%s\n\n", desc);
	}
}

void Z80::debug_opcode_reg_byte(struct zx80_memory* zx80_memory, char *op, char *desc) {
	if (DEBUG_OPCODE == 1) {
		sprintf(this->last_op_desc, "opcode: %s_%02x\n%s\n\n", op,
			zx80_memory->memory[this->registers.PC],
			desc);
		//printf("%s", this->last_op_desc);

		//printf("opcode: %s_&01x\n", op, this->memory.zx80_memory->memory[this->registers.PC]);
		//printf("%s\n\n", desc);
	}
}
void Z80::debug_opcode_reg_byte_byte(struct zx80_memory* zx80_memory, char *op, char *desc) {
	if (DEBUG_OPCODE == 1) {
		sprintf(this->last_op_desc, "opcode: %s_%02x_%02x\n%s\n\n", op,
			zx80_memory->memory[this->registers.PC],
			zx80_memory->memory[this->registers.PC + 1],
			desc);
		//printf("%s", this->last_op_desc);

		//printf("opcode: %s_&01x\n", op, this->memory.zx80_memory->memory[this->registers.PC]);
		//printf("%s\n\n", desc);
	}
}



void Z80::disassembly_current_opcode(struct zx80_memory* zx80_memory, unsigned char current_opcode) {

	char temp[5];
	char line[255];
	unsigned short memADDR = this->registers.PC;

	if (current_opcode == 0xCB ||
		current_opcode == 0xED ||
		current_opcode == 0xDD ||
		current_opcode == 0xFD) {

		memADDR++;
		current_opcode = (((unsigned short)current_opcode) << 8) | RdZ80(zx80_memory, memADDR);
		sprintf(temp, "%04x", current_opcode);
	}
	else
		sprintf(temp, "%02x", current_opcode);



	if (ht_opcodes.find(temp) != ht_opcodes.end()) {
		Tasm_Opcode tt = ht_opcodes[temp];

		sprintf(line, "    %04x]\t%02x:%s", (int)(memADDR - (strlen(temp) / 2)), current_opcode, tt.desc.c_str());

		if (tt.size > 1) {

			int i = 0;
			int opcodesize = (strlen(temp) / 2) - 1;
			int param_size = tt.size - opcodesize;
			sprintf(line + strlen(line), " (");

			for (i = param_size - 2; i >= 0; i--) {
				if (i != param_size - 2)
					//sprintf(line + strlen(line), " %02x", this->cpu.get_current_memory()[memADDR + i]);
					sprintf(line + strlen(line), " %02x", this->RdZ80(zx80_memory, memADDR + i));

				else
					//sprintf(line + strlen(line), "%02x", this->cpu.get_current_memory()[memADDR + i]);
					sprintf(line + strlen(line), "%02x", this->RdZ80(zx80_memory, memADDR + i));
			}
			sprintf(line + strlen(line), ")");
		}

		if (current_opcode == 0xFE)
			sprintf(line + strlen(line), " - %x \'%c\'", MSB(this->registers.AF), MSB(this->registers.AF));

		sprintf(line + strlen(line), "\r\n");

		char str_out[255];
		save_to_log(str_out, fa, line);
		//this->hw_tty.print(str_out);
	}

}


#include "z80_exec_main_codes.h"
#include "z80_extended_code_CB.h"
#include "z80_extended_code_ED.h"
#include "z80_extended_code_DD.h"
#include "z80_extended_code_FD.h"


void Z80::z80_exec(struct zx80_memory* zx80_memory)
{
	unsigned char I; //register
	unsigned short J; //register

	/* Turn tracing on when reached trap address */
	//if(this->registers.PC == this->Trap) this->Trace=1;
	/* Call single-step debugger, exit if requested */
	//if(this->Trace) if(!DebugZ80(z80)) return(this->registers.PC);


	//unsigned char opcode = z80_memory_get(&this->memory, this->registers.PC);
	//this->registers.PC += 1;


	I = this->OpZ80(zx80_memory, this->registers.PC);
	if (this->registers.PC - 1 >= 0xC000 && I != 0x76) I = 0;
	if (DEBUG_LOG)
		this->disassembly_current_opcode(zx80_memory, I);

	unsigned char opcode = I;
	this->ICount -= Cycles[I];

	this->registers.R = (this->registers.R & 0x80) | ((this->registers.R + 1) & 0x7F);

	switch (opcode)
	{
	case PFX_CB: //Bit instructions (CB)
		this->registers.R = (this->registers.R & 0x80) | ((this->registers.R + 1) & 0x7F);
		/*
			this->debug_opcode("PFX_CB","Bit instructions (CB)");
			this->registers.PC--;
			this->registers.IFF |= IFF_HALT;
			this->IBackup = 0;
			this->registers.PC = 0;
			*/
		this->z80_exec_extended_CB(zx80_memory);
		break;
	case PFX_DD: //IX instructions (DD) ..... IX bit instructions (DDCB)
		this->registers.R = (this->registers.R & 0x80) | ((this->registers.R + 1) & 0x7F);
		/*
			this->debug_opcode("PFX_DD","IX instructions (DD) ..... IX bit instructions (DDCB)");
			this->registers.PC--;
			this->registers.IFF |= IFF_HALT;
			this->IBackup = 0;
			this->registers.PC = 0;
			*/
		this->z80_exec_extended_DD(zx80_memory);
		break;
	case PFX_ED: //Extended instructions (ED)
		this->registers.R = (this->registers.R & 0x80) | ((this->registers.R + 1) & 0x7F);
		/*
		this->debug_opcode("PFX_ED","Extended instructions (ED)");
		this->registers.PC--;
		this->registers.IFF |= IFF_HALT;
		this->IBackup = 0;
		this->registers.PC = 0;
		*/
		this->z80_exec_extended_ED(zx80_memory);
		break;
	case PFX_FD: //IY instructions (FD) ...... IY bit instructions (FDCB)
		this->registers.R = (this->registers.R & 0x80) | ((this->registers.R + 1) & 0x7F);
		/*
		this->debug_opcode("PFX_FD","IY instructions (FD) ...... IY bit instructions (FDCB)");
		this->registers.PC--;
		this->registers.IFF |= IFF_HALT;
		this->IBackup = 0;
		this->registers.PC = 0;
		*/
		this->z80_exec_extended_FD(zx80_memory);
		break;

	default: {
		this->z80_exec_main_code(opcode, zx80_memory);

	}
	}

	/* If cycle counter expired... */
	if (this->ICount <= 0 && 0)
	{
		/* If we have come after EI, get address from IRequest */
		/* Otherwise, get it from the loop handler             */
		if (this->registers.IFF & IFF_EI)
		{
			this->registers.IFF = (this->registers.IFF & ~IFF_EI) | IFF_1; /* Done with AfterEI state */
			this->ICount += this->IBackup - 1;       /* Restore the ICount      */

			/* Call periodic handler or set pending IRQ */
			if (this->ICount > 0) J = this->IRequest;
			else
			{
				J = this->LoopZ80();        /* Call periodic handler    */
				this->ICount += this->IPeriod; /* Reset the cycle counter  */
				if (J == INT_NONE) J = this->IRequest;  /* Pending IRQ */
			}
		}
		else
		{
			J = this->LoopZ80();          /* Call periodic handler    */
			this->ICount += this->IPeriod;   /* Reset the cycle counter  */
			if (J == INT_NONE) J = this->IRequest;    /* Pending IRQ */
		}

		if (J == INT_QUIT) return;// (this->registers.PC); /* Exit if INT_QUIT */
		if (J != INT_NONE)
			this->IntZ80(zx80_memory, J);   /* Int-pt if needed */
	}
}