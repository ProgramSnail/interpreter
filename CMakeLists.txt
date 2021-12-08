project(Interpreter)

cmake_minimum_required(VERSION 3.13)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

set(
    HEADERS
    ${Interpreter_SOURCE_DIR}/driver.hh
    ${Interpreter_SOURCE_DIR}/parser.hh
    ${Interpreter_SOURCE_DIR}/parse_tree.hh
    )

BISON_TARGET(
    MyParser
    parser.y
    ${Interpreter_SOURCE_DIR}/parser.cpp
    COMPILE_FLAGS --graph
    DEFINES_FILE ${Interpreter_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
    MyScanner
    scanner.l
    ${Interpreter_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

add_executable(
    Interpreter
    main.cpp
    driver.cpp
    parse_tree.cpp
    ${BISON_MyParser_OUTPUTS}
    ${FLEX_MyScanner_OUTPUTS}
)
target_include_directories(Interpereter PRIVATE ${Interpreter_SOURCE_DIR})



