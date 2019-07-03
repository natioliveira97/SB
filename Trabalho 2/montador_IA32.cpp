#include "montador_IA32.hpp"

using namespace std;

	char LerInteiro_code [] = {'\xC8', '\x0D', '\x00', '\x00', '\xB8', '\x03', '\x00', '\x00', '\x00', '\xBB', '\x00', '\x00', '\x00', '\x00', '\x89', '\xE9', '\x83', '\xE9', '\x0D', '\xBA', '\x0D', '\x00', '\x00', '\x00', '\xCD', '\x80', '\x50', '\x29', '\xC0', '\xB9', '\x0A', '\x00', '\x00', '\x00', '\x80', '\x7D', '\xF3', '\x2D', '\x74', '\x07', '\xBE', '\xF3', '\xFF', '\xFF', '\xFF', '\xEB', '\x05', '\xBE', '\xF4', '\xFF', '\xFF', '\xFF', '\x80', '\x6C', '\x35', '\x00', '\x30', '\x29', '\xDB', '\x8A', '\x5C', '\x35', '\x00', '\x01', '\xD8', '\x46', '\x80', '\x7C', '\x35', '\x00', '\x0A', '\x74', '\x15', '\xF7', '\xE9', '\xEB', '\xE7', '\x80', '\x7D', '\xF3', '\x2D', '\x0F', '\x85', '\x24', '\x01', '\x00', '\x00', '\xBB', '\xFF', '\xFF', '\xFF', '\xFF', '\xF7', '\xEB', '\x8B', '\x5D', '\x08', '\x89', '\x03', '\x58', '\xC9', '\xC3'};
	int LerInteiro_size = 0xe1-0x80;

	char EscreverInteiro_code[] = {'\xC8', '\x00', '\x00', '\x00', '\x8B', '\x5D', '\x08', '\x8B', '\x03', '\x29', '\xF6', '\xB9', '\x0A', '\x00', '\x00', '\x00', '\xBB', '\x01', '\x00', '\x00', '\x00', '\x83', '\xF8', '\x00', '\x7D', '\x07', '\xBB', '\xFF', '\xFF', '\xFF', '\xFF', '\xF7', '\xEB', '\x29', '\xD2', '\xF7', '\xF9', '\x83', '\xC2', '\x30', '\x83', '\xEC', '\x01', '\x88', '\x14', '\x24', '\x46', '\x83', '\xF8', '\x00', '\x75', '\xED', '\x83', '\xFB', '\x00', '\x7D', '\x08', '\x83', '\xEC', '\x01', '\xC6', '\x04', '\x24', '\x2D', '\x46', '\xB8', '\x04', '\x00', '\x00', '\x00', '\xBB', '\x01', '\x00', '\x00', '\x00', '\x89', '\xE1', '\x89', '\xF2', '\xCD', '\x80', '\xC9', '\xC3'};
	int EscreverInteiro_size = 0x134-0xe2;

	char LerChar_code[] = {'\xC8', '\x02', '\x00', '\x00', '\xB8', '\x03', '\x00', '\x00', '\x00', '\xBB', '\x00', '\x00', '\x00', '\x00', '\x89', '\xE9', '\x83', '\xE9', '\x02', '\xBA', '\x02', '\x00', '\x00', '\x00', '\xCD', '\x80', '\x8B', '\x5D', '\x08', '\x8A', '\x4D', '\xFE', '\x89', '\x0B', '\xC9', '\xC3'};
	int LerChar_size = 0x158-0x135;

	char EscreverChar_code[] = {'\xC8', '\x00', '\x00', '\x00', '\xB8', '\x04', '\x00', '\x00', '\x00', '\xBB', '\x01', '\x00', '\x00', '\x00', '\x8B', '\x4D', '\x08', '\xBA', '\x01', '\x00', '\x00', '\x00', '\xCD', '\x80', '\xC9', '\xC3'};
	int EscreverChar_size = 0x172-0x159;

	char LerString_code[] = {'\xC8', '\x00', '\x00', '\x00', '\xB8', '\x03', '\x00', '\x00', '\x00', '\xBB', '\x00', '\x00', '\x00', '\x00', '\x8B', '\x4D', '\x08', '\x8B', '\x55', '\x0C', '\xCD', '\x80', '\xC9', '\xC3'};
	int LerString_size = 0x18a-0x173;

	char EscreverString_code[] = {'\xc8', '\x00', '\x00', '\x00', '\xbe', '\x01', '\x00', '\x00', '\x00','\x8b', '\x45', '\x08', '\x80', '\x7c', '\x30', '\xff', '\x0a','\x74', '\x06', '\x46', '\x3b', '\x75', '\x0c', '\x7c', '\xf0', '\xb8', '\x04', '\x00', '\x00','\x00', '\xbb','\x01', '\x00', '\x00', '\x00', '\x8b', '\x4d', '\x08', '\x89', '\xf2', '\xcd', '\x80', '\xc9', '\xc3'};
	int EscreverString_size = 0x1b6-0x18b;

	char LerHexa_code[] = {'\xC8', '\x09', '\x00', '\x00', '\xB8', '\x03', '\x00', '\x00', '\x00', '\xBB', '\x00', '\x00', '\x00', '\x00', '\x89', '\xE9', '\x83', '\xE9', '\x09', '\xBA', '\x09', '\x00', '\x00', '\x00', '\xCD', '\x80', '\x50', '\x29', '\xC0', '\xBE', '\xF7', '\xFF', '\xFF', '\xFF', '\x80', '\x7C', '\x35', '\x00', '\x39', '\x7F', '\x07', '\x80', '\x6C', '\x35', '\x00', '\x30', '\xEB', '\x13', '\x80', '\x7C', '\x35', '\x00', '\x46', '\x7F', '\x07', '\x80', '\x44', '\x35', '\x00', '\xC9', '\xEB', '\x05', '\x80', '\x44', '\x35', '\x00', '\xA9', '\x03', '\x44', '\x35', '\x00', '\x46', '\x80', '\x7C', '\x35', '\x00', '\x0A', '\x74', '\x05', '\xC1', '\xE0', '\x04', '\xEB', '\xCE', '\x89', '\x45', '\x08', '\x58', '\xC9', '\xC3'};
	int LerHexa_size = 0x202-0x1a3;

	char EscreverHexa_code[] = {'\xC8', '\x00', '\x00', '\x00', '\x8B', '\x5D', '\x08', '\x8B', '\x03', '\x29', '\xF6', '\xB9', '\x10', '\x00', '\x00', '\x00', '\x29', '\xD2', '\xF7', '\xF9', '\x83', '\xFA', '\x0A', '\x7D', '\x05', '\x83', '\xC2', '\x30', '\xEB', '\x03', '\x83', '\xC2', '\x57', '\x83', '\xEC', '\x01', '\x88', '\x14', '\x24', '\x46', '\x83', '\xF8', '\x00', '\x75', '\xE3', '\xB8', '\x04', '\x00', '\x00', '\x00', '\xBB', '\x01', '\x00', '\x00', '\x00', '\x89', '\xE1', '\x89', '\xF2', '\xCD', '\x80', '\xC9', '\xC3'};
	int EscreverHexa_size = 0x241-0x203;


