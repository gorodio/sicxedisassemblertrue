/**************************************************
*  Authors: Sami Badra, masc0673                  *
*           Genaro Orodio, masc0633               *
*           Daniel Silva, masc0624                *
*  Class: CS 530, Spring 2015, TTH 5:30-6:45 PM   *
*  Professor: Guy Leonard                         *
*  Assignment: Assignment #2, SIC/XE Dissassembler*
*  Completion Date: April 27, 2015                *
*                                                 *
*  Filename: main.cpp                             *
*                                                 *
*  This program will disassemble an object file   *
*  and write the contents to a .sic file. Works   *
*  in reverse to a SIC/XE assembler.              *            
*                                                 *
**************************************************/

#include <vector>
#include "OpCode.h"

using namespace std;

#include "Dasm.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <filename>.obj" << endl;
        exit(EXIT_FAILURE);
    }
    Dasm *disassembler = new Dasm;
    disassembler->openFiles(*(argv+1));
    disassembler->disassemble();
    
    return 0;
}
