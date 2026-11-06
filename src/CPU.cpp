#include <cstdint>
#include <string>
#include "ULA.hpp"
#include "CPU.hpp"


    void CPU::cpu_cicle(std::string &instruction_buff)
    {
        this->reg.IR = instruction_buff;

        this->A = this->reg.H;
        this->B = read_B_bus(instruction_buff);
        this->bus.B = this->B;

        m_ULA.A = (int32_t)this->A;
        m_ULA.B = (int32_t)this->B;

        auto opcode = this->m_ULA.decode(instruction_buff);

        this->output = this->m_ULA.execute(opcode);
        this->bus.C  = (uint32_t)this->output;

        write_C_bus(instruction_buff, this->bus.C);

        this->reg.PC++;
    }

    uint32_t CPU::read_B_bus(std::string &instruction_buff)
    {
        int pos = 0;
        for (int i = 0; i < 4; i++)
            pos = (pos << 1) | (instruction_buff[B_START + i] - '0');

        switch (pos)
        {
            case 0: return this->reg.MDR;
            case 1: return this->reg.PC;
            case 2: return (uint32_t)(int32_t)(int8_t)this->reg.MBR;
            case 3: return this->reg.MBR;
            case 4: return this->reg.SP;
            case 5: return this->reg.LV;
            case 6: return this->reg.CPP;
            case 7: return this->reg.TOS;
            case 8: return this->reg.OPC;
        }

        return 0;
    }

    void CPU::write_C_bus(std::string &instruction_buff, uint32_t value)
    {
        uint32_t *dest[9] = {
            &this->reg.H,  &this->reg.OPC, &this->reg.TOS,
            &this->reg.CPP, &this->reg.LV, &this->reg.SP,
            &this->reg.PC, &this->reg.MDR, &this->reg.MAR
        };

        for (int i = 0; i < 9; i++)
            if (instruction_buff[C_START + i] == '1')
                *dest[i] = value;
    }
