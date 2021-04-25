static const unsigned char CyclesDD[256] =
{
   0, 0, 0, 0, 0, 0, 0, 0, 0,15, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0,15, 0, 0, 0, 0, 0, 0,
   0,14,20,10, 9, 9, 9, 0, 0,15,20,10, 9, 9, 9, 0,
   0, 0, 0, 0,23,23,19, 0, 0,15, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 9, 9,19, 0, 0, 0, 0, 0, 9, 9,19, 0,
   0, 0, 0, 0, 9, 9,19, 0, 0, 0, 0, 0, 9, 9,19, 0,
   9, 9, 9, 9, 9, 9,19, 9, 9, 9, 9, 9, 9, 9,19, 9,
  19,19,19,19,19,19,19,19, 0, 0, 0, 0, 9, 9,19, 0,
   0, 0, 0, 0, 9, 9,19, 0, 0, 0, 0, 0, 9, 9,19, 0,
   0, 0, 0, 0, 9, 9,19, 0, 0, 0, 0, 0, 9, 9,19, 0,
   0, 0, 0, 0, 9, 9,19, 0, 0, 0, 0, 0, 9, 9,19, 0,
   0, 0, 0, 0, 9, 9,19, 0, 0, 0, 0, 0, 9, 9,19, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0,14, 0,23, 0,15, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0,10, 0, 0, 0, 0, 0, 0
};


static const unsigned char CyclesDDCB[256] =
{
   0, 0, 0, 0, 0, 0,23, 0, 0, 0, 0, 0, 0, 0,23, 0,
   0, 0, 0, 0, 0, 0,23, 0, 0, 0, 0, 0, 0, 0,23, 0,
   0, 0, 0, 0, 0, 0,23, 0, 0, 0, 0, 0, 0, 0,23, 0,
   0, 0, 0, 0, 0, 0,23, 0, 0, 0, 0, 0, 0, 0,23, 0,
  20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
  20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
  20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
  20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
   0, 0, 0, 0, 0, 0,23, 0, 0, 0, 0, 0, 0, 0,23, 0,
   0, 0, 0, 0, 0, 0,23, 0, 0, 0, 0, 0, 0, 0,23, 0,
   0, 0, 0, 0, 0, 0,23, 0, 0, 0, 0, 0, 0, 0,23, 0,
   0, 0, 0, 0, 0, 0,23, 0, 0, 0, 0, 0, 0, 0,23, 0,
   0, 0, 0, 0, 0, 0,23, 0, 0, 0, 0, 0, 0, 0,23, 0,
   0, 0, 0, 0, 0, 0,23, 0, 0, 0, 0, 0, 0, 0,23, 0,
   0, 0, 0, 0, 0, 0,23, 0, 0, 0, 0, 0, 0, 0,23, 0,
   0, 0, 0, 0, 0, 0,23, 0, 0, 0, 0, 0, 0, 0,23, 0
};


