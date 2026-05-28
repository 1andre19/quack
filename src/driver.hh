#ifndef DRIVER_HH
#define DRIVER_HH
#include "Scopes.h"
#include "SemanticCube.h"
#include "Types.h"
#include "ast.h"
#include "parser.hh"
#include <memory>
#include <string>

// Give Flex the prototype of yylex we want ...
#define YY_DECL yy::parser::symbol_type yylex(driver &drv)
// ... and declare it for the parser's sake.
YY_DECL;

class driver {
  private:
  public:
    ScopeManager scopes;
    SemanticCube cube;
    Type currType;
    std::unique_ptr<ProgramAST> ast;
    driver();

    int parse(const std::string &f);
    // The name of the file being parsed.
    std::string file;
    // Whether to generate parser debug traces.
    bool trace_parsing;
    void scan_begin();
    void scan_end();
    // Whether to generate scanner debug traces.
    bool trace_scanning;
    // The token's location used by the scanner.
    yy::location location;
    void print_symbol_table();
};
#endif // ! DRIVER_HH
