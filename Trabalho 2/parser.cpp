#include "parser.hpp"

using namespace std;

/** \brief Verifica se o token é uma função.
	\param token 
	\return 	true Se é função.
				false Se não é função.
*/
bool parser::isFunction(string token){
	vector<string> functions = {"add","sub","mult","div","jmp","jmpn","jmpp","jmpz","copy","load","store","input","output", "c_input", "c_output", "h_input", "h_output", "s_input", "s_output","stop"};
	token = lowerCase(token);
	for(int i=0; i<functions.size(); ++i){
		if (token == functions[i]){
			return true;
		}
	}
	return false;
}


/** \brief Verifica se o token é uma diretiva de pré processamento.
	\param token 
	\return 	true Se é diretiva.
				false Se não é diretiva.
*/
bool parser::isDirective(string token){
	vector<string> directives = {"macro", "end", "equ", "const", "space", "if"};
	token = lowerCase(token);
	for(int i=0; i<directives.size(); ++i){
		if (token == directives[i]){
			return true;
		}
	}
	return false;	
}

bool parser::isArg(string token){
	return false;
}

/** \brief Verifica se o token é um argumento de macro.
	\param token 
	\return true Se é argumento de macro.
			false Se não é argumento de macro.
*/
bool parser::isMacroArg(string token){
	if(token.at(0) == '&'){
		return true;
	}
	return false;	
}

/** \brief Verifica se o token é um sinal de '+'.
	\param token 
	\return 	true Se é um sinal de '+'.
				false Se não é um sinal de '+'.
*/
bool parser::isPlusSign(string token){
	if(token == "+"){
		return true;
	}
	return false;
}

/**	\brief Verifica se o token é um número.
	\param token 
	\return 	true Se é um número.
				false Se não é um número.
*/
bool parser::isNumber(string token){
	int n = token.length();

	regex hex("0x[0-9a-fA-F]{0,30}");
	regex num("[0-9-]{0,30}");

	if(regex_match(token, hex))
		return true;

	if(regex_match(token, num))
		return true;

	return false;
}

bool parser::isChar(string token){
	int n = token.length();
	if(n == 3){
		if(token[0] == '\'' && token[2] == '\''){
			return true;
		}
	}
	return false;
}

/**	\brief Separa a linha em rotulo, função ou diretiva e argumentos
	\param line Linha do arquivo texto.
	\return Retorna struct da estrutura da linha
*/
lineStruct parser::lineStructure(string line){
	lineStruct structure;
	string token;
	int n = line.length();
	line = lowerCase(line);

	for(int i=0; i<n; ++i){
		while(i<n &&line.at(i)!=' '){
			token = token+line.at(i);
			++i;
		}

		// Se é um rótulo
		if(token.back()==':'){
			structure.rot = token;
			structure.lineCode = structure.lineCode + "R";
		}
		// Se é função
		else if(isFunction(token)){
			structure.funct = token;
			structure.lineCode = structure.lineCode + "F";
		}
		// Se é argumento de função
		else if(isArg(token)){
			structure.arg.push_back(token);
			structure.lineCode = structure.lineCode + "A";
		}
		// Se é diretiva
		else if(isDirective(token)){
			structure.directive = token;
			structure.lineCode = structure.lineCode + "D";
		}
		// Se é argumento de macro
		else if(isMacroArg(token)){
			structure.macroArg.push_back(token);
			structure.lineCode = structure.lineCode + "E";
		}
		// Se é sinal de +
		else if(isPlusSign(token)){
			structure.lineCode = structure.lineCode + "S";
		}
		// Se é número
		else if(isNumber(token)){
			regex hex("0x[0-9a-fA-F]{0,30}");
			if(regex_match(token, hex)){
				int n = stoi(token, nullptr, 16);
				token =  to_string(n);
			}
			structure.number = token;
			structure.lineCode = structure.lineCode + "N";
		}
		else if(isChar(token)){
			structure.lineCode = structure.lineCode + "C";
			structure.character = token;
		}
		else{
			structure.notDefined.push_back(token);
			structure.lineCode = structure.lineCode + "Z";
		}
		token.erase();
	}
	return structure; 
}