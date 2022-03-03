cmake_minimum_required(VERSION 3.16)

# set(CMAKE_CXX_COMPILER riscv64-unknown-elf-g++)
project(easycc)

aux_source_directory(src SRC_DIR )
add_executable(easycc ${SRC_DIR})