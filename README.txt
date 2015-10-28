*************************************************************
*                                                           *
* SOURCE CODE LOCATED IN masc0633, GENARO ORODIO            *
*                                                           *
*************************************************************
 
 
***************************************************
*  Authors: Sami Badra, masc0673                  *
*           Genaro Orodio, masc0633               *
*           Daniel Silva, masc0624                *
*  Class: CS 530, Spring 2015, TTH 5:30-6:45 PM   *
*  Professor: Guy Leonard                         *
*  Assignment: Assignment #2, SIC/XE Dissassembler*
*  Completion Date: April 27, 2015                *
*                                                 *
*  Filename: README.txt                           *
*                                                 *
*  This program will disassemble an object file   *
*  and write the contents to a .sic file. Works   *
*  in reverse to a SIC/XE assembler.              *            
*                                                 *
***************************************************

***********************************************
* FILE MANIFEST:                              *
* Makefile                                    *
* main.cpp                                    *
* OpCode.cpp                                  *
* Dasm.cpp     	                              *
* OpCode.h                                    *
* Dasm.h                                      *
* README.txt                                  *
***********************************************

**************************************************************************
* #####################  INSTRUCTIONS  #######################           *
*                                                                        *         
* Compile instructions: 1. make sure .obj and .sym file in               *
*                          same directory                                *
*                       2. type: make                                    *
*                          to compile.                                   *
*                                                                        *
* Operating instructions:  type dasm <filename>.obj                      *
*                          the disassembled code will be located         *
*                          in a created .sic file in the same            *
*                          directory. A .obj file and its matching .sym  *
*                          file MUST be in the same directory or         *
*                          the program will not proceed.                 *          
**************************************************************************

****************************************************************
* DEFICIENCIES:                                                *
* 1. Only a partial SIC/XE disassembler. Does not have complete*
*    functionally.                                             *
*                                                              *
****************************************************************

*******************************************************
* EXTRA FEATURES:                                     *
* 1. Does file checking and outputs error messages    * 
* 2. Checks user input and outputs error messages     *
* 3. Prints out the listing file                      *       
*******************************************************

************************************************************************************
*   LESSONS LEARNED:                                                               *
*	Designing this program was EXTREMELY DIFFICULT to code alone. Our group    *
*	members each tried to code the program at least once on our own and        *
*	could not do it. This project REQUIRES complete and utter cooperation      * 
*	to finish. The algorithm was the toughest part to grasp. We continually    *
*	met on weekends to discuss how to tackle the project. We programmed side   *
*	by side the majority of the time, and we have learned that teamwork is     *
*	very valuable.                                                             *
*                                                                                  *
*	Bit masking is EXTREMELY useful!                                           *     
*                                                                                  *
*	Another lesson which is pretty obvious, NEVER PUT OFF ASSIGNMENTS,         *
*	especially one of this caliber. Overall, however, the experience of        *
*	working with colleagues on a project together is a fun process. Ideas      *
*	are bounced between one another, ideas are created, and memories are       *  
*	made.                                                                      *
************************************************************************************
                                                                                 