// void Montador::add(lineStruct structure){
// 	IA32File << "add eax, [" << structure.notDefined[0] << "]" << endl;
// }

// void Montador::sub(lineStruct structure){
// 	IA32File << "sub eax, [" << structure.notDefined[0] << "]" << endl;
// }

// void Montador::mult(lineStruct structure){
// 	IA32File << "mov DWORD ebx, [" << structure.notDefined[0] << "]" << endl;
// 	IA32File << "imul ebx" << endl;
// }

// void Montador::div(lineStruct structure){
// 	IA32File << "cdq" << endl;
// 	IA32File << "mov DWORD ebx, [" << structure.notDefined[0] << "]" << endl;
// 	IA32File << "idiv ebx" << endl;
// }

// void Montador::jmp(lineStruct structure){
// 	IA32File << "jmp " << structure.notDefined[0] << endl;
// }

// void Montador::jmpn(lineStruct structure){
// 	IA32File << "cmp eax, 0" << endl;
// 	IA32File << "jl " << structure.notDefined[0] << endl;
// }

// void Montador::jmpp(lineStruct structure){
// 	IA32File << "cmp eax, 0" << endl;
// 	IA32File << "jg " << structure.notDefined[0] << endl;
// }

// void Montador::jmpz(lineStruct structure){
// 	IA32File << "cmp eax, 0" << endl;
// 	IA32File << "je " << structure.notDefined[0] << endl;
// }

// void Montador::copy(lineStruct structure){
// 	IA32File << "mov DWORD ebx, [" << structure.notDefined[0] << "]" << endl;
// 	IA32File << "mov DWORD [" << structure.notDefined[2] << "]" << ", ebx" << endl;
// }

// void Montador::load(lineStruct structure){
// 	IA32File << "mov DWORD eax, [" << structure.notDefined[0] << "]" << endl;
// }

