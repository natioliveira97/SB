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


int findInEquTable(vector<equt> equTable, string token){
	string equ;
	for(int i=0; i<equTable.size(); ++i){
		equ = equTable[i].rot;
		equ.pop_back();
		if(token == equ){
			cout << "e um if "<< equ << " " << equTable[i].rot << endl;
			return i;
		}
	}
	return -1;
}





void preProcessor::expandDirectives(string filename){
	string filename1 = filename + ".temp";
	string filename2 = filename + ".pre";
	string line;
	vector<equt> equTable;
	int f_equt=0; //Ultimo elemento da tabela de EQU
	int i_equt=0; //Indice vetor de EQU
	bool writeNextLine = true;
	int section = 0; //Define em qual sessao o codigo se encontra (0-nao esta na text nem na data, 1-text, 2-data)

	ifstream temporaryFile(filename1);
	ofstream preProcessedFile(filename2);
	if(!preProcessedFile.is_open()){
		cout << "Nao foi possivel abrir arquivo" << endl;
	}
	if(!temporaryFile.is_open()){
		cout << "Nao foi possivel abrir arquivo" << endl;
	}

	//Percorre todas as linhas do arquivo e ...
	//Antes da sessão text é possível ter EQUs e definição de MACROS, guarda essas variáveis em tabelas e nada é escrito no arquivo pré-processado
	//Na sessão text é possível ter IFs e chamadas de MACROS
	//Na sessão data é possível ter chamada de EQUs

	while(getline(temporaryFile,line)){
		lineStruct structure;
		cout << line << endl;
		structure = lineStructure(line);

		cout << structure.lineCode << endl;
		if(lowerCase(line)=="section text"){
			section = 1;
			preProcessedFile << line <<"\n";
			continue;
		}
		if(lowerCase(line)=="section data"){
			section = 2;
			preProcessedFile << line <<"\n";
			continue;
		}

		//Os EQUs e as MACROS são definidos antes da sessão texto
		if(section == 0){
			if(!structure.directive.empty()){
				//Se é declaração de EQU
				if(lowerCase(structure.directive) == "equ"){
					printf("tem equ\n");
					if(structure.lineCode != "RDN"){
						sintaticError(0);
					}
					equTable.push_back(equt());
					equTable[f_equt].rot = lowerCase(structure.rot);
					equTable[f_equt].value = structure.number;
				}
				//Se é declaração de MACRO

			}
		}

		//Na sessão texto há chamadas de macros e IFs
		else if(section == 1){
			if(!structure.directive.empty()){
				if(lowerCase(structure.directive) == "if"){
					printf("tem if\n");
					if(structure.lineCode == "DN"){
						if(!stoi(structure.number)){
							writeNextLine = false;
						}
					}
					if(structure.lineCode == "DZ"){
						i_equt = findInEquTable(equTable, lowerCase(structure.notDefined[0]));
						if(i_equt!=-1){
							if(!stoi(equTable[i_equt].value)){
								writeNextLine = false;
							}
						}					
					}
				}
			}
		}

		else if(section == 2){
			if(structure.lineCode == "RDZ"){
				i_equt = findInEquTable(equTable, lowerCase(structure.notDefined[0]));
				preProcessedFile << structure.rot << " " << structure.directive << " " << equTable[i_equt].value << "\n";
			}
			else{
				preProcessedFile << line << "\n";
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
