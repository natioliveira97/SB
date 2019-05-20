/** 
	\file scanner.cpp
	\author Natalia Oliveira Borges - 16/0015863
	\author Lívia Gomes Costa Fonseca - 16/0034078
	\name Scaner
*/

#include "scanner.hpp"

using namespace std;

/** \brief Transforma uma string para lower case.
	\param token
	\return String não sensivel ao caso.
*/
string scanner::lowerCase(string token){
	string lowerCaseToken;
	int n = token.length();
	char c;

	for(int i=0; i<n; ++i){
		if(token.at(i)>='A' && token.at(i)<='Z'){
			c = token.at(i)+('a'-'A');
		}
		else{
			c = token.at(i);
		}
		lowerCaseToken=lowerCaseToken+c;
	}
	return lowerCaseToken;
}

/** \brief Verifica se o token a válido.
	\param token
	\return true Se o token a válido.
			false Se o token não é válido.
*/
bool scanner::isValido(string token){
	regex regEx ("[_a-zA-Z][_a-zA-z0-9]{0,50}");
	bool valido;

	valido = regex_match(token, regEx);

	return valido;

}