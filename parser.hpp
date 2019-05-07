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
}lineStruct;

class parser : public scanner
{

public:
	bool isFunction(string token);

	int classificaToken(string token);

	lineStruct lineStructure(string line);
};