project(InterpreterProj)

cmake_minimum_required(VERSION 3.13)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

set(
    HEADERS
    ${InterpreterProj_SOURCE_DIR}/driver.hh
    ${InterpreterProj_SOURCE_DIR}/parser.hh
    parse_tree.hh
    )

BISON_TARGET(
    MyParser
    parser.y
    ${InterpreterProj_SOURCE_DIR}/parser.cpp
    COMPILE_FLAGS "--graph -Wcex -Werror"
    DEFINES_FILE ${InterpreterProj_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
    MyScanner
    scanner.l
    ${InterpreterProj_SOURCE_DIR}/scanner.cpp
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

target_include_directories(Interpreter PRIVATE ${InterpreterProj_SOURCE_DIR})



