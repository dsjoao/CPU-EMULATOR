#include<bits/stdc++.h>
#include <fstream>
int main() {
    std::string ir; // registrador de instrução
    int pc = 0;

    std::ifstream entrada;
    entrada.open ("programa_etapa1.txt");
    if(!entrada) // erro, arquivo não existe
        return 1;
    while(getline(entrada,ir)){

        pc++;
    }

    entrada.close();
	return 0;
}
