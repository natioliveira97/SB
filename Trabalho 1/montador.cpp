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
	\return -2 Se o endereço já existe na tabela.
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
	\details Percorre o arquivo pré-processado e coloca os rótulos na tabela de símbolos verificando se há erros léxicos e de dupla declaração de rótulo.
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
		lineStruct structure = lineStructure(line);
		lineNumber++;

		// Verifica se a linha possui algum rótulo.
		regex comp("(R)(.*)");
		// Verifica se a linha possui diretiva.
		regex comp1("(.*)(D)(.*)");
		// Verifica se a linha possui parâmetro de diretiva.
		regex comp2("(.*)(N)(.*)");

		int thereIsRot = regex_match(structure.lineCode, comp);
		if(thereIsRot){
			structure.rot.pop_back();
			if(isValido(structure.rot)){
				if(searchAddress(structure.rot, address) == -1){
					putTable(lowerCase(structure.rot), address, 1, 1);

					if(regex_match(structure.lineCode, comp1)){
						if (lowerCase(structure.directive) == "space"){
							if(thereIsRot){
								TABS[TABS.size()-1].type = 2;
							}
							if(regex_match(structure.lineCode, comp2)){
								TABS[TABS.size()-1].const_value = stoi(structure.number);
							}
							else{
								TABS[TABS.size()-1].const_value = 1;
							}
						}
						else if(lowerCase(structure.directive) == "const"){
							TABS[TABS.size()-1].type = 3;
							if(regex_match(structure.lineCode, comp2)){
								TABS[TABS.size()-1].const_value = stoi(structure.number);
							}
						}
					}
				}
				else if(searchAddress(structure.rot, address) == -2){
					error("sem", lineNumber, "Dois rótulos na mesma linha.");
				}
				else{
					error("sem", lineNumber, "Rótulo já definido.");
				}
			}
			else
				error("lex",lineNumber,"Token Inválido.");
		}


		// Verifica se a linha possui diretiva.
		// Se a diretiva for um "space" e possuir argumento, soma-se o valor do argumento no contador de endereços, senão soma-se 1.
		// Se a diretiva for qualquer outra, soma-se 1 no contador de endereços.
		if(regex_match(structure.lineCode, comp1)){
			if (lowerCase(structure.directive) == "space"){
				if(regex_match(structure.lineCode, comp2)){
					if(stoi(structure.number) > 0)
						address += stoi(structure.number);
					else
						address++;
				}
				else{
					address++;
				}
			}
			else if(lowerCase(structure.directive) == "const"){
				if(!regex_match(structure.lineCode, comp2)){
					error("sin", lineNumber, "Diretiva CONST sem número");
				}
				address++;
			}
		}


		// Verifica se a linha possui função.
		// Se a função for um "copy", soma-se 3 no contador de endereços.
		// Se a função for um "stop", soma-se 1 no contador de endereços.
		// Senão, soma-se 1 no contador de endereços;
		regex comp3("(.*)(F)(.*)");
		if(regex_match(structure.lineCode, comp3)){
			if (lowerCase(structure.funct) == "copy")
				address += 3;
			else if (lowerCase(structure.funct) == "stop")
				address++;
			else
				address += 2;
		}
	}
	textFile.close();
}

/** \brief Encontra quantos argumentos a função requer.
	\param funct Função da qual se deseja saber o número de arguentos.
	\return arg[i] Quantidade de argumetnos da função.
	\return -1 A função não foi encontrada.
*/
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

/** \brief Encontra o opcode de uma função.
	\param funct Função cujo opcode será determinado.
	\return i+1 Opcode da função.
	\return -1 A função não foi encontrada.
*/
int Montador::functionCode(string funct){
	vector<string> functions = {"add","sub","mult","div","jmp","jmpn","jmpp","jmpz","copy","load","store","input","output","stop"};
	for(int i = 0; i < functions.size(); ++i){
		if(funct == functions[i]){
			return i+1;
		}
	}
	return -1;
}

