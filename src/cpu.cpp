#include <bits/stdc++.h>
#include <string>
#include <vector>
#include "ula.cpp"
#include "cont_b.cpp"
#include "cont_c.cpp"
int cont = 1;
using namespace std;
// --- funções de utilidade ---
vector<string> divide_Strings(const string &ir){
    vector<string> str;
    str.push_back(ir.substr(0 ,8));
    str.push_back(ir.substr(8 ,9));
    str.push_back(ir.substr(17,4));
    return str;
}

/*
 * @brief string -> valor de entrada do barramento b
 * @param ir string de bits de entrada
 * @return indice do registrador que será ativo
 */
int decode_barr_b(const string &ir){
    vector<int> imput;
    return stoi(ir,nullptr, 2);
}

/*
 * @brief string -> registradores que serão ativos no barr c
 * @param ir string de bits de entrada
 * @return vector<bool> de registradores que receberão os dados da ula
 */
vector<bool> decode_barr_c(const string &ir){
    vector<bool> imput;
    for(size_t i = 0; i < 9; i++)
        imput.push_back(ir[i] - '0');
    return imput;
}
// -----------------------------------------------------------------------
// --- funções que carregam dados ---
/*SAIDA DA ULA
 * Ela recebe uma string de tamanho == 8
 * A partir dela, tranforma em um vetor de bool, os colocando como
 * entrada da ula e retornando o resultado;
 */
SaidaUla carrega_ula(const string &ir, vector<bool> a, vector<bool> b){
    vector<bool> imput;
    for(size_t i = 0; i < 8; i++)
        imput.push_back(ir[i] - '0');
    return ula(imput[0], imput[1], imput[2], imput[3], imput[4], imput[5],imput[6], imput[7], a, b);
}

// -----------------------------------------------------------------------
// --- registradores e suas operações ---
string ir;
vector<bool> a, b;

// --- Calculo da saida da ula ---
SaidaUla s = carrega_ula(ir, a, b);
// -----------------------------------------------------------------------
