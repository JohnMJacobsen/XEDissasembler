/******************************************************************************
 * Members: John Jacobsen, Carson Elmer, Daniel Valoria
 * Class User Accounts: cssc0400, cssc0401, cssc0402
 * REDIDs: 820405580, 820252778, 820103915
 * 
 * CS530, Spring 2019
 * Assignment #2, XE Disassembler
 * Filename: ProcessTextRecord.h
 * Purpose: Header file for ProcessTextRecord.cpp
******************************************************************************/

#ifndef PROCESSTEXTRECORD_H
#define PROCESSTEXTRECORD_H

class opTable;

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include "opTable.h"
#include "symFile.h"


const int NUM_FLAGS = 6;                            // nixbpe

/**
 * Class Name: ProcessTextRecord
 * Description: Disassembles text record object code.
 */
class ProcessTextRecord : public opTable {
private:
    std::string objCode;                            // string of obj code
    std::string symName;                            // symbol name
    std::string litName;                            // literal name
    
    int progCtr;                                    // program counter
    int baseCtr;                                    // base counter
    int charsToRead;                                // char length in one segment of object code
    int indexCtr;                                   // line counter
    int flags[6];                                   // flags n, i, x, b, p, e

    /**
     * Function: findFormat
     * Prototype: int ProcessTextRecord::findFormat(std::string objCode)
     * Purpose: Retrieves format of instruction.
     * Parameters: 
     *      objCode - individual instruction's object code
     * Returns: Format
     */
    int findFormat(std::string objCode);

    /**
     * Function: findOpCode
     * Prototype: int ProcessTextRecord::findOpCode(std::string objCode, int format)
     * Purpose: Retrieves OpCode of instruction.
     * Parameters: 
     *      objCode - individual instruction's object code
     *      format - format of instruction
     * Returns: Op Code (in hex)
     */
    int findOpCode(std::string objCode, int format);

    /**
     * Function: setFlags
     * Prototype: void ProcessTextRecord::setFlags(std::string objCode)
     * Purpose: Sets the nixbpe flags in the flags[] array.
     * Parameters: 
     *      objCode - individual instruction's object code
     *      opCode - op code of instruction
     * Returns: None
     */
    void setFlags(std::string objCode, int opCode);
    
    /**
     * Function: findMneumonic
     * Prototype: std::string ProcessTextRecord::findMneumonic(int opCode)
     * Purpose: Retrieves mneumonic for output
     * Parameters: 
            opCode - op code of the instruction
     * Returns: mneumonic from opTable
     */
    std::string findMneumonic(int opCode);

    /**
     * Function: findDisp
     * Prototype: int ProcessTextRecord::findDisp(std::string objCode, int format)
     * Purpose: Pulls out displacement from instruction. Makes positive if not so already.
     * Parameters:
     *     objCode - individual instruction's object code
     *     format - format of instruction
     * Returns: displacement (in hex)
     */
    int findDisp(std::string objCode, int format);

    /**
     * Function: calcTargetAddr
     * Prototype: int ProcessTextRecord::calcTargetAddr(int disp, int format)
     * Purpose: Calculates and returns the Target Address.
     * Parameters: 
     *      disp - displacement
     *      format - format
     * Returns: target address (in hex)
     */
    int calcTargetAddr(int disp, int format);

    /**
     * Function: checkSymTab
     * Prototype: bool ProcessTextRecord::checkSymTab(int targetAddr)
     * Purpose: Checks if targetAddr is a symbol.
     * Parameters: 
            targetAddr - target address
     * Returns: whether target address is a symbol
     */
    bool checkSymTab(int targetAddr);

    /**
     * Function: checkLitTab
     * Prototype: bool ProcessTextRecord::checkLitTab(int targetAddr)
     * Purpose: Checks if targetAddr is a literal.
     * Parameters: 
            targetAddr - target address
     * Returns: whether targetAddr is a literal
     */
    bool checkLitTab(int targetAddr);
    
