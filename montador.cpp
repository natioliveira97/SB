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
	\return adresss Índice do rótulo se existente na tabela.
	\return -1 Se o rótulo não existe na tabela.
*/
int Montador::searchAddress(string token, int desiredAddress){
	for(int i = 0; i < TABS.size(); ++i){
		if(TABS[i].name == token){
			return i;
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
		cout << "Nao foi possivel abrir arquivo " << filename1 << endl;
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
					putTable(lowerCase(structure.rot), address, 1, 1);
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
				if(regex_match(structure.lineCode, comp3)){
					address += stoi(structure.number);
					TABS[TABS.size()-1].const_value = stoi(structure.number);
				}
				else{
					address++;
				}
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
	vector<string> functions = {"add","sub","mult","div","jmp","jmpn","jmpp","jmpz","copy","load","store","input","output","stop"};
	vector<int> arg = {1,1,1,1,1,1,1,1,2,1,1,1,1,0};

	for(int i = 0; i < functions.size(); ++i){
		if(funct == functions[i]){
			return arg[i];
		}
	}
	return -1;
}

int Montador::functionCode(string funct){
	vector<string> functions = {"add","sub","mult","div","jmp","jmpn","jmpp","jmpz","copy","load","store","input","output","stop"};
	for(int i = 0; i < functions.size(); ++i){
		if(funct == functions[i]){
			return i+1;
		}
	}
	return -1;
}


void Montador::textSintaxe(string line, int lineNumber){
	lineStruct structure = lineStructure(line);
	int tabsIndex;
	int realAddress;

	//Verifica se a linha possui diretivas.
	regex comp("(.*)(D)(.*)");
	if(regex_match(structure.lineCode, comp)){
		error("sem", lineNumber, "Diretiva na seção texto.");
	}

	//Verifica se a linha possui rótulo.
	regex comp1("(.*)(R)(.*)");
	bool thereIsRot = regex_match(structure.lineCode, comp1);
	if(thereIsRot){
		if(structure.lineCode[0] != 'R'){
			error("sin", lineNumber, "Rótulo declarado em local indevido.");
		}
	}

	//Verifica se tem função.
	regex comp2("(.*)(F)(.*)");
	bool thereIsFunct = regex_match(structure.lineCode, comp2);
	if(thereIsFunct){
		if(thereIsRot){
			if(structure.lineCode[1] != 'F'){
				error("sin", lineNumber, "Função declarada em local indevido.");
			}
		}
		else{
			if(structure.lineCode[0] != 'F'){
				error("sin", lineNumber, "Função declarada em local indevido.");
			}
		}
		objFile << functionCode(structure.funct) << " ";
	}
	else{
		error("sem", lineNumber, "Linha da seção texto sem função.");
		return;
	}

	//Verifica se o número de argumentos da função está correto.
	if(structure.notDefined.size() != functionArgs(structure.funct)){
		error("sin", lineNumber, "Número de argumentos incorreto.");
		return;
	}

	if(functionArgs(structure.funct) == 0){
		//Verifica sintaxe da linha.
		if(structure.lineCode != "F" && structure.lineCode != "RF"){
			error("sin", lineNumber, "Sintaxe inválida");
		}
	}
	else if(functionArgs(structure.funct) == 1){
		//Verifica sintaxe da linha.
		if(structure.lineCode != "FZ" && structure.lineCode != "RFZ" && structure.lineCode != "FZSN" && structure.lineCode != "RFZSN"){
			error("sin", lineNumber, "Sintaxe inválida");
		}

		tabsIndex = searchAddress(structure.notDefined[0],-1);
		if(tabsIndex == -1){
			if(!isValido(structure.notDefined[0])){
				error("lex", lineNumber, "Token inválido.");
			}
			error("sem", lineNumber, "Rótulo não declarado.");
			return;
		}

		regex comp3("(.*)(ZSN)(.*)");
		if(regex_match(structure.lineCode, comp3)){
			if(TABS[tabsIndex].type!=2){
				error("sem", lineNumber, "Operação em rótulo que não é SPACE.");
			}
			if(stoi(structure.number) >= TABS[tabsIndex].const_value){
				error("sem", lineNumber, "Endereço ultrapassa limite do vetor.");
			}
			realAddress = TABS[tabsIndex].address + stoi(structure.number);
		}
		else{
			realAddress = TABS[tabsIndex].address;
		}

		if(structure.funct == "jmp" || structure.funct == "jmpn" || structure.funct == "jmpp" || structure.funct =="jmpz"){
			if(TABS[tabsIndex].type!=1){
				error("sem", lineNumber, "Pulo para rótulo inválido.");
			}
		}
		else if(structure.funct == "div"){
			if(TABS[tabsIndex].type == 1){
				error("sem", lineNumber, "Argumento inválido.");
			}
			if(TABS[tabsIndex].type == 3 && TABS[tabsIndex].const_value == 0){
				error("sem", lineNumber, "Divisão por zero.");
			}
		}
		else if(structure.funct == "add" || structure.funct == "sub" || structure.funct == "mult" || structure.funct == "load" || structure.funct =="output"){
			if(TABS[tabsIndex].type == 1){
				error("sem", lineNumber, "Operando Inválido");
			}
		}
		else if(structure.funct == "store"){
			if(TABS[tabsIndex].type != 2){
				error("sem", lineNumber, "STORE em argumento não variável");
			}
		}
		else if(structure.funct == "input"){
			if(TABS[tabsIndex].type != 2){
				error("sem", lineNumber, "INPUT em argumento não variável");
			}
		}
		objFile << realAddress << " ";
	}

	else if(functionArgs(structure.funct) == 2){
		//Verifica sintaxe da linha, apenas o segundo argumento do copy poderá aceitar acesso vetorial
		if(structure.lineCode != "FZZ" && structure.lineCode != "RFZZ" && structure.lineCode != "FZZSN" && structure.lineCode != "RFZZSN"){
			error("sin", lineNumber, "Sintaxe inválida");
		}

		//Primeiro argumento
		if(structure.notDefined[0].back()!=','){
			error("sin", lineNumber, "Função copy sem vírgula separando os argumentos");
		}
		else{
			structure.notDefined[0].pop_back();
		}
		tabsIndex = searchAddress(structure.notDefined[0],-1);
		if(tabsIndex == -1){
			if(!isValido(structure.notDefined[0])){
				error("lex", lineNumber, "Token inválido.");
			}
			error("sem", lineNumber, "Rótulo não declarado.");
			return;
		}
		if(TABS[tabsIndex].type == 1){
			error("sem", lineNumber, "Argumento inválido");
		}

		objFile << TABS[tabsIndex].address << " ";

		//Segundo argumento
		tabsIndex = searchAddress(structure.notDefined[1],-1);
		if(tabsIndex == -1){
			if(!isValido(structure.notDefined[1])){
				error("lex", lineNumber, "Token inválido.");
			}
			error("sem", lineNumber, "Rótulo não declarado.");
			return;
		}

		regex comp3("(.*)(ZSN)(.*)");
		if(regex_match(structure.lineCode, comp3)){
			if(TABS[tabsIndex].type!=2){
				error("sem", lineNumber, "Operação em rótulo que não é SPACE.");
			}
			if(stoi(structure.number) >= TABS[tabsIndex].const_value){
				error("sem", lineNumber, "Endereço ultrapassa limite do vetor.");
			}
			realAddress = TABS[tabsIndex].address + stoi(structure.number);
		}
		else{
			realAddress = TABS[tabsIndex].address;
		}
		objFile << realAddress << " ";
	}
}






void Montador::dataSintaxe(string line, int lineNumber){
	lineStruct structure = lineStructure(line);

	//Verifica se a linha possui rótulo.
	regex comp1("(.*)(R)(.*)");
	bool thereIsRot = regex_match(structure.lineCode, comp1);
	if(thereIsRot){
		if(structure.lineCode[0] != 'R'){
			error("sin", lineNumber, "Rótulo declarado em local indevido.");
		}
	}
	else{
		error("sem", lineNumber, "Linha da seção dados sem rótulo.");
	}

	regex comp2("(.*)(D)(.*)(D)(.*)");
	if(regex_match(structure.lineCode, comp2)){
		error("sin", lineNumber, "Mais de uma diretiva na mesma linha.");
	}

	regex comp3("(.*)(N)(.*)(N)(.*)");
	if(regex_match(structure.lineCode, comp3)){
		error("sin", lineNumber, "Número de argumentos incorreto.");
	}

	regex comp4("(.*)(ND)(.*)");
	regex comp5("(.*)(Z)(.*)");
	if(regex_match(structure.lineCode, comp4) || regex_match(structure.lineCode, comp5)){
		error("sin", lineNumber, "Sintaxe inválida");
	}

	// Verifica se a linha possui diretiva.
	regex comp6("(.*)(D)(.*)");
	regex comp7("(.*)(N)(.*)");
	if(regex_match(structure.lineCode, comp6)){

		if (lowerCase(structure.directive) == "space"){
			if(regex_match(structure.lineCode, comp7)){
				if(stoi(structure.number) > 0){
					for(int i = 0; i < stoi(structure.number); i++){
						objFile << "0 ";
					}
				}
				else 
					error("sin", lineNumber, "Argumento inválido.");
			}
			else
				objFile << "0 ";
		}

		if (lowerCase(structure.directive) == "const"){
			objFile << structure.number << " ";
		}
	}
	else
		error("sem", lineNumber, "Linha da seção dados sem diretiva.");


	// Verifica se a linha possui função.
	regex comp8("(.*)(F)(.*)");
	if(regex_match(structure.lineCode, comp8)){
		error("sem", lineNumber, "Função na seção dados.");
	}
}







void Montador::secondPass(string filename){
	string filename1 = filename + ".pre";
	string filename2 = filename + ".obj";
	int lineNumber = 0;
	int section = 0;
	int address = 0;
	int thereIsRot;

	textFile.open(filename1);
	objFile.open(filename2);
	string line;

	if(!textFile.is_open()){
		cout << "Nao foi possivel abrir arquivo" << endl;
	}
	if(!objFile.is_open()){
		cout << "Nao foi possivel abrir arquivo" << endl;
	}

	while(getline(textFile,line)){
		++lineNumber;

		if(lowerCase(line) == "section text"){
			section = 1;
			continue;
		}
		if(lowerCase(line) == "section data"){
			if(section == 0){
				error("sin", lineNumber, "Sessão de dados declarada sem prévia declaração de sessão texto");
			}
			section = 2;
			continue;
		}

		if(section == 1){
			textSintaxe(line, lineNumber);
		}
		else if(section == 2){
			dataSintaxe(line, lineNumber);
		}
		
	}
	textFile.close();
	objFile.close();
}


/** \brief Imprime na tela a tabela de símbolos com os nomes dos rótulos e seus respectivos endereços.
*/
void Montador::printTable(){
	cout << "Nome \tEndereço \tTipo \tValor" << endl;

	for(int i = 0; i < TABS.size(); ++i){
		cout << TABS[i].name << "\t" << TABS[i].address << "\t" << TABS[i].type << "\t" << TABS[i].const_value <<  endl;
	}
}


void Montador::error(string errorType, int lineNumber, string description){
	erro = true;
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
	secondPass(filename);
}