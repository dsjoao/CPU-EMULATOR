#include<bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <cassert>
#include "cpu.cpp"
using namespace std;

const char* NOME_B[9] = {"mdr","pc","mbr","mbru","sp","lv","cpp","tos","opc"};
const char* NOME_C[9] = {"mar","mdr","pc","sp","lv","cpp","tos","opc","h"};

void imprime_barramentos(ostream &out, unsigned long b, unsigned long c){
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
	out << "mar = " << r.mar << '\n';
	out << "mdr = " << r.mdr << '\n';
	out << "pc  = " << r.pc  << '\n';
	out << "mbr = " << r.mbr << '\n';
	out << "sp  = " << r.sp  << '\n';
	out << "lv  = " << r.lv  << '\n';
	out << "cpp = " << r.cpp << '\n';
	out << "tos = " << r.tos << '\n';
	out << "opc = " << r.opc << '\n';
	out << "h   = " << r.h   << '\n';
}

void imprime_dados(ostream &log, fstream &dados){
	if(!log || !dados)
		return;
	string linha;
	while(getline(dados, linha)){
		log << linha << '\n';
	}
	dados.clear();  // limpa eofbit e failbit
	dados.seekg(0); // volta para o inicio do arquivo
}


int main() {
	int     ciclo = 1;
	bitset<32> a=0, b=0;
    string  ir; // registrador de instrução
    Reg     r;
    r.mar = 0b100;
    r.mdr = 0;
    r.pc  = 0;
    r.mbr = 0;
    r.sp  = 0b100;
    r.lv  = 0;
    r.cpp = 0;
    r.tos = 0;
    r.opc = 0;
    r.h   = 0;

    // --- abrindo os arquivos ---
    ifstream entrada("../text/microinstrucoes.txt");
    ofstream  log	("log.txt");  // ofstream cria automaticamente arquivos de escrita
    fstream  dados	("dados.txt");
    assert(entrada && log && dados); // assert = "garanta que", se a condição não for verdade o programa para

// 				------------ nomes ------------
    log << "Joao Pedro Duarte Sa:   20250018038" << '\n';
    log << "Thiago Sales Rodrigues: 20250103602" << '\n';
    log << "Luca Borges:            20250103587" << '\n';

// 		------------------ conteúdo prévio --------------------
    log << "------------------------------------------" << '\n';
    log << "-------- Estado inicial da memória -------" << '\n';

    imprime_dados(log, dados);

    log << "------------------------------------------" << '\n';
    log << "---- Estado inicial dos registradores ----" << '\n';

    imprime_registradores(log, r);

//  ------------------ início do programa -------------------
    log << "------------------------------------------" << '\n';
    log << "----------------- inicio -----------------" << '\n';

    while(getline(entrada,ir)){
        if(!ir.empty() && ir.back() == '\r') ir.pop_back();
        assert(ir.size() == 23);

        vector<bitset<32>> comandos = entrada_to_comandos(ir);

        log << "Ciclo: " << ciclo << '\n';
        log << "IR = "   << ir   << '\n' << '\n';

        imprime_barramentos(log, comandos[3].to_ulong(), comandos[1].to_ulong());

        log << "------------------------------------------" << '\n';
        log << "-> Registradores antes da instrução:"       << '\n';

        imprime_registradores(log, r);

        log << "---------------------" << '\n';

        a = r.h;
        b = barramento_b(r, comandos[3]);

        SaidaUla s = carrega_ula(comandos[0], a, b);

        barramento_c(r, comandos[1], s.saidad);

        mem(r, dados, comandos[2]);

        log << "-> Registradores depois da instrução:"       << '\n';

        imprime_registradores(log, r);

        log << "------------------------------------------" << '\n';


        ciclo++;
    }
// 			------------ fim do programa ------------------


    entrada.close();
    log.close();
	return 0;
}
