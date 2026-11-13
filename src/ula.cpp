#include<bits/stdc++.h>
using namespace std;

struct SaidaUla {bitset<32> saida; bitset<32> saidad; bool vaiUm; bool n; bool z;};

SaidaUla ula(bool sll8, bool sra1, bool f0, bool f1, bool ena, bool enb, bool inva, bool vemUm, bitset<32> a, bitset<32> b){
    // --- definindo váriaveis ---
    bitset<32> saida, saidad;
    bool     vaiUm, n=0, z=0;
    bool       carry = vemUm;
    bitset<32>    result = 0;
    // ----------------------------
    for(int i=0; i < 32; i++){
       	// ----------------------------
        // --- primeiras entradas ---
        bool e3 = b.test(i) and enb;
        bool e2 = a.test(i) and ena;
        bool e1 =      inva xor  e2;
        // ----------------------------
        // --- decodificador ---
        bool d1 = !f0 and !f1;
        bool d2 = !f0 and  f1;
        bool d3 =  f0 and !f1;
        bool d4 =  f0 and  f1;
        // ----------------------------
        // --- unidade logica ---
        bool ul1 =  e1 and e3;
        bool ul2 =  e1  or e3;
        bool ul3 = ul1 and d1;
        bool ul4 = ul2 and d2;
        bool ul5 = !e3 and d3;
        // ----------------------------
        // --- somador completo ---
        bool s1 =        e1 xor    e3;
        bool s2 = d4 and e1 and    e3;
        bool s3 = d4 and s1 and carry;
        bool s4 =     carry xor    s1;
        bool s5 =        s4 and    d4;
        bool s6 =         s2 or    s3;
        // ----------------------------
        // --- resultado/carry ---
        bool bit = ul3 or ul4 or ul5 or s5;
        carry    =      s6;
        result.set(i, bit);
        // ----------------------------
    }
    // --- saidas ---
    vaiUm =          carry;
    saida =         result;
    z     =   saida.none();
    n     = saida.test(31);
    // ----------------------------
    // --- deslocamento lógico ---
    saidad = saida;
    if(sll8)
        saidad = (saida << 8);
    else if(sra1){
        saidad = (saida >> 1);
        saidad[31] = saida[31];
    }
    // ----------------------------
    return {saida, saidad, vaiUm, n, z};
}
