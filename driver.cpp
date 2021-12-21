#include "driver.hh"
#include "parser.hh"



Driver::Driver() :
    trace_parsing(false),
    trace_scanning(false),
    location_debug(false),
    scanner(*this), parser(scanner, *this) {
}

void Driver::configStreams(std::istream& in, 
        std::ostream& out, std::ostream& errOut) {
    inStream = &in;
    outStream = &out;
    errOutStream = &errOut;
} 

int Driver::parse(const std::string& f) {
    file = f;
    // initialize location positions
    location.initialize(&file);
    scan_begin();
    parser.set_debug_level(trace_parsing);
    int res = parser();
    scan_end();
    return res;
}

void Driver::scan_begin() {
    scanner.set_debug(trace_scanning);
  if (file.empty () || file == "-") {
  } else {
    in.open(file);
    (*errOutStream) << "File name is " << file << std::endl;
    (*errOutStream) << "Interpreting started.\n";
    // Restart scanner resetting buffer!
    scanner.yyrestart(&in);
  }
}

void Driver::scan_end()
{
    in.close();
    (*errOutStream) << "Interpreting finished." << std::endl;
}

