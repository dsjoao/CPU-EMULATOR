#pragma once
#include <cstdint>
#include <string>


#define F0 0
#define F1 1
#define ENA 2
#define ENB 3
#define INVA 4
#define INC 5


class ULA
{
    private:

        uint8_t instruction[6];

        int32_t A = 0, B = 0;

        uint8_t opcode = 0;

        uint16_t carry_out = 0;

        void decode(std::string &instruction_buff);

        int8_t execute();

        friend class CPU;
};