/** \brief Verifica erros léxicos, sintáticos e semânticos de uma linha da seção texto e escreve no arquivo objeto o código traduzido.
	\param line Conteúdo da linha.
	\param lineNumber Número da linha.
*/
void Montador::textSintaxe(string line, int lineNumber){
	lineStruct structure = lineStructure(line);
	int tabsIndex;
	int realAddress;

	//Verifica se a linha possui diretivas.
	regex comp("(.*)(D)(.*)");
	if(regex_match(structure.lineCode, comp)){
		error("sem", lineNumber, "Diretiva na seção texto.");
		return;
	}

	//Verifica se a linha possui rótulo.
	regex comp1("(.*)(R)(.*)");
	bool thereIsRot = regex_match(structure.lineCode, comp1);
	if(thereIsRot){
		if(structure.lineCode[0] != 'R'){
			error("sin", lineNumber, "Rótulo declarado em local indevido.");
		}
		if(structure.lineCode == "R"){
			return;
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

/** \brief Verifica erros léxicos, sintáticos e semânticos de uma linha da seção dados e escreve no arquivo objeto o código traduzido.
	\param line Conteúdo da linha.
	\param lineNumber Número da linha.
*/
void Montador::dataSintaxe(string line, int lineNumber){
	lineStruct structure = lineStructure(line);

	// Verifica se a linha possui função.
	regex comp("(.*)(F)(.*)");
	if(regex_match(structure.lineCode, comp)){
		error("sem", lineNumber, "Função na seção dados.");
		return;
	}

	//Verifica se a linha possui rótulo.
	regex comp1("(.*)(R)(.*)");
	bool thereIsRot = regex_match(structure.lineCode, comp1);
	if(thereIsRot){
		if(structure.lineCode[0] != 'R'){
			error("sin", lineNumber, "Rótulo declarado em local indevido.");
		}
	}
	else {
		error("sim", lineNumber, "Diretiva sem rótulo.");
	}

	//Verifica se a linha possui mais de uma diretiva.
	regex comp2("(.*)(D)(.*)(D)(.*)");
	if(regex_match(structure.lineCode, comp2)){
		error("sin", lineNumber, "Mais de uma diretiva na mesma linha.");
	}

	//Verifica se a linha possui mais de um argumento de diretiva.
	regex comp3("(.*)(N)(.*)(N)(.*)");
	if(regex_match(structure.lineCode, comp3)){
		error("sin", lineNumber, "Número de argumentos incorreto.");
	}

	//Verifica a sintaxe da linha considerando a ordem dos tokens e se os argumetnos são do tipo certo.
	regex comp4("(.*)(ND)(.*)");
	regex comp5("(.*)(Z)(.*)");
	if(regex_match(structure.lineCode, comp4) || regex_match(structure.lineCode, comp5)){
		error("sin", lineNumber, "Sintaxe inválida");
	}

	// Verifica se a linha possui diretiva e número como argumento.
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
}

/** \brief Segunda passagem do montador.
	\details Passagem na qual verifica-se erros léxicos sintáticos e semânticos e traduz o código, colocando-o no arquivos objeto.
	\param filename Nome do arquivo pre processado.
*/
void Montador::secondPass(string filename){
	string filename1 = filename + ".pre";
	string filename2 = filename + ".obj";
	int lineNumber = 0;
	int section = 0;
	int address = 0;
	int thereIsRot;
	regex comp("(.*)(section)(.*)");

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

		string line2 = lowerCase(line);
		if(line2.find("section") != string::npos){
			if(lowerCase(line) == "section text"){
				section = 1;
				continue;
			}
			else if(lowerCase(line) == "section data"){
				if(section == 0){
					error("sin", lineNumber, "Seção de dados declarada sem prévia declaração de seção texto.");
				}
				section = 2;
				continue;
			}
			else{
				section = 3;
				error("sin", lineNumber, "Seção inválida.");
			}
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


/** \brief Imprime na tela os tipo de erro e a linha em que se encontra e atribui true à variável erro indicando que o arquivo apresentou erro de compilação.
	\param erroType Tipo de erro, que pode ser léxico, sintático ou semântico.
	\param lineNumber Número da linha em que ocorreu o erro.
	\param description Descrição adicional do erro ocorrido.
*/
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
	secondPass(filename);
}