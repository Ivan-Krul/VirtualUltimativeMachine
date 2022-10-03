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
public:
	COORD getresolconsole();
	Window();
	void insert(std::string Sstr_, COORD Swhere_);
	void insert(char Cch_, COORD Swhere_);
	char &operator[](unsigned int UIindex_);
	void update();
	COORD size();
	~Window();
};
