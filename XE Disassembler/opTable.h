/******************************************************************************
 * Members: John Jacobsen, Carson Elmer, Daniel Valoria
 * Class User Accounts: cssc0400, cssc0401, cssc0402
 * REDIDs: 820405580, 820252778, 820103915
 * 
 * CS530, Spring 2019
 * Assignment #2, XE Disassembler
 * Filename: opTable.h
 * Purpose: Header file for opTable.cpp
 ******************************************************************************/

#ifndef OPTABLE_H
#define OPTABLE_H

#include <string>

class opTable {
  private:
     /**
    * Function: opTabs
    * Prototype: opTable::opTabs
    * Purpose: A nested class for the opTable. Stores opCode and mneumonic into one table.
    * Parameters: None
    * Returns: None
    */
    class opTabs {
      public:
        int opCode; //opCode of the instruction
        std::string opName; //mneumonic of the instruction
        opTabs(int newOp, std::string newOpN);
    };

  public:
    opTable();
      /**
     * Function: getMneumonic
     * Prototype: std::string opTable::getMneumonic(int op)
     * Purpose: Returns the mneumonic of the opCode.
     * Parameters: String of the specified mneumonic
     * Returns: A string of the mneumonic;
     */
    std::string getMneumonic(int op);
    
    int opTableSize;//constant size of the opTable
    
    //OPTAB
    opTabs optab[59] = { 
      opTabs(0x18,"ADD"),opTabs(0x58,"ADDF"),opTabs(0x90,"ADDR"),
      opTabs(0x40,"AND"),opTabs(0xB4,"CLEAR"),opTabs(0x28,"COMP"),
      opTabs(0x88,"COMPF"),opTabs(0xA0,"COMPR"),opTabs(0x24,"DIV"),
      opTabs(0x64,"DIVF"),opTabs(0x9C,"DIVR"),opTabs(0xC4,"FIX"),
      opTabs(0xC0,"FLOAT"),opTabs(0xF4,"HIO"),opTabs(0x3C,"J"),
      opTabs(0x30,"JEQ"),opTabs(0x34,"JGT"),opTabs(0x38,"JLT"),
      opTabs(0x48,"JSUB"),opTabs(0x00,"LDA"),opTabs(0x68,"LDB"),
      opTabs(0x50,"LDCH"),opTabs(0x70,"LDF"),opTabs(0x08,"LDL"),
      opTabs(0x6C,"LDS"),opTabs(0x74,"LDT"),opTabs(0x04,"LDX"),
      opTabs(0xD0,"LPS"),opTabs(0x20,"MUL"),opTabs(0x60,"MULF"),
      opTabs(0x98,"MULR"),opTabs(0xC8,"NORM"),opTabs(0x44,"OR"),
      opTabs(0xD8,"RD"),opTabs(0xAC,"RMO"),opTabs(0x4C,"RSUB"),
      opTabs(0xA4,"SHIFTL"),opTabs(0xA8,"SHIFTR"),opTabs(0xF0,"SIO"),
      opTabs(0xEC,"SSK"),opTabs(0x0C,"STA"),opTabs(0x78,"STB"),
      opTabs(0x54,"STCH"),opTabs(0x80,"STF"),opTabs(0xD4,"STI"),
      opTabs(0x14,"STL"),opTabs(0x7C,"STS"),opTabs(0xE8,"STSW"),
      opTabs(0x84,"STT"),opTabs(0x10,"STX"),opTabs(0x1C,"SUB"),
      opTabs(0x5C,"SUBF"),opTabs(0x94,"SUBR"),opTabs(0xB0,"SVC"),
      opTabs(0xE0,"TD"),opTabs(0xF8,"TIO"),opTabs(0x2C,"TIX"),
      opTabs(0xB8,"TIXR"),opTabs(0xDC,"WD")
      };
};

#endif
