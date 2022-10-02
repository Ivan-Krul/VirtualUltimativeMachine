#include <iostream>
#include "Define.h"

int main()
{
#ifndef DEBUG
    fout.open("out.log");
#endif
    CLOG << "{Launch}\n";
    CLOG << "Hello World!\n";
    CLOG << "{Halt}\n";
#ifndef DEBUG
    fout.close();
#endif
}
