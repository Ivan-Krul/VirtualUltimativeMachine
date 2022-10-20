#include "Assembler.h"

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
	const static char regscaleH = 0b01;
	const static char regscaleX = 0b10;
	const static char regescaleX= 0b11;
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
					unsigned char indef = (*CPbuffer >> 2) & MASK_ARG_TYPEDATA;
					unsigned char scale = (*CPbuffer >> 2);
					char regsym = indef + 65;
					char registername[4];
					if(scale == regscaleH)
					{
						registername[0] = regsym;
						registername[1] = 'H';
						registername[2] = '\0';
					}
					else if(scale == regscaleX)
					{
						registername[0] = regsym;
						registername[1] = 'X';
						registername[2] = '\0';
					}
					else if(scale == regescaleX)
					{
						registername[0] = 'e';
						registername[1] = regsym;
						registername[2] = 'X';
						registername[3] = '\0';
					}
					else
					{
						registername[0] = regsym;
						registername[1] = 'L';
						registername[2] = '\0';
					}
					Fout <<'$' << registername<<' ';
				}
				else if((*CPbuffer & MASK_ARG_TYPEDATA) == 0b11)
				{
					// address memory
					Fin.read(CPbuffer, 4);
					Fout << '#' << (unsigned int)(*CPbuffer)<<' ';
				}
				else if((*CPbuffer & MASK_ARG_TYPEDATA) == 0b00)
				{
					// unsigned int
					Fin.read(CPbuffer, 4);
					Fout << (unsigned int)(*CPbuffer)<<' ';
				}
				else if((*CPbuffer & MASK_ARG_TYPEDATA) == 0b01)
				{
					// float
					Fin.read(CPbuffer, 4);
					Fout <<std::dec<< float(*CPbuffer) << ' ' <<std::hex;
				}
				if(arg + 1 != iter.UCargs)
				{
					Fout << ',';
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
					char type;
					char symbol;
					if(value[0] == 'e' && value[2] == 'X')
					{
						type = value[1];
						symbol = 0b10;
						symbol += type - 65;
						symbol += 0b00110000;
						continue;
					}
					else type = value[0];
					if(value[1] == 'X')
					{
						
					}
				}
			}
		}
	}
	fin.close();
	fout.close();
}
