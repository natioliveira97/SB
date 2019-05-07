/** 
	\file scanner.cpp
	\author Natalia Oliveira Borges - 16/0015863
	\author Lívia Gomes Costa Fonseca - 
	\name Scaner
*/

#include "scanner.hpp"

using namespace std;

/** \brief Transforma uma string para lower case.
	\param token
	\return String não sensiva ao caso.
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