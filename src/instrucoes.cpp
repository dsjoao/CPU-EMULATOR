#include <bits/stdc++.h>
#include "cpu.cpp"
using namespace std;

struct Instrucao {
	string nome;
	bool tem_argumento = false;
	vector<string> microinstrucoes;
	int repetida = -1;
};

bool usa_byte(const Instrucao &ins){
	for(const auto &m : ins.microinstrucoes)
		if(m.find('x') != string::npos) return true;
	return false;
}

bool le_inteiro(const string &s, long &valor){
	if(s.empty()) return false;
	size_t pos = 0;
	try{ valor = stol(s, &pos); }
	catch(...){ return false; }
	return pos == s.size();
}

bool le_argumento(const Instrucao &ins, const string &arg, unsigned long &valor, string &erro){
	long v;
	valor = 0;
	if(!ins.tem_argumento){
		if(!arg.empty()){
			erro = ins.nome + " nao recebe argumento";
			return false;
		}
		return true;
	}
	if(arg.empty()){
		erro = ins.nome + " precisa de um argumento";
		return false;
	}
	if(usa_byte(ins)){
		if(arg.size() == 8 && arg.find_first_not_of("01") == string::npos){
			valor = bitset<8>(arg).to_ulong();
			return true;
		}
		if(le_inteiro(arg, v) && v >= -128 && v <= 255){
			valor = (unsigned long)(v & 0xFF);
			return true;
		}
		erro = ins.nome + " precisa de um byte (8 bits binarios ou decimal de -128 a 255)";
		return false;
	}
	if(le_inteiro(arg, v) && v >= 0 && v <= 255){
		valor = (unsigned long)v;
		return true;
	}
	erro = ins.nome + " precisa de um inteiro entre 0 e 255";
	return false;
}

vector<string> gera_microinstrucoes(const Instrucao &ins, unsigned long argumento){
	vector<string> saida;
	string byte = bitset<8>(argumento).to_string();
	for(int i = 0; i < (int)ins.microinstrucoes.size(); i++){
		string m = ins.microinstrucoes[i];
		if(i == ins.repetida){
			for(unsigned long k = 0; k < argumento; k++) saida.push_back(m);
			continue;
		}
		size_t k = 0;
		for(char &ch : m)
			if(ch == 'x') ch = byte[k++ % 8];
		saida.push_back(m);
	}
	return saida;
}

bool executa_instrucao(const Instrucao &ins, unsigned long argumento, const string &linha,
                       Reg &r, fstream &dados, const string &nome_dados, ostream &log, int &ciclo){
	vector<string> micro = gera_microinstrucoes(ins, argumento);

	log << "==========================================" << '\n';
	log << "Instrucao: " << linha << '\n';
	log << "Microinstrucoes geradas:" << '\n';
	for(const auto &m : micro) log << "  " << m << '\n';
	log << "==========================================" << '\n';

	bool ok = true;
	for(const auto &m : micro){
		if(!executa_microinstrucao(r, dados, nome_dados, m, log, ciclo)){
			log << "> Instrucao " << linha << " interrompida." << '\n';
			ok = false;
			break;
		}
	}

	log << "-> Memória depois da instrução " << linha << ":" << '\n';
	imprime_dados(log, dados);
	log << "------------------------------------------" << '\n';
	return ok;
}
