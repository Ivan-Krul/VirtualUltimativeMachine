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

void Window::resizeconsole(short Sx_, short Sy_)
{
	_COORD coord = {Sx_,Sy_};
	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Sy_ - 1;
	Rect.Right = Sx_ - 1;
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(Handle, coord);
	SetConsoleWindowInfo(Handle, TRUE, &Rect);
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

Window::Window(short Sx_, short Sy_)
{
	resizeconsole(Sx_, Sy_);
	_Sresolution = { Sx_,Sy_ };
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

void Window::update(COORD Scurpos_)
{
	_Scurpos = Scurpos_;
	WriteConsoleOutputCharacterA(_Hconsole, _CPscreenbuffer, _UIsizebuffer, _Scurpos, &_UIbyteswritten);
}

COORD Window::size()
{
	return _Sresolution;
}

unsigned int Window::siize()
{
	return _UIsizebuffer;
}

Window::~Window()
{
	delete[] _CPscreenbuffer;
}
