
#include<bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <cassert>
#include "instrucoes.cpp"
using namespace std;

int main() {
	int     ciclo = 1;
    string  ir; // registrador de instrução
    Reg     r;
    r.mar = 0b110;
    r.mdr = 0;
    r.pc  = 0;
    r.mbr = 0;
    r.sp  = 0b110;
    r.lv  = 0b11;
    r.cpp = 0;
    r.tos = 0b1000;
    r.opc = 0;
    r.h   = 0;

    Instrucao ILOAD;
    ILOAD.nome = "ILOAD";
    ILOAD.tem_argumento = true;
    ILOAD.microinstrucoes = {
        "00110100100000000000101",
        "00111001100000000001111",
        "00111000000000001011111",
        "00110101000001001100100",
        "00110100001000000000000"
    };
    ILOAD.repetida = 1;

    Instrucao DUP;
    DUP.nome = "DUP";
    DUP.tem_argumento = false;
    DUP.microinstrucoes = {
        "00110101000001001000100",
        "00110100000000010100111"
    };

    Instrucao BIPUSH;
    BIPUSH.nome = "BIPUSH";
    BIPUSH.tem_argumento = true;
    BIPUSH.microinstrucoes = {
        "00110101000001001000100",
        "xxxxxxxx000000000110000",
        "00111000001000010101111"
    };

    // --- abrindo os arquivos ---
    ifstream entrada("instrucoes.txt");
    ofstream  log	("log.txt");  // ofstream cria automaticamente arquivos de escrita
    string NOME_DADOS = "dados.txt";
    fstream  dados	(NOME_DADOS);
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
        if(ir.find_first_not_of(" \t") == string::npos) continue;

        istringstream in(ir);
        string nome, arg, sobra;
        in >> nome >> arg >> sobra;
        for(char &ch : nome) ch = toupper((unsigned char)ch);

        const Instrucao *atual = nullptr;
        if(nome == ILOAD.nome)       atual = &ILOAD;
        else if(nome == DUP.nome)    atual = &DUP;
        else if(nome == BIPUSH.nome) atual = &BIPUSH;

        string erro;
        unsigned long argumento = 0;
        if(atual == nullptr)
            erro = "instrucao desconhecida";
        else if(!sobra.empty())
            erro = "argumentos demais";
        else
            le_argumento(*atual, arg, argumento, erro);

        if(!erro.empty()){
            log << "==========================================" << '\n';
            log << "> Erro na linha \"" << ir << "\": " << erro << '\n';
            log << "==========================================" << '\n';
            continue;
        }

        executa_instrucao(*atual, argumento, ir, r, dados, NOME_DADOS, log, ciclo);
    }
// 			------------ fim do programa ------------------
    log << "Ciclo: " << ciclo << '\n';
    log << "Fim das instrucoes, EOP." << '\n';
    log << "------------------------------------------" << '\n';

    entrada.close();
    dados.close();
    log.close();
	return 0;
}
