#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include "ULA.hpp"

struct registers
{
 uint16_t
      PC = 0;

    std::string
      IR = "000000";
};


class CPU
{
  public:

    registers reg;
    ULA m_ULA;

    // inputs. I think this is temporary
    int32_t A = 0,B = 0;

    int32_t output = 0;

    void cpu_cicle(std::string &instruction_buff, int32_t A, int32_t B);


  private:

      std::ofstream log_file;

};
