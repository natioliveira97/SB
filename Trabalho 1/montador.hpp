#include <iostream>
#include <fstream>
#include <regex>
#include "parser.hpp"

using namespace std;

#ifndef __MONTADOR_CLASSDEF__
#define __MONTADOR_CLASSDEF__

typedef struct{
	string name;
	int address;
	int type; //1-Rótulo 2-Space 3-Const
	int const_value;
}tabelaSimbolos;

class Montador : public parser
{
private: 
	int address;
	tabelaSimbolos getSimbol(string token, int address, int type, int const_value);
	void putTable(string token, int address, int type, int const_value);
	int searchAddress(string token, int desiredAddress);
	void fillTable(string filename);
	void printTable();
	void error(string errorType, int lineNumber, string description);
	int functionArgs(string funct);
	int functionCode(string funct);
	void secondPass(string filename);
	void textSintaxe(string line, int lineNumber);
	void dataSintaxe(string line, int lineNumber);

	ifstream textFile;
	ofstream objFile;


public:

	vector <tabelaSimbolos> TABS;
	bool erro = false;
	void run(string filename);

};

#endif