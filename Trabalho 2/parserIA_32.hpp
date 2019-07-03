#include <iostream>
#include <fstream>
#include <regex>
#include "scanner.hpp"

using namespace std;

#ifndef __PARSERIA_32_CLASSDEF__
#define __PARSERIA_32_CLASSDEF__

typedef struct{
	string rot;
	string reg;
	string funct;
	vector<string> arg;	
	vector<string> macroArg;
	string number;
	vector<string> notDefined;	

	string lineCode; //Código que classifica o tipo de linha
}lineStruct;

class parserIA_32 : public scanner
{

public:
	bool isFunction(string token);

	bool isRegister(string token);

	bool isPlusSign(string token);

	bool isNumber(string token);

	int classifyToken(string token);

	lineStruct lineStructure(string line);
};

#endif