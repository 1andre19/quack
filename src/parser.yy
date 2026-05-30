
%skeleton "lalr1.cc" // -*- C++ -*-
%require "3.8.1"
%header

%define api.token.raw

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
  #include <string>
  #include <vector>
  #include <memory>
  #include <iostream>
  #include "Types.h" 
  #include "ast.h"
  class driver;
}

%param { driver& drv }
%locations

%define parse.trace
%define parse.error detailed
%define parse.lac full

%define api.token.prefix {TOK_}

%type <std::vector<std::string>> list_id
%type <Type> tipo
%type <Operator> comp signo

%type <std::unique_ptr<ExprAST>> expresion exp termino factor
%type <std::unique_ptr<CallExpr>> llamada
%type <std::vector<std::unique_ptr<ExprAST>>> args list_expr 

%type <std::unique_ptr<StmntAST>> estatuto asigna ciclo imprime
%type <std::vector<std::unique_ptr<StmntAST>>> adentro cuerpo sino
%type <std::unique_ptr<IfStmnt>> condicion

%type <std::vector<std::unique_ptr<VarDeclStmt>>> vars list_vars 
%type <std::unique_ptr<ParamVarDecl>> param
%type <std::vector<std::unique_ptr<ParamVarDecl>>> parametros list_param
%type <std::unique_ptr<FuncDeclStmt>> funcs
%type <Type> tipo_func

%type <std::vector<std::unique_ptr<FuncDeclStmt>>> funcs.opt
%type <std::vector<std::unique_ptr<VarDeclStmt>>> vars.opt

%type <std::unique_ptr<ExprAST>> cte

%token <std::string>  ID LETRERO 
%token <long> CTE_ENT
%token <double> CTE_FLOT

%token
    PROGRAMA  "programa"
    INICIO    "inicio"
    FIN       "fin"
    VARS      "vars"
    ENT       "entero"
    FLOT      "flotante"
    NULO      "nulo"
    DO        "haz"
    WHILE     "mientras"
    IF        "si"
    ELSE      "sino"
    PRINT     "escribe"

%token
    LPAREN    "("
    RPAREN    ")"
    LBRACE    "{"
    RBRACE    "}"
    LBRACKET  "["
    RBRACKET  "]"
    SEMICOLON ";"
    COMMA     ","
    COLON     ":"
    ASSIGN    "="
    GT        ">"
    LT        "<"
    NEQ       "!="
    EQ        "=="
;

%left PLUS  "+"
%left MINUS "-"
%left TIMES "*"
%left DIV   "/"

%start programa

%code {
  #include "driver.hh"
}

%%

programa:
    PROGRAMA ID ";" vars.opt funcs.opt INICIO cuerpo FIN 
    {
        drv.ast = std::make_unique<ProgramAST>(
            $2,
            std::move($4),
            std::move($5),
            std::move($7)
        );
    }
    ;

funcs.opt:
    funcs funcs.opt
    {
        $2.insert($2.begin(), std::move($1));
        $$ = std::move($2);
    }
  | %empty
    {
        $$ = std::vector<std::unique_ptr<FuncDeclStmt>>();
    }
  ;

cuerpo:
    "{" adentro "}" {
        $$ = std::move($2);
    }
  ;

adentro:
    estatuto adentro {
        $2.insert($2.begin(), std::move($1));
        $$ = std::move($2);
    }
  | %empty 
  {
    $$ = std::vector<std::unique_ptr<StmntAST>>();
  }
  ;

estatuto:
    asigna
    {
    $$ = std::move($1);
    }
  | condicion
  {
    $$ = std::move($1);
  }
  | ciclo
  {
    $$ = std::move($1);
  }
  | llamada ";" 
  {
    $$ = std::make_unique<CallStmt>(std::move($1));
  }
  | imprime
  {
    $$ = std::move($1);
  }
  ;

imprime:
    PRINT "(" imprime_args imprime_mas ")" ";"
    {
        $$ = std::make_unique<PrintStmnt>(
            std::vector<std::unique_ptr<ExprAST>>{},
            std::vector<std::string>{}
        );
    }
  ;

imprime_args:
    expresion
  | LETRERO
  ;

imprime_mas:
    "," imprime_args imprime_mas
  | %empty
  ;

ciclo:
    WHILE "(" expresion ")" DO cuerpo ";"
    {
        $$ = std::make_unique<WhileStmnt>(std::move($3), std::move($6));
    }
  ;

condicion:
    IF "(" expresion ")" cuerpo sino ";"
    {
        $$ = std::make_unique<IfStmnt>(std::move($3), std::move($5), std::move($6));
    }
  ;

sino:
    ELSE cuerpo
    {
        $$ = std::move($2);
    }
  | %empty
  {
    $$ = std::vector<std::unique_ptr<StmntAST>>();
  }
  ;

vars:
    VARS list_vars
    {
        $$ = std::move($2);
    }
  ;

