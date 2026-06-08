#include "custom_errors.h"
#include "driver.hh"
#include "vm.h"

int main(int argc, char *argv[]) {
    std::vector<Quadruple> quads;
    FunctionDirectory func_dir;
    const_table ct;

    {
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
                    // std::cout << "Parsing succeeded" << std::endl;
                    try {
                        drv.compile();
                        /*
                        for (int qi = 0; qi < (int)drv.quads.size(); qi++) {
                            auto &q = drv.quads[qi];
                            std::cout << qi << ": " << q.op << " " << q.arg1
                                      << " " << q.arg2 << " " << q.result
                                      << "\n";
                        }
                        */
                    } catch (const SemanticError &e) {
                        std::cerr << "semantic error: " << e.what() << "\n";
                        return 1;
                    }
                } else {
                    std::cerr << "Parsing failed" << std::endl;
                    return result;
                }
            }
        }

        quads = std::move(drv.quads);
        func_dir = std::move(drv.func_dir);
        ct = std::move(drv.ct);
    }

    VM vm(std::move(quads), func_dir, ct);
    vm.execute();

    return 0;
}
