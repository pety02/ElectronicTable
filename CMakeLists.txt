cmake_minimum_required(VERSION 3.28)
project(ElectronicTable)

set(CMAKE_CXX_STANDARD 20)

add_executable(ElectronicTable main.cpp
        Types.h
        Table.h
        CmdInterpreter.h
        ExpressionParser.h
        Tokenizer.h
        Table.cpp
        Tokenizer.cpp
        ExpressionParser.cpp
        CmdInterpreter.cpp)
