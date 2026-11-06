#include <cstdint>
#include <fstream>
#include <bitset>
#include "../include/CPU.hpp"


int main()
{

    std::ifstream file("../textos/programa_etapa2_tarefa1.txt");
    std::ofstream log("log.txt");
    std::string buff;

    CPU CPU;

    CPU.reg.MAR = 0;
    CPU.reg.MDR = 0;
    CPU.reg.TOS = 2;
    CPU.reg.OPC = 0;
    CPU.reg.PC  = 0;
    CPU.reg.SP  = 0;
    CPU.reg.H   = 1;
    CPU.reg.LV  = 0;
    CPU.reg.CPP = 0;
    CPU.reg.MBR = 65;



    log << "~~~~~~~~~~~~~~~~~ COMEÇO DO PROGRAMA ~~~~~~~~~~~~~~~~~\n";

    log <<"\n=-=-=-=-=-=-=-=-=-=-=-=-=!!!!=-=-=-=-=-=-=-=-=-=-=-=-=\n";


    log << "\n-=-=-=-=-=-=-=-=-=-=-=-=####=-=-=-=-=-=-=-=-=-=-=-=-=\n";



    while (std::getline(file,buff))
    {
        CPU.cpu_cicle(buff);

        log <<"\n=-=-=-=-=-=-=-=-=-=-=-=-=!!!!=-=-=-=-=-=-=-=-=-=-=-=-=\n";



        log << "\n-=-=-=-=-=-=-=-=-=-=-=-=####=-=-=-=-=-=-=-=-=-=-=-=-=\n";


    }


    file.close();
    log.close();


	return 0;
}