// void Montador::store(lineStruct structure){
// 	IA32File << "mov DWORD [" << structure.notDefined[0] << "], eax" << endl;
// }

// void Montador::input(lineStruct structure){
// 	IA32File << "push eax" << endl;
// 	IA32File << "push " << structure.notDefined[0] << endl;
// 	IA32File << "call LerInteiro" << endl;
// 	IA32File << "add esp, 4" << endl;
// 	IA32File << "pop eax" << endl;
// 	lerInteiro = true;
// }

// void Montador::output(lineStruct structure){
// 	IA32File << "push eax" << endl;
// 	IA32File << "push " << structure.notDefined[0] << endl;
// 	IA32File << "call EscreverInteiro" << endl;
// 	IA32File << "add esp, 4" << endl;
// 	IA32File << "pop eax" << endl;
// 	escreveInteiro = true;
// }

// void Montador::c_input(lineStruct structure){
// 	IA32File << "push eax" << endl;
// 	IA32File << "push " << structure.notDefined[0] << endl;
// 	IA32File << "call LerChar" << endl;
// 	IA32File << "add esp, 4" << endl;
// 	IA32File << "pop eax" << endl;
// }

// void Montador::c_output(lineStruct structure){
// 	IA32File << "push eax" << endl;
// 	IA32File << "push " << structure.notDefined[0] << endl;
// 	IA32File << "call EscreverChar" << endl;
// 	IA32File << "add esp, 4" << endl;
// 	IA32File << "pop eax" << endl;
// }

// void Montador::h_input(lineStruct structure){
// 	IA32File << "push eax" << endl;
// 	IA32File << "push " << structure.notDefined[0] << endl;
// 	IA32File << "call LerHexa" << endl;
// 	IA32File << "add esp, 4" << endl;
// 	IA32File << "pop eax" << endl;
// }

// void Montador::h_output(lineStruct structure){
// 	IA32File << "push eax" << endl;
// 	IA32File << "push " << structure.notDefined[0] << endl;
// 	IA32File << "call EscreverHexa" << endl;
// 	IA32File << "add esp, 4" << endl;
// 	IA32File << "pop eax" << endl;
// }

// void Montador::s_input(lineStruct structure){
// 	IA32File << "push eax" << endl;
// 	IA32File << "push DWORD " << structure.number << endl;
// 	IA32File << "push " << structure.notDefined[0] << endl;
// 	IA32File << "call LerString" << endl;
// 	IA32File << "add esp, 8" << endl;
// 	IA32File << "pop eax" << endl;
// }

// void Montador::s_output(lineStruct structure){
// 	IA32File << "push eax" << endl;
// 	IA32File << "push DWORD " << structure.number << endl;
// 	IA32File << "push " << structure.notDefined[0] << endl;
// 	IA32File << "call EscreverString" << endl;
// 	IA32File << "add esp, 8" << endl;
// 	IA32File << "pop eax" << endl;
// }

// void Montador::stop(lineStruct structure){
// 	IA32File << "mov eax, 1" << endl;
// 	IA32File << "mov ebx, 0" << endl;
// 	IA32File << "int 80h" << endl;
// }

// void Montador::textSintaxe(string line){
// 	lineStruct structure;
// 	structure = lineStructure(line);

// 	cout << line <<"  "<<structure.lineCode << endl;

// 	if(!structure.rot.empty()){
// 		IA32File << structure.rot << " ";
// 	}

// 	if(structure.lineCode.find('S')!=string::npos){
// 		int n = stoi(structure.number)*4;
// 		structure.notDefined[0] = structure.notDefined[0]+"+"+to_string(n);
// 		cout<<structure.notDefined[0]<<endl;
// 		cout<<to_string(n)<<endl;
// 	}

// 	if(!structure.funct.empty()){
// 		if(structure.funct == "add"){
// 			add(structure);
// 			return;
// 		}
// 		else if(structure.funct == "sub"){
// 			sub(structure);
// 		}
// 		else if(structure.funct == "mult"){
// 			mult(structure);
// 		}
// 		else if(structure.funct == "div"){
// 			div(structure);
// 		}
// 		else if(structure.funct == "jmp"){
// 			jmp(structure);
// 		}
// 		else if(structure.funct == "jmpn"){
// 			jmpn(structure);
// 		}
// 		else if(structure.funct == "jmpp"){
// 			jmpp(structure);
// 		}
// 		else if(structure.funct == "jmpz"){
// 			jmpz(structure);
// 		}
// 		else if(structure.funct == "copy"){
// 			copy(structure);
// 		}
// 		else if(structure.funct == "load"){
// 			load(structure);
// 		}
// 		else if(structure.funct == "store"){
// 			store(structure);
// 		}
// 		else if(structure.funct == "input"){
// 			input(structure);
// 		}
// 		else if(structure.funct == "output"){
// 			output(structure);
// 		}
// 		else if(structure.funct == "c_input"){
// 			c_input(structure);
// 		}
// 		else if(structure.funct == "c_output"){
// 			c_output(structure);
// 		}
// 		else if(structure.funct == "h_input"){
// 			h_input(structure);
// 		}
// 		else if(structure.funct == "h_output"){
// 			h_output(structure);
// 		}
// 		else if(structure.funct == "s_input"){
// 			s_input(structure);
// 		}
// 		else if(structure.funct == "s_output"){
// 			s_output(structure);
// 		}
// 		else if(structure.funct == "stop"){
// 			stop(structure);
// 		}
// 	}

