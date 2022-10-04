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
	unsigned char args(unsigned char UCc_);
	unsigned char args(std::string Sstr_);
	char typedata(unsigned char UCc_);
	unsigned char typedata(char Csym_);
	unsigned char encode(std::string Sstr_);
	std::string typecode();
};

