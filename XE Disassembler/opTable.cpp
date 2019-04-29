/******************************************************************************
 * Members: John Jacobsen, Carson Elmer, Daniel Valoria
 * Class User Accounts: cssc0400, cssc0401, cssc0402
 * REDIDs: 820405580, 820252778, 820103915
 *
 * CS530, Spring 2019
 * Assignment #2, XE Disassembler
 * Filename: opTable.cpp
 * Purpose: Provides OPTAB
******************************************************************************/

#include "opTable.h"

/**
* Function: opTabs
* Prototype: ReadTables::opTabs::opTabs(int newOpCode, std::string newOpName)
* Purpose: Constructor for the table of opCode object.
* Parameters:
*   newOpCode - opCode of the instruction
*   newOpName - mneumonic of the instruction
* Returns: None
*/
opTable::opTabs::opTabs(int newOpCode, std::string newOpName) {
    opCode = newOpCode;
    opName = newOpName;
}

opTable::opTable() {
    opTableSize = 59; //sets opTableSize to 59, for all instructions
}

std::string opTable::getMneumonic(int op) {
    int newOp = op&0xFC;
    for(int i=0;i<opTableSize;i++) {
       if(optab[i].opCode==newOp)
           return optab[i].opName;
    }
    return NULL;
}