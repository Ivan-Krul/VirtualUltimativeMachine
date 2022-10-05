#pragma once
#include <string>
#include <Windows.h>
class TextEditor
{
	std::string _Stext = "";
	COORD _Scurpos = { 0,0 };
	COORD _Sscr = { 0,0 };
	unsigned int _UIcurindex = 0;
	unsigned char _UCtabsize = 4;
	bool _Bisinsertmode = false;
	void _curmovevert(char Cdelta_);
public:
	void swap(char Cch_);
	void tabsize(unsigned char UCtabsize_);
	void curdown(unsigned char UCdelta_);
};

