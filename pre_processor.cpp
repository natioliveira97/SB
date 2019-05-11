/** 
	\file pre_processor.cpp
	\author Natalia Oliveira Borges - 16/0015863
	\author Lívia Gomes Costa Fonseca - 
	\name Pré Processador
*/

#include "pre_processor.hpp"

using namespace std;

/** \brief Remove espaços e tabs desnecessários.
	\details Remove qualque tab. Remove espaço que não possui caractere antecessor, espaço no começo da linha e no fim da linha.
	\param line Linha do arquivo texto.
	\return Linha tratada sem tabs e espaços desnecessários.
*/
string preProcessor::removeSpaceTab(string line){
	bool valid_character=false;
	string newLine;

	if(!line.empty()){
		int n = line.length();

		for(int i=0; i<n; ++i){
			if(line.at(i)=='	'){
				line.at(i) = ' ';
			}
		}

		if(line.at(0)!=' '){
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

/** \brief Remove comentários.
	\details Remove tudo depois de ';'.
	\param line Linha do arquivo texto.
	\return Linha tratada sem comentários.
*/
string preProcessor::removeComment(string line){
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

/** \brief Faz o tratamento do arquivo texto retiranto espaços desnecessários, tabs, enters e comentários.
	\param filename Nome do arquivo sem extensão.
	\return Essa função não possui retorno
*/
void preProcessor::textTreatment(string filename){
	string filename1 = filename + ".asm";
	string filename2 = filename + ".temp";

	ifstream textFile(filename1);
	ofstream temporaryFile(filename2);

	string line;
	string newLine;

	if(!textFile.is_open()){
		cout << "Nao foi possivel abrir arquivo" << endl;
	}
	if(!temporaryFile.is_open()){
		cout << "Nao foi possivel abrir arquivo" << endl;
	}

	while(getline(textFile,line)){
		newLine = removeSpaceTab(line);
		newLine = removeComment(newLine);
		if(!newLine.empty()){
			newLine = newLine + "\n";
			temporaryFile << newLine;
		}
	}

	textFile.close();
	temporaryFile.close();
}





void preProcessor::expandDirectives(string filename){
	string filename1 = filename + ".temp";
	string filename2 = filename + ".pre";
	string line;
	vector<equt> equTable;
	int i_equt=0; //Indice vetor de EQU
	bool writeLine;
	bool writeNextLine;

	ifstream temporaryFile(filename1);
	ofstream preProcessedFile(filename2);
	if(!preProcessedFile.is_open()){
		cout << "Nao foi possivel abrir arquivo" << endl;
	}
	if(!temporaryFile.is_open()){
		cout << "Nao foi possivel abrir arquivo" << endl;
	}

	while(getline(temporaryFile,line)){
		if(writeNextLine == false){
			writeNextLine = true;
			continue;
		}

		lineStruct structure;
		cout << line << endl;
		structure = lineStructure(line);

		cout << structure.lineCode << endl;

		if(!structure.directive.empty()){
			if(structure.directive == "equ"){
				if(structure.lineCode != "RDN"){
					sintaticError(0);
				}
				equTable.push_back(equt());
				equTable[i_equt].rot = structure.rot;
				equTable[i_equt].value = structure.number;
			}
			if(structure.directive == "if"){
				if(structure.lineCode == "DN"){
					if(!atoi(structure.number)){
						writeNextLine = false;
					}
				}
				if(structure.lineCode == "DZ"){
					for(i=0; i<equt.size(); ++i){
						if(structure.)
					}
				}
			}
		}

	}




	temporaryFile.close();
	preProcessedFile.close();
}

void preProcessor::run(string filename){
	textTreatment(filename);
	expandDirectives(filename);

}



//Tirar espacos tabs e enters -Foi
//macros
//equs
//ifs
