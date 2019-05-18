#include "parser.hpp"

using namespace std;

/** \brief Verifica se o token é uma função.
	\param token 
	\return 	true Se é função.
				false Se não é função.
*/
bool parser::isFunction(string token){
	vector<string> functions = {"add","sub","mult","div","jmp","jmpn","jmpp","jmpz","copy","load","store","input","output","stop"};
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
	for(int i=0; i<n; ++i){
		if ((token.at(i) < '0' || token.at(i) > '9')){
			return false;
		}
	}
	return true;
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
			structure.number = token;
			structure.lineCode = structure.lineCode + "N";
		}
		else{
			structure.notDefined.push_back(token);
			structure.lineCode = structure.lineCode + "Z";
		}
		token.erase();
	}
	return structure; 
}

void parser::sintaticError(int errorCode){
	cout << "Erro" << endl;
}