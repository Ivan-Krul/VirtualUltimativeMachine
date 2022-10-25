#include <iostream>
#include "Assembler.h"

int main()
{
	std::cout << "{Launch}\n";
	Assembler a;
	a.compile("what.txt");
	a.decode("what.txt.bin");

	std::cout << "{Halt}\n";
}
