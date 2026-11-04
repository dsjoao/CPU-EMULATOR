#include<bits/stdc++.h>
struct SaidaUla {int saida; bool vaiUm; bool n; bool z;};

SaidaUla ula(bool sll8, bool sra1, bool f0, bool f1, bool ena, bool enb, bool inva, bool vemUm, bool a, bool b){
    // --- primeiras entradas ---
    bool e3 =   b and enb;
    bool e2 =   a and ena;
    bool e1 = inva xor e2;
    // ----------------------------
    // --- decodificador ---
    bool d1 = !f0 and !f1;
    bool d2 =  !f0 and f1;
    bool d3 =  f0 and !f1;
    bool d4 =   f0 and f1;
    // ----------------------------
    // --- unidade logica ---
    bool ul1 =  e1 and e3;
    bool ul2 =   e1 or e3;
    bool ul3 = ul1 and d1;
    bool ul4 = ul2 and d2;
    bool ul5 = !e3 and d3;
    // ----------------------------
    // --- somador completo ---
    bool s1 =           e1 xor e3;
    bool s2 =    d4 and e1 and e3;
    bool s3 = d4 and s1 and vemUm;
    bool s4 =        vemUm xor s1;
    bool s5 =           s4 and d4;
    bool s6 =            s2 or s3;
    // ----------------------------
    // --- saidas ---
    bool z, n;
    int saida = ul3 or ul4 or ul5 or s5;
    bool vaiUm = s6;

    if(saida == 0){
        z = 1;
    }else if(saida < 0){
        n = 1; z = 0;
    }else{
        n = 0; z = 0;
    }
    // deslocamento lógico
    if(sll8)
        saida = (saida << 8);
    else if(sra1)
        saida =  (saida > 1);
    // ----------------------------
    return {saida, vaiUm, n, z};
}
