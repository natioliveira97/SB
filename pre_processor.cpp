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

	textFile.open(filename1);
	temporaryFile1.open(filename2);

	string line;
	string newLine;

	if(!textFile.is_open()){
		cout << "Nao foi possivel abrir arquivo 1 " << filename1 << endl;
	}
	if(!temporaryFile1.is_open()){
		cout << "Nao foi possivel abrir arquivo 2 " << filename2 << endl;
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

void preProcessor::fillMNT(lineStruct structure){
	//Linhas permitidas RD, RDE, RDEE, RDEEE
	if(structure.macroArg.size() > 3){
		sintaticError(0);
	}
	string rot = structure.rot;
	rot.pop_back();
	MNT.push_back(mnt());
	MNT[MNT.size()-1].rot = rot;
	MNT[MNT.size()-1].argNumber = structure.macroArg.size();
	for(int i=0; i<structure.macroArg.size(); ++i){
		MNT[MNT.size()-1].arg.push_back(structure.macroArg[i]);
	}
	MNT[MNT.size()-1].line = f_mdt;

}

int preProcessor::findMNT(string token){
	for(int i=0; i<MNT.size(); ++i){
		if(token == MNT[i].rot){
			return i;
		}
	}
	return -1;
}

void preProcessor::fillMDT(){
	string line;
	while(getline(temporaryFile2,line)){
		lineStruct structure;
		structure = lineStructure(line);

		int n = structure.notDefined.size();

		//Verifica macro dentro de macro
		for(int i=0; i<n; ++i){
			int isMacro = findMNT(structure.notDefined[i]);
			if(isMacro!=-1){
				macroInsideMacro(isMacro);
			}
		}

		MDT.push_back(line);
		++f_mdt;
		if(lowerCase(structure.directive) == "end"){
			break;
		}
	}

}

void preProcessor::macroInsideMacro(int start){
	int i = start;
	while(lowerCase(MDT[i])!="end"){
		MDT.push_back(MDT[i]);
		++i;
		++f_mdt;
	}
}

void preProcessor::expandMacro(int mnt_pos, lineStruct structure){
	int i = MNT[mnt_pos].line;
	int isThereArg = MNT[mnt_pos].argNumber;

	if(isThereArg){
		if(structure.notDefined.size()!=isThereArg+1){
			sintaticError(0);
		}
	}
	cout << " QUantidade de argumentos: " << isThereArg << endl; 

	while(lowerCase(MDT[i]) != "end"){
		string line = MDT[i];
		cout << "Linha ainda nao extendida: "<<line<<endl;
		for(int j=0; j<isThereArg; ++j){
			cout << "1" << endl;
			int found = line.find(MNT[mnt_pos].arg[j]);
			cout << "2" << endl;
			if(found!=string::npos){
				cout << "3" << endl;
				line.replace(found, MNT[mnt_pos].arg[j].size(), structure.notDefined[j+1]);
				cout << "4" << endl;
			}
		}
					
		preProcessedFile << line << '\n';
		cout << "Linha macro expandida:"<< line << '\n';
		++i;
		
	}
}



void preProcessor::expandDirectives(string filename){
	string filename1 = filename + ".temp";
	string filename2 = filename + ".pre";
	string line;
	int f_equt=0; //Ultimo elemento da tabela de EQU
	int i_equt=0; //Indice vetor de EQU
	bool writeNextLine = true;
	int section = 0; //Define em qual sessao o codigo se encontra (0-nao esta na text nem na data, 1-text, 2-data)

	temporaryFile2.open(filename1);
	preProcessedFile.open(filename2);
	if(!preProcessedFile.is_open()){
		cout << "Nao foi possivel abrir arquivo 3 " << filename1 << endl;
	}
	if(!temporaryFile2.is_open()){
		cout << "Nao foi possivel abrir arquivo 4 " << filename2 << endl;
	}

	//Percorre todas as linhas do arquivo e ...
	//Antes da sessão text é possível ter EQUs e definição de MACROS, guarda essas variáveis em tabelas e nada é escrito no arquivo pré-processado
	//Na sessão text é possível ter IFs e chamadas de MACROS
	//Na sessão data é possível ter chamada de EQUs

	while(getline(temporaryFile2,line)){
		//Pula a linha caso a linha anterior aponte um if falso.
		if(writeNextLine == false){
			writeNextLine = true;
			continue;
		}

		lineStruct structure;
		cout << line << endl;
		structure = lineStructure(line);

		cout << structure.lineCode << endl;
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
						sintaticError(0);
					}
					EQUT.push_back(equt());
					EQUT[f_equt].rot = lowerCase(structure.rot);
					EQUT[f_equt].value = structure.number;
				}
			}
		}

		//Na sessão texto há declaração e chamadas de macros e IFs
		else if(section == 1){
			if(!structure.directive.empty()){
				//Se é IF
				if(lowerCase(structure.directive) == "if"){
					//IF com numero
					if(structure.lineCode == "DN"){
						if(!stoi(structure.number)){
							writeNextLine = false;
						}
					}
					//IF com chamada de EQU
					if(structure.lineCode == "DZ"){
						i_equt = findInEQUT(lowerCase(structure.notDefined[0]));
						if(i_equt!=-1){
							if(!stoi(EQUT[i_equt].value)){
								writeNextLine = false;
							}
						}					
					}
				}
				//Se é declaração de MACRO
				if(lowerCase(structure.directive) == "macro"){
					if(structure.lineCode.compare(0,2,"RD")!=0){
						sintaticError(0);
					}
					fillMNT(structure);
					fillMDT();
				}
			}
			else if(structure.funct.empty() && structure.notDefined.size()){
				cout << "Possivel chamada de MACRO" << endl;
				for(int i=0; i<structure.notDefined.size(); ++i){
					int isMacro = findMNT(structure.notDefined[i]);
					cout << "Is macro = " << isMacro << endl;
					if(isMacro!=-1){
						expandMacro(isMacro, structure);
					}
				}
			}
			else{
				preProcessedFile << line <<'\n';
			}
		}

		//Na sessão data só é necessário expandir EQUs
		else if(section == 2){
			if(structure.lineCode == "RDZ"){
				i_equt = findInEQUT(lowerCase(structure.notDefined[0]));
				preProcessedFile << structure.rot << " " << structure.directive << " " << EQUT[i_equt].value << "\n";
			}
			else{
				preProcessedFile << line << "\n";
			}
		}
	}

	cout <<endl << "MNT" <<endl;
	for(int i=0; i<MNT.size(); ++i){
		cout << MNT[i].rot<< endl;
	}

	cout <<endl << "MDT" <<endl;
	for(int i=0; i<MDT.size(); ++i){
		cout << MDT[i]<< endl;
	}

	temporaryFile2.close();
	preProcessedFile.close();
}

void preProcessor::run(string filename){
	textTreatment(filename);
	expandDirectives(filename);

}