#include <iostream>
#include "pre_processor.hpp"
#include "montador.hpp"

int main(int argc, char **argv){
	cout << argc << endl;
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
}