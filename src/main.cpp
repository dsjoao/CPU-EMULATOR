#include<bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "ula.cpp"

bool a=1, b=1;

SaidaUla carrega_ula(const std::string &ir, bool a, bool b){
    std::vector<int> imput;
    for(size_t i = 0; i < 6; i++)
        imput.push_back(ir[i] - '0');
    return ula(imput[0], imput[1], imput[2], imput[3], imput[4], imput[5], a, b);
}


int main() {
    std::string ir; // registrador de instrução
    int pc = 1;

    // --- abrindo os arquivos ---
    std::ifstream entrada;
    entrada.open("../text/programa_etapa1.txt");
    if(!entrada) // erro, arquivo não existe
        return 1;
    std::fstream log;
    log.open("log.txt", std::ios::out);
    if(!log) // erro, arquivo não existe
        return 1;
    // ---------------------------

    log << "------------------------------------------" << '\n';
    log << "----------------- inicio -----------------" << '\n';
    log << "a = " << a << '\n';
    log << "b = " << b << '\n';

    while(getline(entrada,ir)){
        if(!ir.empty() && ir.back() == '\r') ir.pop_back();
        if(ir.size() != 6) break;
        log << "------------------------------------------" << '\n';
        log << "Ciclo: " << pc << '\n' << '\n';
        log << "PC = "   << pc << '\n';
        log << "IR = "   << ir << '\n';
        log << "a  = "   << a  << '\n';
        log << "b  = "   << b  << '\n';
        SaidaUla s = carrega_ula(ir, a, b);
        log << "s  = "   << s.saida << '\n';
        log << "co = "   << s.vaiUm << '\n';
        pc++;
    }

    entrada.close();
	return 0;
}
