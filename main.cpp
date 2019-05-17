#include <iostream>
#include "pre_processor.hpp"
#include "montador.hpp"

int main(){
	string filename = "fatorial";

	preProcessor preProcessor;

	preProcessor.run(filename);

	Montador Montador;
	Montador.run(filename);
}