#include<bits/stdc++.h>
#include <cstdint>
#include <iostream>
using namespace std;

int32_t h, opc, tos, cpp, lv, sp, pc, mdr, mar;
uint8_t mbr;

void escreve_barr_c(int i, int32_t entrada){
	switch (i) {
		case 0:
			mar = entrada;
			break;
		case 1:
			mdr = entrada;
			break;
		case 2:
			pc  = entrada;
			break;
		case 3:
			sp  = entrada;
			break;
		case 4:
			lv  = entrada;
			break;
		case 5:
			cpp = entrada;
			break;
		case 6:
			tos = entrada;
			break;
		case 7:
			opc = entrada;
			break;
		case 8:
			h   = entrada;
			break;
		default: cout << "ERRO, TENTOU ESCREVER EM UM REGISTRADOR INESISTENTE DO BARRAMENTO C";
	}
}

int32_t le_barr_b(int registrador){
	switch (registrador) {
		case 0: return mdr;
		case 1: return pc;
		case 2: return (int8_t)mbr;
		case 3: return mbr;
		case 4: return sp;
		case 5: return lv;
		case 6: return cpp;
		case 7: return tos;
		case 8: return opc;
		default: cout << "ERRO, NÃO FOI FORNECIDO UM REGISTRADOR VALIDO PARA O BARRAMENTO B";
	}
	return 0;
}
