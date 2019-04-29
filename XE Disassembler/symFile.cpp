/******************************************************************************
 * Members: John Jacobsen, Carson Elmer, Daniel Valoria
 * Class User Accounts: cssc0400, cssc0401, cssc0402
 * REDIDs: 820405580, 820252778, 820103915
 * 
 * CS530, Spring 2019
 * Assignment #2, XE Disassembler
 * Filename: symFile.cpp
 * Purpose: Read and process .sym file
******************************************************************************/

#include "symFile.h"

//symbol nested class constructor
symFile::symbols::symbols(std::string name, int addr, std::string flag) {
    symName = name;
    symAddr = addr;
    symFlag = flag;
}

//literal nested class constructor
symFile::literals::literals(std::string name, int len, int addr) {
    lit = name;
    litLen = len;
    litAddr = addr;
}

void symFile::readSymFile(std::string filename) {

    std::ifstream file(filename.c_str());

    //skips the table headers
    file.ignore(50,'\n');
    file.ignore(50,'\n');

    std::string first, second, third;   //a, b, c
    int value, litAddr;                 //valLen, addr
    int x = 0;

    if(file.is_open()) {
        //reading SYMTAB
        while(file >> first >> second >> third) {
            //reading LITTAB
            if(first == "Name") {
                //skips the table headers
                file.ignore(50,'\n');
                file.ignore(50,'\n');
                while(file >> first >> second >> third) {
                    std::istringstream(second) >> std::hex >> value;
                    std::istringstream(third) >> std::hex >> litAddr;
                    litTab.push_back(literals(first, value, litAddr));
                }
            break;
            }

            std::istringstream(second) >> std::hex >> value;
            symTab.push_back(symbols(first, value, third));
        }
    }

    file.close();
}

std::vector<symFile::symbols> symFile::getSymTab() {
    return symTab;
}

std::vector<symFile::literals> symFile::getLitTab() {
    return litTab;
}


