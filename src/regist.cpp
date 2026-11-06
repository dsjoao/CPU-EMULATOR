#include<bits/stdc++.h>
#include <cstdint>
using namespace std;

int32_t h, opc, tos, cpp, lv, sp, pc, mdr, mar, mbr;

void carrega_regist_barr_c(int i, int32_t entrada){
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
	}
}