static void z80_exec_extended_DDCB(struct z80* z80)
{
    unsigned char I; //register
    unsigned short J; //register

    J = z80->registers.IX + OpZ80(z80, z80->registers.PC);
    I = OpZ80(z80, z80->registers.PC);
    unsigned char opcode = I;
    z80->ICount -= CyclesDDCB[I];

    switch(I)
    {
        case RLC_xHL:      debug_opcode(z80, "RLC_xIX+BYTE", "The contents of the memory location pointed to by ix plus BYTE are rotated left one bit position. The content of bit 7 are copied to the carry flag and bit 0.");
            I = RdZ80(z80, J); M_RLC(z80, I); WrZ80(z80,J, I); break; 

        case RRC_xHL:      debug_opcode(z80, "RRC_xIX+BYTE", "The contents of the memory location pointed to by ix plus BYTE are rotated right one bit position. The content of bit 0 are copied to the carry flag and bit 7.");
            I = RdZ80(z80, J); M_RRC(z80, I); WrZ80(z80,J, I); break; 

        case RL_xHL:      debug_opcode(z80, "RL_xIX+BYTE", "The contents of the memory location pointed to by ix plus BYTE are rotated left one bit position. The content of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.");
            I = RdZ80(z80, J); M_RL(z80, I); WrZ80(z80,J, I); break; 

        case RR_xHL:      debug_opcode(z80, "RR_xIX+BYTE", "The contents of the memory location pointed to by ix plus BYTE are rotated right one bit position. The content of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.");
            I = RdZ80(z80, J); M_RR(z80, I); WrZ80(z80,J, I); break; 

        case SLA_xHL:      debug_opcode(z80, "SLA_xIX+BYTE", "The contents of the memory location pointed to by ix plus BYTE are shifted left one bit position. The content of bit 7 are copied to the carry flag and a zero is put into bit 0.");
            I = RdZ80(z80, J); M_SLA(z80, I); WrZ80(z80,J, I); break; 

        case SRA_xHL:      debug_opcode(z80, "SRA_xIX+BYTE", "The contents of the memory location pointed to by ix plus BYTE are shifted right one bit position. The content of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.");
            I = RdZ80(z80, J); M_SRA(z80, I); WrZ80(z80,J, I); break; 

        case SLL_xHL:      debug_opcode(z80, "SLL_xIX+BYTE", "The contents of the memory location pointed to by ix plus BYTE are shifted left one bit position. The content of bit 7 are put into the carry flag and a one is put into bit 0.");
            I = RdZ80(z80, J); M_SLL(z80, I); WrZ80(z80,J, I); break; 

        case SRL_xHL:      debug_opcode(z80, "SRL_xIX+BYTE", "The contents of the memory location pointed to by ix plus BYTE are shifted right one bit position. The content of bit 0 are copied to the carry flag and a zero is put into bit 7.");
            I = RdZ80(z80, J); M_SRL(z80, I); WrZ80(z80,J, I); break; 

        case BIT0_xHL:      debug_opcode(z80, "BIT0_xIX+BYTE", "Test bit 0 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_BIT(z80, 0, I); break; 
        case BIT1_xHL:      debug_opcode(z80, "BIT1_xIX+BYTE", "Test bit 1 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_BIT(z80, 1, I); break; 
        case BIT2_xHL:      debug_opcode(z80, "BIT2_xIX+BYTE", "Test bit 2 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_BIT(z80, 2, I); break; 
        case BIT3_xHL:      debug_opcode(z80, "BIT3_xIX+BYTE", "Test bit 3 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_BIT(z80, 3, I); break; 
        case BIT4_xHL:      debug_opcode(z80, "BIT4_xIX+BYTE", "Test bit 4 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_BIT(z80, 4, I); break; 
        case BIT5_xHL:      debug_opcode(z80, "BIT5_xIX+BYTE", "Test bit 5 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_BIT(z80, 5, I); break; 
        case BIT6_xHL:      debug_opcode(z80, "BIT6_xIX+BYTE", "Test bit 6 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_BIT(z80, 6, I); break; 
        case BIT7_xHL:      debug_opcode(z80, "BIT7_xIX+BYTE", "Test bit 7 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_BIT(z80, 7, I); break; 

        case SET0_xHL:      debug_opcode(z80, "SET0_xIX+BYTE", "Set bit 0 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_SET(z80, 0, I); WrZ80(z80,J, I); break; 
        case SET1_xHL:      debug_opcode(z80, "SET1_xIX+BYTE", "Set bit 1 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_SET(z80, 1, I); WrZ80(z80,J, I); break; 
        case SET2_xHL:      debug_opcode(z80, "SET2_xIX+BYTE", "Set bit 2 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_SET(z80, 2, I); WrZ80(z80,J, I); break; 
        case SET3_xHL:      debug_opcode(z80, "SET3_xIX+BYTE", "Set bit 3 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_SET(z80, 3, I); WrZ80(z80,J, I); break; 
        case SET4_xHL:      debug_opcode(z80, "SET4_xIX+BYTE", "Set bit 4 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_SET(z80, 4, I); WrZ80(z80,J, I); break; 
        case SET5_xHL:      debug_opcode(z80, "SET5_xIX+BYTE", "Set bit 5 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_SET(z80, 5, I); WrZ80(z80,J, I); break; 
        case SET6_xHL:      debug_opcode(z80, "SET6_xIX+BYTE", "Set bit 6 of  the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_SET(z80, 6, I); WrZ80(z80,J, I); break; 
        case SET7_xHL:      debug_opcode(z80, "SET7_xIX+BYTE", "Set bit 7 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_SET(z80, 7, I); WrZ80(z80,J, I); break; 
        
        case RES0_xHL:      debug_opcode(z80, "RES0_xIX+BYTE", "Reset bit 0 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_RES(z80, 0, I); WrZ80(z80,J, I); break;        
        case RES1_xHL:      debug_opcode(z80, "RES1_xIX+BYTE", "Reset bit 1 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_RES(z80, 1, I); WrZ80(z80,J, I); break; 
        case RES2_xHL:      debug_opcode(z80, "RES2_xIX+BYTE", "Reset bit 2 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_RES(z80, 2, I); WrZ80(z80,J, I); break; 
        case RES3_xHL:      debug_opcode(z80, "RES3_xIX+BYTE", "Reset bit 3 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_RES(z80, 3, I); WrZ80(z80,J, I); break; 
        case RES4_xHL:      debug_opcode(z80, "RES4_xIX+BYTE", "Reset bit 4 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_RES(z80, 4, I); WrZ80(z80,J, I); break; 
        case RES5_xHL:      debug_opcode(z80, "RES5_xIX+BYTE", "Reset bit 5 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_RES(z80, 5, I); WrZ80(z80,J, I); break; 
        case RES6_xHL:      debug_opcode(z80, "RES6_xIX+BYTE", "Reset bit 6 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_RES(z80, 6, I); WrZ80(z80,J, I); break; 
        case RES7_xHL:      debug_opcode(z80, "RES7_xIX+BYTE", "Reset bit 7 of the memory location pointed to by ix plus BYTE.");
            I = RdZ80(z80, J); M_RES(z80, 7, I); WrZ80(z80,J, I); break; 
        
	

        default:{
            char str2[20];
            sprintf(str2,"unknown 0x%x",opcode);
            debug_opcode(z80, str2,"");
             if(z80->TrapBadOps)
            printf
            (
                "[Z80 %lX] Unrecognized instruction: DD CB %02X %02X at PC=%04X\n",
                (long)(z80->User),OpZ80(z80, z80->registers.PC-2),OpZ80(z80, z80->registers.PC-1),z80, z80->registers.PC-4
            );
        }
    }
}


static void z80_exec_extended_DD(struct z80* z80)
{
  unsigned char I; //register
  unsigned short J; //register

//  #define XX IX
  I = OpZ80(z80, z80->registers.PC);
  unsigned char opcode = I;
  z80->ICount -= CyclesDD[I];


  switch(I)
  {
  

    case ADD_HL_BC:     debug_opcode(z80, "ADD_IX_BC", "The value of BC is added to IX");
        M_ADDW(z80, IX, BC);break; 
    case ADD_HL_DE:     debug_opcode(z80, "ADD_IX_DE", "The value of DE is added to IX");
        M_ADDW(z80, IX, DE);break;
    case ADD_HL_HL:     debug_opcode(z80, "ADD_IX_IX", "The value of IX is added to IX");
        M_ADDW(z80, IX, IX);break;
    case ADD_HL_SP:     debug_opcode(z80, "ADD_IX_SP", "The value of SP is added to IX");
        M_ADDW(z80, IX, SP);break;

    case ADD_H:         debug_opcode(z80, "ADD_IXh", "Adds IXh to A");
        M_ADD(z80, MSB(z80->registers.IX));break;
    case ADD_L:         debug_opcode(z80, "ADD_IXl", "Adds IXl to A");
        M_ADD(z80, LSB(z80->registers.IX));break;
    case ADD_xHL:       debug_opcode(z80, "ADD_xIX+BYTE", "Adds the value pointed by (IX) plus BYTE to A");
        I = RdZ80(z80, z80->registers.IX + OpZ80(z80, z80->registers.PC));
        M_ADD(z80, I); break;


    case INC_HL:         debug_opcode(z80, "INC_IX", "Adds one to IX");
        z80->registers.IX++;break;
    case INC_H:           debug_opcode(z80, "INC_IXh", "Adds one to IXh");
        M_INC_H(z80, z80->registers.IX);break;
    case INC_L:           debug_opcode(z80, "INC_IXl", "Adds one to IXl");
        M_INC_L(z80, z80->registers.IX);break;
    case INC_xHL:       debug_opcode(z80, "INC_xIX+BYTE", "Adds one to the memory location pointed to by IX plus BYTE.");
        I = RdZ80(z80, z80->registers.IX + RdZ80(z80, z80->registers.PC));
        M_INC_L(z80, I);
        WrZ80(z80, z80->registers.IX + OpZ80(z80, z80->registers.PC), I);
        break;

    case DEC_HL:         debug_opcode(z80, "DEC_IX", "Subtracts one to IX");
        z80->registers.IX--;break;
    case DEC_H:           debug_opcode(z80, "DEC_IXh", "Subtracts one to IXh");
        M_DEC_H(z80, z80->registers.IX);break;
    case DEC_L:           debug_opcode(z80, "DEC_IXl", "Subtracts one to IXl");
        M_DEC_L(z80, z80->registers.IX);break;
    case DEC_xHL:       debug_opcode(z80, "DEC_xIX+BYTE", "Subtracts one from the memory location pointed to by IX plus BYTE.");
        I = RdZ80(z80, z80->registers.IX + RdZ80(z80, z80->registers.PC));
        M_INC_L(z80, I);
        WrZ80(z80, z80->registers.IX + OpZ80(z80, z80->registers.PC), I);
        break;

    case ADC_H:         debug_opcode(z80, "ADC_IXh", "Adds IXh and the carry flag to A");
        M_ADC(z80, MSB(z80->registers.IX));break;
    case ADC_L:         debug_opcode(z80, "ADC_IXl", "Adds IXl and the carry flag to A");
        M_ADC(z80, LSB(z80->registers.IX));break;
    case ADC_xHL:      debug_opcode(z80, "ADC_xIX+BYTE", "Adds the value pointed to by IX plus BYTE and the carry flag to A");        
        I = RdZ80(z80, z80->registers.IX + OpZ80(z80, z80->registers.PC));
        M_ADC(z80, I);break;

    case SUB_H:      debug_opcode(z80, "SUB_IXh", "Subtracts IXh from A");    
        M_SUB(z80, MSB(z80->registers.IX));break;
    case SUB_L:      debug_opcode(z80, "SUB_IXl", "Subtracts IXl from A");    
        M_SUB(z80, LSB(z80->registers.IX));break;
    case SUB_xHL:       debug_opcode(z80, "SUB_xIX+BYTE", "Subtracts the value pointed to by IX plus BYTE from A.");
        I = RdZ80(z80, z80->registers.IX + OpZ80(z80, z80->registers.PC));
        M_SUB(z80, I);break;


    case SBC_H:      debug_opcode(z80, "SBC_IXh", "Subtracts IXh and the carry flag from A");    
        M_SBC(z80, MSB(z80->registers.IX));break;
    case SBC_L:      debug_opcode(z80, "SBC_IXl", "Subtracts IXl and the carry flag from A");    
        M_SBC(z80, LSB(z80->registers.IX));break;
    case SBC_xHL:       debug_opcode(z80, "SBC_xIX+BYTE", "Subtracts the value pointed to by IX plus BYTE and the carry flag from A.");
        I = RdZ80(z80, z80->registers.IX + OpZ80(z80, z80->registers.PC));
        M_SBC(z80, I);break;


    case AND_H:      debug_opcode(z80, "AND_IXh", "Bitwise AND on A with IXh");    
        M_AND(z80, MSB(z80->registers.IX));break;
    case AND_L:      debug_opcode(z80, "AND_IXl", "Bitwise AND on A with IXl");    
        M_AND(z80, LSB(z80->registers.IX));break;
    case AND_xHL:       debug_opcode(z80, "AND_xIX+BYTE", "Bitwise AND on A with value pointed to by IX plus BYTE");
      I = RdZ80(z80, z80->registers.IX + OpZ80(z80, z80->registers.PC));
      M_AND(z80, I);break;

    case XOR_H:      debug_opcode(z80, "XOR_IXh", "Bitwise XOR on A with IXh");    
        M_XOR(z80, MSB(z80->registers.IX));break;
    case XOR_L:      debug_opcode(z80, "XOR_IXl", "Bitwise XOR on A with IXl");    
        M_XOR(z80, LSB(z80->registers.IX));break;
    case XOR_xHL:    debug_opcode(z80, "XOR_xIX+BYTE", "Bitwise XOR on A with value pointed to by IX plus BYTE");
      I = RdZ80(z80, z80->registers.IX + OpZ80(z80, z80->registers.PC));
      M_XOR(z80, I);break;

    case OR_H:      debug_opcode(z80, "XOR_IXh", "Bitwise OR on A with IXh");    
        M_XOR(z80, MSB(z80->registers.IX));break;
    case OR_L:      debug_opcode(z80, "XOR_IXl", "Bitwise OR on A with IXl");    
        M_OR(z80, LSB(z80->registers.IX));break;
    case OR_xHL:    debug_opcode(z80, "XOR_xIX+BYTE", "Bitwise OR on A with value pointed to by IX plus BYTE");
        I = RdZ80(z80, z80->registers.IX + OpZ80(z80, z80->registers.PC));
        M_OR(z80, I);break;

    case CP_H:      debug_opcode(z80, "CP_IXh", "Subtracts IXh from A and affects flags according to the result. A is not modified.");    
        M_CP(z80, MSB(z80->registers.IX));break;
    case CP_L:      debug_opcode(z80, "CP_IXl", "Subtracts IXl from A and affects flags according to the result. A is not modified.");    
        M_CP(z80, LSB(z80->registers.IX));break;
    case CP_xHL:    debug_opcode(z80, "CP_xIX+BYTE", "Subtracts the value pointed to by IX plus BYTE from A and affects flags according to the result. A is not modified.");
        I = RdZ80(z80, z80->registers.IX + OpZ80(z80, z80->registers.PC));
        M_CP(z80, I);break;

    case POP_HL:       debug_opcode(z80, "POP_IX", "The memory location pointed to by SP is stored into IXl and SP is incremented. The memory location pointed to by SP is stored into IXh and SP is incremented again"); 
        M_POP(z80, IX);break;

    case EX_xSP_HL:      debug_opcode(z80, "EX_xSP_IX","Exchanges (SP) with IXl, and (SP+1) with IXh");
        J = z80->registers.IX;
        SET_WORD(z80->registers.IX, RdZ80(z80, z80->registers.SP),  
                                    RdZ80(z80, z80->registers.SP + 1)); 
        
        WrZ80(z80, z80->registers.SP, LSB(J));
        WrZ80(z80, z80->registers.SP+1, MSB(J));

      break;

    case PUSH_HL:       debug_opcode(z80, "PUSH_IX", "SP is decremented and IXh is stored into the memory location pointed to by SP. SP is decremented again and IXl is stored pointed to by SP"); 
        M_PUSH(z80, IX);break;

                    
      case LD_HL_WORD:    debug_opcode_reg_word(z80, "LD_IX_WORD", "Loads ** into IX"); 
          M_LDWORD(z80, z80->registers.IX);break;
      case LD_xWORD_HL:    debug_opcode_reg_word(z80, "LD_xWORD_IX", "Stores IX into the memory location pointed to by WORD");
        SET_LSB(J, OpZ80(z80, z80->registers.PC));
        SET_MSB(J, OpZ80(z80, z80->registers.PC));
        WrZ80(z80,J, LSB(z80->registers.IX));
        J += 1;
        WrZ80(z80,J, MSB(z80->registers.IX));
        break;
      case LD_H_BYTE:     debug_opcode_reg_byte(z80, "LD_IXh_BYTE", "Load BYTE into IXh");
          SET_MSB(z80->registers.IX, OpZ80(z80, z80->registers.PC));
          break;
      case LD_HL_xWORD:    debug_opcode_reg_word(z80, "LD_IX_xWORD", "Load value pointed to by WORD into IX");
        SET_LSB(J, OpZ80(z80, z80->registers.PC));
        SET_MSB(J, OpZ80(z80, z80->registers.PC));
        SET_LSB(z80->registers.IX, RdZ80(z80, J));
        J += 1;
        SET_MSB(z80->registers.IX, RdZ80(z80, J));
        break;
      case LD_L_BYTE:     debug_opcode_reg_byte(z80, "LD_IXl_BYTE", "Load BYTE into IXl");
          SET_LSB(z80->registers.IX, OpZ80(z80, z80->registers.PC));
          break;

      case LD_xHL_BYTE:   debug_opcode_reg_byte(z80, "LD_xIXl_BYTE", "Stores BYTE to the memory location pointed to by IX plus BYTE");
          J = z80->registers.IX + OpZ80(z80, z80->registers.PC);
          WrZ80(z80,J,OpZ80(z80, z80->registers.PC));
          break;


      case LD_B_H:        debug_opcode(z80, "LD_B_IXh", "The content of IXh is loaded into B");
          SET_MSB(z80->registers.BC, MSB(z80->registers.IX));break;
      case LD_B_L:        debug_opcode(z80, "LD_B_IXl", "The content of IXl is loaded into B");
          SET_MSB(z80->registers.BC, LSB(z80->registers.IX));break;
      case LD_B_xHL:      debug_opcode(z80, "LD_B_xIX", "The contents of IX plus BYTE are loaded into B");
          SET_MSB(z80->registers.BC, RdZ80(z80, z80->registers.IX + OpZ80(z80, z80->registers.PC)));
          break;

      case LD_C_H:        debug_opcode(z80, "LD_C_IXh", "The content of IXh is loaded into C");
          SET_LSB(z80->registers.BC, MSB(z80->registers.IX));break;
      case LD_C_L:        debug_opcode(z80, "LD_C_IXl", "The content of IXl is loaded into C");
          SET_LSB(z80->registers.BC, LSB(z80->registers.IX));break;
      case LD_C_xHL:      debug_opcode(z80, "LD_C_xIX", "The contents of IX plus BYTE are loaded into C");
          SET_LSB(z80->registers.BC, RdZ80(z80, z80->registers.IX + OpZ80(z80, z80->registers.PC)));
          break;

      case LD_D_H:        debug_opcode(z80, "LD_D_IXh", "The content of IXh is loaded into D");
          SET_MSB(z80->registers.DE, MSB(z80->registers.IX));break;
      case LD_D_L:        debug_opcode(z80, "LD_D_IXl", "The content of IXl is loaded into D");
          SET_MSB(z80->registers.DE, LSB(z80->registers.IX));break;
      case LD_D_xHL:      debug_opcode(z80, "LD_D_xIX", "The contents of IX plus BYTE are loaded into D");
          SET_MSB(z80->registers.DE, RdZ80(z80, z80->registers.IX + OpZ80(z80, z80->registers.PC)));
          break;

      case LD_E_H:        debug_opcode(z80, "LD_E_IXh", "The content of IXh is loaded into E");
          SET_LSB(z80->registers.DE, MSB(z80->registers.IX));break;
      case LD_E_L:        debug_opcode(z80, "LD_E_IXl", "The content of IXl is loaded into E");
          SET_LSB(z80->registers.DE, LSB(z80->registers.IX));break;
      case LD_E_xHL:      debug_opcode(z80, "LD_E_xIX", "The contents of IX plus BYTE are loaded into E");
          SET_LSB(z80->registers.DE, RdZ80(z80, z80->registers.IX + OpZ80(z80, z80->registers.PC)));
          break;


      case LD_H_B:        debug_opcode(z80, "LD_IXh_B", "The content of B is loaded into IXh");
          SET_MSB(z80->registers.IX, MSB(z80->registers.BC));break;
      case LD_H_C:        debug_opcode(z80, "LD_IXh_C", "The content of C is loaded into IXh");
          SET_MSB(z80->registers.IX, LSB(z80->registers.BC));break;
      case LD_H_D:        debug_opcode(z80, "LD_IXh_D", "The content of D is loaded into IXh");
          SET_MSB(z80->registers.IX, MSB(z80->registers.DE));break;
      case LD_H_E:        debug_opcode(z80, "LD_IXh_E", "The content of E is loaded into IXh");
          SET_MSB(z80->registers.IX, LSB(z80->registers.DE));break;

      case LD_H_H:        debug_opcode(z80, "LD_IXh_IXh", "The content of IXh is loaded into IXh");
          SET_MSB(z80->registers.IX, MSB(z80->registers.IX));break;
      case LD_H_L:        debug_opcode(z80, "LD_IXh_IXl", "The content of IXh is loaded into IXl");
          SET_MSB(z80->registers.IX, LSB(z80->registers.IX));break;
      case LD_H_xHL:      debug_opcode(z80, "LD_H_IXL", "Loads the value pointed to IX plus BYTE into H");
          SET_MSB(z80->registers.HL, RdZ80(z80, z80->registers.IX + OpZ80(z80, z80->registers.PC)));
          break;

      case LD_H_A:      debug_opcode(z80, "LD_xIXh_A", "The contents of A are loaded into IXh");
          SET_MSB(z80->registers.IX, MSB(z80->registers.AF));break;

      case LD_L_B:      debug_opcode(z80, "LD_xIXl_B", "The contents of B are loaded into IXl");
          SET_LSB(z80->registers.IX, MSB(z80->registers.BC));break;
      case LD_L_C:      debug_opcode(z80, "LD_xIXl_C", "The contents of C are loaded into IXl");
          SET_LSB(z80->registers.IX, LSB(z80->registers.BC));break;
      case LD_L_D:      debug_opcode(z80, "LD_xIXl_D", "The contents of D are loaded into IXl");
          SET_LSB(z80->registers.IX, MSB(z80->registers.DE));break;
      case LD_L_E:      debug_opcode(z80, "LD_xIXl_E", "The contents of E are loaded into IXl");
          SET_LSB(z80->registers.IX, LSB(z80->registers.DE));break;

      case LD_L_H:        debug_opcode(z80, "LD_IXl_IXh", "The content of IXl is loaded into IXh");
          SET_LSB(z80->registers.IX, MSB(z80->registers.IX));break;
      case LD_L_L:        debug_opcode(z80, "LD_IXl_IXl", "The content of IXl is loaded into IXl");
          SET_LSB(z80->registers.IX, LSB(z80->registers.IX));break;
      case LD_L_xHL:        debug_opcode(z80, "LD_L_xIX", "Loads the value pointed to IX plus BYTE into L");
          SET_LSB(z80->registers.HL, RdZ80(z80, z80->registers.IX + OpZ80(z80, z80->registers.PC)));
          break;
      case LD_L_A:      debug_opcode(z80, "LD_xIXl_A", "The contents of A are loaded into IXl");
          SET_LSB(z80->registers.IX, MSB(z80->registers.AF));break;

      case LD_xHL_B:      debug_opcode(z80, "LD_xIX_B", "Stores B to the memory location pointed to by IX plus BYTE");
          J=z80->registers.IX + OpZ80(z80, z80->registers.PC);
          WrZ80(z80,J, MSB(z80->registers.BC));break;
      case LD_xHL_C:      debug_opcode(z80, "LD_xIX_C", "Stores C to the memory location pointed to by IX plus BYTE");
          J=z80->registers.IX + OpZ80(z80, z80->registers.PC);
          WrZ80(z80,J,LSB(z80->registers.BC));break;
      case LD_xHL_D:      debug_opcode(z80, "LD_xIX_D", "Stores D to the memory location pointed to by IX plus BYTE");
          J=z80->registers.IX + OpZ80(z80, z80->registers.PC);
          WrZ80(z80,J,MSB(z80->registers.DE));break;
      case LD_xHL_E:      debug_opcode(z80, "LD_xIX_E", "Stores E to the memory location pointed to by IX plus BYTE");
          J=z80->registers.IX + OpZ80(z80, z80->registers.PC);
          WrZ80(z80,J, LSB(z80->registers.DE));break;
      case LD_xHL_H:      debug_opcode(z80, "LD_xIX_H", "Stores H to the memory location pointed to by IX plus BYTE");
          J=z80->registers.IX + OpZ80(z80, z80->registers.PC);
          WrZ80(z80,J,MSB(z80->registers.HL));break;
      case LD_xHL_L:      debug_opcode(z80, "LD_xIX_L", "Stores L to the memory location pointed to by IX plus BYTE");
          J=z80->registers.IX + OpZ80(z80, z80->registers.PC);
          WrZ80(z80,J, LSB(z80->registers.HL));break;

      case LD_xHL_A:      debug_opcode(z80, "LD_xIX_A", "Stores A to the memory location pointed to by IX plus BYTE");
          J=z80->registers.IX + OpZ80(z80, z80->registers.PC);
          WrZ80(z80,J, MSB(z80->registers.AF));break;
      case LD_A_H:        debug_opcode(z80, "LD_A_IXh", "The content of IXh is loaded into A");
          SET_MSB(z80->registers.AF, MSB(z80->registers.IX));break;
      case LD_A_L:        debug_opcode(z80, "LD_A_IXl", "The content of IXl is loaded into A");
          SET_MSB(z80->registers.AF, LSB(z80->registers.IX));break;
      case LD_A_xHL:        debug_opcode(z80, "LD_L_xIX", "Loads the value pointed to IX plus BYTE into A");
          SET_MSB(z80->registers.AF, RdZ80(z80, z80->registers.IX+ OpZ80(z80, z80->registers.PC)));
          break;


      case LD_PC_HL:        debug_opcode(z80, "LD_PC_IX", "Loads the value of IX into PC");
              z80->registers.PC=z80->registers.IX;JumpZ80(z80, z80->registers.PC);break;
      case LD_SP_HL:        debug_opcode(z80, "LD_SP_IX", "Loads the value of IX into SP");
              z80->registers.SP=z80->registers.IX;break;



    case PFX_FD:
    case PFX_DD:
      z80->registers.PC--;break;
    case PFX_CB:
      z80_exec_extended_DDCB(z80);break;
    default:{
      char str2[20];
      sprintf(str2,"unknown 0x%x",opcode);
      debug_opcode(z80, str2,"");
        if(z80->TrapBadOps)
      printf
      (
          "[Z80 %lX] Unrecognized instruction: DD %02X at PC=%04X\n",
          (long)z80->User,OpZ80(z80, z80->registers.PC-1),z80->registers.PC-2
      );
    }
  //#undef XX
  }
}