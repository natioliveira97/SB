#include "compilador.hpp"

using namespace std;

void Compilador::add(lineStruct structure){
	IA32File << "add eax, [" << structure.notDefined[0] << "]" << endl;
}

void Compilador::sub(lineStruct structure){
	IA32File << "sub eax, [" << structure.notDefined[0] << "]" << endl;
}

void Compilador::mult(lineStruct structure){
	IA32File << "mov DWORD ebx, [" << structure.notDefined[0] << "]" << endl;
	IA32File << "imul ebx" << endl;
}

void Compilador::div(lineStruct structure){
	IA32File << "cdq" << endl;
	IA32File << "mov DWORD ebx, [" << structure.notDefined[0] << "]" << endl;
	IA32File << "idiv ebx" << endl;
}

void Compilador::jmp(lineStruct structure){
	IA32File << "jmp " << structure.notDefined[0] << endl;
}

void Compilador::jmpn(lineStruct structure){
	IA32File << "cmp eax, 0" << endl;
	IA32File << "jl " << structure.notDefined[0] << endl;
}

void Compilador::jmpp(lineStruct structure){
	IA32File << "cmp eax, 0" << endl;
	IA32File << "jg " << structure.notDefined[0] << endl;
}

void Compilador::jmpz(lineStruct structure){
	IA32File << "cmp eax, 0" << endl;
	IA32File << "je " << structure.notDefined[0] << endl;
}

void Compilador::copy(lineStruct structure){
	IA32File << "mov DWORD ebx, [" << structure.notDefined[0] << "]" << endl;
	IA32File << "mov DWORD [" << structure.notDefined[2] << "]" << ", ebx" << endl;
}

void Compilador::load(lineStruct structure){
	IA32File << "mov DWORD eax, [" << structure.notDefined[0] << "]" << endl;
}

void Compilador::store(lineStruct structure){
	IA32File << "mov DWORD [" << structure.notDefined[0] << "], eax" << endl;
}

void Compilador::input(lineStruct structure){
	IA32File << "push eax" << endl;
	IA32File << "push " << structure.notDefined[0] << endl;
	IA32File << "call LerInteiro" << endl;
	IA32File << "add esp, 4" << endl;
	IA32File << "pop eax" << endl;
	lerInteiro = true;
}

void Compilador::output(lineStruct structure){
	IA32File << "push eax" << endl;
	IA32File << "push " << structure.notDefined[0] << endl;
	IA32File << "call EscreverInteiro" << endl;
	IA32File << "add esp, 4" << endl;
	IA32File << "pop eax" << endl;
	escreveInteiro = true;
}

void Compilador::c_input(lineStruct structure){
	IA32File << "push eax" << endl;
	IA32File << "push " << structure.notDefined[0] << endl;
	IA32File << "call LerChar" << endl;
	IA32File << "add esp, 4" << endl;
	IA32File << "pop eax" << endl;
}

void Compilador::c_output(lineStruct structure){
	IA32File << "push eax" << endl;
	IA32File << "push " << structure.notDefined[0] << endl;
	IA32File << "call EscreverChar" << endl;
	IA32File << "add esp, 4" << endl;
	IA32File << "pop eax" << endl;
}

void Compilador::h_input(lineStruct structure){
	IA32File << "push eax" << endl;
	IA32File << "push " << structure.notDefined[0] << endl;
	IA32File << "call LerHexa" << endl;
	IA32File << "add esp, 4" << endl;
	IA32File << "pop eax" << endl;
}

void Compilador::h_output(lineStruct structure){
	IA32File << "push eax" << endl;
	IA32File << "push " << structure.notDefined[0] << endl;
	IA32File << "call EscreverHexa" << endl;
	IA32File << "add esp, 4" << endl;
	IA32File << "pop eax" << endl;
}

void Compilador::s_input(lineStruct structure){
	IA32File << "push eax" << endl;
	IA32File << "push DWORD " << structure.number << endl;
	IA32File << "push " << structure.notDefined[0] << endl;
	IA32File << "call LerString" << endl;
	IA32File << "add esp, 8" << endl;
	IA32File << "pop eax" << endl;
}

void Compilador::s_output(lineStruct structure){
	IA32File << "push eax" << endl;
	IA32File << "push DWORD " << structure.number << endl;
	IA32File << "push " << structure.notDefined[0] << endl;
	IA32File << "call EscreverString" << endl;
	IA32File << "add esp, 8" << endl;
	IA32File << "pop eax" << endl;
}

