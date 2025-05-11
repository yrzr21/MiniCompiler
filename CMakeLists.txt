cmake_minimum_required(VERSION 3.5)

project(MiniCompiler)

set(CMAKE_CXX_STANDARD 20)


add_executable(test_lexer Test/test_lexer.cpp Lexer/lexer.cpp)