#include<bits/stdc++.h>
#include <cstdint>
#include <iostream>
using namespace std;

struct Reg {
	bitset<32> h=0, opc=0, tos=0, cpp=0, lv=0, sp=0, pc=0, mdr=0, mar=0;
	bitset<8>  mbr=0;
};

void escreve_barr_c(Reg &r, int i, bitset<32> entrada){
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

bitset<32> le_barr_b(Reg r, unsigned long registrador){
	switch (registrador) {
		case 0: return r.mdr;
		case 1: return r.pc;
		case 2: return bitset<32>((int32_t)(int8_t)r.mbr.to_ulong());
		case 3: return bitset<32>(r.mbr.to_ulong());
		case 4: return r.sp;
		case 5: return r.lv;
		case 6: return r.cpp;
		case 7: return r.tos;
		case 8: return r.opc;
		default: cout << "ERRO, NÃO FOI FORNECIDO UM REGISTRADOR VALIDO PARA O BARRAMENTO B";
	}
	return 0;
}
