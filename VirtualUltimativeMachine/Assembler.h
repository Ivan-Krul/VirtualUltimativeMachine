/*
	Assembler x86 32-bit

	typedata:
		$ - address memory
		# - int (unsigned)
		I - int (signed)
		f - float

*/
#pragma once
#include <fstream>
#include <list>
class Assembler
{
public:
	struct Command
	{
		const char *CMname;
		unsigned char UCregex;
		unsigned char UCargs;
	};
	struct Operator
	{
		char Cchar;
		unsigned char UCregex;
	};
private:
	static std::list<Command> _LCcommands;
	
};

std::list<Assembler::Command> Assembler::_LCcommands = {
	{"NOP"	 , 0xea, 0}, // no operations
	{"JMP"	 , 0x20, 1}, // jump to the flag, what marked by "FLAG"
	{"JZ"	 , 0x21, 2}, // jump if is zero
	{"JNZ"	 , 0x22, 2}, // reverse JZ
	{"JO"	 , 0x23, 3}, // jump if variable is overflow
	{"JNO"	 , 0x24, 3}, // reverse JO
	{"JE"	 , 0x25, 3}, // jump if equal two variables
	{"JNE"	 , 0x26, 3}, // reverse JE
	{"LD"	 , 0x11, 2}, // load from memory to register
	{"ST"	 , 0x12, 2}, // set from register to memory
	{"LDI"	 , 0x11, 2}, // same as from LD, but there load a variable
	{"STI"	 , 0x12, 2}, // same as from ST, but there load a variable
	{"SW"	 , 0x12, 2}, // swap
	{"MOV"	 , 0x10, 2}, // move from one register to another
	{"ADD"	 , 0x04, 2}, // next commands i'll be basic for alu
	{"SUB"	 , 0x05, 2}, 
	{"MUL"	 , 0x06, 2},
	{"DIV"	 , 0x07, 2}, 
	{"AND"	 , 0x08, 2}, 
	{"NOT"	 , 0x09, 2},
	{"OR"	 , 0x0a, 2},
	{"XOR"	 , 0x0b, 2}, 
	{"FLAG"	 , 0x13, 2}, // mark place of command for returning as index
	{"SCAN"	 , 0x14, 2}, // scan a pointed sector of disk and write in pointed memory address
	{"PRINT" , 0x14, 2}, // put to a pointed sector of disk and write from pointed memory address
	{"HLT"	 , 0xf4, 0} // halt
};
