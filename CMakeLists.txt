cmake_minimum_required(VERSION 3.12)
project(testKlasy)

set(CMAKE_CXX_STANDARD 17)

add_executable(wallet test.cc wallet.cc wallet.h)