#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <vector>
#include "ula.cpp"
#include "registradores.cpp"
using namespace std;

// --- funções de utilidade ---
bitset<32> traducao(const string &str){
	return bitset<32>(str);
}
/*
 * @brief Função que, dado um arquivo de memória, le cada linha e transforma num vector
 * útil para outras funções de memória
 * @param fstream &dados   -> o arquivo que sera lido
 * @return vector<bitset<32>> -> vetor com cada bitset<32> sendo uma linha
 */
vector<bitset<32>> le_dados(fstream &dados){
	vector<bitset<32>> linhas(10);
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
 * @param const vector<bitset<32>> -> vetor com os dados que serão escritos
 */
void escreve_dados(fstream &dados, const string &nome, const vector<bitset<32>> linhas){
	if(!dados.is_open()){
		cout << "ERRO AO TENTAR ESCREVER OS DADOS DA MEMORIA\n";
		return;
	}
	if(dados.is_open()) dados.close();
	dados.clear();
	dados.open(nome, ios::out | ios::trunc);
	for(bitset<32> valor : linhas)
		dados << valor << '\n';
}

/*
 * @brief divide uma string geral entre seus dados relevantes
 * @param ir string de bits de entrada (21 bits)
 * @return vector<bitset<32>> com cada um dos dados da entrada padrão:
 * saida[0] = O que a ula vai fazer
 * saida[1] = quais registradores do barr c serão sobre escritos
 * saida[2] = qual registrador vai fornecer os dados para o barr b
 */
vector<bitset<32>> entrada_to_comandos(const string &ir){
    vector<bitset<32>> saida(4);
    saida[0] = traducao(ir.substr(0 ,8));
    saida[1] = traducao(ir.substr(8 ,9));
    saida[2] = traducao(ir.substr(17,2));
    saida[3] = traducao(ir.substr(19,4));
    return saida;
}
// -----------------------------------------------------------------------
/*
 * @brief carrega os dados na ULA e devolve o resultado
 * @param bitset<32> dados do que a ula vai fazer
 * @return SaidaUla {bitset<32> saida; bitset<32> saida deslocada; bool vaiUm; bool n; bool z;}
 */
SaidaUla carrega_ula(bitset<32> in, bitset<32> a, bitset<32> b){
    return ula(in.test(7),in.test(6),in.test(5),in.test(4),in.test(3),in.test(2),in.test(1),in.test(0), a, b);
}

// -----------------------------------------------------------------------
/*
 * @brief Faz a função do barr C: recebe a entrada e os registradores que serão escritos
 * @param bitset<32> registrador_ativo -> quais registradores terão seus dados sobre escritos
 * @param bitset<32> entrada -> a saida da ULA (o que vc quer escrever)
 */
void barramento_c(Reg &r, bitset<32> registradores, bitset<32> entrada){
	for(int i=0; i < 9; i++){
		if(registradores.test(i)){
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
void mem(Reg &r, fstream &dados, bitset<32> entrada){
	vector<bitset<32>>linhas = le_dados(dados);
	unsigned long mar = r.mar.to_ulong();
	if(mar>8){
		cout << "MAR MT GRANDE, ALGO TA ERRADO NOS CALCULOS DO R.MAR";
		return;
	}
	if(entrada.test(0))
		r.mdr = linhas[mar];
	else if(entrada.test(1))
		linhas[mar] = r.mdr;
	escreve_dados(dados, "dados.txt", linhas);
}

// -----------------------------------------------------------------------
/*
 * @brief Faz a função do barr b: bitset<32> -> bitset<32>
 * @param Reg r      -> o "vetor" de registradores para fazer a leitura
 * @param bitset<32> -> o registrador que sera ativado para pegar dados no barr b
 * @return valor da variável B que entra na ULA
 */
bitset<32> barramento_b(Reg r, bitset<32> registrador){
	unsigned long reg = registrador.to_ulong();
	bitset<32> entrada = le_barr_b(r, reg);
	return  entrada;
}
