cmake_minimum_required(VERSION 3.13)

project(telecommunication-one VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(telecommunication-one
               src/main.cpp src/CorrectionMatrix.cpp src/CorrectionMatrix.hpp src/BinaryFileEncoder.cpp src/BinaryFileEncoder.hpp)
