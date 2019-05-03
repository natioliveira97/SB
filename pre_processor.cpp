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

/** \brief Transforma uma string para lower case.
	\param token
	\return String não sensiva ao caso.

*/
string preProcessor::lowerCase(string token){
	string lowerCaseToken;
	int n = token.length();
	char c;

	for(int i=0; i<n; ++i){
		if(token.at(i)>='A' && token.at(i)<='Z'){
			c = token.at(i)+('A'-'a');
		}
		else{
			c = token.at(i);
		}
		lowerCaseToken=lowerCaseToken+c;
	}
	return lowerCaseToken;
}

bool preProcessor::isFunction(string token){
	vector<string> functions = {"add","sub","mul","div","jmp","jmpp","jmpz","copy","load","store","input","output","stop"};
	for(int i=0; i<functions.size(); ++i){
		if (token == functions[i]){
			return true;
		}
	}
	return false;
}

/** \brief Classifica o token em rotulo, função ou diretiva e argumentos(de função ou macro)
	\param line Linha do arquivo texto.
	\return 	1 se é rótulo
				2 se é nome de função
				3 se é argumento de função
				4 se é diretiva
				5 se é argumento de macro

*/
int preProcessor::classificaToken(string token){
	if(token.back()==':'){
		return 1;
	}
	if(isFunction(token)){
		return 2;
	}
}

/** \brief Separa a linha em rotulo, função ou diretiva e argumentos
	\param line Linha do arquivo texto.
	\return Retorna struct da estrutura da linha
*/
lineStruct preProcessor::lineStructure(string line){
	lineStruct structure;
	string token;
	int n = line.length();

	for(int i=0; i<n; ++i){
		while(i<n &&line.at(i)!=' '){
			token=token+line.at(i);
			++i;
		}
		cout<<token<<endl;
		token.erase();
	}
	return structure; 
}

void preProcessor::expandDirectives(string filename){
	string filename1 = filename + ".temp";
	string filename2 = filename + ".pre";
	string line;
	lineStruct lineS;

	ifstream temporaryFile(filename1);
	ofstream preProcessedFile(filename2);
	if(!preProcessedFile.is_open()){
		cout << "Nao foi possivel abrir arquivo" << endl;
	}
	if(!temporaryFile.is_open()){
		cout << "Nao foi possivel abrir arquivo" << endl;
	}

	while(getline(temporaryFile,line)){
		cout<<line<<endl;
		lineStructure(line);


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
