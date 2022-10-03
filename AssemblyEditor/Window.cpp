#include "Window.h"

COORD Window::getresolconsole()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD Sscreenresol;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	Sscreenresol.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	Sscreenresol.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	return Sscreenresol;
}

Window::Window()
{
	_Sresolution = getresolconsole();
	_UIsizebuffer = _Sresolution.X * _Sresolution.Y;
	_CPscreenbuffer = new char[_Sresolution.X * _Sresolution.Y + 1];
	_CPscreenbuffer[_Sresolution.X * _Sresolution.Y] = '\0';
	memset(_CPscreenbuffer, ' ', _UIsizebuffer);
	_Hconsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(_Hconsole);
}

void Window::insert(std::string Sstr_, COORD Swhere_)
{
	if(!(Swhere_.X < _Sresolution.X)) return;
	if(!(Swhere_.Y < _Sresolution.Y)) return;
	for(unsigned int Iiter = 0; Iiter < Sstr_.size(); Iiter++)
		_CPscreenbuffer[Iiter + Swhere_.X + Swhere_.Y * _Sresolution.Y] = Sstr_[Iiter];
}

void Window::insert(char Cch_, COORD Swhere_)
{
	if(!(Swhere_.X < _Sresolution.X)) return;
	if(!(Swhere_.Y < _Sresolution.Y)) return;
	_CPscreenbuffer[Swhere_.X + Swhere_.Y * _Sresolution.Y] = Cch_;
}

char &Window::operator[](unsigned int UIindex_)
{
	if(!(UIindex_ < _UIsizebuffer)) return _CPscreenbuffer[0];
	return _CPscreenbuffer[UIindex_];
}

void Window::update()
{
	WriteConsoleOutputCharacterA(_Hconsole, _CPscreenbuffer, _UIsizebuffer, {0, 0}, &_UIbyteswritten);
}

COORD Window::size()
{
	return _Sresolution;
}

Window::~Window()
{
	delete[] _CPscreenbuffer;
}
