#include <iostream>
#include <fstream>
#include <vector>
#include "parser.hpp"

using namespace std;

typedef struct {
	string name;
	int arg;
	int line;
}mnt;

typedef struct{
	string body;		
}mdt;

class preProcessor : public parser
{

private:

string removeSpaceTab(string line);

string removeComment(string line);

void textTreatment(string filename);

void expandDirectives(string filename);

public:

	vector <mnt> MNT;
	vector <mdt> MDT;

	void run(string filename);
};