****************************************************************************************
*	SOFTWARE DESIGN PROCESS:                                                       *
*	The first order of business when trying to tackle the project was to figure    *
*	out how and when to meet up to start the pseudocode design process. We each    *
*	brushed up on our SIX/XE machine knowledge before that though. The main        *
*	requirement to writing the pseudocode was to completely understand how to      *
*	read object code, understand the formatting, understand the various records,   *
*	and understand how the assembler was able to come up with the numbers.         *
*                                                                                      *
*	Next, we each needed to understand how to read each individual object code     *
*	instruction, disassemble them, and find the corresponding instruction in the   *
*	table given in the back of the class book. This process was pretty fun and     *
*	felt like trying to solve a puzzle. The first two numbers of the object code   *
*	instruction indicated the corresponding SIC/XE instruction. Based on that      *
*	found instruction, there is a specific format associated with it. If either    *
*	format 3 or format 4, we had to worry about the nixbpe bits. Format 2          *
*	would need to utilize registers and format 1 would not have to worry about     *
*	any other references. With this information we were ready to start writing     *
*	pseudocode for the program.                                                    *
*                                                                                      *
*	We didn't really split up duties or parts of the program to different group    *
*	members as we thought that this would make the assignment harder than it       *
*	needed to be. The only segmentation of duties that was implemented was         *
*	some group members made different cpp/h files and when we met up, we all       *
*	reviewed each member's code and how it affected the overall program.           *
*                                                                                      * 
*	We discussed that we somehow needed to organize the data we needed in an       *
*	efficient and easy to access data structure. This is where we ran into a       *
*	bit of trouble. We had not chosen a language to write the program in. We       *
*	tried to use C, but it proved too difficult to implement some of our ideas.    *
*	We ultimately went with C++ because of its easy to use vector capabilities.    *
*                                                                                      *
*	For instruction lookups, we decided to make a struct which contained all       *  
*	the SIC/XE instructions, as well as the format types, and associated opcode.   *
*	Next, we discussed how to read from the object file and symbol file and        *
*	how to write to a sic file. We utilized streams to do this. Next, we had       *
*	to figure out how to replace the file extension and replace it with another    *
*	one. We used append to attach a new file extension in the form of a string     *
*	to create a new filename.                                                      * 
*                                                                                      *
*	The hardest part was trying to seperate the various chunks of opcode present   *
*	within a given text record of the object file. We knew the amount of spaces    *
*	needed for examination for each format type. With this in mind, we created     *
*	an a function called instructionAnalyzer() which parsed through the object     *
*	code in an efficient manner. Data from this function was then passed through   *
*	another function which analyzed the data based on instruction format. Here     *
*	the hardest algorithm of the assignment was implemented. The algorithm to      *
*	compute the nixbpe bits, addressing modes, and target addresses.               *
*                                                                                      *
*	The following pseudocode is an early version of the horrendous algorithm we    * 
*       used to calculate the various addressing modes via the nixbpe bits:            *
*                                                                                      *         
=============================================================================================
|          // 1 1									    |
|          if (nixbpe[0] == nixbpe[1]) // direct addressing			            |
|            +										    |
|            // 1 1 0 0     								    |
|            if (nixbpe[2] == 1 && nixbpe[3] == 1 && nixbpe[4] == 0 && nixbpe[5] == 0)      |
|              targetAddress = objStorage[row].substr(current+3, 3) + base;     	    |
|            // 1 0 1 0								            |
|            else if (nixbpe[2] == 1 && nixbpe[3] == 0 && nixbpe[4] == 1 && nixbpe[5] == 0) |
|              targetAddress = objStorage[row].substr(current+3, 3) + currentAddress + 3;   |
|            // 1 0 0 1  								    |
|            else if (nixbpe[2] == 1 && nixbpe[3] == 0 && nixbpe[4] == 0 && nixbpe[5] == 1) |
|              targetAddress = objStorage[row].substr(current+4, 3);			    |
|            // 1 0 0 0									    |
|            if (nixbpe[2] == 1 && nixbpe[3] == 0 && nixbpe[4] == 0 && nixbpe[5] == 0)      |
|              targetAddress = objStorage[row].substr(current+3, 3);			    |
|            // 0 1 0 0									    |
|            else if (nixbpe[2] == 0 && nixbpe[3] == 1 && nixbpe[4] == 0 && nixbpe[5] == 0) |
|              targetAddress = objStorage[row].substr(current+3, 3) + base;		    |
|            // 0 0 1 0									    |
|            else if (nixbpe[2] == 0 && nixbpe[3] == 0 && nixbpe[4] == 1 && nixbpe[5] == 0) |
|              targetAddress = objStorage[row].substr(current+3, 3) + currentAddress + 3;   |
|            // 0 0 0 1									    |
|            else if (nixbpe[2] == 0 && nixbpe[3] == 0 && nixbpe[4] == 0 && nixbpe[5] == 1) |
|              targetAddress = objStorage[row].substr(current+4, 3);			    |
|            // 0 0 0 0    								    |
|            else 									    |
|              targetAddress = objStorage[row].substr(current+3, 3);			    |
|          // 1 0    									    |
|          else if (nixbpe[0] == 1 && nixbpe[1] == 0) //indirect addressing   		    |
|            @										    |
|            // 0 1 0 0									    |
|            if (nixbpe[2] == 0 && nixbpe[3] == 1 && nixbpe[4] == 0 && nixbpe[5] == 0)      | 
|              targetAddress = objStorage[row].substr(current+3, 3) + base;		    |
|            // 0 0 1 0									    |
|            else if (nixbpe[2] == 0 && nixbpe[3] == 0 && nixbpe[4] == 1 && nixbpe[5] == 0) |
|              targetAddress = objStorage[row].substr(current+3, 3) + currentAddress + 3;   |
|            // 0 0 0 1									    |
|            else if (nixbpe[2] == 0 && nixbpe[3] == 0 && nixbpe[4] == 0 && nixbpe[5] == 1) |
|              targetAddress = objStorage[row].substr(current+4, 3);			    |
|            // 0 0 0 0    								    |
|            else  									    |
|              targetAddress = objStorage[row].substr(current+3, 3);  			    |
|          // 0 1    								            |
|          else if (nixbpe[0] == 0 && nixbpe[1] == 1) //immediate addressing		    |
|            #										    |
|            // 0 1 0 0									    |
|            if (nixbpe[2] == 0 && nixbpe[3] == 1 && nixbpe[4] == 0 && nixbpe[5] == 0)	    | 
|              targetAddress = objStorage[row].substr(current+3, 3) + base;		    |
|            // 0 0 1 0									    |
|            else if (nixbpe[2] == 0 && nixbpe[3] == 0 && nixbpe[4] == 1 && nixbpe[5] == 0) |
|              targetAddress = objStorage[row].substr(current+3, 3) + currentAddress + 3;   |
|            // 0 0 0 1									    |
|            else if (nixbpe[2] == 0 && nixbpe[3] == 0 && nixbpe[4] == 0 && nixbpe[5] == 1) |
|              targetAddress = objStorage[row].substr(current+4, 3);			    |
|            // 0 0 0 0    								    |
|            else 									    |
|              targetAddress = objStorage[row].substr(current+3, 3);			    |
=================================================================================================
*                                                                                               *
*	The final code we eventually utilized significantly reduced the amount of               *
*	checks of the nixbpe bits. The code is now very efficient. This is due                  *
*	to the fact that instead of using numbers to represent the nixbpe bits, we used         *
*	boolean values instead.                                                                 *
*                                                                                               *
*	Bit masking was put to heavy use in this assignment.The use of bit masking significantly*
*	reduced the reliance of IF structures to check bits. Bit masking took two FULL days of  *
*	programming to get right.In the end the use of this technique saved a bunch of headaches*
*	as we further progressed into the assignment and our code is SIGNIFICANTLY shorter and  *
*	SIGNIFICANTLY more efficient and elegant. Here is an example if the minimal coding      *
*       involving bit masking.                                                                  *
*	                                                                                        *
*                                                                                               *
=================================================================================================
|			bool OpCode::getBit(int input, int position) {				|
|			    return ((input >> position) & 1);					|
|			}									|
=================================================================================================
*                                                                                               *
*	Here, nixbpe bits were found efficiently.                                               *
*                                                                                               *
*	Overall, our program runs in this general process:                                      *
*		1. Open and read files into vectors.                                            *
*			a. Perform error checking of input.                                     *
*			b. If files aren't able to open, exit gracefully and print error message*
*		2. Parse through the object code and look up needed references.                 *
*		3. Perform various conversion steps and addressing mode calculations.           *
*		4. Align instructions, symbols, literals, etc. in the proper format.            *
*		5. Print the data to a .sic file.                                               *
*		6. End program.                                                                 *
*                                                                                               *
*	The entire design process was really fun. Programming/coding with others is a blast.    *
*	Though it was a hard project, fun was still had. At first, meeting up was very formal.  *
*	We would try to reserve a room in the school library and wait patiently for others to   *
*	show up to code. Not much would get done as we haven't worked in a group since most of  *
*	our projects till now have been individual.Eventually, we would go each other's house to*
*	code and try to whip out the project in one sitting. Before we know it, 5 or 6 have     *
*	passed and we are still working at the same pace. Time flys when having fun. The whole  *
*	dynamic of the team changes once the members are all on the same page and working toward*
*	a common goal.                                                                          *
*                                                                                               *
*************************************************************************************************



