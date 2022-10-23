#include "Assembler.h"

unsigned char Assembler::_regtocode(char *name_, int size_)
{
	unsigned char res = 0;
	char type;
	char scale = 0;
	if(size_ > 2) type = name_[1];
	else type = name_[0];
	if(name_[0] == 'e' && name_[2]=='X') scale = _regescaleX;
	else if(name_[1] == 'X') scale = _regscaleX;
	else if(name_[1] == 'H') scale = _regscaleH;
	res += _typereg;
	res += (type-65) + (1<<2);
	res += (scale) + (1<<4);
	return res;
}

const char * Assembler::_codetoreg(unsigned char value_)
{
	unsigned char indef = (value_ >>= 2) & MASK_ARG_TYPEDATA;
	unsigned char scale = (value_ >>= 2);
	char regsym = indef + 65;
	char registername[5];
	registername[0] = '$';
	if(scale == _regscaleH)
	{
		registername[1] = regsym;
		registername[2] = 'H';
		registername[3] = '\0';
	}
	else if(scale == _regscaleX)
	{
		registername[1] = regsym;
		registername[2] = 'X';
		registername[3] = '\0';
	}
	else if(scale == _regescaleX)
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
				if((*CPbuffer & MASK_ARG_TYPEDATA) == _typereg) Fout<<_codetoreg(*CPbuffer); // register
				else if((*CPbuffer & MASK_ARG_TYPEDATA) == _typeadmem) // address memory
				{					
					Fin.read(CPbuffer, 4);
					Fout << '#' << (unsigned int)(*CPbuffer);
				}
				else if((*CPbuffer & MASK_ARG_TYPEDATA) == _typeint) // unsigned int
				{
					Fin.read(CPbuffer, 4);
					Fout << (unsigned int)(*CPbuffer);
				}
				else if((*CPbuffer & MASK_ARG_TYPEDATA) == _typefloat) // float
				{
					Fin.read(CPbuffer, 4);
					Fout <<std::dec<< float(*CPbuffer) <<std::hex;
				}
				if(arg + 1 != iter.UCargs) Fout <<", ";
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
				if(value[value.size()-1] == ',') value.pop_back();
				if(buffer[0] == '$')
					fout.write((char *)_regtocode((char*)buffer.c_str(),buffer.size()),1);
				else if(buffer[0] == '#')
				{
					fout.write((char*)_typeadmem,1);
					unsigned int val = std::stoul(value);
					fout.write((char*)val,4);
				}
				else if(buffer[0] == 'U')
				{
					unsigned int val = std::stoul(value);
					fout.write((char*)val,4);
				}
				else if(buffer[0] == 'F')
				{
					union
					{
						float input;
						int   output;
					} data;
					data.input = std::stof(value);
					fout.write((char*)data.output,4);
				}
			}
		}
	}
	fin.close();
	fout.close();
}
