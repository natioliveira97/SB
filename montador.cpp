#include "montador.hpp"

using namespace std;


/** \brief Preenche os campos da struct tabelaSimbols.
	\param token Nome do rótulo.
	\param address Endereço do rótulo.
	\return simbol Struct com os campos preenchidos.
*/
tabelaSimbolos Montador::getSimbol(string token, int address){
	tabelaSimbolos simbol;

	simbol.name = token;
	simbol.address = address;

	return simbol;
}


/** \brief Coloca o rótulo com seu respectivo endereço no vector da tabela de símbolos.
	\param token Nome do rótulo.
	\param address Endereço do rótulo.
*/
void Montador::putTable(string token, int address){
	TABS.push_back(getSimbol(token, address));
}


/** \brief Procura um rótulo na tabela de símbolos.
	\param token Nome do rótulo.
	\return adresss Endereço do rótulo se existente na tabela.
	\return -1 Se o rótulo não existe na tabela.
*/
int Montador::searchAddress(string token){
	for(int i = 0; i < TABS.size(); ++i){
		if(TABS[i].name == token){
			return TABS[i].address;
		}
	}
	return -1;
}


/** \brief Preenche a tabela de símbolos.
	\details Percorre o arquivo pré-processado e coloca os rótulo na tabela de símbolos verificando se há erros léxicso e de dupla declaração de rótulo.
	\param filename Nome do arquivo pré-processado.
*/
void Montador::fillTable(string filename){
	string filename1 = filename + ".pre";
	int address = 0, lineNumber = 0;
	bool erro;

	ifstream textFile(filename1);
	string line;

	if(!textFile.is_open()){
		cout << "Nao foi possivel abrir arquivo" << endl;
	}



	while(getline(textFile,line)){

		lineStruct structure = lineStructure(line);
		lineNumber++;

		
		// Verifia se a linha possui algum rótulo.
		regex comp("(R)(.*)");
		if(regex_match(structure.lineCode, comp)){
			structure.rot.pop_back();

			if(isValido(structure.rot)){

				if(searchAddress(structure.rot) == -1){
					putTable(structure.rot, address);
				}
				else {
					cout << "Erro semântico na linha " << lineNumber << ": rótulo já definido" << endl;
				}
			}
			else
				cout << "Erro léxico na linha " << lineNumber << endl;
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
				if(regex_match(structure.lineCode, comp3))
					address += stoi(structure.number);
				else 
					address++;
			}
			else
				address++;
		}
	}
}


/** \brief Imprime na tela a tabela de símbolos com os nomes dos rótulos e seus respectivos endereços.
*/
void Montador::printTable(){
	cout << "Nome \tEndereço" << endl;

	for(int i = 0; i < TABS.size(); ++i){
		cout << TABS[i].name << "\t" << TABS[i].address << endl;
	}
}


void Montador::run(string filename){
	fillTable(filename);
	printTable();
}
