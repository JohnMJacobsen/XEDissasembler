/******************************************************************************
 * Members: John Jacobsen, Carson Elmer, Daniel Valoria
 * Class User Accounts: cssc0400, cssc0401, cssc0402
 * REDIDs: 820405580, 820252778, 820103915
 * 
 * CS530, Spring 2019
 * Assignment #2, XE Disassembler
 * Filename: OutputFiles.cpp
 * Purpose: Format output for .sic && .lis file
******************************************************************************/

#include "OutputFiles.h"

//constructor
OutputFiles::OutputFiles() {
    indexCtrSIC = 0;
    indexCtrLIS = 0;
    int size = 100;
    
    addresses.resize(size);              //important (.lis only)
    labels.resize(size);                //important (.sic && .lis)
    mneumonics.resize(size);            //important (.sic && .lis)
    operands.resize(size);              //important (.sic && .lis)
    objCodes.resize(size);              //important (.lis only)
}

void OutputFiles::progInfo(std::string programName, 
    std::string startingAddress, 
    std::string programLength, 
    std::string firstExecutableInstruction,
    int indexCounter,
    std::string fileName) {
        
    progName = programName;
    startAddr = getHexValue(startingAddress);
    progLen = getHexValue(programLength);
    firstExecInstr = firstExecutableInstruction;
    indexCtrLIS = indexCounter;
    indexCtrSIC = indexCounter;
    filename = fileName;
    std::string symfile = filename + ".sym";
    symFile readSymFile;
    readSymFile.readSymFile(symfile);
    symTab = readSymFile.getSymTab();
}

void OutputFiles::outputToSIC(std::vector<std::string> outputLabels, 
	    std::vector<std::string> outputMneumonics, 
	    std::vector<std::string> outputOperands) {
    labels = outputLabels;
    mneumonics = outputMneumonics;
    operands = outputOperands;
    
    //Create .sic file
    std::ofstream ofs;
    std::string sic = filename;
    std::string sicFile = sic.append(".sic");
    ofs.open(sicFile.c_str());
    
    std::string lastSym = "";
    int lastSymIndex = 0;
   
    //Output Header Record
    ofs << std::setw(NUM_SPACES) << std::left << progName;
    ofs << std::setw(NUM_SPACES + 1) << " START";
    ofs << std::setw(NUM_SPACES) << startAddr << std::endl;
        
    //Output Labels, Mneumonics, and Operands
    for(int i = 0; i < indexCtrSIC; i ++) {
        
        if(indexCtrSIC == mneumonics.size() - 1) {
            mneumonics.resize(mneumonics.size() * 2);
            operands.resize(operands.size() * 2);
            labels.resize(labels.size() * 2);
            addresses.resize(addresses.size() * 2);
        }
        
        // Handling BASE assembler directive
        if(i>0 && mneumonics[i-1] == "LDB") {
            std::string baseTA = " " + operands[i-1];
            ofs << std::setw(NUM_SPACES) << "";
            ofs << std::setw(NUM_SPACES) << " BASE";
            ofs << std::setw(NUM_SPACES) << baseTA;
            ofs << std::endl;
        }
        
        //Handling LTORG assembler directive
        if(i>0 && (operands[i-1]).at(0) == '=') {
            ofs << std::setw(NUM_SPACES) << "";
            ofs << std::setw(NUM_SPACES) << " LTORG";
            ofs << std::endl;
        }
        
        //Output label
        ofs << std::setw(NUM_SPACES) << labels[i];
        
        if(labels[i] != "")
            lastSym = labels[i];
            
        if(i>0 && (mneumonics[i]).at(0) == '+') {
            ofs << std::setw(NUM_SPACES) << mneumonics[i];
        } else {
            std::string fullMneumonic = " " + mneumonics[i];
            ofs << std::setw(NUM_SPACES) << fullMneumonic;
        }
        
        switch(operands[i].at(0)) {
            case '#':
            case '@':
            case '=':
            case '+':
                ofs << std::setw(NUM_SPACES) << operands[i];
            break;
            
            default:
                std::string fullOperand = " " + operands[i];
                ofs << std::setw(NUM_SPACES) << fullOperand;
            break;
        }
        ofs << std::endl;
    }
    
    for(int i = 0; i < symTab.size(); i++) {
        if((symTab[i].symName) == lastSym)
            lastSymIndex = i;
    }
    
    bool first = true;
    int addr, diff;
    while(lastSymIndex < symTab.size() - 1) {
        if(indexCtrSIC == addresses.size() - 1)
            addresses.resize(addresses.size() * 2);
            
        if(indexCtrSIC == labels.size() - 1)
            labels.resize(labels.size() * 2);
        
        //addresses[indexCtr] = assigns value of PC at current index
        //diff = calculates difference between address of current index and address of next index
        if(first) {
            addr = symTab[lastSymIndex + 2].symAddr;
            addresses[indexCtrLIS] = symTab[lastSymIndex + 1].symAddr;  //addr + disp
            diff = addr - addresses[indexCtrLIS];
            first = false;
        } else {
            if(lastSymIndex < symTab.size() - 2) {
                addr = symTab[lastSymIndex + 2].symAddr;
                diff = addr - symTab[lastSymIndex + 1].symAddr;
                addresses[indexCtrSIC] = symTab[lastSymIndex + 1].symAddr;
            } else {
                addr = progLen;
                diff = addr - symTab[lastSymIndex + 1].symAddr;
                addresses[indexCtrSIC] = symTab[lastSymIndex + 1].symAddr;
            }
        }
        
        //Output label at current index
        labels[indexCtrSIC] = symTab[lastSymIndex + 1].symName;
        ofs << std::setw(NUM_SPACES) << labels[indexCtrSIC];
        
        //Determine whether to output RESW or RESB
        int numWords = 0;
        if(diff % 3 == 0) {
            numWords = diff / 3;
            ofs << std::setw(NUM_SPACES + 1) << " RESW";
        } else {
            numWords = diff;
            ofs << std::setw(NUM_SPACES + 1) << " RESB";
        }
        
        //Output how many bytes are reserved
        ofs << std::setw(NUM_SPACES) <<  numWords;
        ofs << std::endl;
        
        //Increment indexCtr (new line) and lastSymIndex (new label)
        lastSymIndex++;
        indexCtrSIC++;
    }
    
    //Output End Record
    ofs << std::setw(NUM_SPACES) << "";
    ofs << std::setw(NUM_SPACES) << " END";
    ofs << " "<< std::setw(NUM_SPACES) << symTab[0].symName << std::endl;
    
    ofs.close();

}

