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
	vector<bitset<32>> linhas(16);
	string temp;
	int i=0;
	if(!dados.is_open()){
		cout << "ERRO AO TENTAR LER OS DADOS DA MEMORIA\n";
		return linhas;
	}
	while(i < 16 && getline(dados, temp)){
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
void escreve_dados(fstream &dados, const string &nome, const vector<bitset<32>> &linhas){
	dados.close();
	dados.clear();
	dados.open(nome, ios::out | ios::trunc);
	for (const auto &valor : linhas) dados << valor << '\n';
	dados.close();
	dados.open(nome, ios::in | ios::out);   // reabre e começa na posição 0
}
/*
 * @brief divide uma string geral entre seus dados relevantes
 * @param ir string de bits de entrada (21 bits)
 * @return vector<bitset<32>> com cada um dos dados da entrada padrão:
 * saida[0] = O que a ula vai fazer
 * saida[1] = quais registradores do barr c serão sobre escritos
 * saida[2] = que operação vai ser feita na memória
 * saida[3] = qual registrador vai fornecer os dados para o barr b
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
 * @param bitset<32> entrada -> qual bit de memoria esta ativo (3° instrução)
 */
bool mem(Reg &r, fstream &dados, const string &nome, bitset<32> entrada){
	if(entrada.none()) return true;
	unsigned long mar = r.mar.to_ulong();
	if(mar>15) return false;
	vector<bitset<32>>linhas = le_dados(dados);
	if(entrada.test(0)){
		r.mdr = linhas[mar];
		return true;
	}
	linhas[mar] = r.mdr;
	escreve_dados(dados, nome, linhas);
	return true;
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

const char* NOME_B[9] = {"mdr","pc","mbr","mbru","sp","lv","cpp","tos","opc"};
const char* NOME_C[9] = {"mar","mdr","pc","sp","lv","cpp","tos","opc","h"};

void imprime_barramentos(ostream &out, unsigned long b, unsigned long c){
	out << "Barramento B = ";
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
	if(primeiro) out << "nenhum";
	out << '\n';
}

void imprime_registradores(ostream &out, const Reg &r){
	out << "mar = " << r.mar << '\n';
	out << "mdr = " << r.mdr << '\n';
	out << "pc = "  << r.pc  << '\n';
	out << "mbr = " << r.mbr << '\n';
	out << "sp = "  << r.sp  << '\n';
	out << "lv = "  << r.lv  << '\n';
	out << "cpp = " << r.cpp << '\n';
	out << "tos = " << r.tos << '\n';
	out << "opc = " << r.opc << '\n';
	out << "h = "   << r.h   << '\n';
}

void imprime_dados(ostream &log, fstream &dados){
	if(!log || !dados.is_open())
		return;
	dados.clear();
	dados.seekg(0);
	string linha;
	while(getline(dados, linha)){
		log << linha << '\n';
	}
	dados.clear();  // limpa eofbit e failbit
	dados.seekg(0); // volta para o inicio do arquivo
}


bool executa_microinstrucao(Reg &r, fstream &dados, const string &nome, const string &ir, ostream &log, int &ciclo){
	log << "Ciclo: " << ciclo << '\n';
	ciclo++;

	if(ir.size() != 23 || ir.find_first_not_of("01") != string::npos){
		log << "> Erro, microinstrucao invalida: " << ir << '\n';
		log << "------------------------------------------" << '\n';
		return false;
	}

	log << "IR = " << ir.substr(0,8) << ' ' << ir.substr(8,9) << ' '
	    << ir.substr(17,2) << ' ' << ir.substr(19,4) << '\n' << '\n';

	vector<bitset<32>> comandos = entrada_to_comandos(ir);
	bool fetch = comandos[2].test(0) && comandos[2].test(1);

	if(!fetch && comandos[0].test(7) && comandos[0].test(6)){
		log << "> Erro, sinais de controle invalidos (SLL8 e SRA1 ativos)." << '\n';
		log << "------------------------------------------" << '\n';
		return false;
	}

	if(fetch){
		imprime_barramentos(log, 15, 0);
		log << "Fetch: MBR = " << ir.substr(0,8) << ", H = MBR (sem passar pela ULA)" << '\n';
	}
	else
		imprime_barramentos(log, comandos[3].to_ulong(), comandos[1].to_ulong());

	log << "------------------------------------------" << '\n';
	log << "-> Registradores antes da microinstrução:"       << '\n';
	imprime_registradores(log, r);
	log << "---------------------" << '\n';

	bool ok = true;
	if(fetch){
		r.mbr = bitset<8>(ir.substr(0,8));
		r.h   = bitset<32>(r.mbr.to_ulong());
	}
	else{
		bitset<32> a = r.h;
		bitset<32> b = barramento_b(r, comandos[3]);
		SaidaUla s = carrega_ula(comandos[0], a, b);
		barramento_c(r, comandos[1], s.saidad);
		if(!mem(r, dados, nome, comandos[2])){
			log << "> Erro, MAR fora da memoria (" << r.mar.to_ulong() << "), acesso ignorado." << '\n';
			ok = false;
		}
	}

	log << "-> Registradores depois da microinstrução:" << '\n';
	imprime_registradores(log, r);
	log << "------------------------------------------" << '\n';
	return ok;
}
