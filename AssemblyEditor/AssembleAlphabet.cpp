#include "AssembleAlphabet.h"

void AssembleAlphabet::load(std::string Sdir_)
{
	/*
	Sturcture of the file:
		(1) Size of all list of codes
		-->
			(1) Size of string
			-->
				(1) Symbol in string
				<--
			(1) Code in raw
			(1) Count of arguments
			<--
		(1) Size of all list of typedata
		-->
			(1) Symbol of typedata
			(1) Code in raw
			<--
		<--
	*/
	char *CPbuffer = nullptr;
	char Ctypedata;
	unsigned char UCsize = 0;
	unsigned char UCsizestr = 0;
	unsigned char UCdecode;
	unsigned char UCargs;
	std::string Sstr;
	std::ifstream Fin;
	_Mdecoder.clear();
	Fin.open(Sdir_,std::ios::binary);
	if(!Fin.is_open()) return;
	Fin.read(CPbuffer,1);
	UCsize = static_cast<unsigned char>(CPbuffer[0]);
	for(unsigned short Iter = 0; Iter <= UCsize; Iter++)
	{
		Fin.read(CPbuffer, 1);
		UCsizestr = static_cast<unsigned char>(CPbuffer[0]);
		Fin.read(CPbuffer, UCsizestr);
		Sstr = CPbuffer;
		Fin.read(CPbuffer, 1);
		UCdecode = static_cast<unsigned char>(CPbuffer[0]);
		Fin.read(CPbuffer, 1);
		UCargs = static_cast<unsigned char>(CPbuffer[0]);
		_Mdecoder.insert({ {UCdecode,UCargs }, Sstr });
	}
	Fin.read(CPbuffer,1);
	UCsize = static_cast<unsigned char>(CPbuffer[0]);
	for(unsigned short Iter = 0; Iter < UCsize; Iter++)
	{
		Fin.read(CPbuffer, 1);
		Ctypedata = CPbuffer[0];
		Fin.read(CPbuffer, 1);
		UCdecode = static_cast<unsigned char>(CPbuffer[0]);
		_Mtypedata.insert({UCdecode,Ctypedata});
	}
	Fin.close();
}

void AssembleAlphabet::save(std::string Sdir_)
{
	/*
	Sturcture of the file:
		(1) Size of all list of codes - 1
		-->
			(1) Size of string
			-->
				(1) Symbol in string
				<--
			(1) Code in raw
			(1) Count of arguments
			<--
		(1) Size of all list of typedata
		-->
			(1) Symbol of typedata
			(1) Code in raw
			<--
		<--
	*/
	char CMbuffer[1];
	std::ofstream Fout;
	Fout.open(Sdir_,std::ios::binary);
	CMbuffer[0] = static_cast<char>((_Mdecoder.size() - 1) % 256);
	Fout.write(CMbuffer, 1);
	for(auto &i : _Mdecoder)
	{
		
		CMbuffer[0] = static_cast<char>((i.second.size()) % 256);
		Fout.write(i.second.c_str(), i.second.size());
		CMbuffer[0] = i.first.first;
		Fout.write(CMbuffer,1);
		CMbuffer[0] = i.first.second;
		Fout.write(CMbuffer, 1);
	}

	CMbuffer[0] = static_cast<char>((_Mdecoder.size()) % 256);
	Fout.write(CMbuffer, 1);
	for(auto &i : _Mtypedata)
	{
		Fout.write(&i.second, 1);
		CMbuffer[0] = i.first;
		Fout.write(CMbuffer, 1);
	}

}

std::string AssembleAlphabet::decode(unsigned char UCc_)
{
	for(auto &i : _Mdecoder)
	{
		if(i.first.first == UCc_)
			return i.second;
	}
	return "";
}

char AssembleAlphabet::typedata(unsigned char UCc_)
{
	for(auto &i : _Mtypedata)
	{
		if(i.first == UCc_)
			return i.second;
	}
	return 0;
}

unsigned char AssembleAlphabet::typedata(char Csym_)
{
	for(auto &i : _Mtypedata)
	{
		if(i.second == Csym_)
			return i.first;
	}
	return 0;
}

unsigned char AssembleAlphabet::encodee(std::string Sstr_)
{
	for(auto &i : _Mdecoder)
	{
		if(i.second == Sstr_)
			return i.first.first;
	}
	return 0;
}

unsigned char AssembleAlphabet::encodea(std::string Sstr_)
{
	for(auto &i : _Mdecoder)
	{
		if(i.second == Sstr_)
			return i.first.second;
	}
	return 0;
}

std::string AssembleAlphabet::typecode()
{
	return std::string();
}
