cmake_minimum_required(VERSION 3.2)
project(MPAGSCipher VERSION 0.1.0)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 14)
add_executable(mpags-cipher mpags-cipher.cpp MPAGSCipher/TransformChar.cpp MPAGSCipher/TransformChar.hpp MPAGSCipher/runCaesarCipher.cpp MPAGSCipher/runCaesarCipher.hpp)
target_include_directories(mpags-cipher PRIVATE MPAGSCipher)
set(CMAKE_CXX_EXTENSIONS OFF)

target_compile_features(mpags-cipher PRIVATE cxx_auto_type cxx_range_for cxx_uniform_initialization)
