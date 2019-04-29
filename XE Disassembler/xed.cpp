/******************************************************************************
 * Members: John Jacobsen, Carson Elmer, Daniel Valoria
 * Class User Accounts: cssc0400, cssc0401, cssc0402
 * REDIDs: 820405580, 820252778, 820103915
 * 
 * CS530, Spring 2019
 * Assignment #2, XE Disassembler
 * Filename: xed.cpp
 * Purpose: Driver program
 ******************************************************************************/

#include "xed.h"

int main(int argc, char* argv[]) {

    //TODO PERFORM MORE CHECKS
    if (argc != 2) {
        std::cerr << "Incorrect number of runtime arguments" << std::endl;
        exit(-1);
    }

    std::string objFileName = argv[1];
    if (objFileName.substr(objFileName.find_last_of(".") + 1) != "obj") {
        std::cerr << "First argument is not of type 'obj', read " << objFileName << " instead." << std::endl;
        exit(-1);
    }

    std::ifstream objFile(argv[1], std::ifstream::in);
    if (!objFile) {
        std::cerr << "Obj file not found" << std::endl;
        exit(-1);
    }
    std::string filename = objFileName.substr(0, objFileName.find_last_of("."));
    std::string temp = filename;
    std::string symFileName = temp.append(".sym");
    
    std::ifstream sysFile(symFileName.c_str(), std::ifstream::in);
    if (!sysFile) {
        std::cerr << "Sys file not found" << std::endl;
        exit(-1);
    }
    
    symFile readSymFile;
    readSymFile.readSymFile(symFileName);
    
    char lineInitialChar;
    std::string currentReadinLine;
    std::string programName;
    std::string programStartingAddress;
    std::string lengthObjectProgram;
    std::string firstExecutableAddress;
    ProcessTextRecord processRecord;

    while (std::getline(objFile, currentReadinLine)) {

        lineInitialChar = currentReadinLine.at(0);
        
        std::string start;
        std::string length;
        std::string objectCode;
        
        switch (lineInitialChar) {
            case 'H':   programName = currentReadinLine.substr(1, 6);
                        programStartingAddress = currentReadinLine.substr(7, 6);
                        lengthObjectProgram = currentReadinLine.substr(13, 6);
                        break;
                        
            case 'T':   start = currentReadinLine.substr(1, 6);
                        length = currentReadinLine.substr(7, 2);
                        objectCode = currentReadinLine.substr(9);
                        processRecord.processRecord(objectCode, symFileName);
                        break;
			break;
                        
            case 'M':   start = currentReadinLine.substr(1, 6);
                        length = currentReadinLine.substr(7, 2);
                        break;
                        
            case 'E':   firstExecutableAddress = currentReadinLine.substr(1);
                        break;
                      
            default:    std::cout << "Invalid obj file formatting" << std::endl;
                        exit(-1);
        }
    }
    
	std::vector<int> addresses = processRecord.getLocation();
	std::vector<std::string> labels = processRecord.getLabels();
	std::vector<std::string> mneumonics = processRecord.getMneumonics();
	std::vector<std::string> operands = processRecord.getOperands();
	std::vector<std::string> objCodes = processRecord.getObjCodes();
	int indexCtr = processRecord.getIndexCtr();
	
	OutputFiles output;
	output.progInfo(programName, programStartingAddress, lengthObjectProgram, firstExecutableAddress, indexCtr, filename);
	output.outputToSIC(labels, mneumonics, operands);
	output.outputToLIS(addresses, labels, mneumonics, operands, objCodes);
	
	objFile.close();
}
