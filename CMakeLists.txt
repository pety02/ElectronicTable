cmake_minimum_required(VERSION 3.28)

project(ElectronicTable LANGUAGES CXX)

# ----------------------------
# C++ Standard (REQUIRED)
# ----------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ----------------------------
# Main executable
# ----------------------------
add_executable(ElectronicTable
        src/main.cpp
        src/Table.cpp
        src/Tokenizer.cpp
        src/ExpressionParser.cpp
        src/CmdInterpreter.cpp
)

target_include_directories(ElectronicTable PRIVATE src)

# ----------------------------
# Fetch Catch2
# ----------------------------
include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.4
)

FetchContent_MakeAvailable(Catch2)

# ----------------------------
# Tests executable
# ----------------------------
add_executable(tests
        tests/TableTest.cpp
        tests/TokenizerTest.cpp
        tests/ExpressionParserTest.cpp
        tests/CmdInterpreterTests.cpp

        src/Table.cpp
        src/Tokenizer.cpp
        src/ExpressionParser.cpp
        src/CmdInterpreter.cpp
)

target_include_directories(tests PRIVATE src)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)