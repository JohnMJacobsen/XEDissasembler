###########################################################
# File Name: makefile
# Members: John Jacobsen, Carson Elmer, Daniel Valoria
# Class User Accounts: cssc0400, cssc0401, cssc0402
# REDIDs: 820405580, 820252778, 820103915
# CS530, Spring 2019
# Assignment #2, XE Disassembler
# Usage: run command: make -f makefile
# Output File: "outputFile"
###########################################################

# CC tells makefile to compile using g++ for .cpp files
# Fx, where x = files to be compiled
# OUT is the name of the output file

CC = g++

F1 = "xed.cpp"
F2 = "ProcessTextRecord.cpp"
F3 = "symFile.cpp"
F4 = "OutputFiles.cpp"
F5 = "opTable.cpp"

OUT = "outputFile"

all:
	$(CC) $(F1) $(F2) $(F3) $(F4) $(F5) -w -o $(OUT)

#######################[ EOF: Makefile ]###################