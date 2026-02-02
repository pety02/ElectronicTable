cmake_minimum_required(VERSION 3.28)
project(ElectronicTable)

set(CMAKE_CXX_STANDARD 20)

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

# Include headers for main
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

        # Include the source files so tests can link to implementations
        src/Table.cpp
        src/Tokenizer.cpp
        src/ExpressionParser.cpp
        src/CmdInterpreter.cpp
)

# Link Catch2 and include headers
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE src)