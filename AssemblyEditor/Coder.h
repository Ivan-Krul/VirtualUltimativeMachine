#pragma once
#include "TextEditor.h"
#include "AssembleAlphabet.h"
class Coder
{
public:
	unsigned char *UCcode = nullptr;
	void code(TextEditor &CTE_, AssembleAlphabet &CAA_);
	void decode(TextEditor &CTE_, AssembleAlphabet &CAA_);
};

