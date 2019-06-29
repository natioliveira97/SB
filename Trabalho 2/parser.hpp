#include <iostream>
#include <fstream>
#include <regex>
#include "scanner.hpp"

using namespace std;

#ifndef __PARSER_CLASSDEF__
#define __PARSER_CLASSDEF__

typedef struct{
	string rot;
	string directive;
	string funct;
	vector<string> arg;	
	vector<string> macroArg;
	string character;
	string number;
	vector<string> notDefined;	

	string lineCode; //Código que classifica o tipo de linha
}lineStruct;

class parser : public scanner
{

public:
	bool isFunction(string token);

	bool isDirective(string token);

	bool isArg(string token);

	bool isMacroArg(string token);

	bool isPlusSign(string token);

	bool isNumber(string token);

	bool isChar(string token);

	int classifyToken(string token);

	lineStruct lineStructure(string line);
};

#endif