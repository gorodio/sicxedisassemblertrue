###################################################
#  Authors: Sami Badra, masc0673                  #
#           Genaro Orodio, masc0633               #
#           Daniel Silva, masc0624                #
#  Class: CS 530, Spring 2015, TTH 5:30-6:45 PM   #
#  Professor: Guy Leonard                         #
#  Assignment: Assignment #2, SIC/XE Dissassembler#
#  Completion Date: April 27, 2015                #
#                                                 #
#  Filename: MakeFile                             #
#                                                 #
#  This program will disassemble an object file   #
#  and write the contents to a .sic file. Works   #
#  in reverse to a SIC/XE assembler.              #            
#                                                 #
###################################################

CC=g++

CFLAGS=-c

all: dasm

dasm: main.o Dasm.o OpCode.o
	$(CC) main.o Dasm.o OpCode.o -o dasm

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Dasm.o: Dasm.cpp
	$(CC) $(CFLAGS) Dasm.cpp

OpCode.o: OpCode.cpp
	$(CC) $(CFLAGS) OpCode.cpp

clean:
	rm -f core *.o dasm
