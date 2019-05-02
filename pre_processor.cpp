
#include <iostream>
#include <fstream>

using namespace std;


string removeSpaceTab(string line){
	bool valid_character=false;
	string newLine;

	if(!line.empty()){
		int n = line.length();
		if(line.at(0)!=' ' && line.at(0)!='	'){
			newLine = line.at(0);
		}
		
		for(int i=1; i<n; ++i){
			if(line.at(i)==' '){
				if(line.at(i-1) != ' '){
					valid_character = true;
				}
				else{
					valid_character = false;
				}
			}
			else if(line.at(i)=='	'){
				valid_character = false;
			}
			else{
				valid_character = true;
			}
			if(valid_character){
				newLine=newLine+line.at(i);
			}
		}

		if(newLine.back()==' '){
			newLine.pop_back();
		}
	}
	return newLine;
}

string removeComment(string line){
	string newLine;

	if(!line.empty()){
		int n = line.length();

		for(int i=0; i<n; ++i){
			if(line.at(i)==';'){
				break;
			}
			else{
				newLine = newLine+line.at(i);
			}
		}
	}
	return newLine;
}

void textTreatment(string filename){
	string filename1 = filename + ".asm";
	string filename2 = filename + ".temp";

	ifstream textFile(filename1);
	ofstream preProcessedFile(filename2);

	string line;
	string newLine;

	if(!textFile.is_open()){
		cout << "Nao foi possivel abrir" << endl;
	}
	if(!preProcessedFile.is_open()){
		cout << "Nao foi possivel abrir" << endl;
	}
	while(getline(textFile,line)){
		newLine = removeSpaceTab(line);
		newLine = removeComment(newLine);
		if(!newLine.empty()){
			newLine = newLine + "\n";
			preProcessedFile << newLine;
		}
	}

	textFile.close();
	preProcessedFile.close();
}

void preProcessor(string filename){

}



//Tirar espacos tabs e enters -Foi
//macros
//equs
//ifs
