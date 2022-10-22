#include "Assembler.h"

unsigned char Assembler::_regtocode(const char *name_)
{
	return 0;
}

const char * Assembler::_codetoreg(char value_)
{
	const static char regscaleH = 0b01;
	const static char regscaleX = 0b10;
	const static char regescaleX= 0b11;
	unsigned char indef = (value_ >>= 2) & MASK_ARG_TYPEDATA;
	unsigned char scale = (value_ >>= 2);
	char regsym = indef + 65;
	char registername[5];
	registername[0] = '$';
	if(scale == regscaleH)
	{
		registername[1] = regsym;
		registername[2] = 'H';
		registername[3] = '\0';
	}
	else if(scale == regscaleX)
	{
		registername[1] = regsym;
		registername[2] = 'X';
		registername[3] = '\0';
	}
	else if(scale == regescaleX)
	{
		registername[1] = 'e';
		registername[2] = regsym;
		registername[3] = 'X';
		registername[4] = '\0';
	}
	else
	{
		registername[1] = regsym;
		registername[2] = 'L';
		registername[3] = '\0';
	}

	return registername;
}

Assembler &Assembler::getinst()
{
	static Assembler obj;
	return obj;
}

bool Assembler::isletter(char letter_)
{
	return (letter_-65)<26 || (letter_-97)<26;
}

bool Assembler::isaddictsym(char char_)
{
	return !(isletter(char_) || isnumber(char_));
}

bool Assembler::isnumber(char number_)
{
	return (number_-48)<10;
}

void Assembler::decode(std::string Sdir_)
{
	/*
		structure of asm

		[] - byte
		[word or command](if it have an arguments)[typedata|regindef|][value](it it's two or more)[typedata][value]
	*/
	char *CPbuffer;
	unsigned char UCregex;
	std::ifstream Fin;
	std::ofstream Fout;
	Fin.open(Sdir_, std::ios::binary);
	Fout.open(Sdir_ + ".asm");
	Fout << std::hex;
	while(!Fin.eof())
	{
		Fin.read((char *)UCregex, 1);
		for(auto &iter : _LCcommandsS)
		{
			if(iter.UCregex != UCregex) continue;
			Fout << iter.CMname;
			if(iter.UCargs == 0) break;
			for(int arg = 0;arg < iter.UCargs; arg++)
			{
				Fout << '\t';
				Fin.read(CPbuffer, 1);
				if((*CPbuffer & MASK_ARG_TYPEDATA) == 0b10)
				{
					// register	
					Fout<<_codetoreg(*CPbuffer);
				}
				else if((*CPbuffer & MASK_ARG_TYPEDATA) == 0b11)
				{
					// address memory
					Fin.read(CPbuffer, 4);
					Fout << '#' << (unsigned int)(*CPbuffer);
				}
				else if((*CPbuffer & MASK_ARG_TYPEDATA) == 0b00)
				{
					// unsigned int
					Fin.read(CPbuffer, 4);
					Fout << (unsigned int)(*CPbuffer);
				}
				else if((*CPbuffer & MASK_ARG_TYPEDATA) == 0b01)
				{
					// float
					Fin.read(CPbuffer, 4);
					Fout <<std::dec<< float(*CPbuffer) <<std::hex;
				}
				if(arg + 1 != iter.UCargs)
				{
					Fout <<", ";
				}
			}							
		}								
		Fout << '\n';					
	}
	Fin.close();
	Fout.close();
}

void Assembler::compile(std::string dir_)
{
	std::ifstream fin;
	std::ofstream fout;
	std::string buffer;
	fin.open(dir_);
	fout.open(dir_ + ".bin", std::ios::binary);
	while(!fin.eof())
	{
		fin >> buffer;
		for(auto &iter : _LCcommandsS)
		{
			if(iter.CMname != buffer) continue;
			fout.write((const char *)iter.UCregex, 1);
			for(int i = 0; i < iter.UCargs; i++)
			{
				fin >> buffer;
				std::string value(buffer.begin()+1,buffer.end());
				if(buffer[0] == '$')
				{
					// we have a deal with register
					_regtocode(buffer.c_str());
				}
			}
		}
	}
	fin.close();
	fout.close();
}
