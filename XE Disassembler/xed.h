/******************************************************************************
 * Members: John Jacobsen, Carson Elmer, Daniel Valoria
 * Class User Accounts: cssc0400, cssc0401, cssc0402
 * REDIDs: 820405580, 820252778, 820103915
 * 
 * CS530, Spring 2019
 * Assignment #2, XE Disassembler
 * Filename: xed.h
 * Purpose: Header file for xed.cpp
 ******************************************************************************/

#ifndef XED_H
#define XED_H

#include "opTable.h"
#include "OutputFiles.h"
#include "ProcessTextRecord.h"
#include "symFile.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <fstream>
#include <vector>

class xed {
public:
     /**
    * Function: main
    * Prototype: int xed::main(int argc, char *argv[])
    * Purpose: Driver Program 
    *   Reads in the .obj and .sym file contents.
    *   symFile.cpp separates into SYMTAB and LITTAB.
    *   opTable.cpp holds OPTAB.
    *   Loops through .obj code, separating and processing Header, Modification, and End Records.
    *   ProcessTextRecord.cpp disassembles the Text record and prepares for output.
    *   OutputFiles.cpp outputs disassembled object code to .sic and .lis files.
    * Parameters: 
    *   int argc - number of arguments
    *   char*argv[] - arguments
    * Returns: 
    *   success (0), failure (1)
    */
   int main(int argc, char *argv[]);
};

#endif