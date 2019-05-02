#ifndef __PRE_PROCESSOR_H__
#define __PRE_PROCESSOR_H__

#include <iostream>
#include <fstream>

using namespace std;

class preProcessor
{
	
private:

string removeSpaceTab(string line);

string removeComment(string line);

void textTreatment(string filename);

void preProcessor(string filename);

public:

	typedef struct {
		string name;
		int arg;
		int line;
	}mnt;

	typedef struct{
		string body;		
	}mdt;

	vector <mnt> MNT;
	vector <mdt> MDT;
};


#endif