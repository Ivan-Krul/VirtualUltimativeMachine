#include "TextEnvi.h"

void TextEnvi::save()
{
	if(_filedir.empty())
	{
		
	}
	std::ofstream fout;
	fout.open(_filedir);
	fout << _filedir;
	fout.close();
}

void TextEnvi::exit(bool with_save_)
{
	delete[] _screenbuffer;
	if(!with_save_) return;
	save();
}
