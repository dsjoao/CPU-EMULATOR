cmake_minimum_required(VERSION 4.4.0)

project(trabalho_ac2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_DEBUG -Wall -Wextra -Wconversion -Wsign-compare -Werror)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../textos)

add_executable(emulador src/main.cpp src/CPU.cpp src/ULA.cpp)

target_include_directories(emulador PRIVATE include)
