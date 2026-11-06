#include <bits/stdc++.h>
#include <cstdint>
#include <string>
#include <vector>
#include "ula.cpp"
#include "registradores.cpp"
using namespace std;

// --- funções de utilidade ---
int traducao(const string &str){
	return stoi(str, nullptr,2);
}

/*
 * @brief divide uma string geral entre seus dados relevantes
 * @param ir string de bits de entrada (21 bits)
 * @return vector<int32_t> com cada um dos dados da entrada padrão:
 * saida[0] = O que a ula vai fazer
 * saida[1] = quais registradores do barr c serão sobre escritos
 * saida[2] = qual registrador vai fornecer os dados para o barr b
 */
vector<int32_t> entrada_to_comandos(const string &ir){
    vector<int32_t> saida(3);
    saida[0] = traducao((ir.substr(0 ,8)));
    saida[1] = traducao((ir.substr(8 ,9)));
    saida[2] = traducao((ir.substr(17,4)));
    return saida;
}
// -----------------------------------------------------------------------
/*
 * @brief carrega os dados na ULA e devolve o resultado
 * @param int32_t dados do que a ula vai fazer
 * @return SaidaUla {int32_t saida; int32_t saida deslocada; bool vaiUm; bool n; bool z;}
 */
SaidaUla carrega_ula(int32_t in, int32_t a, int32_t b){
    return ula((in >> 7)&1,(in >> 6)&1,(in >> 5)&1,(in >> 4)&1,(in >> 3)&1,(in >> 2)&1,(in >> 1)&1,in&1, a, b);
}

// -----------------------------------------------------------------------
/*
 * @brief recebe a entrada e os registradores que seram escritos
 * @param int32_t registrador_ativo -> quais registradores terão seus dados sobre escritos
 * @param int32_t entrada -> a saida da ULA (o que vc quer escrever)
 */
void barramento_c(Reg &r, int32_t registradores, int32_t entrada){
	for(int i=0; i < 9; i++){
		if((registradores >> i) & 1){
			escreve_barr_c(r, i, entrada);
		}
	}
}

/*
 * @brief int32_t -> int32_t
 * @param int32_t -> o registrador que sera ativado para pegar dados no barr b
 * @return valor da variável B que entra na ULA
 */
int32_t barramento_b(Reg r, int32_t registrador){
	int32_t entrada = le_barr_b(r, registrador);
	return  entrada;
}
