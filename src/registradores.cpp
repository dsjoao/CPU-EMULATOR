#include<bits/stdc++.h>
#include <cstdint>
#include <iostream>
using namespace std;

struct Reg {
	int32_t h=0, opc=0, tos=0, cpp=0, lv=0, sp=0, pc=0, mdr=0, mar=0;
	uint8_t mbr=0;
};

void escreve_barr_c(Reg &r, int i, int32_t entrada){
	switch (i) {
		case 0:
			r.mar = entrada;
			break;
		case 1:
			r.mdr = entrada;
			break;
		case 2:
			r.pc  = entrada;
			break;
		case 3:
			r.sp  = entrada;
			break;
		case 4:
			r.lv  = entrada;
			break;
		case 5:
			r.cpp = entrada;
			break;
		case 6:
			r.tos = entrada;
			break;
		case 7:
			r.opc = entrada;
			break;
		case 8:
			r.h   = entrada;
			break;
		default: cout << "ERRO, TENTOU ESCREVER EM UM REGISTRADOR INESISTENTE DO BARRAMENTO C";
	}
}

int32_t le_barr_b(Reg r, int registrador){
	switch (registrador) {
		case 0: return r.mdr;
		case 1: return r.pc;
		case 2: return (int8_t)r.mbr;
		case 3: return r.mbr;
		case 4: return r.sp;
		case 5: return r.lv;
		case 6: return r.cpp;
		case 7: return r.tos;
		case 8: return r.opc;
		default: cout << "ERRO, NÃO FOI FORNECIDO UM REGISTRADOR VALIDO PARA O BARRAMENTO B";
	}
	return 0;
}
