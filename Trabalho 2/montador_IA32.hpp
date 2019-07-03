#include <iostream>
#include <fstream>
#include <regex>
#include "parser.hpp"

using namespace std;

#ifndef __MONTADOR_CLASSDEF__
#define __MONTADOR_CLASSDEF__


class Montador : public parserIA_32
{
private: 
	int address;

	// void add(lineStruct structure);
	// void sub(lineStruct structure);
	// void mult(lineStruct structure);
	// void div(lineStruct structure);
	// void jmp(lineStruct structure);
	// void jmpn(lineStruct structure);
	// void jmpp(lineStruct structure);
	// void jmpz(lineStruct structure);
	// void copy(lineStruct structure);
	// void load(lineStruct structure);
	// void store(lineStruct structure);
	// void input(lineStruct structure);
	// void output(lineStruct structure);
	// void c_input(lineStruct structure);
	// void c_output(lineStruct structure);
	// void h_input(lineStruct structure);
	// void h_output(lineStruct structure);
	// void s_input(lineStruct structure);
	// void s_output(lineStruct structure);
	// void stop(lineStruct structure);

	bool lerInteiro = false;
	bool escreveInteiro = false;

	void printFuncoes();
	void textSintaxe(string line);
	void dataSintaxe(string line);
	void transformIA32(string filename);

	void traduzLinha(string line);

	ifstream textFile;
	ofstream objFile;
	ofstream IA32File;


public:

	bool erro = false;
	void run(string filename);

};

#endif