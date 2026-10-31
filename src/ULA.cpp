#include <cstdint>
#include <string>
#include "ULA.hpp"
#include "operations.hpp"


    void ULA::decode(std::string &instruction_buff)
    {
        for (size_t i = 0; i < 6; i++)
        {
            instruction[i] = instruction_buff[i] - '0';
        }

        if(!instruction[F0])
            if(!instruction[F1])
                this->opcode = 0;
            else
                this->opcode = 1;
        else
            if(!instruction[F1])
                this->opcode = 2;
            else
                this->opcode = 3;

    }

    int8_t ULA::execute()
    {
        this->A IAND instruction[ENA];
        this->A IXOR instruction[INVA];

        this->B IAND instruction[ENB];

        switch(opcode)
        {
            case 0: return (this->A AND this->B) XOR instruction[INC];
            case 1: return (this->A OR  this->B) XOR instruction[INC];
            case 2: return (this->B XOR 1)       XOR instruction[INC];
            case 3:
            {
                int32_t res = (this->A XOR this->B) XOR instruction[INC];

                // transforma no oposto (1 -> 0, 0 -> 1) e novamente para 1 ou zero. Garante que ao invés de um número como 9 ou 15 ele vai ser 0 ou 1
                this->carry_out = (A AND B) OR ((A XOR B) AND INC);
                return res;
            }
        }

        return INT8_MIN;

    };
