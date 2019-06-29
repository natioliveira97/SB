/** 
	\file pre_processor.cpp
	\author Natalia Oliveira Borges - 16/0015863
	\author Lívia Gomes Costa Fonseca - 16/0034078
	\name Pré Processador
*/

#include "pre_processor.hpp"

using namespace std;

/** \brief Remove espaços e tabs desnecessários.
	\details Remove qualquer tab. Remove espaço que não possui caractere antecessor, espaço no começo da linha e no fim da linha.
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

	textFile.open(filename1);
	temporaryFile1.open(filename2);

	string line;
	string newLine;

	if(!textFile.is_open()){
		cout << "Nao foi possivel abrir arquivo " << filename1 << endl;
	}
	if(!temporaryFile1.is_open()){
		cout << "Nao foi possivel abrir arquivo " << filename2 << endl;
	}

	while(getline(textFile,line)){
		newLine = removeSpaceTab(line);
		newLine = removeComment(newLine);
		if(!newLine.empty()){
			newLine = newLine + "\n";
			temporaryFile1 << newLine;
		}
	}

	textFile.close();
	temporaryFile1.close();
}

/** \brief Procura declaração na tabela de EQUs e retorna a posição que a declaração se encontra na tabela.
	\param token Rótulo a ser procurado na tabela.
	\return Posição da declaração na tabela.
			-1 Caso não esteja na tabela.
*/
int preProcessor::findInEQUT(string token){
	string equ;
	for(int i=0; i<EQUT.size(); ++i){
		equ = EQUT[i].rot;
		equ.pop_back();
		if(token == equ){
			return i;
		}
	}
	return -1;
}

/** \brief Verifica diretiva if.
	\param structure Estrutura da linha.
	\return true Se próxima linha será parte do código.
			false Se próxima linha não seŕa parte do código.
*/
bool preProcessor::ifs(lineStruct structure){
	int i_equt;
	if(lowerCase(structure.directive) == "if"){
		//IF com numero
		if(structure.lineCode == "DN"){
			if(!stoi(structure.number)){
				return  false;
			}
		}
		//IF com chamada de EQU
		if(structure.lineCode == "DZ"){
			i_equt = findInEQUT(lowerCase(structure.notDefined[0]));
			if(i_equt!=-1){
				if(!stoi(EQUT[i_equt].value)){
					return  false;
				}
			}					
		}
	}
	return true;
}


/** \brief Trata a declaração e chamada de EQUs, IFs e MACROS.
	\details Preenche as tabelas MNT, MDT e EQUT e trata as chamadas dessas macros.
	\param filename Nome do arquivo sem extensão.
	\return Essa função não possui retorno.
*/
void preProcessor::expandDirectives(string filename){
	string filename1 = filename + ".temp";
	string filename2 = filename + ".pre";
	string line;
	int i_equt = 0; //Indice vetor de EQU
	bool writeNextLine = true;
	bool writeLine = true;
	int section = 0; //Define em qual sessao o codigo se encontra (0-nao esta na text nem na data, 1-text, 2-data)

	temporaryFile2.open(filename1);
	preProcessedFile.open(filename2);
	if(!preProcessedFile.is_open()){
		cout << "Nao foi possivel abrir arquivo " << filename1 << endl;
	}
	if(!temporaryFile2.is_open()){
		cout << "Nao foi possivel abrir arquivo " << filename2 << endl;
	}

	//Percorre todas as linhas do arquivo e ...
	//Antes da sessão text é possível ter EQUs, guarda essas variáveis em tabelas e nada é escrito no arquivo pré-processado
	//Na sessão text é possível ter IFs
	//Na sessão data é possível ter chamada de EQUs

	while(getline(temporaryFile2,line)){
		writeLine = true;
		//Pula a linha caso a linha anterior aponte um if falso.
		if(writeNextLine == false){
			writeNextLine = true;
			continue;
		}

		lineStruct structure;
		structure = lineStructure(line);

		if(lowerCase(line)=="section text"){
			section = 1;
			preProcessedFile << line << "\n";
			continue;
		}
		if(lowerCase(line)=="section data"){
			section = 2;
			preProcessedFile << line << "\n";
			continue;
		}

		//Os EQUs são definidos antes da sessão texto
		if(section == 0){
			if(!structure.directive.empty()){
				//Se é declaração de EQU
				if(lowerCase(structure.directive) == "equ"){
					if(structure.lineCode != "RDN"){
						error("Sintaxe de EQU incorreta");
					}
					EQUT.push_back(equt());
					EQUT[EQUT.size()-1].rot = lowerCase(structure.rot);
					EQUT[EQUT.size()-1].value = structure.number;
				}
			}
		}

		//Na sessão texto há declaração e chamadas de macros e IFs
		else if(section == 1){
			if(!structure.directive.empty()){
				//Se é IF
				if(lowerCase(structure.directive) == "if"){
					writeNextLine = ifs(structure);
					writeLine = false;
				}
			}
			if(writeLine){
				preProcessedFile << line <<'\n';
			}
		}

		//Na sessão data só é necessário expandir EQUs
		else if(section == 2){
			if(structure.lineCode == "R"){
				preProcessedFile << line << " ";
			}
			else{
				for(int i=0; i<structure.notDefined.size(); ++i){
					i_equt = findInEQUT(lowerCase(structure.notDefined[i]));
					int line_index = line.find(structure.notDefined[i]);
					if(line_index != string::npos && i_equt != -1){
						line.replace(line_index, structure.notDefined[i].size(), EQUT[i_equt].value);
					}
				}
				preProcessedFile << line << "\n";
			}

		}
	}

	temporaryFile2.close();
	preProcessedFile.close();
	remove(filename1.c_str());
}

void preProcessor::error(string description){
	erro = true;
	cout << description << endl;
}

void preProcessor::run(string filename){
	textTreatment(filename);
	expandDirectives(filename);
}