static const unsigned char CyclesED[256] =
{
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  12,12,15,20, 8,14, 8, 9,12,12,15,20, 0,14, 0, 9,
  12,12,15,20, 0, 0, 8, 9,12,12,15,20, 0, 0, 8, 9,
  12,12,15,20, 0, 0, 0,18,12,12,15,20, 0, 0, 0,18,
  12, 0,15,20, 0, 0, 0, 0,12,12,15,20, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  16,16,16,16, 0, 0, 0, 0,16,16,16,16, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

#define M_IN(cpu, Rg)        \
  Rg = InZ80(cpu, cpu->registers.BC);  \
  SET_LSB(cpu->registers.AF, PZSTable[Rg] | (LSB(cpu->registers.AF) & C_FLAG))

  #define M_IN_H(cpu, Rg)        \
  SET_MSB(Rg, InZ80(cpu, cpu->registers.BC));  \
  SET_LSB(cpu->registers.AF, PZSTable[MSB(Rg)] | (LSB(cpu->registers.AF) & C_FLAG))
  
  #define M_IN_L(cpu, Rg)        \
  SET_LSB(Rg, InZ80(cpu, cpu->registers.BC));  \
  SET_LSB(cpu->registers.AF, PZSTable[LSB(Rg)] | (LSB(cpu->registers.AF) & C_FLAG))



static void z80_exec_extended_ED(struct z80* z80)
{
    unsigned char I; //register
    unsigned short J; //register

    I = OpZ80(z80, z80->registers.PC);
    unsigned char opcode = I;
    z80->ICount -= CyclesED[I];

    switch(I)
    {
        //#include "CodesED.h"
        case IN_A_xC:      debug_opcode(z80, "IN_A_xC", "A byte from port C is written to A");
            M_IN_H(z80, z80->registers.AF);break;
        case IN_B_xC:      debug_opcode(z80, "IN_B_xC", "A byte from port C is written to B");
            M_IN_H(z80, z80->registers.BC);break;
        case IN_C_xC:      debug_opcode(z80, "IN_C_xC", "A byte from port C is written to C");
            M_IN_L(z80, z80->registers.BC);break;
        case IN_D_xC:      debug_opcode(z80, "IN_D_xC", "A byte from port C is written to D");
            M_IN_H(z80, z80->registers.DE);break;
        case IN_E_xC:      debug_opcode(z80, "IN_E_xC", "A byte from port C is written to E");
            M_IN_L(z80, z80->registers.DE);break;
        case IN_H_xC:      debug_opcode(z80, "IN_H_xC", "A byte from port C is written to H");
            M_IN_H(z80, z80->registers.HL);break;
        case IN_L_xC:      debug_opcode(z80, "IN_L_xC", "A byte from port C is written to L");
            M_IN_L(z80, z80->registers.HL);break;
        case IN_F_xC:      debug_opcode(z80, "IN_F_xC", "A byte from port C is and affects flags only");
            M_IN_L(z80, J);break;

        case INI:      debug_opcode(z80, "INI", "A byte from port C is written to the memory pointed by HL. Then HL is incremented and B is decremented.");
            WrZ80(z80, z80->registers.HL, InZ80(z80, z80->registers.BC));
            z80->registers.HL += 1;
            SET_MSB(z80->registers.BC, MSB(z80->registers.BC)-1);
            SET_LSB(z80->registers.AF, N_FLAG | (MSB(z80->registers.BC) ? 0: Z_FLAG));
            break;

        case INIR:      debug_opcode(z80, "INIR", "A byte from port C is written to the memory pointed by HL. Then HL is incremented and B is decremented. If B is not zero, this operation is repeated. Interrupts can trigger while this instruction is processing.");
            do
            {
                WrZ80(z80, z80->registers.HL, InZ80(z80, z80->registers.BC));
                z80->registers.HL += 1;
                SET_MSB(z80->registers.BC, MSB(z80->registers.BC)-1);
                z80->ICount -= 21;
            }
            while(MSB(z80->registers.BC) != 0x0);//while(MSB(z80->registers.BC) && (z80->ICount > 0));
            
            if(MSB(z80->registers.BC)) {
                SET_LSB(z80->registers.AF, N_FLAG);
                // ???  z80->registers.PC -= 2; 
            }
            else {
                SET_LSB(z80->registers.AF, Z_FLAG | N_FLAG);
                z80->ICount += 5; 
            }
            break;

        case IND:      debug_opcode(z80, "INI", "A byte from port C is written to the memory pointed by HL. Then HL and B are decremented.");
            WrZ80(z80, z80->registers.HL, InZ80(z80, z80->registers.BC));
            z80->registers.HL -= 1;
            SET_MSB(z80->registers.BC, MSB(z80->registers.BC)-1);
            SET_LSB(z80->registers.AF, N_FLAG | (MSB(z80->registers.BC) ? 0: Z_FLAG));

            break;

        case INDR:      debug_opcode(z80, "INDR", "A byte from port C is written to the memory pointed by HL. Then HL and B are decremented. If B is not zero, this operation is repeated. Interrupts can trigger while this instruction is processing.");
            do
            {
                WrZ80(z80, z80->registers.HL, InZ80(z80, z80->registers.BC));
                z80->registers.HL -= 1;
                SET_MSB(z80->registers.BC, MSB(z80->registers.BC)-1);
                z80->ICount -= 21;
            }
            while(MSB(z80->registers.BC) != 0x0);//while(MSB(z80->registers.BC) && (z80->ICount > 0));
            
            if(MSB(z80->registers.BC)) {
                SET_LSB(z80->registers.AF, N_FLAG);
                // ???  z80->registers.PC -= 2; 
            }
            else {
                SET_LSB(z80->registers.AF, Z_FLAG | N_FLAG);
                z80->ICount += 5; 
            }
            break;


        case OUT_xC_A:      debug_opcode(z80, "OUT_xC_A", "The value of A is written to port C");
            OutZ80(z80, z80->registers.BC, MSB(z80->registers.AF));break;
        case OUT_xC_B:      debug_opcode(z80, "OUT_xC_B", "The value of B is written to port C");
            OutZ80(z80, z80->registers.BC, MSB(z80->registers.BC));break;
        case OUT_xC_C:      debug_opcode(z80, "OUT_xC_C", "The value of C is written to port C");
            OutZ80(z80, z80->registers.BC, LSB(z80->registers.BC));break;
        case OUT_xC_D:      debug_opcode(z80, "OUT_xC_D", "The value of D is written to port C");
            OutZ80(z80, z80->registers.BC, MSB(z80->registers.DE));break;
        case OUT_xC_E:      debug_opcode(z80, "OUT_xC_E", "The value of E is written to port C");
            OutZ80(z80, z80->registers.BC, LSB(z80->registers.DE));break;
        case OUT_xC_H:      debug_opcode(z80, "OUT_xC_H", "The value of H is written to port C");
            OutZ80(z80, z80->registers.BC, MSB(z80->registers.HL));break;
        case OUT_xC_L:      debug_opcode(z80, "OUT_xC_L", "The value of L is written to port C");
            OutZ80(z80, z80->registers.BC, LSB(z80->registers.HL));break;

        case OUTI:      debug_opcode(z80, "OUTI", "A byte from the memory location pointed to by HL is written to port C. Then HL is incremented and B is decremented.");
            SET_MSB(z80->registers.BC, z80->registers.BC - 1);
            I = RdZ80(z80, z80->registers.HL);
            z80->registers.HL += 1;
            OutZ80(z80, z80->registers.BC, I);
            SET_LSB(z80->registers.AF, N_FLAG | (MSB(z80->registers.BC) ? 0: Z_FLAG) | (LSB(z80->registers.HL) + I > 255 ? (C_FLAG | H_FLAG) : 0));
            break;

        case OUTD:      debug_opcode(z80, "OUTD", "A byte from the memory location pointed to by HL is written to port C. Then HL and B are decremented.");
            SET_MSB(z80->registers.BC, z80->registers.BC - 1);
            I = RdZ80(z80, z80->registers.HL);
            z80->registers.HL -= 1;
            OutZ80(z80, z80->registers.BC, I);
            SET_LSB(z80->registers.AF, N_FLAG | (MSB(z80->registers.BC) ? 0: Z_FLAG) | (LSB(z80->registers.HL) + I > 255 ? (C_FLAG | H_FLAG) : 0));
            break;
        
        case OTIR:      debug_opcode(z80, "OTIR", "A byte from the memory location pointed to by HL is written to port C. Then HL is incremented and B is decremented. If b is not zero, this operation is repeated. Interrupts can trigger while this instruction is processing.");
            do
            {
                SET_MSB(z80->registers.BC, z80->registers.BC - 1);
                I = RdZ80(z80, z80->registers.HL);
                z80->registers.HL += 1;
                OutZ80(z80, z80->registers.BC, I);
                z80->ICount -= 21;
            }
            while(MSB(z80->registers.BC) != 0x0);//while(MSB(z80->registers.BC) && (z80->ICount > 0));

            if(MSB(z80->registers.BC))
            {
                SET_LSB(z80->registers.AF, N_FLAG | (LSB(z80->registers.HL) + I > 255 ? (C_FLAG | H_FLAG) : 0));
                // ???  z80->registers.PC -= 2;
            }
            else
            {
                SET_LSB(z80->registers.AF, Z_FLAG | N_FLAG | (LSB(z80->registers.HL) + I > 255 ? (C_FLAG | H_FLAG) : 0));
                z80->ICount += 5;
            }
            break;

        case OTDR:      debug_opcode(z80, "OTDR", "A byte from the memory location pointed to by HL is written to port C. Then HL and B are decremented. If b is not zero, this operation is repeated. Interrupts can trigger while this instruction is processing.");
            do
            {
                SET_MSB(z80->registers.BC, z80->registers.BC - 1);
                I = RdZ80(z80, z80->registers.HL);
                z80->registers.HL -= 1;
                OutZ80(z80, z80->registers.BC, I);
                z80->ICount -= 21;
            }
            while(MSB(z80->registers.BC) != 0x0);//while(MSB(z80->registers.BC) && (z80->ICount > 0));

            if(MSB(z80->registers.BC))
            {
                SET_LSB(z80->registers.AF, N_FLAG | (LSB(z80->registers.HL) + I > 255 ? (C_FLAG | H_FLAG) : 0));
                // ???  z80->registers.PC -= 2;
            }
            else
            {
                SET_LSB(z80->registers.AF, Z_FLAG | N_FLAG | (LSB(z80->registers.HL) + I > 255 ? (C_FLAG | H_FLAG) : 0));
                z80->ICount += 5;
            }
            break;

        case NEG:      debug_opcode(z80, "NEG", "The contents of A are negated (two's complement). Operation is the same as subtracting A from zero.");
            I = MSB(z80->registers.AF);
            SET_MSB(z80->registers.AF, 0);
            M_SUB(z80, I);
            break;

        case SBC_HL_BC:      debug_opcode(z80, "SBC_HL_BC", "Subtracts BC and carry flag from HL."); 
            M_SBCW(z80, BC);break;
        case SBC_HL_DE:      debug_opcode(z80, "SBC_HL_DE", "Subtracts DE and carry flag from HL."); 
            M_SBCW(z80, DE);break;
        case SBC_HL_HL:      debug_opcode(z80, "SBC_HL_HL", "Subtracts HL and carry flag from HL."); 
            M_SBCW(z80, HL);break;
        case SBC_HL_SP:      debug_opcode(z80, "SBC_HL_SP", "Subtracts SP and carry flag from HL."); 
            M_SBCW(z80, SP);break;

        case LD_A_I:      debug_opcode(z80, "LD_A_I", "Stores the value of register I or R into A"); 
            SET_MSB(z80->registers.AF, z80->registers.I);
            SET_LSB(z80->registers.AF, (LSB(z80->registers.AF) & C_FLAG) | (z80->registers.IFF & IFF_2 ? P_FLAG : 0) | ZSTable[MSB(z80->registers.AF)]);
        break;

        case LD_A_R:      debug_opcode(z80, "LD_A_R", "Stores the value of register I or R into A"); 
            
            //z80->registers.R++;
            SET_MSB(z80->registers.AF, z80->registers.R);
            //SET_MSB(z80->registers.AF, (unsigned char)(z80->registers.R - z80->ICount));
            SET_LSB(z80->registers.AF, (LSB(z80->registers.AF) & C_FLAG) | (z80->registers.IFF & IFF_2 ? P_FLAG : 0) | ZSTable[MSB(z80->registers.AF)]);
        break;

        case LD_I_A:      debug_opcode(z80, "LD_I_A", "Stores the value of A into register I or R"); 
            z80->registers.I = MSB(z80->registers.AF);
            break;
        case LD_R_A:      debug_opcode(z80, "LD_R_A", "Stores the value of A into register I or R"); 
            z80->registers.R = MSB(z80->registers.AF);
            break;


        case LD_BC_xWORDe:      debug_opcode(z80, "LD_BC_xWORDe", "Loads the value pointed to by WORD into BC."); 
            M_LDWORD(z80, J); 
            SET_LSB(z80->registers.BC, RdZ80(z80, J));
            J += 1;
            SET_MSB(z80->registers.BC, RdZ80(z80, J));
            break;
        case LD_DE_xWORDe:      debug_opcode(z80, "LD_DE_xWORDe", "Loads the value pointed to by WORD into DE."); 
            M_LDWORD(z80, J); 
            SET_LSB(z80->registers.DE, RdZ80(z80, J));
            J += 1;
            SET_MSB(z80->registers.DE, RdZ80(z80, J));
            break;
        case LD_HL_xWORDe:      debug_opcode(z80, "LD_HL_xWORDe", "Loads the value pointed to by WORD into HL."); 
            M_LDWORD(z80, J); 
            SET_LSB(z80->registers.HL, RdZ80(z80, J));
            J += 1;
            SET_MSB(z80->registers.HL, RdZ80(z80, J));
            break;
        case LD_SP_xWORDe:      debug_opcode(z80, "LD_SP_xWORDe", "Loads the value pointed to by WORD into SP."); 
            M_LDWORD(z80, J); 
            SET_LSB(z80->registers.SP, RdZ80(z80, J));
            J += 1;
            SET_MSB(z80->registers.SP, RdZ80(z80, J));
            break;


        case LD_xWORDe_BC:      debug_opcode(z80, "LD_xWORDe_BC", "Stores BC into the memory location pointed to by WORD."); 
            M_LDWORD(z80, J); 
            WrZ80(z80, J, LSB(z80->registers.BC));
            J += 1;
            WrZ80(z80, J, MSB(z80->registers.BC));
            break;
        case LD_xWORDe_DE:      debug_opcode(z80, "LD_xWORDe_DE", "Stores DE into the memory location pointed to by WORD."); 
            M_LDWORD(z80, J); 
            WrZ80(z80, J, LSB(z80->registers.DE));
            J += 1;
            WrZ80(z80, J, MSB(z80->registers.DE));
            break;
        case LD_xWORDe_HL:      debug_opcode(z80, "LD_xWORDe_HL", "Stores HL into the memory location pointed to by WORD."); 
            M_LDWORD(z80, J); 
            WrZ80(z80, J, LSB(z80->registers.HL));
            J += 1;
            WrZ80(z80, J, MSB(z80->registers.HL));
            break;
        case LD_xWORDe_SP:      debug_opcode(z80, "LD_xWORDe_SP", "Stores SP into the memory location pointed to by WORD."); 
            M_LDWORD(z80, J); 
            WrZ80(z80, J, LSB(z80->registers.SP));
            J += 1;
            WrZ80(z80, J, MSB(z80->registers.SP));
            break;


        case LDI:      debug_opcode(z80, "LDI", "Transfers a byte of data from the memory location pointed to by HL to the memory location pointed to by DE. Then HL and DE are incremented and BC is decremented."); 
            WrZ80(z80, z80->registers.DE, RdZ80(z80, z80->registers.HL));
            z80->registers.DE += 1;
            z80->registers.HL += 1;
            z80->registers.BC -= 1;
            SET_LSB(z80->registers.AF, (LSB(z80->registers.AF) & ~(N_FLAG | H_FLAG | P_FLAG)) | (z80->registers.BC ? P_FLAG:0));
            break;

        case LDD:      debug_opcode(z80, "LDD", "Transfers a byte of data from the memory location pointed to by HL to the memory location pointed to by DE. Then HL, DE and BC are decremented."); 
            WrZ80(z80, z80->registers.DE, RdZ80(z80, z80->registers.HL));
            z80->registers.DE -= 1;
            z80->registers.HL -= 1;
            z80->registers.BC -= 1;
            SET_LSB(z80->registers.AF, (LSB(z80->registers.AF) & ~(N_FLAG | H_FLAG | P_FLAG)) | (z80->registers.BC ? P_FLAG:0));
        break;

        case LDIR:      debug_opcode(z80, "LDIR", "Transfers a byte of data from the memory location pointed to by HL to the memory location pointed to by DE. Then HL and DE are incremented and BC is decremented. If BC is not zero, this operation is repeated. Interrupts can trigger while this instruction is processing."); 
            do
            {
                WrZ80(z80, z80->registers.DE, RdZ80(z80, z80->registers.HL));
                z80->registers.DE += 1;
                z80->registers.HL += 1;
                z80->registers.BC -= 1;
                z80->ICount -= 21;
            }
            while(z80->registers.BC != 0x0);//while(z80->registers.BC && (z80->ICount > 0));

            SET_LSB(z80->registers.AF, LSB(z80->registers.AF) & ~(N_FLAG | H_FLAG | P_FLAG));
            if(z80->registers.BC) 
            { 
                SET_LSB(z80->registers.AF, LSB(z80->registers.AF) | N_FLAG);
                z80->registers.PC -= 2; 
            }
            else 
                z80->ICount += 5;
            break;

        case LDDR:      debug_opcode(z80, "LDDR", "Transfers a byte of data from the memory location pointed to by HL to the memory location pointed to by DE. Then HL, DE and BC are decremented. If BC is not zero, this operation is repeated. Interrupts can trigger while this instruction is processing."); 
            do
            {
                WrZ80(z80, z80->registers.DE, RdZ80(z80, z80->registers.HL));
                z80->registers.DE -= 1;
                z80->registers.HL -= 1;
                z80->registers.BC -= 1;
                z80->ICount -= 21;
            }
            while(z80->registers.BC != 0x0);//while(z80->registers.BC && (z80->ICount > 0));

            SET_LSB(z80->registers.AF, LSB(z80->registers.AF) & ~(N_FLAG | H_FLAG | P_FLAG));
            if(z80->registers.BC) 
            { 
                SET_LSB(z80->registers.AF, LSB(z80->registers.AF) | N_FLAG);
                z80->registers.PC -= 2; 
            }
            else 
                z80->ICount += 5;
            break;


        case RLD:      debug_opcode(z80, "RLD", "The contents of the low-order nibble of (HL) are copied to the high-order nibble of (HL). The previous contents are copied to the low-order nibble of A. The previous contents are copied to the low-order nibble of (HL)."); 
            I = RdZ80(z80, z80->registers.HL);
            SET_LSB(J, (I << 4) | (MSB(z80->registers.AF) & 0x0F));
            WrZ80(z80, z80->registers.HL, LSB(J));
            SET_MSB(z80->registers.AF, (I >> 4) | (MSB(z80->registers.AF) & 0xF0));
            SET_LSB(z80->registers.AF, PZSTable[MSB(z80->registers.AF)] | (LSB(z80->registers.AF) & C_FLAG));
            break;
        
        case RRD:      debug_opcode(z80, "RRD", "The contents of the low-order nibble of (HL) are copied to the low-order nibble of A. The previous contents are copied to the high-order nibble of (HL). The previous contents are copied to the low-order nibble of (HL)."); 
            I = RdZ80(z80, z80->registers.HL);
            SET_LSB(J, (I >> 4) | (MSB(z80->registers.AF) << 4));
            WrZ80(z80, z80->registers.HL, LSB(J));
            SET_MSB(z80->registers.AF, (I & 0x0F) | (MSB(z80->registers.AF) & 0xF0));
            SET_LSB(z80->registers.AF, PZSTable[MSB(z80->registers.AF)] | (LSB(z80->registers.AF) & C_FLAG));
        break;


        case ADC_HL_BC:      debug_opcode(z80, "ADC_HL_BC", "Adds BC and the carry flag to HL"); 
            M_ADCW(z80, BC);break;
        case ADC_HL_DE:      debug_opcode(z80, "ADC_HL_DE", "Adds DE and the carry flag to HL"); 
            M_ADCW(z80, DE);break;
        case ADC_HL_HL:      debug_opcode(z80, "ADC_HL_HL", "Adds HL and the carry flag to HL"); 
            M_ADCW(z80, HL);break;
        case ADC_HL_SP:      debug_opcode(z80, "ADC_HL_SP", "Adds SP and the carry flag to HL"); 
            M_ADCW(z80, SP);break;


        case IM_0:      debug_opcode(z80, "IM_0", "Set interrupt of mode 0."); 
            z80->registers.IFF &= ~(IFF_IM1 | IFF_IM2);
            break;
        case IM_1:      debug_opcode(z80, "IM_1", "Set interrupt of mode 1."); 
            z80->registers.IFF = (z80->registers.IFF & ~IFF_IM2) | IFF_IM1;
            break;
        case IM_2:      debug_opcode(z80, "IM_2", "Set interrupt of mode 2."); 
            z80->registers.IFF = (z80->registers.IFF & ~IFF_IM1) | IFF_IM2;
            break;

        case RETI:      debug_opcode(z80, "RETI", "used at the end of a maskable interrupt service routine. The top stack entry is popped into PC, and signals an I/O device that the interrupt has finished, allowing nested interrupts (not a consideration of the TI).");
        case RETN:      debug_opcode(z80, "RETN", "Used at the end of a non-maskable interrupt service routine (located at $0066) to pop stack entry into PC. The value of IFF2 is copied to IFF1 so that maskable interrupts are allowed to continue as before. NMIs are not enabled on the TI."); 
            if(z80->registers.IFF & IFF_2)
                z80->registers.IFF |= IFF_1;
            else
                z80->registers.IFF &= ~IFF_1;
            M_RET(z80);
        break;


        case CPI:      debug_opcode(z80, "CPI", "Compares the value of the memory location pointed to by HL with A. Then HL is incremented and BC is decremented.");
            I = RdZ80(z80, z80->registers.HL);
            z80->registers.HL += 1;
            SET_LSB(J, MSB(z80->registers.AF) - I);
            z80->registers.BC = z80->registers.BC - 1;
            SET_LSB(z80->registers.AF, 
                N_FLAG | (LSB(z80->registers.AF) & C_FLAG) | ZSTable[LSB(J)] |
                ((MSB(z80->registers.AF) ^ I ^ LSB(J)) & H_FLAG) | (z80->registers.BC ? P_FLAG : 0));
            break;

        case CPD:      debug_opcode(z80, "CPD", "Compares the value of the memory location pointed to by HL with A. Then HL is decremented and BC is decremented.");
            I = RdZ80(z80, z80->registers.HL);
            SET_LSB(J, MSB(z80->registers.AF) - I);
            SET_LSB(z80->registers.AF, 
                N_FLAG | (LSB(z80->registers.AF) & C_FLAG) | ZSTable[LSB(J)] |
                ((MSB(z80->registers.AF) ^ I ^ LSB(J)) & H_FLAG) | (z80->registers.BC ? P_FLAG : 0));
            z80->registers.HL -= 1;
            z80->registers.BC = z80->registers.BC - 1;
        break;

        case CPIR:      debug_opcode(z80, "CPIR", "Compares the value of the memory location pointed to by HL with A. Then HL is incremented and BC is decremented. If BC is not zero and Z is not set, this operation is repeated. Interrupts can trigger while this instruction is processing.");
            do
            {
                I = RdZ80(z80, z80->registers.HL);
                SET_LSB(J, MSB(z80->registers.AF) - I);
                SET_LSB(z80->registers.AF, 
                                N_FLAG | (LSB(z80->registers.AF) & C_FLAG) | ZSTable[LSB(J)] |
                                ((MSB(z80->registers.AF) ^ I ^ LSB(J)) & H_FLAG) | (z80->registers.BC ? P_FLAG : 0));
                
                z80->registers.HL += 1;
                z80->registers.BC = z80->registers.BC - 1;
                z80->ICount -= 21;
            }  
            while(z80->registers.BC != 0x0 && (LSB(z80->registers.AF) & Z_FLAG) == 0);//&& LSB(J) && (z80->ICount > 0)); //while(z80->registers.BC && LSB(J));

          /*
            
            if(z80->registers.BC && LSB(J))
                z80->registers.PC -= 2;
            else
                z80->ICount += 5;
                */
            break; 
        
        case CPDR:      debug_opcode(z80, "CPDR", "Compares the value of the memory location pointed to by HL with A. Then HL and BC are decremented. If BC is not zero and Z is not set, this operation is repeated. Interrupts can trigger while this instruction is processing.");
            do
            {
                I = RdZ80(z80, z80->registers.HL);                
                SET_LSB(J, MSB(z80->registers.AF) - I);
                SET_LSB(z80->registers.AF, 
                        N_FLAG | (LSB(z80->registers.AF) & C_FLAG) | ZSTable[LSB(J)] |
                        ((MSB(z80->registers.AF) ^ I ^ LSB(J)) & H_FLAG) | (z80->registers.BC ? P_FLAG : 0));
                
                z80->registers.HL -= 1;     
                z80->registers.BC = z80->registers.BC - 1;
                z80->ICount -= 21;
            }
            while(z80->registers.BC != 0x0 && (LSB(z80->registers.AF) & Z_FLAG) == 0);//&& LSB(J) && (z80->ICount > 0)); //while(z80->registers.BC && LSB(J));

            
            
            if(z80->registers.BC && LSB(J))
                z80->registers.PC -= 2;
            else
                z80->ICount += 5;
            break; 


        default:{
            char str2[20];
            sprintf(str2,"unknown 0x%x",opcode);
            debug_opcode(z80, str2,"");
             if(z80->TrapBadOps)
            printf
            (
                "[Z80 %lX] Unrecognized instruction: ED %02X at PC=%04X\n",
                (long)z80->User, OpZ80(z80, z80->registers.PC-1),z80->registers.PC-2
            );
        }

    }
}