#include<bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "cpu.cpp"
using namespace std;

const char* NOME_B[9] = {"mdr","pc","mbr","mbru","sp","lv","cpp","tos","opc"};
const char* NOME_C[9] = {"mar","mdr","pc","sp","lv","cpp","tos","opc","h"};

void imprime_barramentos(ostream &out, int b, int c){
	out << "barramento B = ";
	if(b <= 8) out << NOME_B[b];
	else       out << "nenhum";      // códigos 9 a 15
	out << '\n';

	out << "Barramento C = ";
	bool primeiro = true;
	for(int i = 8; i >= 0; i--){
		if((c >> i) & 1){
			if(!primeiro) out << ", ";
			out << NOME_C[i];
			primeiro = false;
		}
	}
	out << '\n';
}

void imprime_registradores(ostream &out, const Reg &r){
	out << "mar = " << bitset<32>(r.mar) << '\n';
	out << "mdr = " << bitset<32>(r.mdr) << '\n';
	out << "pc  = " << bitset<32>(r.pc)  << '\n';
	out << "mbr = " << bitset<8>(r.mbr)  << '\n';
	out << "sp  = " << bitset<32>(r.sp)  << '\n';
	out << "lv  = " << bitset<32>(r.lv)  << '\n';
	out << "cpp = " << bitset<32>(r.cpp) << '\n';
	out << "tos = " << bitset<32>(r.tos) << '\n';
	out << "opc = " << bitset<32>(r.opc) << '\n';
	out << "h   = " << bitset<32>(r.h)   << '\n';
}


int main() {
	int     ciclo = 1;
	int32_t a=0, b=0;
    string  ir; // registrador de instrução
    Reg     r;
    r.mar = 0b00000000000000000000000000000000;
    r.mdr = 0b00000000000000000000000000000000;
    r.pc  = 0b00000000000000000000000000000000;
    r.mbr = 0b10000001;
    r.sp  = 0b00000000000000000000000000000000;
    r.lv  = 0b00000000000000000000000000000000;
    r.cpp = 0b00000000000000000000000000000000;
    r.tos = 0b00000000000000000000000000000010;
    r.opc = 0b00000000000000000000000000000000;
    r.h   = 0b00000000000000000000000000000001;


    // --- abrindo os arquivos ---
    ifstream entrada;
    entrada.open("../text/programa_etapa2_tarefa2.txt");
    if(!entrada) // erro, arquivo não existe
        return 1;
    fstream log;
    log.open("log.txt", ios::out);
    if(!log) // erro, arquivo não existe
        return 1;
    log << "Joao Pedro Duarte Sa   20250018038" << '\n';
    log << "Thiago Sales Rodrigues 20250103602" << '\n';
    log << "Luca Borges            20250103587" << '\n';
    log << "------------------------------------------" << '\n';
    log << "---- Estado inicial dos registradores ----" << '\n';
    imprime_registradores(log, r);

    log << "------------------------------------------" << '\n';
    log << "----------------- inicio -----------------" << '\n';
    while(getline(entrada,ir)){
        if(!ir.empty() && ir.back() == '\r') ir.pop_back();
        if(ir.size() != 21) break;
        vector<int32_t> comandos = entrada_to_comandos(ir);

        log << "Ciclo: " << ciclo << '\n';
        log << "IR = "   << ir   << '\n' << '\n';
        imprime_barramentos(log, comandos[2], comandos[1]);
        log << "------------------------------------------" << '\n';
        log << "-> Registradores antes da instrução:"       << '\n';
        imprime_registradores(log, r);
        log << "---------------------" << '\n';

        a = r.h;
        b = barramento_b(r, comandos[2]);
        SaidaUla s = carrega_ula(comandos[0], a, b);
        barramento_c(r, comandos[1], s.saidad);

        log << "-> Registradores depois da instrução:"       << '\n';
        imprime_registradores(log, r);
        log << "------------------------------------------" << '\n';
        ciclo++;
    }

    entrada.close();
    log.close();
	return 0;
}
