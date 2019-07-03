#include "montador_IA32hpp"

using namespace std;


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

	if(structure.funct ="add"){
		if(structure.reg = "eax"){
			// 
		}else if(structure.reg ="esp"){
			if(structure.number = '4'){
				// \x83\xC4\x04
				// address += 3;
			}
			else if(structure.number = '8'){
				// \x83\xC4\x08
				// address += 3;
			}
		}
	}
	else if(structure.funct ="sub"){

	}
	else if(structure.funct ="imul"){
		if(structure.reg = "ebx"){
			// \xF7\xEB
			//address += 2;
		}
	}
	else if(structure.funct ="idiv"){
		if(structure.reg = "ebx"){
			// \xF7\xFB
			//address += 2;
		}
	}
	else if(structure.funct ="jmp"){

	}
	else if(structure.funct ="mov"){

	}
	else if(structure.funct ="cdq"){
		// \x99
		// address += 1;
	}
	else if(structure.funct ="jl"){

	}
	else if(structure.funct ="cmp"){
		if(structure.reg = "eax"){
			// \x83\xF8\x00
			// address += 3;
		}
	}
	else if(structure.funct ="jg"){

	}
	else if(structure.funct ="je"){

	}
	else if(structure.funct ="push"){
		if(structure.reg = "eax"){
			// \x50
			// address += 1;
		}else if(structure.reg ="ebx"){
			// \x53
			// address += 1;
		}else if(structure.reg ="ecx"){
			// \x51
			// address += 1;
		}else if(structure.reg ="edx"){
			// \x52
			// address += 1;
		}else if(structure.reg ="ebp"){
			// \x55
			// address += 1;
		}else if(structure.reg ="esp"){
			// \x54
			// address += 1;
		}else if(structure.reg ="edi"){
			// \x57
			// address += 1;
		}else if(structure.reg ="esi"){
			// \x56
			// address += 1;
		}

	}
	else if(structure.funct ="call"){

	}
	else if(structure.funct ="pop"){
		if(structure.reg = "eax"){
			// \x58
			// address += 1;
		}else if(structure.reg ="ebx"){
			// \x5b
			// address += 1;
		}else if(structure.reg ="ecx"){
			// \x59
			// address += 1;
		}else if(structure.reg ="edx"){
			// \x5a
			// address += 1;
		}else if(structure.reg ="ebp"){
			// \x5d
			// address += 1;
		}else if(structure.reg ="esp"){
			// \x5c
			// address += 1;
		}else if(structure.reg ="edi"){
			// \x5f
			// address += 1;
		}else if(structure.reg ="esi"){
			// \x5e
			// address += 1;
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
				printFuncoes();
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