    /**
     * Function: getRegisters
     * Prototype: std::string ProcessTextRecord::getRegisters(std::string objCode, int opCode)
     * Purpose: Gets registers 1 & 2 to be inputed into operand vector
     * Parameters: 
            objCode - individual instruction's object code
            opCode - op code of instruction
     * Returns: string of registers for operand vector - "R1, R2"
     */
    std::string getRegisters(std::string objCode, int opCode);


public:
    ProcessTextRecord();                    //initializer method
    std::vector<symFile::symbols> symTab;            //SYMTAB
    std::vector<symFile::literals> litTab;           //LITTAB
    std::vector<std::string> mneumonics;    //stores each instruction for .sic && .lis file
    std::vector<std::string> lits;          //stores literals for .sic && .lis files
    std::vector<std::string> syms;          //stores symbols for .sic && .lis files
    std::vector<std::string> labels;        //stores labels for .sic && .lis files
    std::vector<std::string> operands;      //stores operands for .sic && .lis files
    std::vector<int> location;              //stores location of PC for .lis file
    std::vector<std::string> objCodes;              //stores objCodes for .lis file

    /**
     * Function: processRecord
     * Prototype: ProcessTextRecord::processRecord(std::string record)
     * Purpose: Processes the Text Record
     * Parameters: 
     *      record - the string that holds the object codes of the text record
     * Returns: None
     */
    void processRecord(std::string record, std::string filename);

    /**
     * Function: getSymbolName
     * Prototype: std::string ProcessTextRecord::getSymName(int loc)
     * Purpose: Gets the symbol name.
     * Parameters: 
     *      loc - where to get symbol name from.
     * Returns: symbol name
     */
    std::string getSymName(int loc);

    /**
     * Function: getLitName
     * Prototype: std::string ProcessTextRecord::getLitName(int loc)
     * Purpose: Gets the literal name.
     * Parameters: 
     *      loc - where to get literal name from.
     * Returns: literal name
     */
    std::string getLitName(int loc);

    /**
     * Function: getLitLen
     * Prototype: int ProcessTextRecord::getLitLen(int loc)
     * Purpose: Gets the literal length.
     * Parameters: 
     *      loc - where to get literal length from.
     * Returns: literal length
     */
    int getLitLen(int loc);
    
    /**
     * Function: getHexValue
     * Prototype: int ProcessTextRecord::getHexValue(std::string objCode)
     * Purpose: Parses hex value from string.
     * Parameters: 
     *      objCode - segment of object code to be converted to hex.
     * Returns: unsigned int hex value
     */
    int getHexValue(std::string objCode);
    
    /**
     * Function: getLocation
     * Prototype: std::vector<int> ProcessTextRecord::getLocation()
     * Purpose: Gets location vector for output
     * Parameters: None
     * Returns: location vector
     */
    std::vector<int> getLocation();
    
    /**
     * Function: getLabels
     * Prototype: std::vector<std::string> ProcessTextRecord::getLabels()
     * Purpose: Gets labels vector for output
     * Parameters: None
     * Returns: labels vector
     */
    std::vector<std::string> getLabels();
    
    /**
     * Function: getMneumonics
     * Prototype: std::vector<std::string> ProcessTextRecord::getMneumonics()
     * Purpose: Gets mneumonics vector for output
     * Parameters: None
     * Returns: mneumonics vector
     */
    std::vector<std::string> getMneumonics();
    
    /**
     * Function: getOperands
     * Prototype: std::vector<std::string> ProcessTextRecord::getOperands()
     * Purpose: Gets operands vector for output
     * Parameters: None
     * Returns: operands vector
     */
    std::vector<std::string> getOperands();
    
    /**
     * Function: getObjCodes
     * Prototype: std::vector<string> ProcessTextRecord::getObjCodes()
     * Purpose: Gets objCodes vector for output
     * Parameters: None
     * Returns: objCodes vector
     */
    std::vector<std::string> getObjCodes();
    
    /**
     * Function: getIndexCtr
     * Prototype: int ProcessTextRecord::getIndexCtr()
     * Purpose: Gets index counter for output
     * Parameters: None
     * Returns: indexCtr
     */
    int getIndexCtr();
};
#endif

