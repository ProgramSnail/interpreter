#pragma once

#include <map>
#include <string>
#include <fstream>

#include "scanner.h"
#include "parser.hh"
#include "storage.hh"

class Driver {
 public:
    Driver();
    Storage storage;
    int result;
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
    std::ifstream stream;

};
