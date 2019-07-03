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

	char LerInteiro_code[] = {'\xC8', '\x0D', '\x00', '\x00', '\xB8', '\x03', '\x00', '\x00', '\x00', '\xBB', '\x00', '\x00', '\x00', '\x00', '\x89', '\xE9', '\x83', '\xE9', '\x0D', '\xBA', '\x0D', '\x00', '\x00', '\x00', '\xCD', '\x80', '\x50', '\x29', '\xC0', '\xB9', '\x0A', '\x00', '\x00', '\x00', '\x80', '\x7D', '\xF3', '\x2D', '\x74', '\x07', '\xBE', '\xF3', '\xFF', '\xFF', '\xFF', '\xEB', '\x05', '\xBE', '\xF4', '\xFF', '\xFF', '\xFF', '\x80', '\x6C', '\x35', '\x00', '\x30', '\x29', '\xDB', '\x8A', '\x5C', '\x35', '\x00', '\x01', '\xD8', '\x46', '\x80', '\x7C', '\x35', '\x00', '\x0A', '\x74', '\x15', '\xF7', '\xE9', '\xEB', '\xE7', '\x80', '\x7D', '\xF3', '\x2D', '\x0F', '\x85', '\x24', '\x01', '\x00', '\x00', '\xBB', '\xFF', '\xFF', '\xFF', '\xFF', '\xF7', '\xEB', '\x8B', '\x5D', '\x08', '\x89', '\x03', '\x58', '\xC9', '\xC3'}
	int LerInteiro_size = 0xe1-0x80;

	char EscreverInteiro_code[] = {'\xC8', '\x00', '\x00', '\x00', '\x8B', '\x5D', '\x08', '\x8B', '\x03', '\x29', '\xF6', '\xB9', '\x0A', '\x00', '\x00', '\x00', '\xBB', '\x01', '\x00', '\x00', '\x00', '\x83', '\xF8', '\x00', '\x7D', '\x07', '\xBB', '\xFF', '\xFF', '\xFF', '\xFF', '\xF7', '\xEB', '\x29', '\xD2', '\xF7', '\xF9', '\x83', '\xC2', '\x30', '\x83', '\xEC', '\x01', '\x88', '\x14', '\x24', '\x46', '\x83', '\xF8', '\x00', '\x75', '\xED', '\x83', '\xFB', '\x00', '\x7D', '\x08', '\x83', '\xEC', '\x01', '\xC6', '\x04', '\x24', '\x2D', '\x46', '\xB8', '\x04', '\x00', '\x00', '\x00', '\xBB', '\x01', '\x00', '\x00', '\x00', '\x89', '\xE1', '\x89', '\xF2', '\xCD', '\x80', '\xC9', '\xC3'};
	int EscreverInteiro_size = 0x134-0xe2;

	char LerChar_code[] = {'\xC8', '\x02', '\x00', '\x00', '\xB8', '\x03', '\x00', '\x00', '\x00', '\xBB', '\x00', '\x00', '\x00', '\x00', '\x89', '\xE9', '\x83', '\xE9', '\x02', '\xBA', '\x02', '\x00', '\x00', '\x00', '\xCD', '\x80', '\x8B', '\x5D', '\x08', '\x8A', '\x4D', '\xFE', '\x89', '\x0B', '\xC9', '\xC3'};
	int LerChar_size = 0x158-0x135;

	char EscreverChar_code = {'\xC8', '\x00', '\x00', '\x00', '\xB8', '\x04', '\x00', '\x00', '\x00', '\xBB', '\x01', '\x00', '\x00', '\x00', '\x8B', '\x4D', '\x08', '\xBA', '\x01', '\x00', '\x00', '\x00', '\xCD', '\x80', '\xC9', '\xC3'};
	int EscreverChar_size = 0x172-0x159;

	char LerString_code = {'\xC8', '\x00', '\x00', '\x00', '\xB8', '\x03', '\x00', '\x00', '\x00', '\xBB', '\x00', '\x00', '\x00', '\x00', '\x8B', '\x4D', '\x08', '\x8B', '\x55', '\x0C', '\xCD', '\x80', '\xC9', '\xC3'};
	int LerString_size = 0x18a-0x173;

	char EscreverString_code[] = {'\xC8', '\x00', '\x00', '\x00', '\xB8', '\x04', '\x00', '\x00', '\x00', '\xBB', '\x01', '\x00', '\x00', '\x00', '\x8B', '\x4D', '\x08', '\x8B', '\x55', '\x0C', '\xCD', '\x80', '\xC9', '\xC3'};
	int EscreverString_size = 0x1a2-0x18b;

	char LerHexa_code = {'\xC8', '\x09', '\x00', '\x00', '\xB8', '\x03', '\x00', '\x00', '\x00', '\xBB', '\x00', '\x00', '\x00', '\x00', '\x89', '\xE9', '\x83', '\xE9', '\x09', '\xBA', '\x09', '\x00', '\x00', '\x00', '\xCD', '\x80', '\x50', '\x29', '\xC0', '\xBE', '\xF7', '\xFF', '\xFF', '\xFF', '\x80', '\x7C', '\x35', '\x00', '\x39', '\x7F', '\x07', '\x80', '\x6C', '\x35', '\x00', '\x30', '\xEB', '\x13', '\x80', '\x7C', '\x35', '\x00', '\x46', '\x7F', '\x07', '\x80', '\x44', '\x35', '\x00', '\xC9', '\xEB', '\x05', '\x80', '\x44', '\x35', '\x00', '\xA9', '\x03', '\x44', '\x35', '\x00', '\x46', '\x80', '\x7C', '\x35', '\x00', '\x0A', '\x74', '\x05', '\xC1', '\xE0', '\x04', '\xEB', '\xCE', '\x89', '\x45', '\x08', '\x58', '\xC9', '\xC3'};
	int LerHexa_size = 0x202-0x1a3;

	char EscreverHexa_code = {'\xC8', '\x00', '\x00', '\x00', '\x8B', '\x5D', '\x08', '\x8B', '\x03', '\x29', '\xF6', '\xB9', '\x10', '\x00', '\x00', '\x00', '\x29', '\xD2', '\xF7', '\xF9', '\x83', '\xFA', '\x0A', '\x7D', '\x05', '\x83', '\xC2', '\x30', '\xEB', '\x03', '\x83', '\xC2', '\x57', '\x83', '\xEC', '\x01', '\x88', '\x14', '\x24', '\x46', '\x83', '\xF8', '\x00', '\x75', '\xE3', '\xB8', '\x04', '\x00', '\x00', '\x00', '\xBB', '\x01', '\x00', '\x00', '\x00', '\x89', '\xE1', '\x89', '\xF2', '\xCD', '\x80', '\xC9', '\xC3'};
	int EscreverHexa_size = 0x241-0x203;


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