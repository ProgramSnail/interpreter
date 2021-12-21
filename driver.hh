#pragma once

#include <map>
#include <string>
#include <iostream>
#include <fstream>

#include "scanner.h"
#include "parser.hh"
#include "storage.hh"
#include "parse_tree.hh"

class Driver {
 public:
    Driver();

    Storage storage;
    std::istream* inStream = &std::cin;
    std::ostream* outStream = &std::cout;
    std::ostream* errOutStream = &std::cerr;

    int result;

    void configStreams(std::istream& in = std::cin, 
            std::ostream& out = std::cout,
            std::ostream& errOut = std::cerr);
    
    int parse(const std::string& f);

    std::string file;

    void scan_begin();
    void scan_end();

    bool trace_parsing;
    bool trace_scanning;
    yy::location location;

    friend class Scanner;
    Scanner scanner;
    yy::parser parser;
    bool location_debug;
 private:
    std::ifstream in;
};
