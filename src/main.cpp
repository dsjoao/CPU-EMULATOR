#include <fstream>
#include <iostream>
#include "CPU.hpp"


int main()
{

    std::ifstream file("../textos/programa_etapa1.txt");
    std::ofstream log("log.txt");
    std::string buff;

    CPU CPU(log);

    CPU.log();

    int A,B;

    while (std::getline(file,buff))
    {
        std::cin >> A >> B;
        CPU.cpu_cicle(buff,A,B);
    }


    file.close();
    log.close();


	return 0;
}
