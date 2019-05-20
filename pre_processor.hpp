#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include "parser.hpp"

using namespace std;


#ifndef __PRE_PROCESSOR_CLASSDEF__
#define __PRE_PROCESSOR_CLASSDEF__

typedef struct {
	string rot;
	int argNumber;
	vector<string> arg;
	int line;
}mnt;

typedef struct{
	string rot;
	string value;
}equt;

class preProcessor : public parser
{

private:

	string removeSpaceTab(string line);

	string removeComment(string line);

	void textTreatment(string filename);

	void expandDirectives(string filename);

	int findInEQUT(string token);

	void fillMNT(lineStruct structure);

	int findMNT(string token);

	void fillMDT();

	bool ifs(lineStruct structure);

	void expandMacro(int mnt_pos, lineStruct structure, bool inMDT);

	void error(string description);

	bool erro = false;


public:

	vector <mnt> MNT;
	vector<string> MDT;
	vector<equt> EQUT;

	ifstream textFile;
	ofstream temporaryFile1;
	ifstream temporaryFile2;
	ofstream preProcessedFile;

	void run(string filename);
};

#endif