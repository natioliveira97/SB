#include <iostream>
#include <fstream>
#include <vector>

#include "scanner.hpp"

using namespace std;

typedef struct{
	string rot;
	string directive;
	string funct;
	vector<string> arg;	
	vector<string> macroArg;
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

	int classifyToken(string token);

	void sintaticError(int errorCode);

	lineStruct lineStructure(string line);
};