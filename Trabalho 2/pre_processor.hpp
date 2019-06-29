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

	bool ifs(lineStruct structure);

	void error(string description);

	bool erro = false;


public:

	vector<equt> EQUT;

	ifstream textFile;
	ofstream temporaryFile1;
	ifstream temporaryFile2;
	ofstream preProcessedFile;

	void run(string filename);
};

#endif