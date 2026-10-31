#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include "ULA.hpp"


class CPU
{
  public:

      CPU(std::ofstream &log_file);
      ~CPU();

    uint16_t
      PC = 0;

    std::string
      IR = "000000";

    // inputs. I think this is temporary
    int16_t A = 0,B = 0;


    void cpu_cicle(std::string &instruction_buff, int32_t A, int32_t B);

    void log();

  private:

      ULA m_ULA;

      std::ofstream log_file;

      // temporary, will be changed later
      int16_t current_value = 0;

};
