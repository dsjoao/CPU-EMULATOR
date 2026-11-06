#include <cstdint>
#include <string>
#include <vector>
#include "ULA.hpp"
#include "operations.hpp"


    std::vector<uint8_t> ULA::decode(std::string &instruction_buff)
    {
    	std::vector<uint8_t> instruction(8);
        for (size_t i = 0; i < 8; i++)
            instruction[i] = instruction_buff[i] - '0';

        return instruction;
    }

    int32_t ULA::execute(std::vector<uint8_t> &op)
    {
       	if(!op[ENA])  this->A = 0;
        if(op[INVA]) this->A = ~this->A;

        if(!op[ENB])  this->B = 0;

        int32_t res;

        if( !op[F0]  &  !op[F1])  res = this->A AND this->B;
        if((!op[F0]) &   op[F1])  res = this->A OR  this->B;
        if(  op[F0]  & (!op[F1])) res = 		   ~this->B;
        if(  op[F0]  &   op[F1])  res = this->A + this->B;


        res += op[INC];

        this->signals.N 		= (res < 0)  ? 1 : 0;
        this->signals.Z 		= (res == 0) ? 1 : 0;
        this->signals.carry_out = ((int64_t)(res) >> 32) & 1;



        this->output = res;

        if(op[SLL8] & op[SRA1]) res = 0xfffffffe;
        if(op[SLL8]) 			res ILSHIFT 8;
        if(op[SRA1]) 			res IRSHIFT 1;


        return res;
    };
