#pragma once
#include <cstdint>
#include <string>
#include <vector>


#define SLL8 0
#define SRA1 1
#define F0 2
#define F1 3
#define ENA 4
#define ENB 5
#define INVA 6
#define INC 7

struct signal
{
    uint16_t N = 0, Z = 0;
    uint16_t carry_out = 0;
};

class ULA
{
    public:

        signal signals;

        int32_t A = 0, B = 0;

        int32_t output = 0;

        std::vector<uint8_t> decode(std::string &instruction_buff);

        int32_t execute(std::vector<uint8_t> &instructions);

        friend class CPU;
};
