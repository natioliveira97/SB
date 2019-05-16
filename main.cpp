#include <iostream>
#include "pre_processor.hpp"

int main(){
	string filename = "fatorial";

	preProcessor preProcessor;

	preProcessor.run(filename);

	Montador Montador;
	Montador.run(filename);
}