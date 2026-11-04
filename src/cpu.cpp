#include <bits/stdc++.h>
#include <string>
#include <vector>
#include "ula.cpp"
#include "cont_b.cpp"
#include "cont_c.cpp"
int pc = 1;

std::vector<std::string> divide_Strings(const std::string &ir){
    std::vector<std::string> str;
    str[0] = ir.substr(0, 8);
    str[1] = ir.substr(8,9);
    str[2] = ir.substr(16, 4);
    return str;
}

SaidaUla carrega_ula(const std::string &ir, bool a, bool b){
    std::vector<int> imput;
    for(size_t i = 0; i < 8; i++)
        imput.push_back(ir[i] - '0');
    return ula(imput[0], imput[1], imput[2], imput[3], imput[4], imput[5],imput[6], imput[7], a, b);
}

/*BARRAMENTO B
 * Ele recebe como entrada uma string de tamanho == 4
 * ela representa as 8 possibilidades de registradores que podem aparecer,
 * então convertemos essa string para um num real e passamos ele para a função
 * controle_barr_b, retornando o resultado
 */
void carrega_barr_b(const std::string &ir){
    std::vector<int> imput;
    controle_barr_b(std::stoi(ir,nullptr, 2));
}

/* BARRAMENTO C
 * Ele recebe uma string de tamanho == 9
 * a função converte essa string para um vetor de bool e passa cada um
 * singularmente como entrada para dizer quais registradores serão ativados
 */
void carrega_barr_c(const std::string &ir){
    std::vector<int> imput;
    for(size_t i = 0; i < 9; i++)
        imput.push_back(ir[i] - '0');
    return controle_barr_c(imput[0], imput[1], imput[2], imput[3], imput[4], imput[5],imput[6], imput[7], imput[8]);
}
