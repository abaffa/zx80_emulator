static const unsigned char CyclesCB[256] =
{
   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
   8, 8, 8, 8, 8, 8,12, 8, 8, 8, 8, 8, 8, 8,12, 8,
   8, 8, 8, 8, 8, 8,12, 8, 8, 8, 8, 8, 8, 8,12, 8,
   8, 8, 8, 8, 8, 8,12, 8, 8, 8, 8, 8, 8, 8,12, 8,
   8, 8, 8, 8, 8, 8,12, 8, 8, 8, 8, 8, 8, 8,12, 8,
   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8,
   8, 8, 8, 8, 8, 8,15, 8, 8, 8, 8, 8, 8, 8,15, 8 
};


static void z80_exec_extended_CB(struct z80* z80)
{
    unsigned char I; //register

    I = OpZ80(z80, z80->registers.PC);
    unsigned char opcode = I;
    z80->ICount -= CyclesCB[I];

    switch(I)
    {
        case RLC_A:      debug_opcode(z80, "RLC_A", "The contents of A are rotated left one bit position. The content of bit 7 are copied to the carry flag and bit 0.");
            M_RLC_H(z80, z80->registers.AF); break; 
        case RLC_B:      debug_opcode(z80, "RLC_B", "The contents of B are rotated left one bit position. The content of bit 7 are copied to the carry flag and bit 0.");
            M_RLC_H(z80, z80->registers.BC); break;
        case RLC_C:      debug_opcode(z80, "RLC_C", "The contents of C are rotated left one bit position. The content of bit 7 are copied to the carry flag and bit 0.");
            M_RLC_L(z80, z80->registers.BC); break; 
        case RLC_D:      debug_opcode(z80, "RLC_D", "The contents of D are rotated left one bit position. The content of bit 7 are copied to the carry flag and bit 0.");
            M_RLC_H(z80, z80->registers.DE); break;
        case RLC_E:      debug_opcode(z80, "RLC_E", "The contents of E are rotated left one bit position. The content of bit 7 are copied to the carry flag and bit 0.");
            M_RLC_L(z80, z80->registers.DE); break; 
        case RLC_H:      debug_opcode(z80, "RLC_H", "The contents of H are rotated left one bit position. The content of bit 7 are copied to the carry flag and bit 0.");
            M_RLC_H(z80, z80->registers.HL); break;
        case RLC_L:      debug_opcode(z80, "RLC_L", "The contents of L are rotated left one bit position. The content of bit 7 are copied to the carry flag and bit 0.");
            M_RLC_L(z80, z80->registers.HL); break; 
        case RLC_xHL:      debug_opcode(z80, "RLC_xHL", "The contents of (HL) are rotated left one bit position. The content of bit 7 are copied to the carry flag and bit 0.");
            I = RdZ80(z80, z80->registers.HL); M_RLC(z80, I); WrZ80(z80,z80->registers.HL, I); break; 

        case RRC_A:      debug_opcode(z80, "RRC_A", "The contents of A are rotated right one bit position. The content of bit 0 are copied to the carry flag and bit 7.");
            M_RRC_H(z80, z80->registers.AF); break; 
        case RRC_B:      debug_opcode(z80, "RRC_B", "The contents of B are rotated right one bit position. The content of bit 0 are copied to the carry flag and bit 7.");
            M_RRC_H(z80, z80->registers.BC); break;
        case RRC_C:      debug_opcode(z80, "RRC_C", "The contents of C are rotated right one bit position. The content of bit 0 are copied to the carry flag and bit 7.");
            M_RRC_L(z80, z80->registers.BC); break; 
        case RRC_D:      debug_opcode(z80, "RRC_D", "The contents of D are rotated right one bit position. The content of bit 0 are copied to the carry flag and bit 7.");
            M_RRC_H(z80, z80->registers.DE); break;
        case RRC_E:      debug_opcode(z80, "RRC_E", "The contents of E are rotated right one bit position. The content of bit 0 are copied to the carry flag and bit 7.");
            M_RRC_L(z80, z80->registers.DE); break; 
        case RRC_H:      debug_opcode(z80, "RRC_H", "The contents of H are rotated right one bit position. The content of bit 0 are copied to the carry flag and bit 7.");
            M_RRC_H(z80, z80->registers.HL); break;
        case RRC_L:      debug_opcode(z80, "RRC_L", "The contents of L are rotated right one bit position. The content of bit 0 are copied to the carry flag and bit 7.");
            M_RRC_L(z80, z80->registers.HL); break; 
        case RRC_xHL:      debug_opcode(z80, "RRC_xHL", "The contents of (HL) are rotated right one bit position. The content of bit 0 are copied to the carry flag and bit 7.");
            I = RdZ80(z80, z80->registers.HL); M_RRC(z80, I); WrZ80(z80,z80->registers.HL, I); break; 

        case RL_A:      debug_opcode(z80, "RL_A", "The contents of A are rotated left one bit position. The content of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.");
            M_RL_H(z80, z80->registers.AF); break; 
        case RL_B:      debug_opcode(z80, "RL_B", "The contents of B are rotated left one bit position. The content of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.");
            M_RL_H(z80, z80->registers.BC); break;
        case RL_C:      debug_opcode(z80, "RL_C", "The contents of C are rotated left one bit position. The content of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.");
            M_RL_L(z80, z80->registers.BC); break; 
        case RL_D:      debug_opcode(z80, "RL_D", "The contents of D are rotated left one bit position. The content of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.");
            M_RL_H(z80, z80->registers.DE); break;
        case RL_E:      debug_opcode(z80, "RL_E", "The contents of E are rotated left one bit position. The content of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.");
            M_RL_L(z80, z80->registers.DE); break; 
        case RL_H:      debug_opcode(z80, "RL_H", "The contents of H are rotated left one bit position. The content of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.");
            M_RL_H(z80, z80->registers.HL); break;
        case RL_L:      debug_opcode(z80, "RL_L", "The contents of L are rotated left one bit position. The content of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.");
            M_RL_L(z80, z80->registers.HL); break; 
        case RL_xHL:      debug_opcode(z80, "RL_xHL", "The contents of (HL) are rotated left one bit position. The content of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.");
            I = RdZ80(z80, z80->registers.HL); M_RL(z80, I); WrZ80(z80,z80->registers.HL, I); break; 

        case RR_A:      debug_opcode(z80, "RR_A", "The contents of A are rotated right one bit position. The content of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.");
            M_RR_H(z80, z80->registers.AF); break; 
        case RR_B:      debug_opcode(z80, "RR_B", "The contents of B are rotated right one bit position. The content of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.");
            M_RR_H(z80, z80->registers.BC); break;
        case RR_C:      debug_opcode(z80, "RR_C", "The contents of C are rotated right one bit position. The content of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.");
            M_RR_L(z80, z80->registers.BC); break; 
        case RR_D:      debug_opcode(z80, "RR_D", "The contents of D are rotated right one bit position. The content of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.");
            M_RR_H(z80, z80->registers.DE); break;
        case RR_E:      debug_opcode(z80, "RR_E", "The contents of E are rotated right one bit position. The content of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.");
            M_RR_L(z80, z80->registers.DE); break; 
        case RR_H:      debug_opcode(z80, "RR_H", "The contents of H are rotated right one bit position. The content of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.");
            M_RR_H(z80, z80->registers.HL); break;
        case RR_L:      debug_opcode(z80, "RR_L", "The contents of L are rotated right one bit position. The content of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.");
            M_RR_L(z80, z80->registers.HL); break; 
        case RR_xHL:      debug_opcode(z80, "RR_xHL", "The contents of (HL) are rotated right one bit position. The content of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.");
            I = RdZ80(z80, z80->registers.HL); M_RR(z80, I); WrZ80(z80,z80->registers.HL, I); break; 

        case SLA_A:      debug_opcode(z80, "SLA_A", "The contents of A are shifted left one bit position. The content of bit 7 are copied to the carry flag and a zero is put into bit 0.");
            M_SLA_H(z80, z80->registers.AF); break; 
        case SLA_B:      debug_opcode(z80, "SLA_B", "The contents of B are shifted left one bit position. The content of bit 7 are copied to the carry flag and a zero is put into bit 0.");
            M_SLA_H(z80, z80->registers.BC); break;
        case SLA_C:      debug_opcode(z80, "SLA_C", "The contents of C are shifted left one bit position. The content of bit 7 are copied to the carry flag and a zero is put into bit 0.");
            M_SLA_L(z80, z80->registers.BC); break; 
        case SLA_D:      debug_opcode(z80, "SLA_D", "The contents of D are shifted left one bit position. The content of bit 7 are copied to the carry flag and a zero is put into bit 0.");
            M_SLA_H(z80, z80->registers.DE); break;
        case SLA_E:      debug_opcode(z80, "SLA_E", "The contents of E are shifted left one bit position. The content of bit 7 are copied to the carry flag and a zero is put into bit 0.");
            M_SLA_L(z80, z80->registers.DE); break; 
        case SLA_H:      debug_opcode(z80, "SLA_H", "The contents of H are shifted left one bit position. The content of bit 7 are copied to the carry flag and a zero is put into bit 0.");
            M_SLA_H(z80, z80->registers.HL); break;
        case SLA_L:      debug_opcode(z80, "SLA_L", "The contents of L are shifted left one bit position. The content of bit 7 are copied to the carry flag and a zero is put into bit 0.");
            M_SLA_L(z80, z80->registers.HL); break; 
        case SLA_xHL:      debug_opcode(z80, "SLA_xHL", "The contents of (HL) are shifted left one bit position. The content of bit 7 are copied to the carry flag and a zero is put into bit 0.");
            I = RdZ80(z80, z80->registers.HL); M_SLA(z80, I); WrZ80(z80,z80->registers.HL, I); break; 

        case SRA_A:      debug_opcode(z80, "SRA_A", "The contents of A are shifted right one bit position. The content of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.");
            M_SRA_H(z80, z80->registers.AF); break; 
        case SRA_B:      debug_opcode(z80, "SRA_B", "The contents of B are shifted right one bit position. The content of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.");
            M_SRA_H(z80, z80->registers.BC); break;
        case SRA_C:      debug_opcode(z80, "SRA_C", "The contents of C are shifted right one bit position. The content of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.");
            M_SRA_L(z80, z80->registers.BC); break; 
        case SRA_D:      debug_opcode(z80, "SRA_D", "The contents of D are shifted right one bit position. The content of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.");
            M_SRA_H(z80, z80->registers.DE); break;
        case SRA_E:      debug_opcode(z80, "SRA_E", "The contents of E are shifted right one bit position. The content of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.");
            M_SRA_L(z80, z80->registers.DE); break; 
        case SRA_H:      debug_opcode(z80, "SRA_H", "The contents of H are shifted right one bit position. The content of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.");
            M_SRA_H(z80, z80->registers.HL); break;
        case SRA_L:      debug_opcode(z80, "SRA_L", "The contents of L are shifted right one bit position. The content of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.");
            M_SRA_L(z80, z80->registers.HL); break; 
        case SRA_xHL:      debug_opcode(z80, "SRA_xHL", "The contents of (HL) are shifted right one bit position. The content of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.");
            I = RdZ80(z80, z80->registers.HL); M_SRA(z80, I); WrZ80(z80,z80->registers.HL, I); break; 

        case SLL_A:      debug_opcode(z80, "SLL_A", "The contents of A are shifted left one bit position. The content of bit 7 are put into the carry flag and a one is put into bit 0.");
            M_SLL_H(z80, z80->registers.AF); break; 
        case SLL_B:      debug_opcode(z80, "SLL_B", "The contents of B are shifted left one bit position. The content of bit 7 are put into the carry flag and a one is put into bit 0.");
            M_SLL_H(z80, z80->registers.BC); break;
        case SLL_C:      debug_opcode(z80, "SLL_C", "The contents of C are shifted left one bit position. The content of bit 7 are put into the carry flag and a one is put into bit 0.");
            M_SLL_L(z80, z80->registers.BC); break; 
        case SLL_D:      debug_opcode(z80, "SLL_D", "The contents of D are shifted left one bit position. The content of bit 7 are put into the carry flag and a one is put into bit 0.");
            M_SLL_H(z80, z80->registers.DE); break;
        case SLL_E:      debug_opcode(z80, "SLL_E", "The contents of E are shifted left one bit position. The content of bit 7 are put into the carry flag and a one is put into bit 0.");
            M_SLL_L(z80, z80->registers.DE); break; 
        case SLL_H:      debug_opcode(z80, "SLL_H", "The contents of H are shifted left one bit position. The content of bit 7 are put into the carry flag and a one is put into bit 0.");
            M_SLL_H(z80, z80->registers.HL); break;
        case SLL_L:      debug_opcode(z80, "SLL_L", "The contents of L are shifted left one bit position. The content of bit 7 are put into the carry flag and a one is put into bit 0.");
            M_SLL_L(z80, z80->registers.HL); break; 
        case SLL_xHL:      debug_opcode(z80, "SLL_xHL", "The contents of (HL) are shifted left one bit position. The content of bit 7 are put into the carry flag and a one is put into bit 0.");
            I = RdZ80(z80, z80->registers.HL); M_SLL(z80, I); WrZ80(z80,z80->registers.HL, I); break; 

        case SRL_A:      debug_opcode(z80, "SRL_A", "The contents of A are shifted right one bit position. The content of bit 0 are copied to the carry flag and a zero is put into bit 7.");
            M_SRL_H(z80, z80->registers.AF); break; 
        case SRL_B:      debug_opcode(z80, "SRL_B", "The contents of B are shifted right one bit position. The content of bit 0 are copied to the carry flag and a zero is put into bit 7.");
            M_SRL_H(z80, z80->registers.BC); break;
        case SRL_C:      debug_opcode(z80, "SRL_C", "The contents of C are shifted right one bit position. The content of bit 0 are copied to the carry flag and a zero is put into bit 7.");
            M_SRL_L(z80, z80->registers.BC); break; 
        case SRL_D:      debug_opcode(z80, "SRL_D", "The contents of D are shifted right one bit position. The content of bit 0 are copied to the carry flag and a zero is put into bit 7.");
            M_SRL_H(z80, z80->registers.DE); break;
        case SRL_E:      debug_opcode(z80, "SRL_E", "The contents of E are shifted right one bit position. The content of bit 0 are copied to the carry flag and a zero is put into bit 7.");
            M_SRL_L(z80, z80->registers.DE); break; 
        case SRL_H:      debug_opcode(z80, "SRL_H", "The contents of H are shifted right one bit position. The content of bit 0 are copied to the carry flag and a zero is put into bit 7.");
            M_SRL_H(z80, z80->registers.HL); break;
        case SRL_L:      debug_opcode(z80, "SRL_L", "The contents of L are shifted right one bit position. The content of bit 0 are copied to the carry flag and a zero is put into bit 7.");
            M_SRL_L(z80, z80->registers.HL); break; 
        case SRL_xHL:      debug_opcode(z80, "SRL_xHL", "The contents of (HL) are shifted right one bit position. The content of bit 0 are copied to the carry flag and a zero is put into bit 7.");
            I = RdZ80(z80, z80->registers.HL); M_SRL(z80, I); WrZ80(z80,z80->registers.HL, I); break; 

        case BIT0_A:      debug_opcode(z80, "BIT0_A", "Test bit 0 of A");
            M_BIT(z80, 0, MSB(z80->registers.AF)); break;
        case BIT0_B:      debug_opcode(z80, "BIT0_B", "Test bit 0 of B");
            M_BIT(z80, 0, MSB(z80->registers.BC)); break;
        case BIT0_C:      debug_opcode(z80, "BIT0_C", "Test bit 0 of C");
            M_BIT(z80, 0, LSB(z80->registers.BC)); break;
        case BIT0_D:      debug_opcode(z80, "BIT0_D", "Test bit 0 of D");
            M_BIT(z80, 0, MSB(z80->registers.DE)); break;
        case BIT0_E:      debug_opcode(z80, "BIT0_E", "Test bit 0 of E");
            M_BIT(z80, 0, LSB(z80->registers.DE)); break;
        case BIT0_H:      debug_opcode(z80, "BIT0_H", "Test bit 0 of H");
            M_BIT(z80, 0, MSB(z80->registers.HL)); break;
        case BIT0_L:      debug_opcode(z80, "BIT0_L", "Test bit 0 of L");
            M_BIT(z80, 0, LSB(z80->registers.HL)); break;
        case BIT0_xHL:      debug_opcode(z80, "BIT0_xHL", "Test bit 0 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_BIT(z80, 0, I); break; 

        case BIT1_A:      debug_opcode(z80, "BIT1_A", "Test bit 1 of A");
            M_BIT(z80, 1, MSB(z80->registers.AF)); break;
        case BIT1_B:      debug_opcode(z80, "BIT1_B", "Test bit 1 of B");
            M_BIT(z80, 1, MSB(z80->registers.BC)); break;
        case BIT1_C:      debug_opcode(z80, "BIT1_C", "Test bit 1 of C");
            M_BIT(z80, 1, LSB(z80->registers.BC)); break;
        case BIT1_D:      debug_opcode(z80, "BIT1_D", "Test bit 1 of D");
            M_BIT(z80, 1, MSB(z80->registers.DE)); break;
        case BIT1_E:      debug_opcode(z80, "BIT1_E", "Test bit 1 of E");
            M_BIT(z80, 1, LSB(z80->registers.DE)); break;
        case BIT1_H:      debug_opcode(z80, "BIT1_H", "Test bit 1 of H");
            M_BIT(z80, 1, MSB(z80->registers.HL)); break;
        case BIT1_L:      debug_opcode(z80, "BIT1_L", "Test bit 1 of L");
            M_BIT(z80, 1, LSB(z80->registers.HL)); break;
        case BIT1_xHL:      debug_opcode(z80, "BIT1_xHL", "Test bit 1 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_BIT(z80, 1, I); break; 
    
        case BIT2_A:      debug_opcode(z80, "BIT2_A", "Test bit 2 of A");
            M_BIT(z80, 2, MSB(z80->registers.AF)); break;
        case BIT2_B:      debug_opcode(z80, "BIT2_B", "Test bit 2 of B");
            M_BIT(z80, 2, MSB(z80->registers.BC)); break;
        case BIT2_C:      debug_opcode(z80, "BIT2_C", "Test bit 2 of C");
            M_BIT(z80, 2, LSB(z80->registers.BC)); break;
        case BIT2_D:      debug_opcode(z80, "BIT2_D", "Test bit 2 of D");
            M_BIT(z80, 2, MSB(z80->registers.DE)); break;
        case BIT2_E:      debug_opcode(z80, "BIT2_E", "Test bit 2 of E");
            M_BIT(z80, 2, LSB(z80->registers.DE)); break;
        case BIT2_H:      debug_opcode(z80, "BIT2_H", "Test bit 2 of H");
            M_BIT(z80, 2, MSB(z80->registers.HL)); break;
        case BIT2_L:      debug_opcode(z80, "BIT2_L", "Test bit 2 of L");
            M_BIT(z80, 2, LSB(z80->registers.HL)); break;
        case BIT2_xHL:      debug_opcode(z80, "BIT2_xHL", "Test bit 2 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_BIT(z80, 2, I); break; 

        case BIT3_A:      debug_opcode(z80, "BIT3_A", "Test bit 3 of A");
            M_BIT(z80, 3, MSB(z80->registers.AF)); break;
        case BIT3_B:      debug_opcode(z80, "BIT3_B", "Test bit 3 of B");
            M_BIT(z80, 3, MSB(z80->registers.BC)); break;
        case BIT3_C:      debug_opcode(z80, "BIT3_C", "Test bit 3 of C");
            M_BIT(z80, 3, LSB(z80->registers.BC)); break;
        case BIT3_D:      debug_opcode(z80, "BIT3_D", "Test bit 3 of D");
            M_BIT(z80, 3, MSB(z80->registers.DE)); break;
        case BIT3_E:      debug_opcode(z80, "BIT3_E", "Test bit 3 of E");
            M_BIT(z80, 3, LSB(z80->registers.DE)); break;
        case BIT3_H:      debug_opcode(z80, "BIT3_H", "Test bit 3 of H");
            M_BIT(z80, 3, MSB(z80->registers.HL)); break;
        case BIT3_L:      debug_opcode(z80, "BIT3_L", "Test bit 3 of L");
            M_BIT(z80, 3, LSB(z80->registers.HL)); break;
        case BIT3_xHL:      debug_opcode(z80, "BIT3_xHL", "Test bit 3 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_BIT(z80, 3, I); break; 

        case BIT4_A:      debug_opcode(z80, "BIT4_A", "Test bit 4 of A");
            M_BIT(z80, 4, MSB(z80->registers.AF)); break;
        case BIT4_B:      debug_opcode(z80, "BIT4_B", "Test bit 4 of B");
            M_BIT(z80, 4, MSB(z80->registers.BC)); break;
        case BIT4_C:      debug_opcode(z80, "BIT4_C", "Test bit 4 of C");
            M_BIT(z80, 4, LSB(z80->registers.BC)); break;
        case BIT4_D:      debug_opcode(z80, "BIT4_D", "Test bit 4 of D");
            M_BIT(z80, 4, MSB(z80->registers.DE)); break;
        case BIT4_E:      debug_opcode(z80, "BIT4_E", "Test bit 4 of E");
            M_BIT(z80, 4, LSB(z80->registers.DE)); break;
        case BIT4_H:      debug_opcode(z80, "BIT4_H", "Test bit 4 of H");
            M_BIT(z80, 4, MSB(z80->registers.HL)); break;
        case BIT4_L:      debug_opcode(z80, "BIT4_L", "Test bit 4 of L");
            M_BIT(z80, 4, LSB(z80->registers.HL)); break;
        case BIT4_xHL:      debug_opcode(z80, "BIT4_xHL", "Test bit 4 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_BIT(z80, 4, I); break; 
    
        case BIT5_A:      debug_opcode(z80, "BIT5_A", "Test bit 5 of A");
            M_BIT(z80, 5, MSB(z80->registers.AF)); break;
        case BIT5_B:      debug_opcode(z80, "BIT5_B", "Test bit 5 of B");
            M_BIT(z80, 5, MSB(z80->registers.BC)); break;
        case BIT5_C:      debug_opcode(z80, "BIT5_C", "Test bit 5 of C");
            M_BIT(z80, 5, LSB(z80->registers.BC)); break;
        case BIT5_D:      debug_opcode(z80, "BIT5_D", "Test bit 5 of D");
            M_BIT(z80, 5, MSB(z80->registers.DE)); break;
        case BIT5_E:      debug_opcode(z80, "BIT5_E", "Test bit 5 of E");
            M_BIT(z80, 5, LSB(z80->registers.DE)); break;
        case BIT5_H:      debug_opcode(z80, "BIT5_H", "Test bit 5 of H");
            M_BIT(z80, 5, MSB(z80->registers.HL)); break;
        case BIT5_L:      debug_opcode(z80, "BIT5_L", "Test bit 5 of L");
            M_BIT(z80, 5, LSB(z80->registers.HL)); break;
        case BIT5_xHL:      debug_opcode(z80, "BIT5_xHL", "Test bit 5 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_BIT(z80, 5, I); break; 

        case BIT6_A:      debug_opcode(z80, "BIT6_A", "Test bit 6 of A");
            M_BIT(z80, 6, MSB(z80->registers.AF)); break;
        case BIT6_B:      debug_opcode(z80, "BIT6_B", "Test bit 6 of B");
            M_BIT(z80, 6, MSB(z80->registers.BC)); break;
        case BIT6_C:      debug_opcode(z80, "BIT6_C", "Test bit 6 of C");
            M_BIT(z80, 6, LSB(z80->registers.BC)); break;
        case BIT6_D:      debug_opcode(z80, "BIT6_D", "Test bit 6 of D");
            M_BIT(z80, 6, MSB(z80->registers.DE)); break;
        case BIT6_E:      debug_opcode(z80, "BIT6_E", "Test bit 6 of E");
            M_BIT(z80, 6, LSB(z80->registers.DE)); break;
        case BIT6_H:      debug_opcode(z80, "BIT6_H", "Test bit 6 of H");
            M_BIT(z80, 6, MSB(z80->registers.HL)); break;
        case BIT6_L:      debug_opcode(z80, "BIT6_L", "Test bit 6 of L");
            M_BIT(z80, 6, LSB(z80->registers.HL)); break;
        case BIT6_xHL:      debug_opcode(z80, "BIT6_xHL", "Test bit 6 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_BIT(z80, 6, I); break; 

        case BIT7_A:      debug_opcode(z80, "BIT7_A", "Test bit 7 of A");
            M_BIT(z80, 7, MSB(z80->registers.AF)); break;
        case BIT7_B:      debug_opcode(z80, "BIT7_B", "Test bit 7 of B");
            M_BIT(z80, 7, MSB(z80->registers.BC)); break;
        case BIT7_C:      debug_opcode(z80, "BIT7_C", "Test bit 7 of C");
            M_BIT(z80, 7, LSB(z80->registers.BC)); break;
        case BIT7_D:      debug_opcode(z80, "BIT7_D", "Test bit 7 of D");
            M_BIT(z80, 7, MSB(z80->registers.DE)); break;
        case BIT7_E:      debug_opcode(z80, "BIT7_E", "Test bit 7 of E");
            M_BIT(z80, 7, LSB(z80->registers.DE)); break;
        case BIT7_H:      debug_opcode(z80, "BIT7_H", "Test bit 7 of H");
            M_BIT(z80, 7, MSB(z80->registers.HL)); break;
        case BIT7_L:      debug_opcode(z80, "BIT7_L", "Test bit 7 of L");
            M_BIT(z80, 7, LSB(z80->registers.HL)); break;
        case BIT7_xHL:      debug_opcode(z80, "BIT7_xHL", "Test bit 7 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_BIT(z80, 7, I); break; 


        case SET0_A:      debug_opcode(z80, "SET0_A", "Set bit 0 of A");
            M_SET_H(z80, 0, z80->registers.AF); break;
        case SET0_B:      debug_opcode(z80, "SET0_B", "Set bit 0 of B");
            M_SET_H(z80, 0, z80->registers.BC); break;
        case SET0_C:      debug_opcode(z80, "SET0_C", "Set bit 0 of C");
            M_SET_L(z80, 0, z80->registers.BC); break;
        case SET0_D:      debug_opcode(z80, "SET0_D", "Set bit 0 of D");
            M_SET_H(z80, 0, z80->registers.DE); break;
        case SET0_E:      debug_opcode(z80, "SET0_E", "Set bit 0 of E");
            M_SET_L(z80, 0, z80->registers.DE); break;
        case SET0_H:      debug_opcode(z80, "SET0_H", "Set bit 0 of H");
            M_SET_H(z80, 0, z80->registers.HL); break;
        case SET0_L:      debug_opcode(z80, "SET0_L", "Set bit 0 of L");
            M_SET_L(z80, 0, z80->registers.HL); break;
        case SET0_xHL:      debug_opcode(z80, "SET0_xHL", "Set bit 0 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_SET(z80, 0, I); WrZ80(z80,z80->registers.HL, I); break; 
        
        case SET1_A:      debug_opcode(z80, "SET1_A", "Set bit 1 of A");
            M_SET_H(z80, 1, z80->registers.AF); break;
        case SET1_B:      debug_opcode(z80, "SET1_B", "Set bit 1 of B");
            M_SET_H(z80, 1, z80->registers.BC); break;
        case SET1_C:      debug_opcode(z80, "SET1_C", "Set bit 1 of C");
            M_SET_L(z80, 1, z80->registers.BC); break;
        case SET1_D:      debug_opcode(z80, "SET1_D", "Set bit 1 of D");
            M_SET_H(z80, 1, z80->registers.DE); break;
        case SET1_E:      debug_opcode(z80, "SET1_E", "Set bit 1 of E");
            M_SET_L(z80, 1, z80->registers.DE); break;
        case SET1_H:      debug_opcode(z80, "SET1_H", "Set bit 1 of H");
            M_SET_H(z80, 1, z80->registers.HL); break;
        case SET1_L:      debug_opcode(z80, "SET1_L", "Set bit 1 of L");
            M_SET_L(z80, 1, z80->registers.HL); break;
        case SET1_xHL:      debug_opcode(z80, "SET1_xHL", "Set bit 1 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_SET(z80, 1, I); WrZ80(z80,z80->registers.HL, I); break; 
        
        case SET2_A:      debug_opcode(z80, "SET2_A", "Set bit 2 of A");
            M_SET_H(z80, 2, z80->registers.AF); break;
        case SET2_B:      debug_opcode(z80, "SET2_B", "Set bit 2 of B");
            M_SET_H(z80, 2, z80->registers.BC); break;
        case SET2_C:      debug_opcode(z80, "SET2_C", "Set bit 2 of C");
            M_SET_L(z80, 2, z80->registers.BC); break;
        case SET2_D:      debug_opcode(z80, "SET2_D", "Set bit 2 of D");
            M_SET_H(z80, 2, z80->registers.DE); break;
        case SET2_E:      debug_opcode(z80, "SET2_E", "Set bit 2 of E");
            M_SET_L(z80, 2, z80->registers.DE); break;
        case SET2_H:      debug_opcode(z80, "SET2_H", "Set bit 2 of H");
            M_SET_H(z80, 2, z80->registers.HL); break;
        case SET2_L:      debug_opcode(z80, "SET2_L", "Set bit 2 of L");
            M_SET_L(z80, 2, z80->registers.HL); break;
        case SET2_xHL:      debug_opcode(z80, "SET2_xHL", "Set bit 2 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_SET(z80, 2, I); WrZ80(z80,z80->registers.HL, I); break; 
        
        case SET3_A:      debug_opcode(z80, "SET3_A", "Set bit 3 of A");
            M_SET_H(z80, 3, z80->registers.AF); break;
        case SET3_B:      debug_opcode(z80, "SET3_B", "Set bit 3 of B");
            M_SET_H(z80, 3, z80->registers.BC); break;
        case SET3_C:      debug_opcode(z80, "SET3_C", "Set bit 3 of C");
            M_SET_L(z80, 3, z80->registers.BC); break;
        case SET3_D:      debug_opcode(z80, "SET3_D", "Set bit 3 of D");
            M_SET_H(z80, 3, z80->registers.DE); break;
        case SET3_E:      debug_opcode(z80, "SET3_E", "Set bit 3 of E");
            M_SET_L(z80, 3, z80->registers.DE); break;
        case SET3_H:      debug_opcode(z80, "SET3_H", "Set bit 3 of H");
            M_SET_H(z80, 3, z80->registers.HL); break;
        case SET3_L:      debug_opcode(z80, "SET3_L", "Set bit 3 of L");
            M_SET_L(z80, 3, z80->registers.HL); break;
        case SET3_xHL:      debug_opcode(z80, "SET3_xHL", "Set bit 3 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_SET(z80, 3, I); WrZ80(z80,z80->registers.HL, I); break; 
        
        case SET4_A:      debug_opcode(z80, "SET4_A", "Set bit 4 of A");
            M_SET_H(z80, 4, z80->registers.AF); break;
        case SET4_B:      debug_opcode(z80, "SET4_B", "Set bit 4 of B");
            M_SET_H(z80, 4, z80->registers.BC); break;
        case SET4_C:      debug_opcode(z80, "SET4_C", "Set bit 4 of C");
            M_SET_L(z80, 4, z80->registers.BC); break;
        case SET4_D:      debug_opcode(z80, "SET4_D", "Set bit 4 of D");
            M_SET_H(z80, 4, z80->registers.DE); break;
        case SET4_E:      debug_opcode(z80, "SET4_E", "Set bit 4 of E");
            M_SET_L(z80, 4, z80->registers.DE); break;
        case SET4_H:      debug_opcode(z80, "SET4_H", "Set bit 4 of H");
            M_SET_H(z80, 4, z80->registers.HL); break;
        case SET4_L:      debug_opcode(z80, "SET4_L", "Set bit 4 of L");
            M_SET_L(z80, 4, z80->registers.HL); break;
        case SET4_xHL:      debug_opcode(z80, "SET4_xHL", "Set bit 4 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_SET(z80, 4, I); WrZ80(z80,z80->registers.HL, I); break; 
        
        case SET5_A:      debug_opcode(z80, "SET5_A", "Set bit 5 of A");
            M_SET_H(z80, 5, z80->registers.AF); break;
        case SET5_B:      debug_opcode(z80, "SET5_B", "Set bit 5 of B");
            M_SET_H(z80, 5, z80->registers.BC); break;
        case SET5_C:      debug_opcode(z80, "SET5_C", "Set bit 5 of C");
            M_SET_L(z80, 5, z80->registers.BC); break;
        case SET5_D:      debug_opcode(z80, "SET5_D", "Set bit 5 of D");
            M_SET_H(z80, 5, z80->registers.DE); break;
        case SET5_E:      debug_opcode(z80, "SET5_E", "Set bit 5 of E");
            M_SET_L(z80, 5, z80->registers.DE); break;
        case SET5_H:      debug_opcode(z80, "SET5_H", "Set bit 5 of H");
            M_SET_H(z80, 5, z80->registers.HL); break;
        case SET5_L:      debug_opcode(z80, "SET5_L", "Set bit 5 of L");
            M_SET_L(z80, 5, z80->registers.HL); break;
        case SET5_xHL:      debug_opcode(z80, "SET5_xHL", "Set bit 5 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_SET(z80, 5, I); WrZ80(z80,z80->registers.HL, I); break; 
        
        case SET6_A:      debug_opcode(z80, "SET6_A", "Set bit 6 of A");
            M_SET_H(z80, 6, z80->registers.AF); break;
        case SET6_B:      debug_opcode(z80, "SET6_B", "Set bit 6 of B");
            M_SET_H(z80, 6, z80->registers.BC); break;
        case SET6_C:      debug_opcode(z80, "SET6_C", "Set bit 6 of C");
            M_SET_L(z80, 6, z80->registers.BC); break;
        case SET6_D:      debug_opcode(z80, "SET6_D", "Set bit 6 of D");
            M_SET_H(z80, 6, z80->registers.DE); break;
        case SET6_E:      debug_opcode(z80, "SET6_E", "Set bit 6 of E");
            M_SET_L(z80, 6, z80->registers.DE); break;
        case SET6_H:      debug_opcode(z80, "SET6_H", "Set bit 6 of H");
            M_SET_H(z80, 6, z80->registers.HL); break;
        case SET6_L:      debug_opcode(z80, "SET6_L", "Set bit 6 of L");
            M_SET_L(z80, 6, z80->registers.HL); break;
        case SET6_xHL:      debug_opcode(z80, "SET6_xHL", "Set bit 6 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_SET(z80, 6, I); WrZ80(z80,z80->registers.HL, I); break; 
        
        case SET7_A:      debug_opcode(z80, "SET7_A", "Set bit 7 of A");
            M_SET_H(z80, 7, z80->registers.AF); break;
        case SET7_B:      debug_opcode(z80, "SET7_B", "Set bit 7 of B");
            M_SET_H(z80, 7, z80->registers.BC); break;
        case SET7_C:      debug_opcode(z80, "SET7_C", "Set bit 7 of C");
            M_SET_L(z80, 7, z80->registers.BC); break;
        case SET7_D:      debug_opcode(z80, "SET7_D", "Set bit 7 of D");
            M_SET_H(z80, 7, z80->registers.DE); break;
        case SET7_E:      debug_opcode(z80, "SET7_E", "Set bit 7 of E");
            M_SET_L(z80, 7, z80->registers.DE); break;
        case SET7_H:      debug_opcode(z80, "SET7_H", "Set bit 7 of H");
            M_SET_H(z80, 7, z80->registers.HL); break;
        case SET7_L:      debug_opcode(z80, "SET7_L", "Set bit 7 of L");
            M_SET_L(z80, 7, z80->registers.HL); break;
        case SET7_xHL:      debug_opcode(z80, "SET7_xHL", "Set bit 7 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_SET(z80, 7, I); WrZ80(z80,z80->registers.HL, I); break; 
        
        
        case RES0_A:      debug_opcode(z80, "RES0_A", "Reset bit 0 of A");
            M_RES_H(z80, 0, z80->registers.AF); break;
        case RES0_B:      debug_opcode(z80, "RES0_B", "Reset bit 0 of B");
            M_RES_H(z80, 0, z80->registers.BC); break;
        case RES0_C:      debug_opcode(z80, "RES0_C", "Reset bit 0 of C");
            M_RES_L(z80, 0, z80->registers.BC); break;
        case RES0_D:      debug_opcode(z80, "RES0_D", "Reset bit 0 of D");
            M_RES_H(z80, 0, z80->registers.DE); break;
        case RES0_E:      debug_opcode(z80, "RES0_E", "Reset bit 0 of E");
            M_RES_L(z80, 0, z80->registers.DE); break;
        case RES0_H:      debug_opcode(z80, "RES0_H", "Reset bit 0 of H");
            M_RES_H(z80, 0, z80->registers.HL); break;
        case RES0_L:      debug_opcode(z80, "RES0_L", "Reset bit 0 of L");
            M_RES_L(z80, 0, z80->registers.HL); break;
        case RES0_xHL:      debug_opcode(z80, "RES0_xHL", "Reset bit 0 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_RES(z80, 0, I); WrZ80(z80,z80->registers.HL, I); break; 
        
        case RES1_A:      debug_opcode(z80, "RES1_A", "Reset bit 1 of A");
            M_RES_H(z80, 1, z80->registers.AF); break;
        case RES1_B:      debug_opcode(z80, "RES1_B", "Reset bit 1 of B");
            M_RES_H(z80, 1, z80->registers.BC); break;
        case RES1_C:      debug_opcode(z80, "RES1_C", "Reset bit 1 of C");
            M_RES_L(z80, 1, z80->registers.BC); break;
        case RES1_D:      debug_opcode(z80, "RES1_D", "Reset bit 1 of D");
            M_RES_H(z80, 1, z80->registers.DE); break;
        case RES1_E:      debug_opcode(z80, "RES1_E", "Reset bit 1 of E");
            M_RES_L(z80, 1, z80->registers.DE); break;
        case RES1_H:      debug_opcode(z80, "RES1_H", "Reset bit 1 of H");
            M_RES_H(z80, 1, z80->registers.HL); break;
        case RES1_L:      debug_opcode(z80, "RES1_L", "Reset bit 1 of L");
            M_RES_L(z80, 1, z80->registers.HL); break;
        case RES1_xHL:      debug_opcode(z80, "RES1_xHL", "Reset bit 1 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_RES(z80, 1, I); WrZ80(z80,z80->registers.HL, I); break; 
        
        case RES2_A:      debug_opcode(z80, "RES2_A", "Reset bit 2 of A");
            M_RES_H(z80, 2, z80->registers.AF); break;
        case RES2_B:      debug_opcode(z80, "RES2_B", "Reset bit 2 of B");
            M_RES_H(z80, 2, z80->registers.BC); break;
        case RES2_C:      debug_opcode(z80, "RES2_C", "Reset bit 2 of C");
            M_RES_L(z80, 2, z80->registers.BC); break;
        case RES2_D:      debug_opcode(z80, "RES2_D", "Reset bit 2 of D");
            M_RES_H(z80, 2, z80->registers.DE); break;
        case RES2_E:      debug_opcode(z80, "RES2_E", "Reset bit 2 of E");
            M_RES_L(z80, 2, z80->registers.DE); break;
        case RES2_H:      debug_opcode(z80, "RES2_H", "Reset bit 2 of H");
            M_RES_H(z80, 2, z80->registers.HL); break;
        case RES2_L:      debug_opcode(z80, "RES2_L", "Reset bit 2 of L");
            M_RES_L(z80, 2, z80->registers.HL); break;
        case RES2_xHL:      debug_opcode(z80, "RES2_xHL", "Reset bit 2 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_RES(z80, 2, I); WrZ80(z80,z80->registers.HL, I); break; 
        
        case RES3_A:      debug_opcode(z80, "RES3_A", "Reset bit 3 of A");
            M_RES_H(z80, 3, z80->registers.AF); break;
        case RES3_B:      debug_opcode(z80, "RES3_B", "Reset bit 3 of B");
            M_RES_H(z80, 3, z80->registers.BC); break;
        case RES3_C:      debug_opcode(z80, "RES3_C", "Reset bit 3 of C");
            M_RES_L(z80, 3, z80->registers.BC); break;
        case RES3_D:      debug_opcode(z80, "RES3_D", "Reset bit 3 of D");
            M_RES_H(z80, 3, z80->registers.DE); break;
        case RES3_E:      debug_opcode(z80, "RES3_E", "Reset bit 3 of E");
            M_RES_L(z80, 3, z80->registers.DE); break;
        case RES3_H:      debug_opcode(z80, "RES3_H", "Reset bit 3 of H");
            M_RES_H(z80, 3, z80->registers.HL); break;
        case RES3_L:      debug_opcode(z80, "RES3_L", "Reset bit 3 of L");
            M_RES_L(z80, 3, z80->registers.HL); break;
        case RES3_xHL:      debug_opcode(z80, "RES3_xHL", "Reset bit 3 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_RES(z80, 3, I); WrZ80(z80,z80->registers.HL, I); break; 
        
        case RES4_A:      debug_opcode(z80, "RES4_A", "Reset bit 4 of A");
            M_RES_H(z80, 4, z80->registers.AF); break;
        case RES4_B:      debug_opcode(z80, "RES4_B", "Reset bit 4 of B");
            M_RES_H(z80, 4, z80->registers.BC); break;
        case RES4_C:      debug_opcode(z80, "RES4_C", "Reset bit 4 of C");
            M_RES_L(z80, 4, z80->registers.BC); break;
        case RES4_D:      debug_opcode(z80, "RES4_D", "Reset bit 4 of D");
            M_RES_H(z80, 4, z80->registers.DE); break;
        case RES4_E:      debug_opcode(z80, "RES4_E", "Reset bit 4 of E");
            M_RES_L(z80, 4, z80->registers.DE); break;
        case RES4_H:      debug_opcode(z80, "RES4_H", "Reset bit 4 of H");
            M_RES_H(z80, 4, z80->registers.HL); break;
        case RES4_L:      debug_opcode(z80, "RES4_L", "Reset bit 4 of L");
            M_RES_L(z80, 4, z80->registers.HL); break;
        case RES4_xHL:      debug_opcode(z80, "RES4_xHL", "Reset bit 4 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_RES(z80, 4, I); WrZ80(z80,z80->registers.HL, I); break; 
        
        case RES5_A:      debug_opcode(z80, "RES5_A", "Reset bit 5 of A");
            M_RES_H(z80, 5, z80->registers.AF); break;
        case RES5_B:      debug_opcode(z80, "RES5_B", "Reset bit 5 of B");
            M_RES_H(z80, 5, z80->registers.BC); break;
        case RES5_C:      debug_opcode(z80, "RES5_C", "Reset bit 5 of C");
            M_RES_L(z80, 5, z80->registers.BC); break;
        case RES5_D:      debug_opcode(z80, "RES5_D", "Reset bit 5 of D");
            M_RES_H(z80, 5, z80->registers.DE); break;
        case RES5_E:      debug_opcode(z80, "RES5_E", "Reset bit 5 of E");
            M_RES_L(z80, 5, z80->registers.DE); break;
        case RES5_H:      debug_opcode(z80, "RES5_H", "Reset bit 5 of H");
            M_RES_H(z80, 5, z80->registers.HL); break;
        case RES5_L:      debug_opcode(z80, "RES5_L", "Reset bit 5 of L");
            M_RES_L(z80, 5, z80->registers.HL); break;
        case RES5_xHL:      debug_opcode(z80, "RES5_xHL", "Reset bit 5 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_RES(z80, 5, I); WrZ80(z80,z80->registers.HL, I); break; 
        
        case RES6_A:      debug_opcode(z80, "RES6_A", "Reset bit 6 of A");
            M_RES_H(z80, 6, z80->registers.AF); break;
        case RES6_B:      debug_opcode(z80, "RES6_B", "Reset bit 6 of B");
            M_RES_H(z80, 6, z80->registers.BC); break;
        case RES6_C:      debug_opcode(z80, "RES6_C", "Reset bit 6 of C");
            M_RES_L(z80, 6, z80->registers.BC); break;
        case RES6_D:      debug_opcode(z80, "RES6_D", "Reset bit 6 of D");
            M_RES_H(z80, 6, z80->registers.DE); break;
        case RES6_E:      debug_opcode(z80, "RES6_E", "Reset bit 6 of E");
            M_RES_L(z80, 6, z80->registers.DE); break;
        case RES6_H:      debug_opcode(z80, "RES6_H", "Reset bit 6 of H");
            M_RES_H(z80, 6, z80->registers.HL); break;
        case RES6_L:      debug_opcode(z80, "RES6_L", "Reset bit 6 of L");
            M_RES_L(z80, 6, z80->registers.HL); break;
        case RES6_xHL:      debug_opcode(z80, "RES6_xHL", "Reset bit 6 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_RES(z80, 6, I); WrZ80(z80,z80->registers.HL, I); break; 
        
        case RES7_A:      debug_opcode(z80, "RES7_A", "Reset bit 7 of A");
            M_RES_H(z80, 7, z80->registers.AF); break;
        case RES7_B:      debug_opcode(z80, "RES7_B", "Reset bit 7 of B");
            M_RES_H(z80, 7, z80->registers.BC); break;
        case RES7_C:      debug_opcode(z80, "RES7_C", "Reset bit 7 of C");
            M_RES_L(z80, 7, z80->registers.BC); break;
        case RES7_D:      debug_opcode(z80, "RES7_D", "Reset bit 7 of D");
            M_RES_H(z80, 7, z80->registers.DE); break;
        case RES7_E:      debug_opcode(z80, "RES7_E", "Reset bit 7 of E");
            M_RES_L(z80, 7, z80->registers.DE); break;
        case RES7_H:      debug_opcode(z80, "RES7_H", "Reset bit 7 of H");
            M_RES_H(z80, 7, z80->registers.HL); break;
        case RES7_L:      debug_opcode(z80, "RES7_L", "Reset bit 7 of L");
            M_RES_L(z80, 7, z80->registers.HL); break;
        case RES7_xHL:      debug_opcode(z80, "RES7_xHL", "Reset bit 7 of (HL)");
            I = RdZ80(z80, z80->registers.HL); M_RES(z80, 7, I); WrZ80(z80,z80->registers.HL, I); break; 
        
	

        default:{
            char str2[20];
            sprintf(str2,"unknown 0x%x",opcode);
            debug_opcode(z80, str2,"");
             if(z80->TrapBadOps)
            printf
            (
                "[Z80 %lX] Unrecognized instruction: CB %02X at PC=%04X\n",
                (long)z80->User,OpZ80(z80, z80->registers.PC-1),z80->registers.PC-2
            );
        }
    }
}
