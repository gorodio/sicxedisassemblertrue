/**************************************************
*  Authors: Sami Badra, masc0673                  *
*           Genaro Orodio, masc0633               *
*           Daniel Silva, masc0624                *
*  Class: CS 530, Spring 2015, TTH 5:30-6:45 PM   *
*  Professor: Guy Leonard                         *
*  Assignment: Assignment #2, SIC/XE Dissassembler*
*  Completion Date: April 27, 2015                *
*                                                 *
*  Filename: OpCode.h                             *
*                                                 *
*  This program will disassemble an object file   *
*  and write the contents to a .sic file. Works   *
*  in reverse to a SIC/XE assembler.              *            
*                                                 *
**************************************************/

#ifndef __a2__C_____OpCode__
#define __a2__C_____OpCode__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

class OpCode {
public:
    bool getBit(int input, int position);
    string getOpName(int opCode);
    int getOpFormat(int opCode);
};
#endif /* defined(__a2__C_____OpCode__) */
