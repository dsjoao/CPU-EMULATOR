#include <bits/stdc++.h>
#include <cstdint>
#include <string>
#include <vector>
#include "ula.cpp"
#include "cont_b.cpp"
#include "cont_c.cpp"
#include "registradores.cpp"

int cont = 1;
using namespace std;
// --- funções de utilidade ---
/*
 * @brief divide uma string geral entre seus dados relevantes, ainda em string
 * @param ir string de bits de entrada (21 bits)
 * @return vector<string> com cada um dos dados da entrada padrão:
 * str[0] = O que a ula vai fazer
 * str[1] = quais registradores do barr c serão sobre escritos
 * str[2] = qual registrador vai fornecer os dados para o barr b
 */
vector<string> divide_Strings(const string &ir){
    vector<string> str;
    str.push_back(ir.substr(0 ,8));
    str.push_back(ir.substr(8 ,9));
    str.push_back(ir.substr(17,4));
    return str;
}

/*
 * @brief string -> valor de entrada do barramento b
 * @param ir string de bits de entrada (4 bits)
 * @return indice do registrador que será ativo
 */
int decode_barr_b(const string &ir){
    vector<int> imput;
    return stoi(ir,nullptr, 2);
}

/*
 * @brief string -> registradores que serão ativos no barr c
 * @param ir string de bits de entrada (9 bits)
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
// --- Operações com os barramentos ---
/*
 * @brief recebe a entrada e os registradores que seram escritos
 * @param vector<bool> registrador_ativo -> quais registradores terão seus dados sobre escritos
 * @param int32_t entrada -> a saida da ULA (o que vc quer escrever)
 */
void barramento_c(vector<bool>regist_ativo, int32_t entrada){
	for(int i=0; i < 9; i++){
		if(regist_ativo[i]){
			carrega_regist_barr_c(8-i, entrada); // 8-i para acessar na ordem correta
		}
	}
}

/*
 * @brief String -> int32_t
 * @param ir string de bits do barramento b (4 bits)
 * @return valor da variável B que entra na ULA
 */
int32_t barramento_b(const string &ir){
	int registrador = decode_barr_b(ir);
	int32_t entrada = carrega_ula_barr_b(registrador);
	return entrada;
}
