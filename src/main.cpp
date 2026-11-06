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

    int32_t A = 1, B = -2147483648 ;

    log << "~~~~~~~~~~~~~~~~~ COMEÇO DO PROGRAMA ~~~~~~~~~~~~~~~~~\n";

    log <<"\n=-=-=-=-=-=-=-=-=-=-=-=-=!!!!=-=-=-=-=-=-=-=-=-=-=-=-=\n";

    log << "PC = " << CPU.reg.PC << "\n";
    log << "IR = " << CPU.reg.IR << "\n";
    log << "valor de A = " << static_cast<std::bitset<32>>(A) << "\n";
    log << "valor de B = " << static_cast<std::bitset<32>>(B) << "\n";
    log << "saída = " << static_cast<std::bitset<32>>(CPU.output) << "\n";
    log << "saída pós deslocador = " << static_cast<std::bitset<32>>(CPU.output) << "\n";
    log << "N = " << CPU.m_ULA.signals.N << "\n";
    log << "Z = " << CPU.m_ULA.signals.Z << "\n";
    log << "carry out = " << CPU.m_ULA.signals.carry_out << "\n";

    log << "\n-=-=-=-=-=-=-=-=-=-=-=-=####=-=-=-=-=-=-=-=-=-=-=-=-=\n";



    while (std::getline(file,buff))
    {
        CPU.cpu_cicle(buff,A,B);

        log <<"\n=-=-=-=-=-=-=-=-=-=-=-=-=!!!!=-=-=-=-=-=-=-=-=-=-=-=-=\n";

        log << "PC = " << CPU.reg.PC << "\n";
        log << "IR = " << CPU.reg.IR << "\n";
        if(CPU.reg.IR[0] == '1' && CPU.reg.IR[1] == '1') { log << "incorrect control signals \n-=-=-=-=-=-=-=-=-=-=-=-=####=-=-=-=-=-=-=-=-=-=-=-=-=\n"; continue;}
        log << "valor de A = " << static_cast<std::bitset<32>>(A) << "\n";
        log << "valor de B = " << static_cast<std::bitset<32>>(B) << "\n";
        log << "saída = " << static_cast<std::bitset<32>>(CPU.m_ULA.output) << "\n";
        log << "saída pós deslocador = " << static_cast<std::bitset<32>>(CPU.output) << "\n";
        log << "N = " << CPU.m_ULA.signals.N << "\n";
        log << "Z = " << CPU.m_ULA.signals.Z << "\n";
        log << "carry out = " << CPU.m_ULA.signals.carry_out << "\n";

        log << "\n-=-=-=-=-=-=-=-=-=-=-=-=####=-=-=-=-=-=-=-=-=-=-=-=-=\n";


    }


    file.close();
    log.close();


	return 0;
}
