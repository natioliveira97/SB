#ifndef __PRE_PROCESSOR_H__
#define __PRE_PROCESSOR_H__

#include <iostream>
#include <vector>

using namespace std;

class preProcessor
{

public:

	typedef struct {
		string name;
		int arg;
		int line;
	}mnt;

	typedef struct{
		string body;		
	}mdt;

	vector<int> a;

	vector <mnt> MNT;
	vector <mdt> MDT;
};


#endif