#include <iostream>
#include <fstream>
#include <vector>
#include "parser.hpp"

using namespace std;

#ifndef __MONTADOR_CLASSDEF__
#define __MONTADOR_CLASSDEF__

typedef struct{
	string name;
	int address;
}tabelaSimbolos;



class Montador : public parser
{
private: 
	int address;
	tabelaSimbolos getSimbol(string token, int address);
	void putTable(string token, int address);
	int searchAddress(string token);
	void fillTable(string filename);
	void printTable();


public:

	vector <tabelaSimbolos> TABS;

	void run(string filename);

};

#endif