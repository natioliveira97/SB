
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct {
	string name;
	int arg;
	int line;
}mnt;

typedef struct{
	string body;		
}mdt;

typedef struct{
	string rot;
	string directive;
	string funct;
	vector<string> arg;	
	vector<string> macroArg;	
}lineStruct;

class preProcessor
{

private:

string removeSpaceTab(string line);

string removeComment(string line);

void textTreatment(string filename);

void expandDirectives(string filename);


lineStruct lineStructure(string line);


public:

	vector <mnt> MNT;
	vector <mdt> MDT;

	void run(string filename);
};

