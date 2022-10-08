#pragma once
#include <string>
#include <vector>
#include <Windows.h>
class TextEditor
{
	std::vector<std::string> _VStext;
	COORD _Scurpos = { 0,0 };
	COORD _Sscr = { 0,0 };
	unsigned char _UCtabsize = 4;
	bool _Bisinsertmode = false;
	void _curmovevert(char Cdelta_);
	void _curmovehors(char Cdelta_);
public:
	void swap(char Cch_);
	void tabsize(unsigned char UCtabsize_);
	void curdown(unsigned char UCdelta_);
	void curup(unsigned char UCdelta_);
	void curleft(unsigned char UCdelta_);
	void curright(unsigned char UCdelta_);
};

