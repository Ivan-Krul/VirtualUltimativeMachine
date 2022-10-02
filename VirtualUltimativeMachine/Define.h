#pragma once
#define DEBUG

#ifdef DEBUG
#include <iostream>
#define CLOG std::clog
#else
#include <fstream>
static std::ofstream fout;
#define CLOG fout
#endif

