#pragma once
#include <cstdint>
#include <string>
#include "ULA.hpp"

#define INSTR_SIZE 21
#define C_START    8
#define B_START    17

struct registers
{
    uint32_t
      PC  = 0,
      H   = 0,
      OPC = 0,
      CPP = 0,
      LV  = 0,
      SP  = 0,
      TOS = 0,
      MDR = 0,
      MAR = 0;

    uint8_t
      MBR = 0;

    std::string
      IR = "000000000000000000000";
};


struct data_bus
{
    uint32_t B = 0, C = 0;
};


class CPU
{
  public:

    data_bus bus;
    registers reg;
    ULA m_ULA;

    uint32_t A = 0, B = 0;

    int32_t output = 0;

    void cpu_cicle(std::string &instruction_buff);

    uint32_t read_B_bus(std::string &instruction_buff);

    void write_C_bus(std::string &instruction_buff, uint32_t value);
};
