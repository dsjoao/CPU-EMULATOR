#include <bits/stdc++.h>
#include <cstdint>
#include <vector>
using namespace std;
struct SaidaRegist {bool a; bool b;};

/* Ordem dos registradores dentro do vetor registrador:
 * H OPC TOS CPP LV SP PC MDR MAR
 */
vector<int32_t>registradores(12);
void barramento_c(vector<bool>regist_ativo, int32_t entrada){
	for(int i=0; i < 9; i++){
		if(regist_ativo[i]){
			registradores[i] = entrada;
		}
	}
}

SaidaRegist barramento_b(int saida, const vector<bool> &barr_c){


    return {1, 0};
}
