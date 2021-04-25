        case NOP:           debug_opcode(z80, "NOP", "No operation is performed"); break;

        // LD

        case LD_A_A:        debug_opcode(z80, "LD_A_A", "The content of A is loaded into A");
            SET_MSB(z80->registers.AF, MSB(z80->registers.AF));break;
        case LD_A_B:        debug_opcode(z80, "LD_A_B", "The content of B is loaded into A");
            SET_MSB(z80->registers.AF, MSB(z80->registers.BC));break;
        case LD_A_C:        debug_opcode(z80, "LD_A_C", "The content of C is loaded into A");
            SET_MSB(z80->registers.AF, LSB(z80->registers.BC));break;
        case LD_A_D:        debug_opcode(z80, "LD_A_D", "The content of D is loaded into A");
            SET_MSB(z80->registers.AF, MSB(z80->registers.DE));break;
        case LD_A_E:        debug_opcode(z80, "LD_A_E", "The content of E is loaded into A");
            SET_MSB(z80->registers.AF, LSB(z80->registers.DE));break;
        case LD_A_H:        debug_opcode(z80, "LD_A_H", "The content of H is loaded into A");
            SET_MSB(z80->registers.AF, MSB(z80->registers.HL));break;
        case LD_A_L:        debug_opcode(z80, "LD_A_L", "The content of L is loaded into A");
            SET_MSB(z80->registers.AF, LSB(z80->registers.HL));break;
        
        // 8

        case LD_B_A:        debug_opcode(z80, "LD_B_A", "The content of A is loaded into B");
            SET_MSB(z80->registers.BC, MSB(z80->registers.AF));break;
        case LD_B_B:        debug_opcode(z80, "LD_B_B", "The content of B is loaded into B");
            SET_MSB(z80->registers.BC, MSB(z80->registers.BC));break;
        case LD_B_C:        debug_opcode(z80, "LD_B_C", "The content of C is loaded into B");
            SET_MSB(z80->registers.BC, LSB(z80->registers.BC));break;
        case LD_B_D:        debug_opcode(z80, "LD_B_D", "The content of D is loaded into B");
            SET_MSB(z80->registers.BC, MSB(z80->registers.DE));break;
        case LD_B_E:        debug_opcode(z80, "LD_B_E", "The content of E is loaded into B");
            SET_MSB(z80->registers.BC, LSB(z80->registers.DE));break;
        case LD_B_H:        debug_opcode(z80, "LD_B_H", "The content of H is loaded into B");
            SET_MSB(z80->registers.BC, MSB(z80->registers.HL));break;
        case LD_B_L:        debug_opcode(z80, "LD_B_L", "The content of L is loaded into B");
            SET_MSB(z80->registers.BC, LSB(z80->registers.HL));break;

        //15

        case LD_C_A:        debug_opcode(z80, "LD_C_A", "The content of A is loaded into C");
            SET_LSB(z80->registers.BC, MSB(z80->registers.AF));break;
        case LD_C_B:        debug_opcode(z80, "LD_C_B", "The content of B is loaded into C");
            SET_LSB(z80->registers.BC, MSB(z80->registers.BC));break;
        case LD_C_C:        debug_opcode(z80, "LD_C_C", "The content of C is loaded into C");
            SET_LSB(z80->registers.BC, LSB(z80->registers.BC));break;
        case LD_C_D:        debug_opcode(z80, "LD_C_D", "The content of D is loaded into C");
            SET_LSB(z80->registers.BC, MSB(z80->registers.DE));break;
        case LD_C_E:        debug_opcode(z80, "LD_C_E", "The content of E is loaded into C");
            SET_LSB(z80->registers.BC, LSB(z80->registers.DE));break;
        case LD_C_H:        debug_opcode(z80, "LD_C_H", "The content of H is loaded into C");
            SET_LSB(z80->registers.BC, MSB(z80->registers.HL));break;
        case LD_C_L:        debug_opcode(z80, "LD_C_L", "The content of L is loaded into C");
            SET_LSB(z80->registers.BC, LSB(z80->registers.HL));break;

        //22

        case LD_D_A:        debug_opcode(z80, "LD_D_A", "The content of A is loaded into D");
            SET_MSB(z80->registers.DE, MSB(z80->registers.AF));break;
        case LD_D_B:        debug_opcode(z80, "LD_D_B", "The content of B is loaded into D");
            SET_MSB(z80->registers.DE, MSB(z80->registers.BC));break;
        case LD_D_C:        debug_opcode(z80, "LD_D_C", "The content of C is loaded into D");
            SET_MSB(z80->registers.DE, LSB(z80->registers.BC));break;
        case LD_D_D:        debug_opcode(z80, "LD_D_D", "The content of D is loaded into D");
            SET_MSB(z80->registers.DE, MSB(z80->registers.DE));break;
        case LD_D_E:        debug_opcode(z80, "LD_D_E", "The content of E is loaded into D");
            SET_MSB(z80->registers.DE, LSB(z80->registers.DE));break;
        case LD_D_H:        debug_opcode(z80, "LD_D_H", "The content of H is loaded into D");
            SET_MSB(z80->registers.DE, MSB(z80->registers.HL));break;
        case LD_D_L:        debug_opcode(z80, "LD_D_L", "The content of L is loaded into D");
            SET_MSB(z80->registers.DE, LSB(z80->registers.HL));break;

        //29

        case LD_E_A:        debug_opcode(z80, "LD_E_A", "The content of A is loaded into E");
            SET_LSB(z80->registers.DE, MSB(z80->registers.AF));break;
        case LD_E_B:        debug_opcode(z80, "LD_E_B", "The content of B is loaded into E");
            SET_LSB(z80->registers.DE, MSB(z80->registers.BC));break;
        case LD_E_C:        debug_opcode(z80, "LD_E_C", "The content of C is loaded into E");
            SET_LSB(z80->registers.DE, LSB(z80->registers.BC));break;
        case LD_E_D:        debug_opcode(z80, "LD_E_D", "The content of D is loaded into E");
            SET_LSB(z80->registers.DE, MSB(z80->registers.DE));break;
        case LD_E_E:        debug_opcode(z80, "LD_E_E", "The content of E is loaded into E");
            SET_LSB(z80->registers.DE, LSB(z80->registers.DE));break;
        case LD_E_H:        debug_opcode(z80, "LD_E_H", "The content of H is loaded into E");
            SET_LSB(z80->registers.DE, MSB(z80->registers.HL));break;
        case LD_E_L:        debug_opcode(z80, "LD_E_L", "The content of L is loaded into E");
            SET_LSB(z80->registers.DE, LSB(z80->registers.HL));break;

        //36

        case LD_H_A:        debug_opcode(z80, "LD_H_A", "The content of A is loaded into H");
            SET_MSB(z80->registers.HL, MSB(z80->registers.AF));break;
        case LD_H_B:        debug_opcode(z80, "LD_H_B", "The content of B is loaded into H");
            SET_MSB(z80->registers.HL, MSB(z80->registers.BC));break;
        case LD_H_C:        debug_opcode(z80, "LD_H_C", "The content of C is loaded into H");
            SET_MSB(z80->registers.HL, LSB(z80->registers.BC));break;
        case LD_H_D:        debug_opcode(z80, "LD_H_D", "The content of D is loaded into H");
            SET_MSB(z80->registers.HL, MSB(z80->registers.DE));break;
        case LD_H_E:        debug_opcode(z80, "LD_H_E", "The content of E is loaded into H");
            SET_MSB(z80->registers.HL, LSB(z80->registers.DE));break;
        case LD_H_H:        debug_opcode(z80, "LD_H_H", "The content of H is loaded into H");
            SET_MSB(z80->registers.HL, MSB(z80->registers.HL));break;
        case LD_H_L:        debug_opcode(z80, "LD_H_L", "The content of L is loaded into H");
            SET_MSB(z80->registers.HL, LSB(z80->registers.HL));break;

        //43

        case LD_L_A:        debug_opcode(z80, "LD_L_A", "The content of A is loaded into L");
            SET_LSB(z80->registers.HL, MSB(z80->registers.AF));break;
        case LD_L_B:        debug_opcode(z80, "LD_L_B", "The content of B is loaded into L");
            SET_LSB(z80->registers.HL, MSB(z80->registers.BC));break;
        case LD_L_C:        debug_opcode(z80, "LD_L_C", "The content of C is loaded into L");
            SET_LSB(z80->registers.HL, LSB(z80->registers.BC));break;
        case LD_L_D:        debug_opcode(z80, "LD_L_D", "The content of D is loaded into L");
            SET_LSB(z80->registers.HL, MSB(z80->registers.DE));break;
        case LD_L_E:        debug_opcode(z80, "LD_L_E", "The content of E is loaded into L");
            SET_LSB(z80->registers.HL, LSB(z80->registers.DE));break;
        case LD_L_H:        debug_opcode(z80, "LD_L_H", "The content of H is loaded into L");
            SET_LSB(z80->registers.HL, MSB(z80->registers.HL));break;
        case LD_L_L:        debug_opcode(z80, "LD_L_L", "The content of L is loaded into L");
            SET_LSB(z80->registers.HL, LSB(z80->registers.HL));break;

        //50

        case LD_BC_WORD:    debug_opcode_reg_word(z80, "LD_BC_WORD", "Loads ** into BC"); 
            M_LDWORD(z80, z80->registers.BC); break;
        case LD_DE_WORD:    debug_opcode_reg_word(z80, "LD_DE_WORD", "Loads ** into DE"); 
            M_LDWORD(z80, z80->registers.DE); break;
        case LD_HL_WORD:    debug_opcode_reg_word(z80, "LD_HL_WORD", "Loads ** into HL"); 
            M_LDWORD(z80, z80->registers.HL); break;
        case LD_SP_WORD:    debug_opcode_reg_word(z80, "LD_SP_WORD", "Loads ** into SP"); 
            M_LDWORD(z80, z80->registers.SP); break;

        case LD_A_xBC:      debug_opcode(z80, "LD_A_xBC", "The contents of BC are loaded into A");
            SET_MSB(z80->registers.AF, RdZ80(z80, z80->registers.BC));break;
        case LD_A_xDE:      debug_opcode(z80, "LD_A_xDE", "The contents of DE are loaded into A");
            SET_MSB(z80->registers.AF, RdZ80(z80, z80->registers.DE));break;

        case LD_xBC_A:      debug_opcode(z80, "LD_xBC_A", "Stores A into the memory location pointed to by BC");
            WrZ80(z80, z80->registers.BC, MSB(z80->registers.AF)); break;
        case LD_xDE_A:      debug_opcode(z80, "LD_xDE_A", "Stores A into the memory location pointed to by DE");
            WrZ80(z80, z80->registers.DE, MSB(z80->registers.AF)); break;

        case LD_A_xHL:      debug_opcode(z80, "LD_A_xHL", "The contents of (HL) are loaded into A");
            SET_MSB(z80->registers.AF, RdZ80(z80, z80->registers.HL));break;
        case LD_B_xHL:      debug_opcode(z80, "LD_B_xHL", "The contents of (HL) are loaded into B");
            SET_MSB(z80->registers.BC, RdZ80(z80, z80->registers.HL));break;
        case LD_C_xHL:      debug_opcode(z80, "LD_C_xHL", "The contents of (HL) are loaded into C");
            SET_LSB(z80->registers.BC, RdZ80(z80, z80->registers.HL));break;
        case LD_D_xHL:      debug_opcode(z80, "LD_D_xHL", "The contents of (HL) are loaded into D");
            SET_MSB(z80->registers.DE, RdZ80(z80, z80->registers.HL));break;
        case LD_E_xHL:      debug_opcode(z80, "LD_E_xHL", "The contents of (HL) are loaded into E");
            SET_LSB(z80->registers.DE, RdZ80(z80, z80->registers.HL));break;
        case LD_H_xHL:      debug_opcode(z80, "LD_H_xHL", "The contents of (HL) are loaded into H");
            SET_MSB(z80->registers.HL, RdZ80(z80, z80->registers.HL));break;
        case LD_L_xHL:      debug_opcode(z80, "LD_L_xHL", "The contents of (HL) are loaded into L");
            SET_LSB(z80->registers.HL, RdZ80(z80, z80->registers.HL));break;

        case LD_xHL_A:      debug_opcode(z80, "LD_xHL_A", "The contents of A are loaded into (HL)");
            WrZ80(z80, z80->registers.HL, MSB(z80->registers.AF));break;
        case LD_xHL_B:      debug_opcode(z80, "LD_xHL_B", "The contents of B are loaded into (HL)");
            WrZ80(z80, z80->registers.HL, MSB(z80->registers.BC));break;
        case LD_xHL_C:      debug_opcode(z80, "LD_xHL_C", "The contents of C are loaded into (HL)");
            WrZ80(z80, z80->registers.HL, LSB(z80->registers.BC));break;
        case LD_xHL_D:      debug_opcode(z80, "LD_xHL_D", "The contents of D are loaded into (HL)");
            WrZ80(z80, z80->registers.HL, MSB(z80->registers.DE));break;
        case LD_xHL_E:      debug_opcode(z80, "LD_xHL_E", "The contents of E are loaded into (HL)");
            WrZ80(z80, z80->registers.HL, LSB(z80->registers.DE));break;
        case LD_xHL_H:      debug_opcode(z80, "LD_xHL_H", "The contents of H are loaded into (HL)");
            WrZ80(z80, z80->registers.HL, MSB(z80->registers.HL));break;
        case LD_xHL_L:      debug_opcode(z80, "LD_xHL_L", "The contents of L are loaded into (HL)");
            WrZ80(z80, z80->registers.HL, LSB(z80->registers.HL));break;
        
        //72

        case LD_xWORD_A:    debug_opcode_reg_word(z80, "LD_xWORD_A", "Stores A into the memory location pointed to by WORD");
            M_LDWORD(z80, J); 
            WrZ80(z80, J, MSB(z80->registers.AF));
            break;        
        case LD_xWORD_HL:    debug_opcode_reg_word(z80, "LD_xWORD_HL", "Stores HL into the memory location pointed to by WORD");
            M_LDWORD(z80, J); 
            WrZ80(z80, J, LSB(z80->registers.HL)); // ???
            J += 1;
            WrZ80(z80, J, MSB(z80->registers.HL));
            break;      
        case LD_A_xWORD:    debug_opcode_reg_word(z80, "LD_A_xWORD", "Load value pointed to by WORD into A");
            M_LDWORD(z80, J); 
            SET_MSB(z80->registers.AF, RdZ80(z80, J));
            break;
        case LD_HL_xWORD:    debug_opcode_reg_word(z80, "LD_HL_xWORD", "Load value pointed to by WORD into HL");
            M_LDWORD(z80, J); 
            SET_LSB(z80->registers.HL, RdZ80(z80,J));
            J += 1;
            SET_MSB(z80->registers.HL, RdZ80(z80, J));
            break;

        //76
        
        case LD_PC_HL:      debug_opcode(z80, "LD_PC_HL", "Load value of HL into PC");
            z80->registers.PC = z80->registers.HL; JumpZ80(z80, z80->registers.PC); break;
        case LD_SP_HL:      debug_opcode(z80, "LD_SP_HL", "Load value of HL into SP");
            z80->registers.SP = z80->registers.HL; break;

        case LD_A_BYTE:     debug_opcode_reg_byte(z80, "LD_A_BYTE", "Load BYTE into A");
            SET_MSB(z80->registers.AF, OpZ80(z80, z80->registers.PC)); break;
        case LD_B_BYTE:     debug_opcode_reg_byte(z80, "LD_B_BYTE", "Load BYTE into B");
            SET_MSB(z80->registers.BC, OpZ80(z80, z80->registers.PC)); break;
        case LD_C_BYTE:     debug_opcode_reg_byte(z80, "LD_C_BYTE", "Load BYTE into C");
            SET_LSB(z80->registers.BC, OpZ80(z80, z80->registers.PC)); break;
        case LD_D_BYTE:     debug_opcode_reg_byte(z80, "LD_D_BYTE", "Load BYTE into D");
            SET_MSB(z80->registers.DE, OpZ80(z80, z80->registers.PC)); break;
        case LD_E_BYTE:     debug_opcode_reg_byte(z80, "LD_E_BYTE", "Load BYTE into E");
            SET_LSB(z80->registers.DE, OpZ80(z80, z80->registers.PC)); break;
        case LD_H_BYTE:     debug_opcode_reg_byte(z80, "LD_H_BYTE", "Load BYTE into H");
            SET_MSB(z80->registers.HL, OpZ80(z80, z80->registers.PC)); break;
        case LD_L_BYTE:     debug_opcode_reg_byte(z80, "LD_L_BYTE", "Load BYTE into L");
            SET_LSB(z80->registers.HL, OpZ80(z80, z80->registers.PC)); break;
        case LD_xHL_BYTE:   debug_opcode_reg_byte(z80, "LD_xHL_BYTE", "Load BYTE into (HL)");
            WrZ80(z80, z80->registers.HL, OpZ80(z80, z80->registers.PC)); break;
        
        //INC 86

        case INC_A:         debug_opcode(z80, "INC_A", "Adds one to A");
            M_INC_H(z80, z80->registers.AF);break;
        case INC_B:         debug_opcode(z80, "INC_B", "Adds one to B");    
            M_INC_H(z80, z80->registers.BC);break;
        case INC_C:         debug_opcode(z80, "INC_C", "Adds one to C");    
            M_INC_L(z80, z80->registers.BC);break;
        case INC_D:         debug_opcode(z80, "INC_D", "Adds one to D");    
            M_INC_H(z80, z80->registers.DE);break;
        case INC_E:         debug_opcode(z80, "INC_E", "Adds one to E");    
            M_INC_L(z80, z80->registers.DE);break;
        case INC_H:         debug_opcode(z80, "INC_H", "Adds one to H");    
            M_INC_H(z80, z80->registers.HL);break;
        case INC_L:         debug_opcode(z80, "INC_L", "Adds one to L");    
            M_INC_L(z80, z80->registers.HL);break;

        case INC_BC:        debug_opcode(z80, "INC_BC", "Adds one to BC");
            z80->registers.BC++; break;
        case INC_DE:        debug_opcode(z80, "INC_DE", "Adds one to DE");
            z80->registers.DE++;break;
        case INC_HL:        debug_opcode(z80, "INC_HL", "Adds one to HL");
            z80->registers.HL++;break;
        case INC_SP:        debug_opcode(z80, "INC_SP", "Adds one to SP");
            z80->registers.SP++;break;
        case INC_xHL:       debug_opcode(z80, "INC_xHL", "Adds one to (HL)");
            I = RdZ80(z80, z80->registers.HL); M_INC_L(z80, I); WrZ80(z80, z80->registers.HL,I); break;

        //DEC 98

        case DEC_A:         debug_opcode(z80, "DEC_A", "Subtracts one from A");
            M_DEC_H(z80, z80->registers.AF);break;
        case DEC_B:         debug_opcode(z80, "DEC_B", "Subtracts one from B");
            M_DEC_H(z80, z80->registers.BC);break;
        case DEC_C:         debug_opcode(z80, "DEC_C", "Subtracts one from C");
            M_DEC_L(z80, z80->registers.BC);break;
        case DEC_D:         debug_opcode(z80, "DEC_D", "Subtracts one from D");
            M_DEC_H(z80, z80->registers.DE);break;
        case DEC_E:         debug_opcode(z80, "DEC_E", "Subtracts one from E");
            M_DEC_L(z80, z80->registers.DE);break;
        case DEC_H:         debug_opcode(z80, "DEC_H", "Subtracts one from H");
            M_DEC_H(z80, z80->registers.HL);break;
        case DEC_L:         debug_opcode(z80, "DEC_L", "Subtracts one from L");
            M_DEC_L(z80, z80->registers.HL);break;

        case DEC_BC:        debug_opcode(z80, "DEC_BC", "Subtracts one from BC");
            z80->registers.BC--; break;
        case DEC_DE:        debug_opcode(z80, "DEC_BC", "Subtracts one from DE");
            z80->registers.DE--;break;
        case DEC_HL:        debug_opcode(z80, "DEC_BC", "Subtracts one from HL");
            z80->registers.HL--;break;
        case DEC_SP:        debug_opcode(z80, "DEC_BC", "Subtracts one from SP");
            z80->registers.SP--;break;
        case DEC_xHL:       debug_opcode(z80, "DEC_BC", "Subtracts one from (HL)");
            I = RdZ80(z80, z80->registers.HL); M_DEC_L(z80, I); WrZ80(z80, z80->registers.HL,I); break;

        //110

        case ADD_A:         debug_opcode(z80, "ADD_A", "Adds A to A");
            M_ADD(z80, MSB(z80->registers.AF)); break;
        case ADD_B:         debug_opcode(z80, "ADD_B", "Adds B to A");
            M_ADD(z80, MSB(z80->registers.BC)); break;
        case ADD_C:         debug_opcode(z80, "ADD_C", "Adds C to A");
            M_ADD(z80, LSB(z80->registers.BC));break;
        case ADD_D:         debug_opcode(z80, "ADD_D", "Adds D to A");
            M_ADD(z80, MSB(z80->registers.DE));break;
        case ADD_E:         debug_opcode(z80, "ADD_E", "Adds E to A");
            M_ADD(z80, LSB(z80->registers.DE));break;
        case ADD_H:         debug_opcode(z80, "ADD_H", "Adds H to A");
            M_ADD(z80, MSB(z80->registers.HL));break;
        case ADD_L:         debug_opcode(z80, "ADD_L", "Adds L to A");
            M_ADD(z80, LSB(z80->registers.HL));break;
        case ADD_xHL:       debug_opcode(z80, "ADD_xHL", "Adds (HL) to A");
            I = RdZ80(z80, z80->registers.HL); M_ADD(z80, I); break;
        case ADD_BYTE:      debug_opcode(z80, "ADD_BYTE", "Adds BYTE to A");
            I = OpZ80(z80, z80->registers.PC); M_ADD(z80, I); break;

        case ADD_HL_BC:     debug_opcode(z80, "ADD_HL_BC", "The value of BC is added to HL");
            M_ADDW(z80, HL, BC);break; 
        case ADD_HL_DE:     debug_opcode(z80, "ADD_HL_DE", "The value of DE is added to HL");
            M_ADDW(z80, HL, DE);break;
        case ADD_HL_HL:     debug_opcode(z80, "ADD_HL_HL", "The value of HL is added to HL");
            M_ADDW(z80, HL, HL);break;
        case ADD_HL_SP:     debug_opcode(z80, "ADD_HL_SP", "The value of SP is added to HL");
            M_ADDW(z80, HL, SP);break;

        case ADC_A:         debug_opcode(z80, "ADC_A", "Adds A and the carry flag to A");
            M_ADC(z80, MSB(z80->registers.AF));break;
        case ADC_B:         debug_opcode(z80, "ADC_B", "Adds B and the carry flag to A");
            M_ADC(z80, MSB(z80->registers.BC));break;
        case ADC_C:         debug_opcode(z80, "ADC_C", "Adds C and the carry flag to A");
            M_ADC(z80, LSB(z80->registers.BC));break;
        case ADC_D:         debug_opcode(z80, "ADC_D", "Adds D and the carry flag to A");
            M_ADC(z80, MSB(z80->registers.DE));break;
        case ADC_E:         debug_opcode(z80, "ADC_E", "Adds E and the carry flag to A");
            M_ADC(z80, LSB(z80->registers.DE));break;
        case ADC_H:         debug_opcode(z80, "ADC_H", "Adds H and the carry flag to A");
            M_ADC(z80, MSB(z80->registers.HL));break;
        case ADC_L:         debug_opcode(z80, "ADC_L", "Adds L and the carry flag to A");
            M_ADC(z80, LSB(z80->registers.HL));break;
        case ADC_xHL:       debug_opcode(z80, "ADC_xHL", "Adds (HL) and the carry flag to A");
            I = RdZ80(z80, z80->registers.HL); M_ADC(z80, I); break;
        case ADC_BYTE:      debug_opcode(z80, "ADC_xHL", "Adds BYTE and the carry flag to A");
            I = OpZ80(z80, z80->registers.PC); M_ADC(z80, I); break;
  
        //132

        case SUB_A:      debug_opcode(z80, "SUB_A", "Subtracts A from A");    
            SET_MSB(z80->registers.AF, 0);
            SET_LSB(z80->registers.AF, N_FLAG | Z_FLAG);
            break;
        case SUB_B:      debug_opcode(z80, "SUB_B", "Subtracts B from A");    
            M_SUB(z80, MSB(z80->registers.BC));break;
        case SUB_C:      debug_opcode(z80, "SUB_C", "Subtracts C from A");    
            M_SUB(z80, LSB(z80->registers.BC));break;
        case SUB_D:      debug_opcode(z80, "SUB_D", "Subtracts D from A");    
            M_SUB(z80, MSB(z80->registers.DE));break;
        case SUB_E:      debug_opcode(z80, "SUB_E", "Subtracts E from A");    
            M_SUB(z80, LSB(z80->registers.DE));break;
        case SUB_H:      debug_opcode(z80, "SUB_H", "Subtracts H from A");    
            M_SUB(z80, MSB(z80->registers.HL));break;
        case SUB_L:      debug_opcode(z80, "SUB_L", "Subtracts L from A");    
            M_SUB(z80, LSB(z80->registers.HL));break;
        case SUB_xHL:       debug_opcode(z80, "SUB_xHL", "Subtracts (HL) from A");
            I = RdZ80(z80, z80->registers.HL);M_SUB(z80, I);break;
        case SUB_BYTE:      debug_opcode(z80, "SUB_BYTE", "Subtracts BYTE from A");
            I = OpZ80(z80, z80->registers.PC);M_SUB(z80, I);break;

        case SBC_A:      debug_opcode(z80, "SBC_A", "Subtracts A and the carry flag from A");    
            M_SBC(z80, MSB(z80->registers.AF));break;
        case SBC_B:      debug_opcode(z80, "SBC_B", "Subtracts B and the carry flag from A");    
            M_SBC(z80, MSB(z80->registers.BC));break;
        case SBC_C:      debug_opcode(z80, "SBC_C", "Subtracts C and the carry flag from A");    
            M_SBC(z80, LSB(z80->registers.BC));break;
        case SBC_D:      debug_opcode(z80, "SBC_D", "Subtracts D and the carry flag from A");    
            M_SBC(z80, MSB(z80->registers.DE));break;
        case SBC_E:      debug_opcode(z80, "SBC_E", "Subtracts E and the carry flag from A");    
            M_SBC(z80, LSB(z80->registers.DE));break;
        case SBC_H:      debug_opcode(z80, "SBC_H", "Subtracts H and the carry flag from A");    
            M_SBC(z80, MSB(z80->registers.HL));break;
        case SBC_L:      debug_opcode(z80, "SBC_L", "Subtracts L and the carry flag from A");    
            M_SBC(z80, LSB(z80->registers.HL));break;
        case SBC_xHL:       debug_opcode(z80, "SBC_xHL", "Subtracts (HL) and the carry flag from A");
            I = RdZ80(z80, z80->registers.HL);M_SBC(z80, I);break;
        case SBC_BYTE:      debug_opcode(z80, "SBC_BYTE", "Subtracts BYTE and the carry flag from A");
            I = OpZ80(z80, z80->registers.PC);M_SBC(z80, I);break;

        //150

        case AND_A:      debug_opcode(z80, "AND_A", "Bitwise AND on A with A");    
            M_AND(z80, MSB(z80->registers.AF));break;
        case AND_B:      debug_opcode(z80, "AND_B", "Bitwise AND on A with B");    
            M_AND(z80, MSB(z80->registers.BC));break;
        case AND_C:      debug_opcode(z80, "AND_C", "Bitwise AND on A with C");    
            M_AND(z80, LSB(z80->registers.BC));break;
        case AND_D:      debug_opcode(z80, "AND_D", "Bitwise AND on A with D");    
            M_AND(z80, MSB(z80->registers.DE));break;
        case AND_E:      debug_opcode(z80, "AND_E", "Bitwise AND on A with E");    
            M_AND(z80, LSB(z80->registers.DE));break;
        case AND_H:      debug_opcode(z80, "AND_H", "Bitwise AND on A with H");    
            M_AND(z80, MSB(z80->registers.HL));break;
        case AND_L:      debug_opcode(z80, "AND_L", "Bitwise AND on A with L");    
            M_AND(z80, LSB(z80->registers.HL));break;
        case AND_xHL:       debug_opcode(z80, "AND_xHL", "Bitwise AND on A with (HL)");
            I = RdZ80(z80, z80->registers.HL);M_AND(z80, I);break;
        case AND_BYTE:      debug_opcode(z80, "AND_BYTE", "Bitwise AND on A with BYTE");
            I = OpZ80(z80, z80->registers.PC);M_AND(z80, I);break;

        case OR_A:      debug_opcode(z80, "OR_A", "Bitwise OR on A with A");    
            M_OR(z80, MSB(z80->registers.AF));break;
        case OR_B:      debug_opcode(z80, "OR_B", "Bitwise OR on A with B");    
            M_OR(z80, MSB(z80->registers.BC));break;
        case OR_C:      debug_opcode(z80, "OR_C", "Bitwise OR on A with C");    
            M_OR(z80, LSB(z80->registers.BC));break;
        case OR_D:      debug_opcode(z80, "OR_D", "Bitwise OR on A with D");    
            M_OR(z80, MSB(z80->registers.DE));break;
        case OR_E:      debug_opcode(z80, "OR_E", "Bitwise OR on A with E");    
            M_OR(z80, LSB(z80->registers.DE));break;
        case OR_H:      debug_opcode(z80, "OR_H", "Bitwise OR on A with H");    
            M_OR(z80, MSB(z80->registers.HL));break;
        case OR_L:      debug_opcode(z80, "OR_L", "Bitwise OR on A with L");    
            M_OR(z80, LSB(z80->registers.HL));break;
        case OR_xHL:       debug_opcode(z80, "OR_xHL", "Bitwise OR on A with (HL)");
            I = RdZ80(z80, z80->registers.HL);M_OR(z80, I);break;
        case OR_BYTE:      debug_opcode(z80, "OR_BYTE", "Bitwise OR on A with BYTE");
            I = OpZ80(z80, z80->registers.PC);M_OR(z80, I);break;

        case XOR_A:      debug_opcode(z80, "XOR_A", "Bitwise XOR on A with A");    
            SET_MSB(z80->registers.AF, 0);
            SET_LSB(z80->registers.AF, P_FLAG | Z_FLAG);        
            break;
        case XOR_B:      debug_opcode(z80, "XOR_B", "Bitwise XOR on A with B");    
            M_XOR(z80, MSB(z80->registers.BC));break;
        case XOR_C:      debug_opcode(z80, "XOR_C", "Bitwise XOR on A with C");    
            M_XOR(z80, LSB(z80->registers.BC));break;
        case XOR_D:      debug_opcode(z80, "XOR_D", "Bitwise XOR on A with D");    
            M_XOR(z80, MSB(z80->registers.DE));break;
        case XOR_E:      debug_opcode(z80, "XOR_E", "Bitwise XOR on A with E");    
            M_XOR(z80, LSB(z80->registers.DE));break;
        case XOR_H:      debug_opcode(z80, "XOR_H", "Bitwise XOR on A with H");    
            M_XOR(z80, MSB(z80->registers.HL));break;
        case XOR_L:      debug_opcode(z80, "XOR_L", "Bitwise XOR on A with L");    
            M_XOR(z80, LSB(z80->registers.HL));break;
        case XOR_xHL:       debug_opcode(z80, "XOR_xHL", "Bitwise XOR on A with (HL)");
            I = RdZ80(z80, z80->registers.HL);M_XOR(z80, I);break;
        case XOR_BYTE:      debug_opcode(z80, "XOR_BYTE", "Bitwise XOR on A with BYTE");
            I = OpZ80(z80, z80->registers.PC);M_XOR(z80, I);break;
   
        case CP_A:      debug_opcode(z80, "CP_A", "Subtracts A from A and affects flags according to the result. A is not modified.");    
            SET_LSB(z80->registers.AF, N_FLAG | Z_FLAG);        
            break;
        case CP_B:      debug_opcode(z80, "CP_B", "Subtracts B from A and affects flags according to the result. A is not modified.");    
            M_CP(z80, MSB(z80->registers.BC));break;
        case CP_C:      debug_opcode(z80, "CP_C", "Subtracts C from A and affects flags according to the result. A is not modified.");    
            M_CP(z80, LSB(z80->registers.BC));break;
        case CP_D:      debug_opcode(z80, "CP_D", "Subtracts D from A and affects flags according to the result. A is not modified.");    
            M_CP(z80, MSB(z80->registers.DE));break;
        case CP_E:      debug_opcode(z80, "CP_E", "Subtracts E from A and affects flags according to the result. A is not modified.");    
            M_CP(z80, LSB(z80->registers.DE));break;
        case CP_H:      debug_opcode(z80, "CP_H", "Subtracts H from A and affects flags according to the result. A is not modified.");    
            M_CP(z80, MSB(z80->registers.HL));break;
        case CP_L:      debug_opcode(z80, "CP_L", "Subtracts J from A and affects flags according to the result. A is not modified.");    
            M_CP(z80, LSB(z80->registers.HL));break;
        case CP_xHL:       debug_opcode(z80, "CP_xHL", "Subtracts (HL) from A and affects flags according to the result. A is not modified.");
            I = RdZ80(z80, z80->registers.HL);M_CP(z80, I);break;
        case CP_BYTE:      debug_opcode(z80, "CP_BYTE", "Subtracts BYTE from A and affects flags according to the result. A is not modified.");
            I = OpZ80(z80, z80->registers.PC);M_CP(z80, I);break;

        //186

        case CALL:       debug_opcode(z80, "CALL", "The current PC value +3 is pushed onto stack, then is loaded with WORD");
            M_CALL(z80); break;
        case CALL_NZ:       debug_opcode(z80, "CALL_NZ", "If condition Z is false, the current PC value +3 is pushed onto stack, then is loaded with WORD");
            if((LSB(z80->registers.AF) & Z_FLAG) == 0x0) {M_CALL(z80); } else z80->registers.PC += 2; break;        
        case CALL_NC:       debug_opcode(z80, "CALL_NC", "If condition C is false, the current PC value +3 is pushed onto stack, then is loaded with WORD");
            if((LSB(z80->registers.AF) & C_FLAG) == 0x0) {M_CALL(z80); } else z80->registers.PC += 2; break;        
        case CALL_PO:       debug_opcode(z80, "CALL_PO", "If condition P is false, the current PC value +3 is pushed onto stack, then is loaded with WORD");
            if((LSB(z80->registers.AF) & P_FLAG) == 0x0) {M_CALL(z80); } else z80->registers.PC += 2; break;        
        case CALL_P:       debug_opcode(z80, "CALL_P", "If condition S is false, the current PC value +3 is pushed onto stack, then is loaded with WORD");
            if((LSB(z80->registers.AF) & S_FLAG) == 0x0) {M_CALL(z80); } else z80->registers.PC += 2; break;        
        
        case CALL_Z:       debug_opcode(z80, "CALL_Z", "If condition Z is true, the current PC value +3 is pushed onto stack, then is loaded with WORD");
            if(LSB(z80->registers.AF) & Z_FLAG) {M_CALL(z80); } else z80->registers.PC += 2; break;        
        case CALL_C:       debug_opcode(z80, "CALL_C", "If condition C is true, the current PC value +3 is pushed onto stack, then is loaded with WORD");
            if(LSB(z80->registers.AF) & C_FLAG) {M_CALL(z80); } else z80->registers.PC += 2; break;        
        case CALL_PE:       debug_opcode(z80, "CALL_PE", "If condition P is true, the current PC value +3 is pushed onto stack, then is loaded with WORD"); 
            if(LSB(z80->registers.AF) & P_FLAG) {M_CALL(z80); } else z80->registers.PC += 2; break;        
        case CALL_M:       debug_opcode(z80, "CALL_M", "If condition S is true, the current PC value +3 is pushed onto stack, then is loaded with WORD");
            if(LSB(z80->registers.AF) & S_FLAG) {M_CALL(z80); } else z80->registers.PC += 2; break;        
        

        case RET:        debug_opcode(z80, "RET", "The top stack entry is popped into PC");
            M_RET(z80); break;
        case RET_NZ:        debug_opcode(z80, "RET_NZ", "If condition Z is false, the top stack entry is popped into PC");
            if((LSB(z80->registers.AF) & Z_FLAG) == 0x0) {M_RET(z80); } break;
        case RET_NC:        debug_opcode(z80, "RET_NC", "If condition C is false, the top stack entry is popped into PC");
            if((LSB(z80->registers.AF) & C_FLAG) == 0x0) {M_RET(z80); } break;
        case RET_PO:        debug_opcode(z80, "RET_PO", "If condition P is false, the top stack entry is popped into PC");
            if((LSB(z80->registers.AF) & P_FLAG) == 0x0) {M_RET(z80); } break;
        case RET_P:        debug_opcode(z80, "RET_P", "If condition S is false, the top stack entry is popped into PC");
            if((LSB(z80->registers.AF) & S_FLAG) == 0x0) {M_RET(z80); } break;
        
        case RET_Z:        debug_opcode(z80, "RET_Z", "If condition Z is true, the top stack entry is popped into PC");
            if(LSB(z80->registers.AF) & Z_FLAG) {M_RET(z80); } break;
        case RET_C:        debug_opcode(z80, "RET_C", "If condition C is true, the top stack entry is popped into PC");
            if(LSB(z80->registers.AF) & C_FLAG) {M_RET(z80); } break;
        case RET_PE:        debug_opcode(z80, "RET_PE", "If condition P is true, the top stack entry is popped into PC");
            if(LSB(z80->registers.AF) & P_FLAG) {M_RET(z80); } break;
        case RET_M:        debug_opcode(z80, "RET_M", "If condition S is true, the top stack entry is popped into PC");
            if(LSB(z80->registers.AF) & S_FLAG) {M_RET(z80); } break;

        case JR:        debug_opcode(z80, "JR", "The signed value BYTE is added to PC. The jump is measured from the start of the instruction opcode.");
            M_JR(z80); break;
        case JR_NZ:        debug_opcode(z80, "JR_NZ", "If condition Z is false, the signed value BYTE is added to PC. The jump is measured from the start of the instruction opcode.");
            if((LSB(z80->registers.AF) & Z_FLAG) == 0x0) { M_JR(z80); } else z80->registers.PC++; break;
        case JR_NC:        debug_opcode(z80, "JR_NC", "If condition C is false, the signed value BYTE is added to PC. The jump is measured from the start of the instruction opcode.");
            if((LSB(z80->registers.AF) & C_FLAG) == 0x0) { M_JR(z80); } else z80->registers.PC++; break;
        
        case JR_Z:        debug_opcode(z80, "JR_Z", "If condition Z is true, the signed value BYTE is added to PC. The jump is measured from the start of the instruction opcode.");
            if(LSB(z80->registers.AF) & Z_FLAG) { M_JR(z80); } else z80->registers.PC++; break;
        case JR_C:        debug_opcode(z80, "JR_C", "If condition C is true, the signed value BYTE is added to PC. The jump is measured from the start of the instruction opcode.");
            if(LSB(z80->registers.AF) & C_FLAG) { M_JR(z80); } else z80->registers.PC++; break;

        case JP:        debug_opcode(z80, "JP", "WORD is copied to PC");
            M_JP(z80); break;
        case JP_NZ:        debug_opcode(z80, "JP_NZ", "If condition Z is false, WORD is copied to PC");
            if((LSB(z80->registers.AF) & Z_FLAG) == 0x0) { M_JP(z80); } else z80->registers.PC += 2; break;
        case JP_NC:        debug_opcode(z80, "JP_NC", "If condition C is false, WORD is copied to PC");
            if((LSB(z80->registers.AF) & C_FLAG) == 0x0) { M_JP(z80); } else z80->registers.PC += 2; break;
        case JP_PO:        debug_opcode(z80, "JP_PO", "If condition P is false, WORD is copied to PC");
            if((LSB(z80->registers.AF) & P_FLAG) == 0x0) { M_JP(z80); } else z80->registers.PC += 2; break;
        case JP_P:        debug_opcode(z80, "JP_P", "If condition S is false, WORD is copied to PC");
            if((LSB(z80->registers.AF) & S_FLAG) == 0x0) { M_JP(z80); } else z80->registers.PC += 2; break;
        
        case JP_Z:        debug_opcode(z80, "JP_Z", "If condition Z is true, WORD is copied to PC");
            if(LSB(z80->registers.AF) & Z_FLAG) { M_JP(z80); } else z80->registers.PC += 2; break;
        case JP_C:        debug_opcode(z80, "JP_C", "If condition C is true, WORD is copied to PC");
            if(LSB(z80->registers.AF) & C_FLAG) { M_JP(z80); } else z80->registers.PC += 2; break;
        case JP_PE:        debug_opcode(z80, "JP_PE", "If condition P is true, WORD is copied to PC");
            if(LSB(z80->registers.AF) & P_FLAG) { M_JP(z80); } else z80->registers.PC += 2; break;
        case JP_M:        debug_opcode(z80, "JP_M", "If condition S is true, WORD is copied to PC");
            if(LSB(z80->registers.AF) & S_FLAG) { M_JP(z80); } else z80->registers.PC += 2; break;

        //214
        
        case DJNZ:        debug_opcode(z80, "DJNZ", "The B register is decremented, and if not zero, the signed value BYTE is added to PC. The jump is measured from the start of the instruction opcode.");
            SET_MSB(z80->registers.BC, MSB(z80->registers.BC)-1);
            if(MSB(z80->registers.BC) > 0) { 
                M_JR(z80); 
            } 
                else z80->registers.PC++;
            break;
        
        case SCF:        debug_opcode(z80, "SCF", "Sets the carry flag");
            S(z80, C_FLAG); R(z80, N_FLAG | H_FLAG);break;
            
        case CCF:      debug_opcode(z80, "CCF","Inverts the carry flag");
            SET_LSB(z80->registers.AF, LSB(z80->registers.AF) ^ C_FLAG);
            R(z80, N_FLAG | H_FLAG);
            SET_LSB(z80->registers.AF, LSB(z80->registers.AF) | ((LSB(z80->registers.AF) & C_FLAG) ? 0 : H_FLAG));
            break;

        case CPL:        debug_opcode(z80, "CPL", "The contents of A are inverted (one's complement)");
            SET_MSB(z80->registers.AF, ~MSB(z80->registers.AF));
            S(z80, N_FLAG | H_FLAG);
            break;


        case OUTA:        debug_opcode(z80, "OUTA", "The value of A is written on port BYTE");
            I = OpZ80(z80, z80->registers.PC);
            OutZ80(z80, I | (z80->registers.AF & 0xFF00), MSB(z80->registers.AF));
            break;

        case INA:        debug_opcode(z80, "INA", "A byte from port BYTE is written to A");
            I = OpZ80(z80, z80->registers.PC);
            SET_MSB(z80->registers.AF, InZ80(z80, I | (z80->registers.AF & 0xFF00)));
            break;

        //223
              
        case RLCA:          debug_opcode(z80, "RLCA", "The contents of A are rotated left one bit position. The content of bit 7 are copied to the carry flag and bit 0"); 
            I = MSB(z80->registers.AF) & 0x80 ? C_FLAG : 0;
            SET_MSB(z80->registers.AF, (MSB(z80->registers.AF) << 1) | I);
            SET_LSB(z80->registers.AF, (LSB(z80->registers.AF) & ~(C_FLAG | N_FLAG | H_FLAG)) | I);
            break;
 
        case RLA:           debug_opcode(z80, "RLA", "The contents of A are rotated left one bit position. The contents of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0");
            I = MSB(z80->registers.AF) & 0x80 ? C_FLAG : 0;
            SET_MSB(z80->registers.AF, (MSB(z80->registers.AF) << 1) | (LSB(z80->registers.AF) & C_FLAG));
            SET_LSB(z80->registers.AF, (LSB(z80->registers.AF) & ~(C_FLAG | N_FLAG | H_FLAG)) | I);
            break;
        case RRCA:          debug_opcode(z80, "RRCA", "The contents of A are rotated right one bit position. The contents of bit 0 are copied to the carry flag and bit 7");
            I = MSB(z80->registers.AF) & 0x01;
            SET_MSB(z80->registers.AF, (MSB(z80->registers.AF) >> 1) | (I ? 0x80 : 0));
            SET_LSB(z80->registers.AF, (LSB(z80->registers.AF) & ~(C_FLAG | N_FLAG | H_FLAG)) | I); 
            break;
        case RRA:           debug_opcode(z80, "RRA", "The contents of A are rotated right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7");
            I = MSB(z80->registers.AF) & 0x01;
            SET_MSB(z80->registers.AF, (MSB(z80->registers.AF) >> 1) | (LSB(z80->registers.AF) & C_FLAG ? 0x80 : 0));
            SET_LSB(z80->registers.AF, (LSB(z80->registers.AF) & ~(C_FLAG | N_FLAG | H_FLAG)) | I);
            break;

        case RST00:       debug_opcode(z80, "RST00", "The current PC value plus one is pushed onto the stack, then is loaded with 00h"); 
            M_RST(z80, 0x0000);break;      
        case RST08:       debug_opcode(z80, "RST08", "The current PC value plus one is pushed onto the stack, then is loaded with 08h"); 
            M_RST(z80, 0x0008);break;
        case RST10:       debug_opcode(z80, "RST10", "The current PC value plus one is pushed onto the stack, then is loaded with 10h"); 
            M_RST(z80, 0x0010);break;
        case RST18:       debug_opcode(z80, "RST18", "The current PC value plus one is pushed onto the stack, then is loaded with 18h"); 
            M_RST(z80, 0x0018);break;
        case RST20:       debug_opcode(z80, "RST20", "The current PC value plus one is pushed onto the stack, then is loaded with 20h"); 
            M_RST(z80, 0x0020);break;
        case RST28:       debug_opcode(z80, "RST28", "The current PC value plus one is pushed onto the stack, then is loaded with 28h");
            M_RST(z80, 0x0028);break;
        case RST30:       debug_opcode(z80, "RST30", "The current PC value plus one is pushed onto the stack, then is loaded with 30h");
            M_RST(z80, 0x0030);break;
        case RST38:       debug_opcode(z80, "RST38", "The current PC value plus one is pushed onto the stack, then is loaded with 38h"); 
            M_RST(z80, 0x0038);break;
          
        case PUSH_AF:       debug_opcode(z80, "PUSH_AF", "SP is decremented and A is stored into the memory location pointed to by SP. SP is decremented again and F is stored pointed to by SP"); 
            M_PUSH(z80, AF);break;
        case PUSH_BC:       debug_opcode(z80, "PUSH_BC", "SP is decremented and B is stored into the memory location pointed to by SP. SP is decremented again and C is stored pointed to by SP"); 
            M_PUSH(z80, BC);break;
        case PUSH_DE:       debug_opcode(z80, "PUSH_DE", "SP is decremented and D is stored into the memory location pointed to by SP. SP is decremented again and E is stored pointed to by SP"); 
            M_PUSH(z80, DE);break;
        case PUSH_HL:       debug_opcode(z80, "PUSH_HL", "SP is decremented and H is stored into the memory location pointed to by SP. SP is decremented again and L is stored pointed to by SP"); 
            M_PUSH(z80, HL);break;
            
        //239

        case POP_AF:       debug_opcode(z80, "POP_AF", "The memory location pointed to by SP is stored into F and SP is incremented. The memory location pointed to by SP is stored into A and SP is incremented again"); 
           M_POP(z80, AF);break;
        case POP_BC:       debug_opcode(z80, "POP_BC", "The memory location pointed to by SP is stored into C and SP is incremented. The memory location pointed to by SP is stored into B and SP is incremented again"); 
           M_POP(z80, BC);break;
        case POP_DE:       debug_opcode(z80, "POP_DE", "The memory location pointed to by SP is stored into E and SP is incremented. The memory location pointed to by SP is stored into D and SP is incremented again"); 
           M_POP(z80, DE);break;
        case POP_HL:       debug_opcode(z80, "POP_HL", "The memory location pointed to by SP is stored into L and SP is incremented. The memory location pointed to by SP is stored into H and SP is incremented again"); 
           M_POP(z80, HL);break;

        case EX_AF_AFl:      debug_opcode(z80, "EX_AF_AFl","Exchanges the 16bit contents of AF and AFl"); 
            J = z80->registers.AF;
            z80->registers.AF = z80->registers.AFl;
            z80->registers.AFl = J;
            break;  
        case EX_DE_HL:      debug_opcode(z80, "EX_DE_HL","Exchanges the 16bit contents of DE and HL");
            J = z80->registers.DE;
            z80->registers.DE = z80->registers.HL;
            z80->registers.HL = J;
            break;
        case EX_xSP_HL:      debug_opcode(z80, "EX_xSP_HL","Exchanges (SP) with L, and (SP+1) with H");
            J = z80->registers.HL;
            SET_WORD(z80->registers.HL, RdZ80(z80, z80->registers.SP),  
                                        RdZ80(z80, z80->registers.SP + 1)); 
            
            WrZ80(z80, z80->registers.SP, LSB(J));
            WrZ80(z80, z80->registers.SP+1, MSB(J));
            
            break;
        case EXX:      debug_opcode(z80, "EXX","Exchanges the 16bit contents of BC, DE and HL with BC', DE' and HL'"); 
            J = z80->registers.BC;
            z80->registers.BC =z80->registers.BCl;
            z80->registers.BCl = J;

            J = z80->registers.DE;
            z80->registers.DE = z80->registers.DEl;
            z80->registers.DEl = J;
            
            J = z80->registers.HL;
            z80->registers.HL = z80->registers.HLl;
            z80->registers.HLl = J;
            break;



        case DI:      debug_opcode(z80, "DI","Resets both interrupt flip-flops, thus prenting maskable interrups from triggering");
            if(z80->registers.IFF & IFF_EI) z80->registers.PC += z80->IBackup-1;
            z80->registers.IFF &= ~(IFF_1 | IFF_2 | IFF_EI);
            break;
        case EI:      debug_opcode(z80, "EI","Sets both interrupt flip-flops, thus allowing maskable interrupts to occur. An interrupt will not occur. An interrupts will not occur until after the immediatedly following instruction.");
            if((z80->registers.IFF & (IFF_1 | IFF_EI)) == 0x0)
            {
                z80->registers.IFF |= IFF_2 | IFF_EI;
                z80->IBackup = z80->ICount;
                z80->ICount = 1;
            }
              break;

        case DAA:      debug_opcode(z80, "DAA","Adjusts a for BCD addition and subtraction operations");
            J = MSB(z80->registers.AF);
            if(LSB(z80->registers.AF) & C_FLAG) J |= 256;
            if(LSB(z80->registers.AF) & H_FLAG) J |= 512;
            if(LSB(z80->registers.AF) & N_FLAG) J |= 1024;
            z80->registers.AF = DAATable[J];
            break;


        case HALT:      debug_opcode(z80, "HALT","Suspends CPU operation until an interrupt or reset occurs");
            z80->registers.PC--;
            z80->registers.IFF |= IFF_HALT;
            z80->IBackup = 0;
            break;

        //253