#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "pre_processor.hpp"
#include "montador.hpp"

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

	Montador Montador;
	Montador.run(filename);

	if(Montador.erro == true){
		cout << "Não foi possível montar o arquivo." << endl;
		string filename2 = filename + ".obj";
		remove(filename2.c_str());
	}
}