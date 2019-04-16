#ifndef __PRE_PROCESSOR_H__
#define __PRE_PROCESSOR_H__

#include <iostream>

using namespace std;

class preProcessor{


public:

	struct{
		string name;
		int arg;
		int line;
	}mnt;

	struct{
		string body;		
	}mdt;

	vector<mnt> MNT;
	vector<mdt> MDT;
}


#endif