// }


void Montador::traduzLinha(string line){
	lineStruct structure = lineStructure(line);

	code = "";
	size = 0;

	cout << structure.lineCode << endl;

	if(structure.funct =="add"){
		if(structure.reg == "eax"){
			// 
		}else if(structure.reg =="esp"){
			if(structure.number == "4"){
				// \x83\xC4\x04
				// address += 3;
			}
			else if(structure.number == "8"){
				// \x83\xC4\x08
				// address += 3;
			}
		}
	}
	else if(structure.funct =="sub"){

	}
	else if(structure.funct =="imul"){
		if(structure.reg == "ebx"){
			// \xF7\xEB
			//address += 2;
		}
	}
	else if(structure.funct =="idiv"){
		if(structure.reg == "ebx"){
			// \xF7\xFB
			//address += 2;
		}
	}
	else if(structure.funct =="jmp"){

	}
	else if(structure.funct =="mov"){

	}
	else if(structure.funct =="cdq"){
		// \x99
		// address += 1;
	}
	else if(structure.funct =="jl"){

	}
	else if(structure.funct =="cmp"){
		if(structure.reg == "eax"){
			// \x83\xF8\x00
			// address += 3;
		}
	}
	else if(structure.funct =="jg"){

	}
	else if(structure.funct =="je"){

	}
	else if(structure.funct =="push"){
		if(structure.reg == "eax"){
			// \x50
			// address += 1;
		}else if(structure.reg =="ebx"){
			// \x53
			// address += 1;
		}else if(structure.reg =="ecx"){
			// \x51
			// address += 1;
		}else if(structure.reg =="edx"){
			// \x52
			// address += 1;
		}else if(structure.reg =="ebp"){
			// \x55
			// address += 1;
		}else if(structure.reg =="esp"){
			// \x54
			// address += 1;
		}else if(structure.reg =="edi"){
			// \x57
			// address += 1;
		}else if(structure.reg =="esi"){
			// \x56
			// address += 1;
		}

	}
	else if(structure.funct =="call"){

	}
	else if(structure.funct =="pop"){
		if(structure.reg == "eax"){
			char code = '\x58';
			address += 1;
		}
	}
}


void Montador::printFuncoes(){
	string line;
	ifstream funcoes("funcoes.asm");
	while(getline(funcoes,line)){
		IA32File << line << endl;
	}

}

void Montador::dataSintaxe(string line){
	lineStruct structure;
	structure = lineStructure(line);

	cout<<line << "    " << structure.lineCode << endl;

	// if(!structure.rot.empty()){
	// 	string rot = structure.rot;
	// 	rot.pop_back();
	// 	IA32File << rot << " ";
	// }

	// if(!structure.directive.empty()){
	// 	if(structure.directive == "const"){
	// 		if(!structure.number.empty()){
	// 			IA32File << "dd " << structure.number << endl; 
	// 		}
	// 		else if(!structure.character.empty()){
	// 			IA32File << "dd " << structure.character << endl;
	// 		}
	// 	}
	// 	else if(structure.directive == "space"){
	// 		int n = 1;
	// 		if(!structure.number.empty()){
	// 			n = stoi(structure.number);
	// 		}
	// 		IA32File << "dd"; 
	// 		for(int i=0; i<n; ++i){
	// 			IA32File << " 0";
	// 			if(i < n-1){
	// 				IA32File << ",";
	// 			}
	// 		}
	// 		IA32File << endl;
	// 	}

	// }
}


void Montador::transformIA32(string filename){
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
				IA32File << "global _start" << endl;
				IA32File << "_start:" << endl;
				section = 1;
				continue;
			}
			else if(lowerCase(line) == "section data"){
				//printFuncoes();
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
}

void Montador::run(string filename){
	transformIA32(filename);

}
