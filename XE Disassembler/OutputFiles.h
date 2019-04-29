/******************************************************************************
 * Members: John Jacobsen, Carson Elmer, Daniel Valoria
 * Class User Accounts: cssc0400, cssc0401, cssc0402
 * REDIDs: 820405580, 820252778, 820103915
 * 
 * CS530, Spring 2019
 * Assignment #2, XE Disassembler
 * Filename: OutputFiles.h
 * Purpose: Header file for OutputFiles.cpp
******************************************************************************/

#ifndef OUTPUTFILES_H
#define OUTPUTFILES_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <fstream>
#include "symFile.h"


const int NUM_SPACES = 8;                            //column width

/**
 * Class Name: OutputFiles
 * Description: Dissassembles text record object code.
 */
class OutputFiles {
private:
    int indexCtrSIC;
    int indexCtrLIS;
    std::string progName;
    int startAddr;
    int progLen;
    std::string firstExecInstr;
    std::string filename;

public:
    OutputFiles();                                  //initializer method
    
    std::vector<symFile::symbols> symTab;           //SYMTAB
    std::vector<std::string> mneumonics;            //stores each instruction
    std::vector<std::string> labels;                //stores labels
    std::vector<std::string> operands;              //stores operands
    std::vector<int> addresses;                     //stores location
    std::vector<std::string> objCodes;              //stores objCodes

    /**
     * Function: progInfo
     * Prototype: 
     *      OutputFiles::progInfo(std::string programName, 
     *          std::string startingAddress, 
     *          std::string programLength, 
     *          std::string firstExecutableInstruction, 
     *          int indexCounter,
     *          std::vector<SymbolTable> symbols)
     * Purpose: Obtain program information
     * Parameters: 
     *      programName - name of the program
     *      startingAddress - address of first executable instruction
     *      programLength - length of the program
     *      firstExecutableInstruction - first executable instruction
     *      fileName - name of the file
     * Returns: None
     */
    void progInfo(std::string programName, 
             std::string startingAddress, 
             std::string programLength, 
             std::string firstExecutableInstruction, 
             int indexCounter,
             std::string fileName);    

    /**
     * Function: getHexValue
     * Prototype: int OutputFiles::getHexValue(std::string str)
     * Purpose: Parses hex value from string.
     * Parameters: 
     *      str - string to be converted to hex.
     * Returns: unsigned int hex value
     */
    int getHexValue(std::string str);

        /**
     * Function: outputToSIC
     * Prototype: OutputFiles::outputToSIC(std::vector<std::string> outputLabels, 
	    std::vector<std::string> outputMneumonics, 
	    std::vector<std::string> outputOperands)
     * Purpose: Outputs contents of the Header, Text, and End records to the .sic file.
     * Parameters: 
     *      outputLabels - vector containing all labels
     *      outputMneumonics - vector containing all mneumonics
     *      outputOperands - vector containing all operands
     * Returns: None
     */
    void outputToSIC(std::vector<std::string> outputLabels, 
	    std::vector<std::string> outputMneumonics, 
	    std::vector<std::string> outputOperands);
    
    /**
     * Function: outputToLIS
     * Prototype: 
     *      OutputFiles::outputToLIS(std::vector<int> outputAddresses, std::vector<std::string> outputLabels, 
	            std::vector<std::string> outputMneumonics, 
	            std::vector<std::string> outputOperands.
	            std::vector<int> outputObjCodes)
     * Purpose: Outputs contents of the Header, Text, and End records to the .lis file, along with addresses and objCodes.
     * Parameters: 
     *      outputAddresses - vector containing all addresses
     *      outputLabels - vector containing all labels
     *      outputMneumonics - vector containing all mneumonics
     *      outputOperands - vector containing all operands
     *      outputObjCodes - vector containing all objCodes
     * Returns: None
     */
    void outputToLIS(std::vector<int> outputAddresses, std::vector<std::string> outputLabels, 
	       std::vector<std::string> outputMneumonics, 
	       std::vector<std::string> outputOperands,
	       std::vector<std::string> outputObjCodes);
};
#endif
