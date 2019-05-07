#include "parser.hpp"

using namespace std;

bool parser::isFunction(string token){
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
int parser::classificaToken(string token){
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
lineStruct parser::lineStructure(string line){
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