#include <cstdint>
#include <fstream>
#include <string>
#include "ULA.hpp"
#include "CPU.hpp"



        CPU::CPU(std::ofstream &log_file)
        {
            this->log_file = std::move(log_file);

            this->log_file << "~~~~~~~~~~~~~~~~~ COMEÇO DO PROGRAMA ~~~~~~~~~~~~~~~~~\n";
        }

        CPU::~CPU()
        {
            this->log_file << "\n~~~~~~~~~~~~~~~~~ FIM DO PROGRAMA ~~~~~~~~~~~~~~~~~\n";
        }


    void CPU::cpu_cicle(std::string &instruction_buff, int32_t A, int32_t B)
    {
        this->IR = instruction_buff;

        this->A = A;
        this->B = B;

        m_ULA.A = A;
        m_ULA.B = B;

        // fetch
        this->m_ULA.decode(instruction_buff);
        // see later if all instructions that will come are all on the ALU scope
        this->current_value = this->m_ULA.execute();

        this->PC++;

        log();

    }

    void CPU::log()
    {
        this->log_file << "\n=-=-=-=-=-=-=-=-=-=-=-=-=!!!!=-=-=-=-=-=-=-=-=-=-=-=-=\n";
        this->log_file << " PC = " << this->PC <<
                        "\n IR = " << this->IR <<
                        "\n valor de A = " << this->A <<
                        "\n valor de B = " << this->B <<
                        "\n valor do carry = " << m_ULA.carry_out <<
                        "\n resultado da operação = " << this->current_value << "\n";
        this->log_file << "\n=-=-=-=-=-=-=-=-=-=-=-=-=####=-=-=-=-=-=-=-=-=-=-=-=-=\n";
    }
