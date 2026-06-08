#include "driver.hh"
#include "astVisitor.h"
#include "const_table.h"
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
    // also need to calculate resources for program
    func_dir.add_entry("global", {}, {}, Type::VOID,
                       0); // start_quad esta mal pero no lousaremos
    MemoryManager mm;
    QuadGenerator gen(func_dir, quads, cube, mm, ct);
    ast->accept(gen);
}
