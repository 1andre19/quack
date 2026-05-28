#include "driver.hh"

int main(int argc, char *argv[]) {
    driver drv;
    int result = 0;
    for (int i = 1; i < argc; ++i) {
        if (argv[i] == std::string("-p")) {
            drv.trace_parsing = true;
        } else if (argv[i] == std::string("-s")) {
            drv.trace_scanning = true;
        } else {
            result = drv.parse(argv[i]);
            if (result == 0) {
                std::cout << "Success!" << std::endl;
                drv.scopes.currentScope->print_table();
            } else {
                // tho technically will still see th emessage if parsing
                // succeeds but semantic checks fail, must be clearer on that
                std::cerr << "Parsing failed" << std::endl;
            }
        }
    }
    return result;
}
