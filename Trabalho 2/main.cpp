#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "pre_processor.hpp"
#include "compilador.hpp"

/** \brief Recebe o nome de um arquivo .asm em assembly inventado e traduz para um arquivo .s em assembly IA-32.
	\param argv[2] Nome do arquivo
*/
int main(int argc, char **argv){
	if(argc != 2){
		cout << "Passe o nome do arquivo .asm como argumento" << endl;
		return 0;
	}

	int i=0;
	string filename;
	while(argv[1][i]!='.'){
		filename = filename + argv[1][i];
		++i;
	}
	

	preProcessor preProcessor;
	preProcessor.run(filename);

	Compilador compilador;
	compilador.run(filename);

}