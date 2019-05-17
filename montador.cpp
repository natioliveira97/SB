#include "montador.hpp"

using namespace std;


/** \brief Preenche os campos da struct tabelaSimbols.
	\param token Nome do rótulo.
	\param address Endereço do rótulo.
	\return simbol Struct com os campos preenchidos.
*/
tabelaSimbolos Montador::getSimbol(string token, int address, int type, int const_value){
	tabelaSimbolos simbol;

	simbol.name = token;
	simbol.address = address;
	simbol.type = type;
	simbol.const_value = const_value;

	return simbol;
}


/** \brief Coloca o rótulo com seu respectivo endereço no vector da tabela de símbolos.
	\param token Nome do rótulo.
	\param address Endereço do rótulo.
*/
void Montador::putTable(string token, int address, int type, int const_value){
	TABS.push_back(getSimbol(token, address, type, const_value));
}


/** \brief Procura um rótulo na tabela de símbolos.
	\param token Nome do rótulo.
	\return adresss Endereço do rótulo se existente na tabela.
	\return -1 Se o rótulo não existe na tabela.
*/
int Montador::searchAddress(string token, int desiredAddress){
	for(int i = 0; i < TABS.size(); ++i){
		if(TABS[i].name == token){
			return TABS[i].address;
		}
		if(TABS[i].address == desiredAddress){
			return -2;
		}
	}
	return -1;
}


/** \brief Preenche a tabela de símbolos.
	\details Percorre o arquivo pré-processado e coloca os rótulo na tabela de símbolos verificando se há erros léxicos e de dupla declaração de rótulo.
	\param filename Nome do arquivo pré-processado.
*/
void Montador::fillTable(string filename){
	string filename1 = filename + ".pre";
	int address = 0, lineNumber = 0;

	ifstream textFile(filename1);
	string line;

	if(!textFile.is_open()){
		cout << "Nao foi possivel abrir arquivo" << endl;
	}

	while(getline(textFile,line)){
			
		cout << address << " " << line << endl;
		lineStruct structure = lineStructure(line);
		lineNumber++;

		// Verifia se a linha possui algum rótulo.
		regex comp("(R)(.*)");
		int thereIsRot = regex_match(structure.lineCode, comp);
		if(thereIsRot){
			structure.rot.pop_back();
			if(isValido(structure.rot)){
				if(searchAddress(structure.rot,-1) == -1){
					putTable(lowerCase(structure.rot), address, 1, 0);
				}
				else {
					error("sem", lineNumber, "Rótulo já definido.");
				}
			}
			else
				error("lex",lineNumber,"Token Inválido.");
		}


		// Verifica se a linha possui fução.
		// Se a função for um "copy", soma-se 3 no contador de endereços.
		// Se a função for um "stop", soma-se 1 no contador de endereços.
		// Senão, soma-se 1 no contador de endereços;
		regex comp1("(.*)(F)(.*)");
		if(regex_match(structure.lineCode, comp1)){
			if (lowerCase(structure.funct) == "copy")
				address += 3;
			else if (lowerCase(structure.funct) == "stop")
				address++;
			else
				address += 2;
		}

		// Verifica se a linha possui diretiva.
		// Se a diretiva for um "space" e possuir argumento, soma-se o valor do argumento no contador de endereços, senão soma-se 1.
		// Se a diretiva for qualquer outra, soma-se 1 no contador de endereços.
		regex comp2("(.*)(D)(.*)");
		regex comp3("(.*)(N)(.*)");
		if(regex_match(structure.lineCode, comp2)){
			if (lowerCase(structure.directive) == "space"){
				if(thereIsRot){
					TABS[TABS.size()-1].type = 2;
				}
				else{
					error("sin", lineNumber, "Diretiva SPACE sem rótulo");
				}
				if(regex_match(structure.lineCode, comp3))
					address += stoi(structure.number);
				else 
					address++;
			}
			else if(lowerCase(structure.directive) == "const"){
				if(thereIsRot){
					TABS[TABS.size()-1].type = 3;
					TABS[TABS.size()-1].const_value = stoi(structure.number);
				}
				else{
					error("sin", lineNumber, "Diretiva CONST sem rótulo");
				}
				address++;
			}
		}
	}
	textFile.close();
}

int Montador::functionArgs(string funct){
	vector<string> functions = {"add","sub","mul","div","jmp","jmpp","jmpz","copy","load","store","input","output","stop"};
	vector<int> arg = {1,1,1,1,1,1,1,2,3,4,5,6,7};

	for(int i = 0; i < functions.size(); ++i){
		if(funct == functions[i]){
			return arg[i];
		}
	}
	return -1;
}

// int Montador::functionCode(string funct){
// 	vector<string> functions = {"add","sub","mul","div","jmp","jmpp","jmpz","copy","load","store","input","output","stop"};
// 	for(int i = 0; i < functions.size(); ++i){
// 		if(funct == functions[i]){
// 			return i+1;
// 		}
// 	}
// 	return -1;
// }

void Montador::textSintaxe(string line int lineNumber){
	lineStruct structure = lineStructure(line);

	regex comp1("(.*)(F)(.*)");
	if(regex_match(structure.lineCode, comp1)){
		//objFile <<  functionCode(structure.funct) << " ";
		if(structure.notDefined.size() != functionArgs(structure.funct)){
			error("sin", lineNumber, "Número de argumentos errado.");
		}
		for(int i = 0; i < structure.notDefined.size(); ++i){
			address = searchAddress(structure.notDefined[i], -1);
			if(address == -1){
				error("sem", lineNumber, "Argumento não declarado");
			}
		}




	}
	else{
		error("sin", lineNumber, "Linha da sessão texto sem declaração de função.");
	}
}

void Montador::secondPass(string filename){
	string filename1 = filename + ".pre";
	string filename2 = filename + ".obj";
	int lineNumber = 0;
	int section = 0;
	int address = 0;
	int thereIsRot;

	ifstream textFile(filename1);
	ofstream objFile(filename2);
	string line;

	if(!textFile.is_open()){
		cout << "Nao foi possivel abrir arquivo" << endl;
	}
	if(!objFile.is_open()){
		cout << "Nao foi possivel abrir arquivo" << endl;
	}

	while(getline(textFile,line)){

		if(lowerCase(line) == "section text"){
			section = 1;
			continue;
		}
		if(lowerCase(line) == "section data"){
			if(section == 0){
				error("sin", lineNumber, "Sessão de dados declarada sem prévia declaração de sessão texto");
			}
			section == 2;
			continue;
		}

		//Na sessão texto todas as linhas devem ter função.
		if(section == 1){
			textSintaxe(line, lineNumber);

		}


		
	}
	textFile.close();
	objFile.close();
}





/** \brief Imprime na tela a tabela de símbolos com os nomes dos rótulos e seus respectivos endereços.
*/
void Montador::printTable(){
	cout << "Nome \tEndereço" << endl;

	for(int i = 0; i < TABS.size(); ++i){
		cout << TABS[i].name << "\t" << TABS[i].address << endl;
	}
}


void Montador::error(string errorType, int lineNumber, string description){
	if(errorType == "lex"){
		cout << "Erro léxico na linha " << lineNumber << ": " << description << endl;
	}
	else if(errorType == "sin"){
		cout << "Erro sintático na linha " << lineNumber << ": " << description << endl;
	}
	else{
		cout << "Erro semântico na linha " << lineNumber << ": " << description << endl;
	}

}


void Montador::run(string filename){
	fillTable(filename);
	printTable();

}
