#include "custom_errors.h"
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
                try {
                    drv.compile();

                    for (int qi = 0; qi < (int)drv.quads.size(); qi++) {
                        auto &q = drv.quads[qi];
                        std::cout << qi << ": " << q.op << " " << q.arg1 << " "
                                  << q.arg2 << " " << q.result << "\n";
                    }
                } catch (const SemanticError &e) {
                    std::cerr << "SemanticError: " << e.what() << "\n";
                    return 1;
                }

            } else {
                // tho technically will still see th emessage if parsing
                // succeeds but semantic checks fail, must be clearer on that
                std::cerr << "Parsing failed" << std::endl;
            }
        }
    }
    return result;
}
