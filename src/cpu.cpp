#include <bits/stdc++.h>
#include <cstdint>
#include <fstream>
#include <iterator>
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
 * @brief Função que, dado um arquivo de memória, le cada linha e transforma num vector
 * útil para outras funções de memória
 * @param fstream &dados   -> o arquivo que sera lido
 * @return vector<int32_t> -> vetor com cada int32_t sendo uma linha
 */
vector<int32_t> le_dados(fstream &dados){
	vector<int32_t> linhas(10);
	string temp;
	int i=0;
	if(!dados.is_open()){
		cout << "ERRO AO TENTAR LER OS DADOS DA MEMORIA\n";
		return linhas;
	}
	while(i < 10 && getline(dados, temp)){
		if(temp.empty()) continue;
		linhas[i] = traducao(temp);
		i++;
	}
	dados.clear();  // limpa eofbit e failbit
	dados.seekg(0); // volta para o inicio do arquivo
	return linhas;
}

/*
 * @brief Reescreve um arquivo a partir de um vetor de dados
 * @param fstream &dados -> o arquivo que sera escrito
 * @param const string &nome -> nome do arquivo, ex "dados.txt"
 * @param const vector<int32_t> -> vetor com os dados que serão escritos
 */
void escreve_dados(fstream &dados, const string &nome, const vector<int32_t> linhas){
	if(!dados.is_open()){
		cout << "ERRO AO TENTAR ESCREVER OS DADOS DA MEMORIA\n";
		return;
	}
	if(dados.is_open()) dados.close();
	dados.clear();
	dados.open(nome, ios::out | ios::trunc);
	for(int32_t valor : linhas)
		dados << valor << '\n';
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
    vector<int32_t> saida(4);
    saida[0] = traducao(ir.substr(0 ,8));
    saida[1] = traducao(ir.substr(8 ,9));
    saida[2] = traducao(ir.substr(17,2));
    saida[3] = traducao(ir.substr(19,4));
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
 * @brief Faz a função do barr C: recebe a entrada e os registradores que serão escritos
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
// -----------------------------------------------------------------------
/*
 * @brief Executa as operações de leitura/escrita na memória na posição do reg MAR
 * @param Reg &r         -> o "vetor" de registradores em que os dados serão armazenados/lidos
 * @param fstream &dados -> o arquivo que serve como memória de dados do sitema
 */
void mem(Reg &r, fstream &dados, int32_t entrada){
	vector<int32_t>linhas = le_dados(dados);
	unsigned long mar = stoul(to_string(r.mar), nullptr, 2); // tranforma r.mar num numero normal
	if(mar>8){
		cout << "MAR MT GRANDE, ALGO TA ERRADO NOS CALCULOS DO R.MAR";
		return;
	}
	if(entrada & 1)
		r.mdr = linhas[mar];
	else if((entrada >> 1) & 1)
		linhas[mar] = r.mdr;
	escreve_dados(dados, "dados.txt", linhas);
}




// -----------------------------------------------------------------------
/*
 * @brief Faz a função do barr b: int32_t -> int32_t
 * @param Reg r   -> o "vetor" de registradores para fazer a leitura
 * @param int32_t -> o registrador que sera ativado para pegar dados no barr b
 * @return valor da variável B que entra na ULA
 */
int32_t barramento_b(Reg r, int32_t registrador){
	int32_t entrada = le_barr_b(r, registrador);
	return  entrada;
}