void OutputFiles::outputToLIS(std::vector<int> outputAddresses, 
	    std::vector<std::string> outputLabels, 
	    std::vector<std::string> outputMneumonics, 
	    std::vector<std::string> outputOperands, 
	    std::vector<std::string> outputObjCodes) {
    addresses = outputAddresses;
    labels = outputLabels;
    mneumonics = outputMneumonics;
    operands = outputOperands;
    objCodes = outputObjCodes;
    
    //Create .lis file
    std::ofstream ofs;
    std::string lisFile = filename.append(".lis");
    ofs.open(lisFile.c_str());
    
    std::string lastSym = "";
    int lastSymIndex = 0;
    
    //Output Header Record
    ofs << std::setw(4) << std::left << "0000  ";
    ofs << std::setw(9) << std::left << progName;
    ofs << std::setw(8) << std::left << "START";
    ofs << std::setw(5) << startAddr << std::endl;
    
    //Output Labels, Mneumonics, and Operands
    for(int i = 0; i < indexCtrLIS; i ++) {
        
        if(indexCtrLIS == mneumonics.size() - 1) {
            mneumonics.resize(mneumonics.size() * 2);
            operands.resize(operands.size() * 2);
            labels.resize(labels.size() * 2);
            objCodes.resize(operands.size() * 2);
            addresses.resize(addresses.size() * 2);
        }
        
        // Handling BASE assembler directive
        if(i>0 && mneumonics[i-1] == "LDB") {
            std::string baseTA = " " + operands[i-1];
            ofs << std::setw(4) << addresses[i];
            ofs << std::setw(4) << "";
            ofs << std::setw(4) << " BASE";
            ofs << std::setw(4) << baseTA;
            ofs << std::endl;
        }
        
        //Handling LTORG assembler directive
        if(i>0 && (operands[i-1]).at(0) == '=') {
            ofs << std::setfill('0') << std::setw(4) << std::right << addresses[i];
            ofs << std::setfill(' ') << std::setw(2) << " ";
            ofs << std::setw(8) << std::left << "LTORG";
            ofs << std::endl;
        }
        
        //Output address
        ofs << std::setfill('0') << std::setw(4) << std::right << std::hex << addresses[i];
        ofs << std::setw(2) << std::setfill(' ') << " ";
	//std::string temp = addresses[i]; //convert to string
	//temp.length() - 4 = numSpacesToPrint

        //Output label
        ofs << std::setw(8) << std::left << labels[i];
        
        if(labels[i] != "")
            lastSym = labels[i];
            
        //Output mneumonic
        if(i>0 && (mneumonics[i]).at(0) == '+') {
            ofs << std::setw(8) << std::left << mneumonics[i];
        } else {
            std::string fullMneumonic = " " + mneumonics[i];
            ofs << std::setw(8) << std::left << fullMneumonic;
        }
        
        //Output operand
        switch(operands[i].at(0)) {
            case '#':
            case '@':
            case '=':
            case '+':
                ofs << std::setw(11) << std::left << operands[i];
            break;
            
            default:
                std::string fullOperand = " " + operands[i];
                ofs << std::setw(11) << std::left << fullOperand;
            break;
        }
        
        //Output objCode
        ofs << std::setw(4) << std::right << objCodes[i];        
        ofs << std::endl;
        
    }
    
    for(int i = 0; i < symTab.size(); i++) {
        if(symTab[i].symName == lastSym)
            lastSymIndex = i;
    }
    
    bool first = true;
    int addr, diff;
    while(lastSymIndex < symTab.size() - 1) {
        if(indexCtrLIS == addresses.size() - 1)
            addresses.resize(addresses.size() * 2);
            
        if(indexCtrLIS == labels.size() - 1)
            labels.resize(labels.size() * 2);
        
        //addresses[indexCtr] = assigns value of PC at current index
        //diff = calculates difference between address of current index and address of next index
        if(first) {
            addr = symTab[lastSymIndex + 2].symAddr;
            addresses[indexCtrLIS] = symTab[lastSymIndex + 1].symAddr; 	//addr + disp
            diff = addr - addresses[indexCtrLIS];
	    first = false;
        } else {
            if(lastSymIndex < symTab.size() - 2) {
                addr = symTab[lastSymIndex + 2].symAddr;
                diff = addr - symTab[lastSymIndex + 1].symAddr;
                addresses[indexCtrLIS] = symTab[lastSymIndex + 1].symAddr;
            } else {
                addr = progLen;
                diff = addr - symTab[lastSymIndex + 1].symAddr;
                addresses[indexCtrLIS] = symTab[lastSymIndex + 1].symAddr;
            }
        }
        
        //Output address at current index
        ofs << std::setfill('0') << std::setw(4) << std::right << std::hex << addresses[indexCtrLIS];
        ofs << std::setw(2) << std::setfill(' ') << " ";
        //Output label at current index
        labels[indexCtrLIS] = symTab[lastSymIndex + 1].symName;
        ofs << std::setw(8) << std::left << labels[indexCtrLIS];
        
        //determines whether to output RESW or RESB
        int numWords = 0;
        if(diff % 3 == 0) {
            numWords = diff / 3;
            ofs << std::setw(9) << std::left << " RESW";
        } else {
            numWords = diff;
            ofs << std::setw(9) << std::left << " RESB";
        }
	int outValue = numWords;
        
        //outputs how many bytes are reserved
        ofs << std::setw(4) <<  std::dec << outValue;
        ofs << std::endl;
        
        //increment indexCtr (new line) and lastSymIndex (new label)
        lastSymIndex++;
        indexCtrLIS++;
    }
    ofs << std::setw(15) << "";
    ofs << std::setw(7) << std::left << "END";
    ofs << " "<< std::setw(4) << symTab[0].symName << std::endl;
    
    ofs.close();
}

int OutputFiles::getHexValue(std::string str){
    int x = 0;   
    std::istringstream(str) >> std::hex >> x;
    return x;
}

