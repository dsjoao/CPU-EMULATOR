#include <bits/stdc++.h>
#include <cstdint>
#include <string>
#include <vector>
#include "ula.cpp"
#include "cont_b.cpp"
#include "cont_c.cpp"
int cont = 1;

std::vector<std::string> divide_Strings(const std::string &ir){
    std::vector<std::string> str;
    str.push_back(ir.substr(0 ,8));
    str.push_back(ir.substr(8 ,9));
    str.push_back(ir.substr(17,4));
    return str;
}
/*SAIDA DA ULA
 * Ela recebe uma string de tamanho == 8
 * A partir dela, tranforma em um vetor de bool, os colocando como
 * entrada da ula e retornando o resultado;
 */
SaidaUla carrega_ula(const std::string &ir, std::vector<bool> a, std::vector<bool> b){
    std::vector<bool> imput;
    for(size_t i = 0; i < 8; i++)
        imput.push_back(ir[i] - '0');
    return ula(imput[0], imput[1], imput[2], imput[3], imput[4], imput[5],imput[6], imput[7], a, b);
}

/*
 * @brief string -> valor de entrada do barramento b
 * @param ir string de bits de entrada
 * @return indice do registrador que será ativo
 */
int decode_barr_b(const std::string &ir){
    std::vector<int> imput;
    return std::stoi(ir,nullptr, 2);
}

/*
 * @brief string -> registradores que serão ativos no barr c
 * @param ir string de bits de entrada
 * @return vector<bool> de registradores que receberão os dados da ula
 */
std::vector<int> carrega_barr_c(const std::string &ir){
    std::vector<int> imput;
    for(size_t i = 0; i < 9; i++)
        imput.push_back(ir[i] - '0');
    return imput;
}
// ------- registradores e suas operações -------
std::vector<int32_t> h, opc, tos, cpp, lv, sp, pc, mdr, mar;
