#include <cstdint>
#include <string>
#include "ULA.hpp"
#include "CPU.hpp"


    void CPU::cpu_cicle(std::string &instruction_buff, int32_t A, int32_t B)
    {
        this->reg.IR = instruction_buff;

        this->A = A;
        this->B = B;

        m_ULA.A = A;
        m_ULA.B = B;

        // fetch

        auto opcode = this->m_ULA.decode(instruction_buff);

        this->output = this->m_ULA.execute(opcode);

        this->reg.PC++;
    }
