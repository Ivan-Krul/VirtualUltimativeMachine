#include "TextEditor.h"

void TextEditor::_curmovevert(char Cdelta_)
{
	short SnextposY = _Scurpos.Y + Cdelta_;
	short SnextposX = _Scurpos.X;
	if(!(SnextposY < _VStext.size()))
		SnextposY = _VStext.size() - 1;
	else if(SnextposY < 0)
		SnextposY = 0;
	if(!(SnextposX < _VStext[SnextposY].size()))
		SnextposX = _VStext[SnextposY].size() - 1;
	_Scurpos = { SnextposX, SnextposY };
}

void TextEditor::_curmovehors(char Cdelta_)
{
	short SnextposX = _Scurpos.X + Cdelta_;

	while()
}

void TextEditor::swap(char Cch_)
{
	if(Cch_ == 0x13)
	{
		_VStext[_Scurpos.Y][_Scurpos.X] = Cch_;
		if(_VStext[_Scurpos.Y].capacity() == _VStext[_Scurpos.Y].size())
			_VStext[_Scurpos.Y].reserve(_VStext[_Scurpos.Y].size() * 1.25f);
		_VStext.push_back(std::string());
		_Scurpos.Y++;
		_Scurpos.X = 0;
		if(_VStext.capacity() == _VStext.size())
			_VStext.reserve(_VStext.capacity() * 1.25f);
		return;
	}
	if(!_Bisinsertmode)
	{
		if(_VStext[_Scurpos.Y].capacity() == _VStext[_Scurpos.Y].size())
			_VStext[_Scurpos.Y].reserve(_VStext[_Scurpos.Y].size() * 1.25f);
		_VStext[_Scurpos.Y].insert(_VStext[_Scurpos.Y].begin()+_Scurpos.X, Cch_);
		_Scurpos.X++;
		return;
	}
	if(!(_Scurpos.X < _VStext[_Scurpos.Y].size()))
	{
		if(_VStext[_Scurpos.Y].capacity() == _VStext[_Scurpos.Y].size())
			_VStext[_Scurpos.Y].reserve(_VStext[_Scurpos.Y].size() * 1.25f);
		_VStext[_Scurpos.Y].insert(_VStext[_Scurpos.Y].begin() + _Scurpos.X, Cch_);
	}
	_VStext[_Scurpos.Y][_Scurpos.X] = Cch_;
}

void TextEditor::tabsize(unsigned char UCtabsize_)
{
	_UCtabsize = UCtabsize_;
}

void TextEditor::curdown(unsigned char UCdelta_)
{
	_curmovevert(-UCdelta_);
}

void TextEditor::curup(unsigned char UCdelta_)
{
	_curmovevert(UCdelta_);
}
