#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

#ifndef __SCANNER_CLASSDEF__
#define __SCANNER_CLASSDEF__

class scanner
{

public:
	string lowerCase(string token);
	bool isValido(string token);
};

#endif