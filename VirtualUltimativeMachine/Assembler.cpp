#include "Assembler.h"

Assembler &Assembler::getinst()
{
	static Assembler obj;
	return obj;
}

void Assembler::decode(std::string Sdir_)
{
	/*
		structure of asm

		[] - byte
		[word or command](if it have an arguments)[typedata][value](it it's two or more)[typedata][value]
	*/
	char *CPbuffer;
	char *CPname;
	unsigned char UCregex;
	std::ifstream Fin;
	std::ofstream Fout;
	Fin.open(Sdir_, std::ios::binary);
	Fout.open(Sdir_ + ".asm");
	Fin.read((char*)UCregex, 1);
	for(auto &iter : _LCcommandsS)
	{
		if(iter.UCregex != UCregex) continue;

	}
	CPbuffer;
	Fout << 
	Fin.close();
	Fout.close();
}
