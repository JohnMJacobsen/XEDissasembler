/******************************************************************************
 * Members: John Jacobsen, Carson Elmer, Daniel Valoria
 * Class User Accounts: cssc0400, cssc0401, cssc0402
 * REDIDs: 820405580, 820252778, 820103915
 * 
 * CS530, Spring 2019
 * Assignment #2, XE Disassembler
 * Filename: ProcessTextRecord.cpp
 * Purpose: Disassemble Text Records from the .obj file
 ******************************************************************************/
 
 #include "ProcessTextRecord.h"
 
 ProcessTextRecord::ProcessTextRecord() {
    // startingAddr = -1;
    // recordLen = -1;
    progCtr = 0;
    baseCtr = 0;
    charsToRead = 0;
    indexCtr = 0;

    for(int i = 0; i < NUM_FLAGS; i ++)
        flags[i] = 0;

    int size = 100;
    
    mneumonics.resize(size);            //important (.sic && .lis)
    syms.resize(size);
    labels.resize(size);                //important (.sic && .lis)
    lits.resize(size);
    operands.resize(size);              //important (.sic && .lis)
    location.resize(size);              //important (.lis only)
    objCodes.resize(size);              //important (.lis only)
 }
 
 void ProcessTextRecord::processRecord(std::string record, std::string filename) {
        
    symFile readSymFile;
    readSymFile.readSymFile(filename);
    symTab = readSymFile.getSymTab();
    litTab = readSymFile.getLitTab();

    std::string objCodeLine = record;
    while(objCodeLine.length() > 0) {
        int format = findFormat(objCodeLine);   //get format
        charsToRead = format * 2;
        std::string currObjCode = objCodeLine.substr(0, charsToRead);       //get current obj code to be processed
        objCodes[indexCtr] = currObjCode;
        
        int opCode = findOpCode(currObjCode, format);
        if(format == 3 || format == 4)                  //set flags
            setFlags(currObjCode, opCode);
        
        mneumonics[indexCtr] = findMneumonic(opCode);  //get mneumonic for output
        int disp = findDisp(currObjCode, format);
        int targetAddr = calcTargetAddr(disp, format);

        //Special Cases:
        if(opCode == 0x68)      //LDB Instruction
            baseCtr = targetAddr;
            
        if(indexCtr == mneumonics.size() - 1) {
            mneumonics.resize(mneumonics.size() * 2);
            operands.resize(operands.size() * 2);
            labels.resize(labels.size() * 2);
            objCodes.resize(objCodes.size() * 2);
            location.resize(location.size() * 2);
        }
            
        if(format == 1) {
            operands[indexCtr] = "";    //No operand
        } else if(format == 2) {
            operands[indexCtr] = getRegisters(currObjCode, opCode);     //operand = "R1, R2"
            
        } else {
            //at least one of the nbpe flags must be set for sym
            bool flagCheck = ((flags[3] == 1) || (flags[4] == 1) || (flags[5] == 1));
            flagCheck |= (flags[0] == 1);
            
            if(checkSymTab(targetAddr) && flagCheck) {      //check for symbol as operand
                //store in symbols
                std::string sym = getSymName(targetAddr);
                syms[indexCtr] = sym;

                if(flags[2] == 1) {                         //indexed addressing symbol
                    sym.append(", X");
                }
                if((flags[0] == 1) && (flags[1] == 0)) {    //indirect addressing symbol
                    sym.insert(0, "@");
                }
                if((flags[0] == 0) && (flags[1] == 1)) {    //immediate addressing symbol
                    sym.insert(0, "#");
                }
                //store in operands
                operands[indexCtr] = sym;
                
                
            } else if(checkLitTab(disp)) {                  //check for literal as operand
                //store in literals
                std::string lit = getLitName(disp);
                lits[indexCtr] = lit;
                
                //getLitLen() ?
                int indexOfQuote = lits[indexCtr].find("'");
                charsToRead += (lits[indexCtr].substr(3, indexOfQuote)).length();
                
                //store in operands
                operands[indexCtr] = lit;
                
                
            } else {
                if((flags[0] == 0) && (flags[1] == 1)) {    //check for immediate addressing mode
                   std::string value;
                   std::stringstream ss;
                   ss << targetAddr;                        //convert target address toString()
                   ss >> value;
                   
                   value.insert(0,"#");
                   operands[indexCtr] = value;//store in operands
            
                } else {
                    operands[indexCtr] = " ";
                }
            }
            
        }

	if(opCode == 0x4C)      //RSUB Instruction
            operands[indexCtr] = " ";
        
        //stores labels
        if(checkSymTab(progCtr)) {
            labels[indexCtr] = getSymName(progCtr);
        } else {
            labels[indexCtr] = "";
        }
        
        //stores location of PC
        location[indexCtr] = progCtr;
        //updates record
        objCodeLine = objCodeLine.substr(charsToRead);
        progCtr += ceil(charsToRead/2);

        indexCtr++;
    }
    
 }
 
 int ProcessTextRecord::findFormat(std::string objCode) {
    int opCode = getHexValue(objCode.substr(0, 2));
    int f = getHexValue(objCode.substr(2, 1));
    
    switch(opCode) {
        case 0xC4:
        case 0xC0:
        case 0xF4:
        case 0xC8:
        case 0xF0:
        case 0xF8:
            return 1;
        break;
        
        case 0x90:
        case 0x94:
        case 0x98:
        case 0xA0:
        case 0xA4:
        case 0xA8:
        case 0xAC:
        case 0xB0:
        case 0xB4:
        case 0xB8:
            return 2;
        break;
        
        default:
            if(f % 2 != 0)   //e bit set
                return 4;
            return 3;
        break;
    }
 }
 
 int ProcessTextRecord::findOpCode(std::string objCode, int format) {
    std::string opCode = objCode.substr(0,1);
    if(format > 2) {
        switch(objCode.at(1)) {
            case '0':
            case '1': 
            case '2':
            case '3':
                opCode.append("0");
            break;
            
            case '4': 
            case '5':
            case '6':
            case '7':
                opCode.append("4");
            break;
            
            case '8':
            case '9':
            case 'A':
            case 'B':
                opCode.append("8");
            break;
            
            case 'C':
            case 'D':
            case 'E':
            case 'F':
                opCode.append("C");
            break;
            
            default:
            break;
        }
    } else {
        opCode = objCode.substr(0, 2);
    }
    
    return getHexValue(opCode);
 }
 
 void ProcessTextRecord::setFlags(std::string objCode, int opCode) {
    //ni flags
    int ni = getHexValue(objCode.substr(0, 2)) - opCode;
    if(ni == 1) {          //n = 0, i = 1
        flags[0] = 0;
        flags[1] = 1;
    } else if(ni == 2) {   //n = 1, i = 0
        flags[0] = 1;
        flags[1] = 0;
    } else if(ni == 3) {   //n = 1, i = 1
        flags[0] = 1;
        flags[1] = 1;
    }
    
    //xbpe flags
    int xbpe = getHexValue(objCode.substr(2, 1));
    int j = 8;
    for(int i = 0; i < 4; i++) {
        if((xbpe/j) == 1) {
            flags[i+2] = 1;
            xbpe %= j;
        } else {
            flags[i+2] = 0;
        }
        j/=2;
    }
 }
 
 std::string ProcessTextRecord::findMneumonic(int opCode) {
    opTable opTab;
    std::string m = opTab.getMneumonic(opCode);
    if(flags[5] == 1)
        m.insert(0, "+");
    return m;
 }
 
 int ProcessTextRecord::findDisp(std::string objCode, int format) {
    if(format > 2) {
        return getHexValue(objCode.substr(3));
    }
    return -1;
 }
 
 int ProcessTextRecord::calcTargetAddr(int disp, int format) {
    int target = -1;
    if(format == 3) {
        //n, i flags set or indirect addressing
        if((flags[0] == 1 && flags[1] == 1) || (flags[0] == 1 && flags[1] == 0)) {
            if(flags[3] == 1) {                         //b flag set
                target = (baseCtr + disp);
            } else if(flags[4] == 1) {                  //p flag set
                target = (progCtr + disp + 3);
		        if(target > 4096) {
        		    target -= 4096;
    		    }
            }
        } else {                                        //n = 1 || i = 1
            target = disp;
        } 
    } else if(format == 4) {                            //e flag set
        target = disp;
    }
    return target;
 }
 
 std::string ProcessTextRecord::getRegisters(std::string objCode, int opCode) {
    char r1 = objCode.at(2);               //register 1
    char r2 = objCode.at(3);               //register 2
    std::string regs;
    switch(r1) {
        case '0': regs = "A";
        break;
        
        case '1': regs = "X";
        break;
        
        case '2': regs = "L";
        break;
        
        case '3': regs = "B";
        break;
        
        case '4': regs = "S";
        break;
        
        case '5': regs = "T";
        break;
        
        case '6': regs = "F";
        break;
        
        default: regs = "r1";
        break;
    } 
    if(opCode == 0xB4 || opCode == 0xB8) {
        return regs;
    }
    switch(r2) {
        case '0': regs.append(",A");
        break;
        
        case '1': regs.append(",X");
        break;
        
        case '2': regs.append(",L");
        break;
        
        case '3': regs.append(",B");
        break;
        
        case '4': regs.append(",S");
        break;
        
        case '5': regs.append(",T");
        break;
        
        case '6': regs.append(",F");
        break;
        
        default: regs.append("r2");
        break;
    }
    return regs;
 }
 
 bool ProcessTextRecord::checkSymTab(int loc) {
    for(int i = 0; i < symTab.size(); i++) {
        if(symTab[i].symAddr == loc)
            return true;
    }
    return false;
 }
 
 bool ProcessTextRecord::checkLitTab(int loc) {
    for(int i = 0; i < litTab.size(); i++) {
        if(litTab[i].litAddr == loc) {
            return true;
	    }
    }
    return false;
 }
 
 std::string ProcessTextRecord::getSymName(int loc) {
    for(int i = 0; i < symTab.size(); i++) {
        if(symTab[i].symAddr == loc)
            return symTab[i].symName;
    }
    return NULL;
 }
 
 std::string ProcessTextRecord::getLitName(int loc) {
    for(int i = 0; i < litTab.size(); i++) {
        if(litTab[i].litAddr == loc)
            return litTab[i].lit;
    }
    return NULL;
 }
 
 int ProcessTextRecord::getHexValue(std::string objCode) {
    int x = 0;   
    std::istringstream(objCode) >> std::hex >> x;
    return x;
 }
 
 std::vector<int> ProcessTextRecord::getLocation() {
     return location;
 }
 
 std::vector<std::string> ProcessTextRecord::getLabels() {
     return labels;
 }
 
 std::vector<std::string> ProcessTextRecord::getMneumonics() {
     return mneumonics;
 }
 
 std::vector<std::string> ProcessTextRecord::getOperands() {
     return operands;
 }
 
 std::vector<std::string> ProcessTextRecord::getObjCodes() {
     return objCodes;
 }
 
 int ProcessTextRecord::getIndexCtr() {
     return indexCtr;
 }
 
