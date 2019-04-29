/******************************************************************************
 * Members: John Jacobsen, Carson Elmer, Daniel Valoria
 * Class User Accounts: cssc0400, cssc0401, cssc0402
 * REDIDs: 820405580, 820252778, 820103915
 * 
 * CS530, Spring 2019
 * Assignment #2, XE Disassembler
 * Filename: README.md

 ******************************************************************************/

Files included in this project:

*  makefile
*  opTable.cpp
*  opTable.h
*  OutputFiles.cpp
*  OutputFiles.h
*  ProcessTextRecord.cpp
*  ProcessTextRecord.h
*  README.md
*  sample.lis
*  sample.obj
*  sample.sic
*  sample.sym
*  sample2.lis
*  sample2.obj
*  sample2.sic
*  sample2.sym
*  symFile.cpp
*  symFile.h
*  xed.cpp
*  xed.h


Compile Instructions: Run command: make

Operating instructions: $ ./xed *filename.obj*

Description of significant design decisions:
* Main Program (xed.cpp): 
*       Reads in files 
*       Reads Header, Text, Modification, and End Records
* Disassemble Text Record (ProcessTextRecord.cpp): 
*       Disassembles Text Record
*       Prepares output
* Process Tables (opTable.cpp, symFile.cpp): 
*       Reads in SYMTAB and LITTAB
*       Places into vector data structure
*       Generates OPTAB
* Generate Output Files (OutputFiles.cpp)
*       Formats output for .sic file
*       Formats output for .lis file


List of extra features/algorithms/functionality included which were not required: 
*  No extra features included in this program.

List of all known deficiencies or bugs:
*  Program cannot handle EQU, ORG, BYTE, or WORD assembler directives.
*  Program can only reserve bytes and words at the end of the program.

Lessons Learned:
* How to work collaboratively with a group to complete a large project
* How to design a large-scale project using software engineering techniques
* How an object program is disassembled
* How the different records work
* How to create a .lis file