vars.opt:
    vars
    {
        $$ = std::move($1);
    }
  | %empty
  {
    $$ = std::vector<std::unique_ptr<VarDeclStmt>>();
  }
  ;

list_vars:
    ID list_id ":" tipo ";" list_vars
    {
        $2.insert($2.begin(), $1);

        $6.insert($6.begin(), std::make_unique<VarDeclStmt>($2, $4));
        $$ = std::move($6);
    }
    | %empty
    {
        $$ = std::vector<std::unique_ptr<VarDeclStmt>>();
    }
  ;

list_id:
   "," ID list_id
    {
        $$ = std::move($3);
        $$.insert($$.begin(), $2);
    }
    | %empty
    {
        $$ = std::vector<std::string>();
    }
  ;

tipo:
    ENT
    {
        $$ = Type::INT;
    }
  | FLOT
    {
        $$ = Type::FLOAT;
    }
  ;

cte:
    CTE_FLOT
    {
        $$ = std::make_unique<FloatingLiteral>($1);
    }
  | CTE_ENT
    {
        $$ = std::make_unique<IntegerLiteral>($1);
    }

  ;

asigna:
    ID "=" expresion ";" 
    {
        $$ = std::make_unique<AssignmentStmnt>($1, std::move($3));
    }
  ;

expresion:
    exp
    {
        $$ = std::move($1);
    }
  | exp comp exp
  {
    $$ = std::make_unique<BinaryOpExpr>($2, std::move($1), std::move($3));
  }
  ;

exp:
    termino 
    {
        $$ = std::move($1);
    }
  | exp PLUS termino
  {
    $$ = std::make_unique<BinaryOpExpr>(Operator::PLUS, std::move($1), std::move($3));
  }
  | exp MINUS termino
  {
    $$ = std::make_unique<BinaryOpExpr>(Operator::MINUS, std::move($1), std::move($3));
  }

  ;

comp:
    ">"
    {
        $$ = Operator::GT;
    }
  | "<"
    {
        $$ = Operator::LT;
    }

  | "!="
    {
        $$ = Operator::NEQ;
    }

  | "=="
    {
        $$ = Operator::EQ;
    }

  ;

termino:
    factor
    {
        $$ = std::move($1);
    }
  | termino TIMES factor
  {
    $$ = std::make_unique<BinaryOpExpr>(Operator::TIMES, std::move($1), std::move($3));
  }
  | termino DIV factor
  {
    $$ = std::make_unique<BinaryOpExpr>(Operator::DIV, std::move($1), std::move($3));
  }

  ;

factor:
    "(" expresion ")"
    {
        $$ = std::move($2);
    }
  | ID
  {
    $$ = std::make_unique<ReferenceExpr>($1);
  }
  | cte
  {
    $$ = std::move($1);
  }
  | signo ID
  {
    $$ = std::make_unique<UnaryOpExpr>($1, std::make_unique<ReferenceExpr>($2));

  }
  | signo cte
  {
    $$ = std::make_unique<UnaryOpExpr>($1, std::move($2));
  }
  | llamada
  {
    $$ = std::move($1);
  }
  ;

signo:
    "+"
    {
        $$ = Operator::PLUS;
    }
  | "-"
  {
    $$ = Operator::MINUS;
  }
  ;

llamada:
    ID "(" args ")" 
    {
        $$ = std::make_unique<CallExpr>($1, std::move($3));
    }
  ;

args:
    expresion list_expr 
    { 
        $2.insert($2.begin(), std::move($1));
        $$ = std::move($2);
    }
  | %empty 
    { 
        $$ = std::vector<std::unique_ptr<ExprAST>>();
    }
  ;

list_expr:
    "," expresion list_expr 
    {
        $3.insert($3.begin(), std::move($2));
        $$ = std::move($3);
    }
    | %empty
    {
        $$ = std::vector<std::unique_ptr<ExprAST>>();
    }
  ;

funcs:
    tipo_func ID "(" parametros ")" "{" vars.opt cuerpo "}" ";" 
    {
        $$ = std::make_unique<FuncDeclStmt>(std::move($2), std::move($4), $1, std::move($8));     
    }
  ;

parametros:
    param list_param
    {
        $2.insert($2.begin(), std::move($1));
        $$ = std::move($2);
    }
    | %empty
    {
        $$ = std::vector<std::unique_ptr<ParamVarDecl>>();
    }
    ;

param:
     ID ":" tipo
     {
        $$ = std::make_unique<ParamVarDecl>($1, $3);
     }
     ;

list_param:
    "," param list_param
    {
        $3.insert($3.begin(), std::move($2));
        $$ = std::move($3);
    }
    | %empty
    {
        $$ = std::vector<std::unique_ptr<ParamVarDecl>>();
    }
    ;


tipo_func:
    NULO
    {
        $$ = Type::VOID;
    }
  | tipo
    {
        $$ = $1;
    }
  ;

%%

void yy::parser::error(const location_type& l, const std::string& m) {
  std::cerr << l << ": " << m << '\n';
}

