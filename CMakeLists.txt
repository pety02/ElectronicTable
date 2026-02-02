cmake_minimum_required(VERSION 3.28)
project(ElectronicTable)

set(CMAKE_CXX_STANDARD 20)

add_executable(ElectronicTable src/main.cpp
        src/Types.h
        src/Table.h
        src/CmdInterpreter.h
        src/ExpressionParser.h
        src/Tokenizer.h
        src/Table.cpp
        src/Tokenizer.cpp
        src/ExpressionParser.cpp
        src/CmdInterpreter.cpp
)

include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.4
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests
        # all tests goes here
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE include)