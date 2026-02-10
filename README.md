# Spreadsheet Engine named 'Electronic Table' (Project 6 – Data Structures)

> This project implements a console-based spreadsheet engine written in C++ (C++17). It supports arithmetic and logical expressions, absolute and relative cell addressing, aggregation functions over cell ranges, and persistent storage using CSV files.
>
> The project was developed as part of the Data Structures course at the Faculty of Mathematics and Informatics, Sofia University.

---

# Features

- Sparse spreadsheet representation (memory-efficient for large tables)
- Arithmetic expressions: +, -, *, /, %
- Logical and comparison operators: and, or, not, ==, !=, <, >
- Conditional expressions: if(condition, expr1, expr2)
- Absolute and relative cell addressing:
  - Absolute: R5C3
  - Relative: R[-1]C[0]
- Aggregation functions over rectangular areas:
  - sum, count, min, max, avg
- Lazy evaluation with cached cell values
- CSV import/export (SAVE / LOAD)
- Robust error handling
- Fully unit-tested using Catch2

---

# Architecture Overview

> The system is divided into several well-defined components:

## Core Structures

- Coordinates
  
> Represents a cell position using (row, column) with 64-bit integers, allowing very large indices.

- Cell

> Stores:
> 
> - the original expression as a string;
> - a cached numeric value (double);
> -its coordinates.

- Area

> Represents a rectangular region of the spreadsheet, defined by two corner coordinates. Used for range-based operations and printing.

## Spreadsheet Storage

- Table
  - Implemented as std::unordered_map<Coordinates, Cell>
  - Stores only non-empty cells (sparse representation)
  - Supports:
    - setting and retrieving cell expressions;
    - aggregation functions over areas;
    - table boundary detection for printing.

> This design allows the spreadsheet to scale to extremely large sizes (e.g. R100000C100000) while using memory efficiently.

## Expression Processing

- Tokenizer
  - Performs lexical analysis of expressions
  - Recognizes:
    - numbers;
    - operators;
    - identifiers (if, sum, and, etc.);
    - absolute and relative cell references.

- ExpressionParser
  - Recursive descent parser
  - Evaluates expressions on-the-fly
  - Supports operator precedence and associativity (C++-like semantics)
  - Resolves cell references relative to the currently evaluated cell
  - Evaluates only the necessary branches of if expressions

## Command Interface

- CmdInterpreter
  - Processes user commands:
    - SET
    - PRINT VAL
    - PRINT EXPR
    - PRINT VAL ALL
    - PRINT EXPR ALL
    - SAVE
    - LOAD
  - Validates input
    - Connects user commands to table operations and expression evaluation
    - Provides clear error messages

## Algorithms Used

- Sparse data representation using hash tables
- Custom coordinate hashing based on SplitMix64 (Sebastiano Vigna)
- Linear-time tokenization
- Recursive descent parsing
- Lazy evaluation with value caching
- Efficient range aggregation based on existing cells only
- CSV serialization/deserialization

## Project Structure
```php
.
├── src/        # Core implementation (.h / .cpp files)
├── tests/      # Unit tests (Catch2)
├── public/     # Test data and demonstration scripts
├── CMakeLists.txt
└── README.md
```

## Testing

- The project includes comprehensive unit tests written with Catch2, covering:
  - Tokenization correctness
  - Expression parsing and evaluation
  - Absolute and relative cell addressing
  - Table operations
  - Aggregation functions
  - CSV save/load functionality

> Tests are modular, isolated, and easy to extend.

## Technologies & Dependencies

- **Language**: C++17
- **Build system**: CMake
- **Testing framework**: Catch2
- **Standard library only** (no smart pointers used)
- **File formats**: CSV (storage), JSON (test/demo data)

## External Resources

- Custom Hash Functions – Codeforces
> https://codeforces.com/blog/entry/62393

- SplitMix64 algorithm and license – Sebastiano Vigna
> https://xoshiro.di.unimi.it/splitmix64.c

---

# Author

> **Full Name**: Petya Licheva
> **Faculty**: Faculty of Mathematics and Informatics
> **University**: Sofia University “St. Kliment Ohridski”
> **Date**: January 2026
