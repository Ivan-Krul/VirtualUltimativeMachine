#pragma once
#include <string>
#include <map>
#include <fstream>
class AssembleAlphabet
{
	std::map<std::pair<unsigned char, unsigned char>, std::string> _Mdecoder;
	std::map<unsigned char, char> _Mtypedata;
	std::string _typecode;
public:
	void load(std::string Sdir_);
	void save(std::string Sdir_);
	std::string decode(unsigned char UCc_);
	char typedata(unsigned char UCc_);
	unsigned char typedata(char Csym_);
	unsigned char encodee(std::string Sstr_);
	unsigned char encodea(std::string Sstr_);
	std::string typecode();
};

