#pragma once
#include <Windows.h>
#include <string>
class Window
{
	COORD _Sresolution;
	unsigned int _UIsizebuffer = 0;
	char *_CPscreenbuffer;
	HANDLE _Hconsole;
	DWORD _UIbyteswritten = 0;
	COORD _Scurpos = { 0,0 };
public:
	COORD getresolconsole();
	void resizeconsole(short Sx_, short Sy_);
	Window();
	Window(short USx_, short USy_);
	void insert(std::string Sstr_, COORD Swhere_);
	void insert(char Cch_, COORD Swhere_);
	char &operator[](unsigned int UIindex_);
	void update(COORD Scurpos_);
	COORD size();
	unsigned int siize();
	~Window();
};
