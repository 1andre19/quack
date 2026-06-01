#include "driver.hh"
#include "astVisitor.h"
#include "parser.hh"

driver::driver()
    : trace_parsing(false), trace_scanning(false), scopes(), cube() {}
int driver::parse(const std::string &f) {
    file = f;
    location.initialize(&file);
    scan_begin();
    yy::parser parse(*this);
    parse.set_debug_level(trace_parsing);
    int res = parse();
    scan_end();
    return res;
}

void driver::compile() {
    if (!ast) {
        std::cout << "No ast" << std::endl;
    }
    func_dir.add_entry("global", {}, Type::VOID);
    QuadGenerator gen(func_dir, quads, cube);
    ast->accept(gen);
}
