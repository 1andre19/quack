
%{
#include "driver.hh"
#include "parser.hh"

#define YY_USER_ACTION drv.location.columns(yyleng);
%}

%option noyywrap nounput noinput batch debug

%%

%{
  drv.location.step();
%}

[ \t\r]+        drv.location.step();
\n+             { drv.location.lines(yyleng); drv.location.step(); }

"programa"      return yy::parser::make_PROGRAMA(drv.location);
"inicio"        return yy::parser::make_INICIO(drv.location);
"fin"           return yy::parser::make_FIN(drv.location);
"vars"          return yy::parser::make_VARS(drv.location);
"entero"        return yy::parser::make_ENT(drv.location);
"flotante"      return yy::parser::make_FLOT(drv.location);
"nulo"          return yy::parser::make_NULO(drv.location);
"mientras"      return yy::parser::make_WHILE(drv.location);
"haz"           return yy::parser::make_DO(drv.location);
"si"            return yy::parser::make_IF(drv.location);
"sino"          return yy::parser::make_ELSE(drv.location);
"escribe"       return yy::parser::make_PRINT(drv.location);

"("             return yy::parser::make_LPAREN(drv.location);
")"             return yy::parser::make_RPAREN(drv.location);
"{"             return yy::parser::make_LBRACE(drv.location);
"}"             return yy::parser::make_RBRACE(drv.location);
"["             return yy::parser::make_LBRACKET(drv.location);
"]"             return yy::parser::make_RBRACKET(drv.location);
";"             return yy::parser::make_SEMICOLON(drv.location);
","             return yy::parser::make_COMMA(drv.location);
":"             return yy::parser::make_COLON(drv.location);
"="             return yy::parser::make_ASSIGN(drv.location);
"+"             return yy::parser::make_PLUS(drv.location);
"-"             return yy::parser::make_MINUS(drv.location);
"*"             return yy::parser::make_TIMES(drv.location);
"/"             return yy::parser::make_DIV(drv.location);
">"             return yy::parser::make_GT(drv.location);
"<"             return yy::parser::make_LT(drv.location);
"!="            return yy::parser::make_NEQ(drv.location);
"=="            return yy::parser::make_EQ(drv.location);

[0-9]+"."[0-9]+         return yy::parser::make_CTE_FLOT(std::stod(yytext), drv.location);
[0-9]+                  return yy::parser::make_CTE_ENT(std::stol(yytext), drv.location);
\"[^\"]*\"              return yy::parser::make_LETRERO(yytext, drv.location);
[A-Za-z][A-Za-z0-9_]*  return yy::parser::make_ID(yytext, drv.location);

.   {
      throw yy::parser::syntax_error(drv.location,
        "caracter desconocido: " + std::string(yytext));
    }

<<EOF>>         return yy::parser::make_YYEOF(drv.location);
%%
void driver::scan_begin() {
    yy_flex_debug = trace_scanning;
    if (file.empty() || file == "-")
        yyin = stdin;
    else if (!(yyin = fopen(file.c_str(), "r"))) {
        std::cerr << "cannot open " << file << ": "
                  << strerror(errno) << '\n';
        exit(EXIT_FAILURE);
    }
}

void driver::scan_end() {
    fclose(yyin);
}
