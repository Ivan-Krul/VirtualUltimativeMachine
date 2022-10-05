#include "TextEditor.h"

void TextEditor::_curmovevert(char Cdelta_)
{
	/*
		We are counting a vertical axis, every end line we decrement an iterator.
		If we 
	*/
	COORD Snextcurpos = _Scurpos;
	unsigned int UInextcurindex = _UIcurindex;
	unsigned int UIiter = Cdelta_ < 0 ? -Cdelta_ : Cdelta_;
	Snextcurpos.Y += Cdelta_;
	for(UIiter; UIiter != 0; UIiter--)
	{
		while()
		{

		}
	}
}

void TextEditor::swap(char Cch_)
{
	_Stext[_UIcurindex] = Cch_;
}

void TextEditor::tabsize(unsigned char UCtabsize_)
{
	_UCtabsize = UCtabsize_;
}

void TextEditor::curdown(unsigned char UCdelta_)
{
}
