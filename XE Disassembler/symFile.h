/******************************************************************************
 * Members: John Jacobsen, Carson Elmer, Daniel Valoria
 * Class User Accounts: cssc0400, cssc0401, cssc0402
 * REDIDs: 820405580, 820252778, 820103915
 * 
 * CS530, Spring 2019
 * Assignment #2, XE Disassembler
 * Filename: symFile.h
 * Purpose: Header file for symFile.h
******************************************************************************/

#ifndef SYMFILE_H
#define SYMFILE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class symFile {
    public:
        //symbol vector class
        class symbols {
            public:
                std::string symName;
                int symAddr;
                std::string symFlag;
                symbols(std::string name, int addr, std::string flag);
        };
        //literal vector class
        class literals {
            public:
                std::string lit;
                int litLen;
                int litAddr;
                literals(std::string name, int len, int addr);
        };
    
    // used to store the contents of the SYMTAB
    std::vector<symbols> symTab;
    //used to store the contents of the LITTAB
    std::vector<literals> litTab;

    /**
     * Function: readSymFile
     * Prototype: void symFile::readSymFile()
     * Purpose: Reads and stores the SYMTAB and LITTAB.
     * Parameters: .sym file name
     * Returns: None
     */
    void readSymFile(std::string filename);
    
    /**
     * Function: getSymTab
     * Prototype: vector<symFile::symbols> symFile::getSymTab()
     * Purpose: gets SYMTAB
     * Parameters: None
     * Returns: SYMTAB
     */
    std::vector<symFile::symbols> getSymTab();
    
    /**
     * Function: getLitTab
     * Prototype: vector<symFile::literals> symFile::getLitTab()
     * Purpose: gets LITTAB
     * Parameters: None
     * Returns: LITTAB
     */
    std::vector<symFile::literals> getLitTab();
};

#endif