void Compilador::stop(lineStruct structure){
	IA32File << "mov eax, 1" << endl;
	IA32File << "mov ebx, 0" << endl;
	IA32File << "int 80h" << endl;
}

void Compilador::textSintaxe(string line){
	lineStruct structure;
	structure = lineStructure(line);


	if(!structure.rot.empty()){
		IA32File << structure.rot << " ";
	}

	if(structure.lineCode.find('S')!=string::npos){
		int n = stoi(structure.number)*4;
		structure.notDefined[0] = structure.notDefined[0]+"+"+to_string(n);
	}

	if(!structure.funct.empty()){
		if(structure.funct == "add"){
			add(structure);
			return;
		}
		else if(structure.funct == "sub"){
			sub(structure);
		}
		else if(structure.funct == "mult"){
			mult(structure);
		}
		else if(structure.funct == "div"){
			div(structure);
		}
		else if(structure.funct == "jmp"){
			jmp(structure);
		}
		else if(structure.funct == "jmpn"){
			jmpn(structure);
		}
		else if(structure.funct == "jmpp"){
			jmpp(structure);
		}
		else if(structure.funct == "jmpz"){
			jmpz(structure);
		}
		else if(structure.funct == "copy"){
			copy(structure);
		}
		else if(structure.funct == "load"){
			load(structure);
		}
		else if(structure.funct == "store"){
			store(structure);
		}
		else if(structure.funct == "input"){
			input(structure);
		}
		else if(structure.funct == "output"){
			output(structure);
		}
		else if(structure.funct == "c_input"){
			c_input(structure);
		}
		else if(structure.funct == "c_output"){
			c_output(structure);
		}
		else if(structure.funct == "h_input"){
			h_input(structure);
		}
		else if(structure.funct == "h_output"){
			h_output(structure);
		}
		else if(structure.funct == "s_input"){
			s_input(structure);
		}
		else if(structure.funct == "s_output"){
			s_output(structure);
		}
		else if(structure.funct == "stop"){
			stop(structure);
		}
	}

}

void Compilador::printFuncoes(){
	string line;
	ifstream funcoes("funcoes.asm");
	while(getline(funcoes,line)){
		IA32File << line << endl;
	}

}

void Compilador::dataSintaxe(string line){
	lineStruct structure;
	structure = lineStructure(line);


	if(!structure.rot.empty()){
		string rot = structure.rot;
		rot.pop_back();
		IA32File << rot << " ";
	}

	if(!structure.directive.empty()){
		if(structure.directive == "const"){
			if(!structure.number.empty()){
				IA32File << "dd " << structure.number << endl; 
			}
			else if(!structure.character.empty()){
				IA32File << "dd " << structure.character << endl;
			}
		}
		else if(structure.directive == "space"){
			int n = 1;
			if(!structure.number.empty()){
				n = stoi(structure.number);
			}
			IA32File << "dd"; 
			for(int i=0; i<n; ++i){
				IA32File << " 0";
				if(i < n-1){
					IA32File << ",";
				}
			}
			IA32File << endl;
		}

	}
}


void Compilador::transformIA32(string filename){
	string filename1 = filename + ".pre";
	string filename2 = filename + ".s";

	ifstream textFile(filename1);
	IA32File.open(filename2);
	string line;
	int section = 0;

	if(!textFile.is_open()){
		cout << "Nao foi possivel abrir arquivo " << filename1 << endl;
	}
	if(!IA32File.is_open()){
		cout << "Nao foi possivel abrir arquivo " << filename2 << endl;
	}

	while(getline(textFile,line)){
		string line2 = lowerCase(line);

		if(line2.find("section") != string::npos){
			if(lowerCase(line) == "section text"){
				IA32File << "section .text" << endl;
				printFuncoes();
				IA32File << "global _start" << endl;
				IA32File << "_start:" << endl;
				section = 1;
				continue;
			}
			else if(lowerCase(line) == "section data"){
				IA32File << "section .data" << endl;
				section = 2;
				continue;
			}
			else{
				section = 3;
			}
		}
		if(section == 1){
			textSintaxe(line2);
		}
		if(section == 2){
			dataSintaxe(line2);
		}

	}

	textFile.close();
	remove(filename1.c_str());
	IA32File.close();
}

void Compilador::run(string filename){
	transformIA32(filename);

}
