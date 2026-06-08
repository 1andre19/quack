// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.hh"


// Unqualified %code blocks.
#line 101 "parser.yy"

  #include "driver.hh"

#line 50 "parser.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 142 "parser.cc"

  /// Build a parser object.
  parser::parser (driver& drv_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false),
      drv (drv_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_comp: // comp
        value.YY_MOVE_OR_COPY< Operator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tipo: // tipo
      case symbol_kind::S_tipo_func: // tipo_func
        value.YY_MOVE_OR_COPY< Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CTE_FLOT: // CTE_FLOT
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CTE_ENT: // CTE_ENT
        value.YY_MOVE_OR_COPY< long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
      case symbol_kind::S_LETRERO: // LETRERO
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_llamada: // llamada
        value.YY_MOVE_OR_COPY< std::unique_ptr<CallExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_imprime_args: // imprime_args
      case symbol_kind::S_cte: // cte
      case symbol_kind::S_expresion: // expresion
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_termino: // termino
      case symbol_kind::S_factor: // factor
        value.YY_MOVE_OR_COPY< std::unique_ptr<ExprAST> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_funcs: // funcs
        value.YY_MOVE_OR_COPY< std::unique_ptr<FuncDeclStmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_condicion: // condicion
        value.YY_MOVE_OR_COPY< std::unique_ptr<IfStmnt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param: // param
        value.YY_MOVE_OR_COPY< std::unique_ptr<ParamVarDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_retorna: // retorna
        value.YY_MOVE_OR_COPY< std::unique_ptr<ReturnStmnt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_estatuto: // estatuto
      case symbol_kind::S_imprime: // imprime
      case symbol_kind::S_ciclo: // ciclo
      case symbol_kind::S_asigna: // asigna
        value.YY_MOVE_OR_COPY< std::unique_ptr<StmntAST> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_list_id: // list_id
        value.YY_MOVE_OR_COPY< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_imprime_mas: // imprime_mas
      case symbol_kind::S_args: // args
      case symbol_kind::S_list_expr: // list_expr
        value.YY_MOVE_OR_COPY< std::vector<std::unique_ptr<ExprAST>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_44_funcs_opt: // funcs.opt
        value.YY_MOVE_OR_COPY< std::vector<std::unique_ptr<FuncDeclStmt>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parametros: // parametros
      case symbol_kind::S_list_param: // list_param
        value.YY_MOVE_OR_COPY< std::vector<std::unique_ptr<ParamVarDecl>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cuerpo: // cuerpo
      case symbol_kind::S_adentro: // adentro
      case symbol_kind::S_sino: // sino
        value.YY_MOVE_OR_COPY< std::vector<std::unique_ptr<StmntAST>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vars: // vars
      case symbol_kind::S_56_vars_opt: // vars.opt
      case symbol_kind::S_list_vars: // list_vars
        value.YY_MOVE_OR_COPY< std::vector<std::unique_ptr<VarDeclStmt>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_comp: // comp
        value.move< Operator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tipo: // tipo
      case symbol_kind::S_tipo_func: // tipo_func
        value.move< Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CTE_FLOT: // CTE_FLOT
        value.move< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CTE_ENT: // CTE_ENT
        value.move< long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
      case symbol_kind::S_LETRERO: // LETRERO
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_llamada: // llamada
        value.move< std::unique_ptr<CallExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_imprime_args: // imprime_args
      case symbol_kind::S_cte: // cte
      case symbol_kind::S_expresion: // expresion
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_termino: // termino
      case symbol_kind::S_factor: // factor
        value.move< std::unique_ptr<ExprAST> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_funcs: // funcs
        value.move< std::unique_ptr<FuncDeclStmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_condicion: // condicion
        value.move< std::unique_ptr<IfStmnt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param: // param
        value.move< std::unique_ptr<ParamVarDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_retorna: // retorna
        value.move< std::unique_ptr<ReturnStmnt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_estatuto: // estatuto
      case symbol_kind::S_imprime: // imprime
      case symbol_kind::S_ciclo: // ciclo
      case symbol_kind::S_asigna: // asigna
        value.move< std::unique_ptr<StmntAST> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_list_id: // list_id
        value.move< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_imprime_mas: // imprime_mas
      case symbol_kind::S_args: // args
      case symbol_kind::S_list_expr: // list_expr
        value.move< std::vector<std::unique_ptr<ExprAST>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_44_funcs_opt: // funcs.opt
        value.move< std::vector<std::unique_ptr<FuncDeclStmt>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parametros: // parametros
      case symbol_kind::S_list_param: // list_param
        value.move< std::vector<std::unique_ptr<ParamVarDecl>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cuerpo: // cuerpo
      case symbol_kind::S_adentro: // adentro
      case symbol_kind::S_sino: // sino
        value.move< std::vector<std::unique_ptr<StmntAST>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vars: // vars
      case symbol_kind::S_56_vars_opt: // vars.opt
      case symbol_kind::S_list_vars: // list_vars
        value.move< std::vector<std::unique_ptr<VarDeclStmt>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_comp: // comp
        value.copy< Operator > (that.value);
        break;

      case symbol_kind::S_tipo: // tipo
      case symbol_kind::S_tipo_func: // tipo_func
        value.copy< Type > (that.value);
        break;

      case symbol_kind::S_CTE_FLOT: // CTE_FLOT
        value.copy< double > (that.value);
        break;

      case symbol_kind::S_CTE_ENT: // CTE_ENT
        value.copy< long > (that.value);
        break;

      case symbol_kind::S_ID: // ID
      case symbol_kind::S_LETRERO: // LETRERO
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_llamada: // llamada
        value.copy< std::unique_ptr<CallExpr> > (that.value);
        break;

      case symbol_kind::S_imprime_args: // imprime_args
      case symbol_kind::S_cte: // cte
      case symbol_kind::S_expresion: // expresion
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_termino: // termino
      case symbol_kind::S_factor: // factor
        value.copy< std::unique_ptr<ExprAST> > (that.value);
        break;

      case symbol_kind::S_funcs: // funcs
        value.copy< std::unique_ptr<FuncDeclStmt> > (that.value);
        break;

      case symbol_kind::S_condicion: // condicion
        value.copy< std::unique_ptr<IfStmnt> > (that.value);
        break;

      case symbol_kind::S_param: // param
        value.copy< std::unique_ptr<ParamVarDecl> > (that.value);
        break;

      case symbol_kind::S_retorna: // retorna
        value.copy< std::unique_ptr<ReturnStmnt> > (that.value);
        break;

      case symbol_kind::S_estatuto: // estatuto
      case symbol_kind::S_imprime: // imprime
      case symbol_kind::S_ciclo: // ciclo
      case symbol_kind::S_asigna: // asigna
        value.copy< std::unique_ptr<StmntAST> > (that.value);
        break;

      case symbol_kind::S_list_id: // list_id
        value.copy< std::vector<std::string> > (that.value);
        break;

      case symbol_kind::S_imprime_mas: // imprime_mas
      case symbol_kind::S_args: // args
      case symbol_kind::S_list_expr: // list_expr
        value.copy< std::vector<std::unique_ptr<ExprAST>> > (that.value);
        break;

      case symbol_kind::S_44_funcs_opt: // funcs.opt
        value.copy< std::vector<std::unique_ptr<FuncDeclStmt>> > (that.value);
        break;

      case symbol_kind::S_parametros: // parametros
      case symbol_kind::S_list_param: // list_param
        value.copy< std::vector<std::unique_ptr<ParamVarDecl>> > (that.value);
        break;

      case symbol_kind::S_cuerpo: // cuerpo
      case symbol_kind::S_adentro: // adentro
      case symbol_kind::S_sino: // sino
        value.copy< std::vector<std::unique_ptr<StmntAST>> > (that.value);
        break;

      case symbol_kind::S_vars: // vars
      case symbol_kind::S_56_vars_opt: // vars.opt
      case symbol_kind::S_list_vars: // list_vars
        value.copy< std::vector<std::unique_ptr<VarDeclStmt>> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_comp: // comp
        value.move< Operator > (that.value);
        break;

      case symbol_kind::S_tipo: // tipo
      case symbol_kind::S_tipo_func: // tipo_func
        value.move< Type > (that.value);
        break;

      case symbol_kind::S_CTE_FLOT: // CTE_FLOT
        value.move< double > (that.value);
        break;

      case symbol_kind::S_CTE_ENT: // CTE_ENT
        value.move< long > (that.value);
        break;

      case symbol_kind::S_ID: // ID
      case symbol_kind::S_LETRERO: // LETRERO
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_llamada: // llamada
        value.move< std::unique_ptr<CallExpr> > (that.value);
        break;

      case symbol_kind::S_imprime_args: // imprime_args
      case symbol_kind::S_cte: // cte
      case symbol_kind::S_expresion: // expresion
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_termino: // termino
      case symbol_kind::S_factor: // factor
        value.move< std::unique_ptr<ExprAST> > (that.value);
        break;

      case symbol_kind::S_funcs: // funcs
        value.move< std::unique_ptr<FuncDeclStmt> > (that.value);
        break;

      case symbol_kind::S_condicion: // condicion
        value.move< std::unique_ptr<IfStmnt> > (that.value);
        break;

      case symbol_kind::S_param: // param
        value.move< std::unique_ptr<ParamVarDecl> > (that.value);
        break;

      case symbol_kind::S_retorna: // retorna
        value.move< std::unique_ptr<ReturnStmnt> > (that.value);
        break;

      case symbol_kind::S_estatuto: // estatuto
      case symbol_kind::S_imprime: // imprime
      case symbol_kind::S_ciclo: // ciclo
      case symbol_kind::S_asigna: // asigna
        value.move< std::unique_ptr<StmntAST> > (that.value);
        break;

      case symbol_kind::S_list_id: // list_id
        value.move< std::vector<std::string> > (that.value);
        break;

      case symbol_kind::S_imprime_mas: // imprime_mas
      case symbol_kind::S_args: // args
      case symbol_kind::S_list_expr: // list_expr
        value.move< std::vector<std::unique_ptr<ExprAST>> > (that.value);
        break;

      case symbol_kind::S_44_funcs_opt: // funcs.opt
        value.move< std::vector<std::unique_ptr<FuncDeclStmt>> > (that.value);
        break;

      case symbol_kind::S_parametros: // parametros
      case symbol_kind::S_list_param: // list_param
        value.move< std::vector<std::unique_ptr<ParamVarDecl>> > (that.value);
        break;

      case symbol_kind::S_cuerpo: // cuerpo
      case symbol_kind::S_adentro: // adentro
      case symbol_kind::S_sino: // sino
        value.move< std::vector<std::unique_ptr<StmntAST>> > (that.value);
        break;

      case symbol_kind::S_vars: // vars
      case symbol_kind::S_56_vars_opt: // vars.opt
      case symbol_kind::S_list_vars: // list_vars
        value.move< std::vector<std::unique_ptr<VarDeclStmt>> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // Discard the LAC context in case there still is one left from a
    // previous invocation.
    yy_lac_discard_ ("init");

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (drv));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        if (!yy_lac_establish_ (yyla.kind ()))
          goto yyerrlab;
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        if (!yy_lac_establish_ (yyla.kind ()))
          goto yyerrlab;

        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    yy_lac_discard_ ("shift");
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_comp: // comp
        yylhs.value.emplace< Operator > ();
        break;

      case symbol_kind::S_tipo: // tipo
      case symbol_kind::S_tipo_func: // tipo_func
        yylhs.value.emplace< Type > ();
        break;

      case symbol_kind::S_CTE_FLOT: // CTE_FLOT
        yylhs.value.emplace< double > ();
        break;

      case symbol_kind::S_CTE_ENT: // CTE_ENT
        yylhs.value.emplace< long > ();
        break;

      case symbol_kind::S_ID: // ID
      case symbol_kind::S_LETRERO: // LETRERO
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_llamada: // llamada
        yylhs.value.emplace< std::unique_ptr<CallExpr> > ();
        break;

      case symbol_kind::S_imprime_args: // imprime_args
      case symbol_kind::S_cte: // cte
      case symbol_kind::S_expresion: // expresion
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_termino: // termino
      case symbol_kind::S_factor: // factor
        yylhs.value.emplace< std::unique_ptr<ExprAST> > ();
        break;

      case symbol_kind::S_funcs: // funcs
        yylhs.value.emplace< std::unique_ptr<FuncDeclStmt> > ();
        break;

      case symbol_kind::S_condicion: // condicion
        yylhs.value.emplace< std::unique_ptr<IfStmnt> > ();
        break;

      case symbol_kind::S_param: // param
        yylhs.value.emplace< std::unique_ptr<ParamVarDecl> > ();
        break;

      case symbol_kind::S_retorna: // retorna
        yylhs.value.emplace< std::unique_ptr<ReturnStmnt> > ();
        break;

      case symbol_kind::S_estatuto: // estatuto
      case symbol_kind::S_imprime: // imprime
      case symbol_kind::S_ciclo: // ciclo
      case symbol_kind::S_asigna: // asigna
        yylhs.value.emplace< std::unique_ptr<StmntAST> > ();
        break;

      case symbol_kind::S_list_id: // list_id
        yylhs.value.emplace< std::vector<std::string> > ();
        break;

      case symbol_kind::S_imprime_mas: // imprime_mas
      case symbol_kind::S_args: // args
      case symbol_kind::S_list_expr: // list_expr
        yylhs.value.emplace< std::vector<std::unique_ptr<ExprAST>> > ();
        break;

      case symbol_kind::S_44_funcs_opt: // funcs.opt
        yylhs.value.emplace< std::vector<std::unique_ptr<FuncDeclStmt>> > ();
        break;

      case symbol_kind::S_parametros: // parametros
      case symbol_kind::S_list_param: // list_param
        yylhs.value.emplace< std::vector<std::unique_ptr<ParamVarDecl>> > ();
        break;

      case symbol_kind::S_cuerpo: // cuerpo
      case symbol_kind::S_adentro: // adentro
      case symbol_kind::S_sino: // sino
        yylhs.value.emplace< std::vector<std::unique_ptr<StmntAST>> > ();
        break;

      case symbol_kind::S_vars: // vars
      case symbol_kind::S_56_vars_opt: // vars.opt
      case symbol_kind::S_list_vars: // list_vars
        yylhs.value.emplace< std::vector<std::unique_ptr<VarDeclStmt>> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // programa: "programa" ID ";" vars.opt funcs.opt "inicio" cuerpo "fin"
#line 109 "parser.yy"
    {
        drv.ast = std::make_unique<ProgramAST>(
            yystack_[6].value.as < std::string > (),
            std::move(yystack_[4].value.as < std::vector<std::unique_ptr<VarDeclStmt>> > ()),
            std::move(yystack_[3].value.as < std::vector<std::unique_ptr<FuncDeclStmt>> > ()),
            std::move(yystack_[1].value.as < std::vector<std::unique_ptr<StmntAST>> > ())
        );
    }
#line 999 "parser.cc"
    break;

  case 3: // funcs.opt: funcs funcs.opt
#line 121 "parser.yy"
    {
        yystack_[0].value.as < std::vector<std::unique_ptr<FuncDeclStmt>> > ().insert(yystack_[0].value.as < std::vector<std::unique_ptr<FuncDeclStmt>> > ().begin(), std::move(yystack_[1].value.as < std::unique_ptr<FuncDeclStmt> > ()));
        yylhs.value.as < std::vector<std::unique_ptr<FuncDeclStmt>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<FuncDeclStmt>> > ());
    }
#line 1008 "parser.cc"
    break;

  case 4: // funcs.opt: %empty
#line 126 "parser.yy"
    {
        yylhs.value.as < std::vector<std::unique_ptr<FuncDeclStmt>> > () = std::vector<std::unique_ptr<FuncDeclStmt>>();
    }
#line 1016 "parser.cc"
    break;

  case 5: // cuerpo: "{" adentro "}"
#line 132 "parser.yy"
                    {
        yylhs.value.as < std::vector<std::unique_ptr<StmntAST>> > () = std::move(yystack_[1].value.as < std::vector<std::unique_ptr<StmntAST>> > ());
    }
#line 1024 "parser.cc"
    break;

  case 6: // adentro: estatuto adentro
#line 138 "parser.yy"
                     {
        yystack_[0].value.as < std::vector<std::unique_ptr<StmntAST>> > ().insert(yystack_[0].value.as < std::vector<std::unique_ptr<StmntAST>> > ().begin(), std::move(yystack_[1].value.as < std::unique_ptr<StmntAST> > ()));
        yylhs.value.as < std::vector<std::unique_ptr<StmntAST>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<StmntAST>> > ());
    }
#line 1033 "parser.cc"
    break;

  case 7: // adentro: %empty
#line 143 "parser.yy"
  {
    yylhs.value.as < std::vector<std::unique_ptr<StmntAST>> > () = std::vector<std::unique_ptr<StmntAST>>();
  }
#line 1041 "parser.cc"
    break;

  case 8: // estatuto: asigna
#line 150 "parser.yy"
    {
    yylhs.value.as < std::unique_ptr<StmntAST> > () = std::move(yystack_[0].value.as < std::unique_ptr<StmntAST> > ());
    }
#line 1049 "parser.cc"
    break;

  case 9: // estatuto: condicion
#line 154 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<StmntAST> > () = std::move(yystack_[0].value.as < std::unique_ptr<IfStmnt> > ());
  }
#line 1057 "parser.cc"
    break;

  case 10: // estatuto: ciclo
#line 158 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<StmntAST> > () = std::move(yystack_[0].value.as < std::unique_ptr<StmntAST> > ());
  }
#line 1065 "parser.cc"
    break;

  case 11: // estatuto: llamada ";"
#line 162 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<StmntAST> > () = std::make_unique<CallStmt>(std::move(yystack_[1].value.as < std::unique_ptr<CallExpr> > ()));
  }
#line 1073 "parser.cc"
    break;

  case 12: // estatuto: imprime ";"
#line 166 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<StmntAST> > () = std::move(yystack_[1].value.as < std::unique_ptr<StmntAST> > ());
  }
#line 1081 "parser.cc"
    break;

  case 13: // estatuto: retorna ";"
#line 170 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<StmntAST> > () = std::move(yystack_[1].value.as < std::unique_ptr<ReturnStmnt> > ());
  }
#line 1089 "parser.cc"
    break;

  case 14: // retorna: "retorna" expresion
#line 177 "parser.yy"
       {
            yylhs.value.as < std::unique_ptr<ReturnStmnt> > () = std::make_unique<ReturnStmnt>(std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ()));
       }
#line 1097 "parser.cc"
    break;

  case 15: // imprime: "escribe" "(" imprime_args imprime_mas ")"
#line 184 "parser.yy"
    {
        yystack_[1].value.as < std::vector<std::unique_ptr<ExprAST>> > ().insert(yystack_[1].value.as < std::vector<std::unique_ptr<ExprAST>> > ().begin(), std::move(yystack_[2].value.as < std::unique_ptr<ExprAST> > ()));
        yylhs.value.as < std::unique_ptr<StmntAST> > () = std::make_unique<PrintStmnt>(
            std::move(yystack_[1].value.as < std::vector<std::unique_ptr<ExprAST>> > ())
        );
    }
#line 1108 "parser.cc"
    break;

  case 16: // imprime_args: expresion
#line 194 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<ExprAST> > () = std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ());
    }
#line 1116 "parser.cc"
    break;

  case 17: // imprime_args: LETRERO
#line 198 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<ExprAST> > () = std::make_unique<StringLiteral>(yystack_[0].value.as < std::string > ());
    }
#line 1124 "parser.cc"
    break;

  case 18: // imprime_mas: "," imprime_args imprime_mas
#line 205 "parser.yy"
    {
        yystack_[0].value.as < std::vector<std::unique_ptr<ExprAST>> > ().insert(yystack_[0].value.as < std::vector<std::unique_ptr<ExprAST>> > ().begin(), std::move(yystack_[1].value.as < std::unique_ptr<ExprAST> > ()));
        yylhs.value.as < std::vector<std::unique_ptr<ExprAST>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<ExprAST>> > ());
    }
#line 1133 "parser.cc"
    break;

  case 19: // imprime_mas: %empty
#line 210 "parser.yy"
  {
    yylhs.value.as < std::vector<std::unique_ptr<ExprAST>> > () = std::vector<std::unique_ptr<ExprAST>>();
  }
#line 1141 "parser.cc"
    break;

  case 20: // ciclo: "mientras" "(" expresion ")" "haz" cuerpo ";"
#line 217 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<StmntAST> > () = std::make_unique<WhileStmnt>(std::move(yystack_[4].value.as < std::unique_ptr<ExprAST> > ()), std::move(yystack_[1].value.as < std::vector<std::unique_ptr<StmntAST>> > ()));
    }
#line 1149 "parser.cc"
    break;

  case 21: // condicion: "si" "(" expresion ")" cuerpo sino ";"
#line 224 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<IfStmnt> > () = std::make_unique<IfStmnt>(std::move(yystack_[4].value.as < std::unique_ptr<ExprAST> > ()), std::move(yystack_[2].value.as < std::vector<std::unique_ptr<StmntAST>> > ()), std::move(yystack_[1].value.as < std::vector<std::unique_ptr<StmntAST>> > ()));
    }
#line 1157 "parser.cc"
    break;

  case 22: // sino: "sino" cuerpo
#line 231 "parser.yy"
    {
        yylhs.value.as < std::vector<std::unique_ptr<StmntAST>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<StmntAST>> > ());
    }
#line 1165 "parser.cc"
    break;

  case 23: // sino: %empty
#line 235 "parser.yy"
  {
    yylhs.value.as < std::vector<std::unique_ptr<StmntAST>> > () = std::vector<std::unique_ptr<StmntAST>>();
  }
#line 1173 "parser.cc"
    break;

  case 24: // vars: "vars" list_vars
#line 242 "parser.yy"
    {
        yylhs.value.as < std::vector<std::unique_ptr<VarDeclStmt>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<VarDeclStmt>> > ());
    }
#line 1181 "parser.cc"
    break;

  case 25: // vars.opt: vars
#line 249 "parser.yy"
    {
        yylhs.value.as < std::vector<std::unique_ptr<VarDeclStmt>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<VarDeclStmt>> > ());
    }
#line 1189 "parser.cc"
    break;

  case 26: // vars.opt: %empty
#line 253 "parser.yy"
  {
    yylhs.value.as < std::vector<std::unique_ptr<VarDeclStmt>> > () = std::vector<std::unique_ptr<VarDeclStmt>>();
  }
#line 1197 "parser.cc"
    break;

  case 27: // list_vars: ID list_id ":" tipo ";" list_vars
#line 260 "parser.yy"
    {
        yystack_[4].value.as < std::vector<std::string> > ().insert(yystack_[4].value.as < std::vector<std::string> > ().begin(), yystack_[5].value.as < std::string > ());

        yystack_[0].value.as < std::vector<std::unique_ptr<VarDeclStmt>> > ().insert(yystack_[0].value.as < std::vector<std::unique_ptr<VarDeclStmt>> > ().begin(), std::make_unique<VarDeclStmt>(yystack_[4].value.as < std::vector<std::string> > (), yystack_[2].value.as < Type > ()));
        yylhs.value.as < std::vector<std::unique_ptr<VarDeclStmt>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<VarDeclStmt>> > ());
    }
#line 1208 "parser.cc"
    break;

  case 28: // list_vars: %empty
#line 267 "parser.yy"
    {
        yylhs.value.as < std::vector<std::unique_ptr<VarDeclStmt>> > () = std::vector<std::unique_ptr<VarDeclStmt>>();
    }
#line 1216 "parser.cc"
    break;

  case 29: // list_id: "," ID list_id
#line 274 "parser.yy"
    {
        yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[0].value.as < std::vector<std::string> > ());
        yylhs.value.as < std::vector<std::string> > ().insert(yylhs.value.as < std::vector<std::string> > ().begin(), yystack_[1].value.as < std::string > ());
    }
#line 1225 "parser.cc"
    break;

  case 30: // list_id: %empty
#line 279 "parser.yy"
    {
        yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>();
    }
#line 1233 "parser.cc"
    break;

  case 31: // tipo: "entero"
#line 286 "parser.yy"
    {
        yylhs.value.as < Type > () = Type::INT;
    }
#line 1241 "parser.cc"
    break;

  case 32: // tipo: "flotante"
#line 290 "parser.yy"
    {
        yylhs.value.as < Type > () = Type::FLOAT;
    }
#line 1249 "parser.cc"
    break;

  case 33: // cte: CTE_FLOT
#line 297 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<ExprAST> > () = std::make_unique<FloatingLiteral>(yystack_[0].value.as < double > ());
    }
#line 1257 "parser.cc"
    break;

  case 34: // cte: CTE_ENT
#line 301 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<ExprAST> > () = std::make_unique<IntegerLiteral>(yystack_[0].value.as < long > ());
    }
#line 1265 "parser.cc"
    break;

  case 35: // asigna: ID "=" expresion ";"
#line 309 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<StmntAST> > () = std::make_unique<AssignmentStmnt>(yystack_[3].value.as < std::string > (), std::move(yystack_[1].value.as < std::unique_ptr<ExprAST> > ()));
    }
#line 1273 "parser.cc"
    break;

  case 36: // expresion: exp
#line 316 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<ExprAST> > () = std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ());
    }
#line 1281 "parser.cc"
    break;

  case 37: // expresion: exp comp exp
#line 320 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<ExprAST> > () = std::make_unique<BinaryOpExpr>(yystack_[1].value.as < Operator > (), std::move(yystack_[2].value.as < std::unique_ptr<ExprAST> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ()));
  }
#line 1289 "parser.cc"
    break;

  case 38: // exp: termino
#line 327 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<ExprAST> > () = std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ());
    }
#line 1297 "parser.cc"
    break;

  case 39: // exp: exp PLUS termino
#line 331 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<ExprAST> > () = std::make_unique<BinaryOpExpr>(Operator::PLUS, std::move(yystack_[2].value.as < std::unique_ptr<ExprAST> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ()));
  }
#line 1305 "parser.cc"
    break;

  case 40: // exp: exp MINUS termino
#line 335 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<ExprAST> > () = std::make_unique<BinaryOpExpr>(Operator::MINUS, std::move(yystack_[2].value.as < std::unique_ptr<ExprAST> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ()));
  }
#line 1313 "parser.cc"
    break;

  case 41: // comp: ">"
#line 343 "parser.yy"
    {
        yylhs.value.as < Operator > () = Operator::GT;
    }
#line 1321 "parser.cc"
    break;

  case 42: // comp: "<"
#line 347 "parser.yy"
    {
        yylhs.value.as < Operator > () = Operator::LT;
    }
#line 1329 "parser.cc"
    break;

  case 43: // comp: "!="
#line 352 "parser.yy"
    {
        yylhs.value.as < Operator > () = Operator::NEQ;
    }
#line 1337 "parser.cc"
    break;

  case 44: // comp: "=="
#line 357 "parser.yy"
    {
        yylhs.value.as < Operator > () = Operator::EQ;
    }
#line 1345 "parser.cc"
    break;

  case 45: // termino: factor
#line 365 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<ExprAST> > () = std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ());
    }
#line 1353 "parser.cc"
    break;

  case 46: // termino: termino TIMES factor
#line 369 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<ExprAST> > () = std::make_unique<BinaryOpExpr>(Operator::TIMES, std::move(yystack_[2].value.as < std::unique_ptr<ExprAST> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ()));
  }
#line 1361 "parser.cc"
    break;

  case 47: // termino: termino DIV factor
#line 373 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<ExprAST> > () = std::make_unique<BinaryOpExpr>(Operator::DIV, std::move(yystack_[2].value.as < std::unique_ptr<ExprAST> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ()));
  }
#line 1369 "parser.cc"
    break;

  case 48: // factor: PLUS factor
#line 381 "parser.yy"
      {
        yylhs.value.as < std::unique_ptr<ExprAST> > () = std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ());
      }
#line 1377 "parser.cc"
    break;

  case 49: // factor: MINUS factor
#line 385 "parser.yy"
      {
            yylhs.value.as < std::unique_ptr<ExprAST> > () = std::make_unique<UnaryOpExpr>(
            Operator::MINUS,
            std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ())
        );
      }
#line 1388 "parser.cc"
    break;

  case 50: // factor: "(" expresion ")"
#line 392 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<ExprAST> > () = std::move(yystack_[1].value.as < std::unique_ptr<ExprAST> > ());
    }
#line 1396 "parser.cc"
    break;

  case 51: // factor: ID
#line 396 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<ExprAST> > () = std::make_unique<ReferenceExpr>(yystack_[0].value.as < std::string > ());
  }
#line 1404 "parser.cc"
    break;

  case 52: // factor: cte
#line 400 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<ExprAST> > () = std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ());
  }
#line 1412 "parser.cc"
    break;

  case 53: // factor: llamada
#line 404 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<ExprAST> > () = std::move(yystack_[0].value.as < std::unique_ptr<CallExpr> > ());
  }
#line 1420 "parser.cc"
    break;

  case 54: // llamada: ID "(" args ")"
#line 422 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<CallExpr> > () = std::make_unique<CallExpr>(yystack_[3].value.as < std::string > (), std::move(yystack_[1].value.as < std::vector<std::unique_ptr<ExprAST>> > ()));
    }
#line 1428 "parser.cc"
    break;

  case 55: // args: expresion list_expr
#line 429 "parser.yy"
    { 
        yystack_[0].value.as < std::vector<std::unique_ptr<ExprAST>> > ().insert(yystack_[0].value.as < std::vector<std::unique_ptr<ExprAST>> > ().begin(), std::move(yystack_[1].value.as < std::unique_ptr<ExprAST> > ()));
        yylhs.value.as < std::vector<std::unique_ptr<ExprAST>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<ExprAST>> > ());
    }
#line 1437 "parser.cc"
    break;

  case 56: // args: %empty
#line 434 "parser.yy"
    { 
        yylhs.value.as < std::vector<std::unique_ptr<ExprAST>> > () = std::vector<std::unique_ptr<ExprAST>>();
    }
#line 1445 "parser.cc"
    break;

  case 57: // list_expr: "," expresion list_expr
#line 441 "parser.yy"
    {
        yystack_[0].value.as < std::vector<std::unique_ptr<ExprAST>> > ().insert(yystack_[0].value.as < std::vector<std::unique_ptr<ExprAST>> > ().begin(), std::move(yystack_[1].value.as < std::unique_ptr<ExprAST> > ()));
        yylhs.value.as < std::vector<std::unique_ptr<ExprAST>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<ExprAST>> > ());
    }
#line 1454 "parser.cc"
    break;

  case 58: // list_expr: %empty
#line 446 "parser.yy"
    {
        yylhs.value.as < std::vector<std::unique_ptr<ExprAST>> > () = std::vector<std::unique_ptr<ExprAST>>();
    }
#line 1462 "parser.cc"
    break;

  case 59: // funcs: tipo_func ID "(" parametros ")" "{" vars.opt cuerpo "}" ";"
#line 453 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<FuncDeclStmt> > () = std::make_unique<FuncDeclStmt>(std::move(yystack_[8].value.as < std::string > ()), std::move(yystack_[6].value.as < std::vector<std::unique_ptr<ParamVarDecl>> > ()), std::move(yystack_[3].value.as < std::vector<std::unique_ptr<VarDeclStmt>> > ()), yystack_[9].value.as < Type > (), std::move(yystack_[2].value.as < std::vector<std::unique_ptr<StmntAST>> > ()));     
    }
#line 1470 "parser.cc"
    break;

  case 60: // parametros: param list_param
#line 460 "parser.yy"
    {
        yystack_[0].value.as < std::vector<std::unique_ptr<ParamVarDecl>> > ().insert(yystack_[0].value.as < std::vector<std::unique_ptr<ParamVarDecl>> > ().begin(), std::move(yystack_[1].value.as < std::unique_ptr<ParamVarDecl> > ()));
        yylhs.value.as < std::vector<std::unique_ptr<ParamVarDecl>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<ParamVarDecl>> > ());
    }
#line 1479 "parser.cc"
    break;

  case 61: // parametros: %empty
#line 465 "parser.yy"
    {
        yylhs.value.as < std::vector<std::unique_ptr<ParamVarDecl>> > () = std::vector<std::unique_ptr<ParamVarDecl>>();
    }
#line 1487 "parser.cc"
    break;

  case 62: // param: ID ":" tipo
#line 472 "parser.yy"
     {
        yylhs.value.as < std::unique_ptr<ParamVarDecl> > () = std::make_unique<ParamVarDecl>(yystack_[2].value.as < std::string > (), yystack_[0].value.as < Type > ());
     }
#line 1495 "parser.cc"
    break;

  case 63: // list_param: "," param list_param
#line 479 "parser.yy"
    {
        yystack_[0].value.as < std::vector<std::unique_ptr<ParamVarDecl>> > ().insert(yystack_[0].value.as < std::vector<std::unique_ptr<ParamVarDecl>> > ().begin(), std::move(yystack_[1].value.as < std::unique_ptr<ParamVarDecl> > ()));
        yylhs.value.as < std::vector<std::unique_ptr<ParamVarDecl>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<ParamVarDecl>> > ());
    }
#line 1504 "parser.cc"
    break;

  case 64: // list_param: %empty
#line 484 "parser.yy"
    {
        yylhs.value.as < std::vector<std::unique_ptr<ParamVarDecl>> > () = std::vector<std::unique_ptr<ParamVarDecl>>();
    }
#line 1512 "parser.cc"
    break;

  case 65: // tipo_func: "nulo"
#line 492 "parser.yy"
    {
        yylhs.value.as < Type > () = Type::VOID;
    }
#line 1520 "parser.cc"
    break;

  case 66: // tipo_func: tipo
#line 496 "parser.yy"
    {
        yylhs.value.as < Type > () = yystack_[0].value.as < Type > ();
    }
#line 1528 "parser.cc"
    break;


#line 1532 "parser.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      yy_lac_discard_ ("error recovery");
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    static const char *const yy_sname[] =
    {
    "end of file", "error", "invalid token", "ID", "LETRERO", "CTE_ENT",
  "CTE_FLOT", "programa", "inicio", "fin", "vars", "entero", "flotante",
  "nulo", "haz", "mientras", "si", "sino", "escribe", "retorna", "(", ")",
  "{", "}", "[", "]", ";", ",", ":", "=", ">", "<", "!=", "==", "PLUS",
  "+", "MINUS", "-", "TIMES", "*", "DIV", "/", "$accept", "programa",
  "funcs.opt", "cuerpo", "adentro", "estatuto", "retorna", "imprime",
  "imprime_args", "imprime_mas", "ciclo", "condicion", "sino", "vars",
  "vars.opt", "list_vars", "list_id", "tipo", "cte", "asigna", "expresion",
  "exp", "comp", "termino", "factor", "llamada", "args", "list_expr",
  "funcs", "parametros", "param", "list_param", "tipo_func", YY_NULLPTR
    };
    return yy_sname[yysymbol];
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

#if YYDEBUG
    // Execute LAC once. We don't care if it is successful, we
    // only do it for the sake of debugging output.
    if (!yyparser_.yy_lac_established_)
      yyparser_.yy_lac_check_ (yyla_.kind ());
#endif

    for (int yyx = 0; yyx < YYNTOKENS; ++yyx)
      {
        symbol_kind_type yysym = YY_CAST (symbol_kind_type, yyx);
        if (yysym != symbol_kind::S_YYerror
            && yysym != symbol_kind::S_YYUNDEF
            && yyparser_.yy_lac_check_ (yysym))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
          }
      }
    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }




  bool
  parser::yy_lac_check_ (symbol_kind_type yytoken) const
  {
    // Logically, the yylac_stack's lifetime is confined to this function.
    // Clear it, to get rid of potential left-overs from previous call.
    yylac_stack_.clear ();
    // Reduce until we encounter a shift and thereby accept the token.
#if YYDEBUG
    YYCDEBUG << "LAC: checking lookahead " << symbol_name (yytoken) << ':';
#endif
    std::ptrdiff_t lac_top = 0;
    while (true)
      {
        state_type top_state = (yylac_stack_.empty ()
                                ? yystack_[lac_top].state
                                : yylac_stack_.back ());
        int yyrule = yypact_[+top_state];
        if (yy_pact_value_is_default_ (yyrule)
            || (yyrule += yytoken) < 0 || yylast_ < yyrule
            || yycheck_[yyrule] != yytoken)
          {
            // Use the default action.
            yyrule = yydefact_[+top_state];
            if (yyrule == 0)
              {
                YYCDEBUG << " Err\n";
                return false;
              }
          }
        else
          {
            // Use the action from yytable.
            yyrule = yytable_[yyrule];
            if (yy_table_value_is_error_ (yyrule))
              {
                YYCDEBUG << " Err\n";
                return false;
              }
            if (0 < yyrule)
              {
                YYCDEBUG << " S" << yyrule << '\n';
                return true;
              }
            yyrule = -yyrule;
          }
        // By now we know we have to simulate a reduce.
        YYCDEBUG << " R" << yyrule - 1;
        // Pop the corresponding number of values from the stack.
        {
          std::ptrdiff_t yylen = yyr2_[yyrule];
          // First pop from the LAC stack as many tokens as possible.
          std::ptrdiff_t lac_size = std::ptrdiff_t (yylac_stack_.size ());
          if (yylen < lac_size)
            {
              yylac_stack_.resize (std::size_t (lac_size - yylen));
              yylen = 0;
            }
          else if (lac_size)
            {
              yylac_stack_.clear ();
              yylen -= lac_size;
            }
          // Only afterwards look at the main stack.
          // We simulate popping elements by incrementing lac_top.
          lac_top += yylen;
        }
        // Keep top_state in sync with the updated stack.
        top_state = (yylac_stack_.empty ()
                     ? yystack_[lac_top].state
                     : yylac_stack_.back ());
        // Push the resulting state of the reduction.
        state_type state = yy_lr_goto_state_ (top_state, yyr1_[yyrule]);
        YYCDEBUG << " G" << int (state);
        yylac_stack_.push_back (state);
      }
  }

  // Establish the initial context if no initial context currently exists.
  bool
  parser::yy_lac_establish_ (symbol_kind_type yytoken)
  {
    /* Establish the initial context for the current lookahead if no initial
       context is currently established.

       We define a context as a snapshot of the parser stacks.  We define
       the initial context for a lookahead as the context in which the
       parser initially examines that lookahead in order to select a
       syntactic action.  Thus, if the lookahead eventually proves
       syntactically unacceptable (possibly in a later context reached via a
       series of reductions), the initial context can be used to determine
       the exact set of tokens that would be syntactically acceptable in the
       lookahead's place.  Moreover, it is the context after which any
       further semantic actions would be erroneous because they would be
       determined by a syntactically unacceptable token.

       yy_lac_establish_ should be invoked when a reduction is about to be
       performed in an inconsistent state (which, for the purposes of LAC,
       includes consistent states that don't know they're consistent because
       their default reductions have been disabled).

       For parse.lac=full, the implementation of yy_lac_establish_ is as
       follows.  If no initial context is currently established for the
       current lookahead, then check if that lookahead can eventually be
       shifted if syntactic actions continue from the current context.  */
    if (yy_lac_established_)
      return true;
    else
      {
#if YYDEBUG
        YYCDEBUG << "LAC: initial context established for "
                 << symbol_name (yytoken) << '\n';
#endif
        yy_lac_established_ = true;
        return yy_lac_check_ (yytoken);
      }
  }

  // Discard any previous initial lookahead context.
  void
  parser::yy_lac_discard_ (const char* event)
  {
   /* Discard any previous initial lookahead context because of Event,
      which may be a lookahead change or an invalidation of the currently
      established initial context for the current lookahead.

      The most common example of a lookahead change is a shift.  An example
      of both cases is syntax error recovery.  That is, a syntax error
      occurs when the lookahead is syntactically erroneous for the
      currently established initial context, so error recovery manipulates
      the parser stacks to try to find a new initial context in which the
      current lookahead is syntactically acceptable.  If it fails to find
      such a context, it discards the lookahead.  */
    if (yy_lac_established_)
      {
        YYCDEBUG << "LAC: initial context discarded due to "
                 << event << '\n';
        yy_lac_established_ = false;
      }
  }


  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
         In the first two cases, it might appear that the current syntax
         error should have been detected in the previous state when
         yy_lac_check was invoked.  However, at that time, there might
         have been a different syntax error that discarded a different
         initial context during error recovery, leaving behind the
         current lookahead.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -80;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
       3,    31,    13,    -6,   -80,    35,    47,   -80,    17,    24,
     -80,   -80,   -80,   -80,    44,   -80,    17,    52,    55,    39,
      46,   -80,    49,    24,    20,    38,    57,    67,   -80,    45,
      -2,    53,    54,    56,     6,    58,    38,    51,    59,   -80,
     -80,   -80,    60,   -80,    50,    61,    48,    47,     6,     6,
       6,     6,     1,    63,   -80,   -80,     6,     6,     6,   -80,
     -80,    29,   -15,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
      20,    62,    67,   -80,   -80,    64,    66,    68,    69,    71,
     -80,    70,   -80,    72,   -80,   -80,   -80,   -80,   -80,   -80,
       6,     6,     6,     6,     6,   -80,    35,    48,     6,   -80,
     -80,   -80,    65,    46,     1,    74,   -80,   -15,   -15,    10,
     -80,   -80,    46,   -80,    64,    46,    79,    70,   -80,    75,
     -80,    73,    46,    76,   -80,    77,   -80,   -80,   -80,   -80
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     1,    26,    28,    25,     4,    30,
      24,    31,    32,    65,     0,    66,     4,     0,     0,     0,
       0,     3,     0,    30,     0,     7,     0,    61,    29,     0,
       0,     0,     0,     0,     0,     0,     7,     0,     0,    10,
       9,     8,     0,     2,     0,     0,    64,    28,    56,     0,
       0,     0,     0,    51,    34,    33,     0,     0,     0,    52,
      14,    36,    38,    45,    53,     5,     6,    13,    12,    11,
       0,     0,     0,    60,    27,    58,     0,     0,     0,     0,
      17,    19,    16,     0,    48,    49,    41,    42,    43,    44,
       0,     0,     0,     0,     0,    62,    26,    64,     0,    55,
      54,    35,     0,     0,     0,     0,    50,    39,    40,    37,
      46,    47,     0,    63,    58,     0,    23,    19,    15,     0,
      57,     0,     0,     0,    18,     0,    20,    22,    21,    59
  };

  const signed char
  parser::yypgoto_[] =
  {
     -80,   -80,    84,   -79,    36,   -80,   -80,   -80,   -24,   -29,
     -80,   -80,   -80,   -80,    -7,    78,    81,   -23,   -80,   -80,
     -34,     9,   -80,   -42,   -55,   -17,   -80,    -9,   -80,   -80,
      34,    11,   -80
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,     2,    14,    26,    35,    36,    37,    38,    81,   105,
      39,    40,   123,     7,     8,    10,    19,    15,    59,    41,
      82,    61,    92,    62,    63,    64,    76,    99,    16,    45,
      46,    73,    17
  };

  const unsigned char
  parser::yytable_[] =
  {
      60,    29,    84,    85,    53,    80,    54,    55,    42,    53,
       1,    54,    55,     4,    75,    77,    78,    79,    48,    42,
       5,    56,    83,    93,   116,    94,    56,    49,    11,    12,
      13,    11,    12,   119,     3,    57,   121,    58,   110,   111,
      57,    30,    58,   127,    90,     6,    91,    95,   107,   108,
       9,    18,    20,    31,    32,    22,    33,    34,    23,    86,
      87,    88,    89,    90,   114,    91,    43,    24,    25,    27,
      44,    47,    66,    50,    51,    72,    52,    67,    70,   115,
     117,    65,    71,    48,    96,    68,    69,   100,   124,   112,
     102,    98,   103,   106,   101,   118,   122,   104,   125,   126,
      21,   109,   128,   129,    28,   120,    97,     0,   113,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    74
  };

  const signed char
  parser::yycheck_[] =
  {
      34,    24,    57,    58,     3,     4,     5,     6,    25,     3,
       7,     5,     6,     0,    48,    49,    50,    51,    20,    36,
      26,    20,    56,    38,   103,    40,    20,    29,    11,    12,
      13,    11,    12,   112,     3,    34,   115,    36,    93,    94,
      34,     3,    36,   122,    34,    10,    36,    70,    90,    91,
       3,    27,     8,    15,    16,     3,    18,    19,     3,    30,
      31,    32,    33,    34,    98,    36,     9,    28,    22,    20,
       3,    26,    36,    20,    20,    27,    20,    26,    28,    14,
     104,    23,    21,    20,    22,    26,    26,    21,   117,    96,
      21,    27,    21,    21,    26,    21,    17,    27,    23,    26,
      16,    92,    26,    26,    23,   114,    72,    -1,    97,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47
  };

  const signed char
  parser::yystos_[] =
  {
       0,     7,    43,     3,     0,    26,    10,    55,    56,     3,
      57,    11,    12,    13,    44,    59,    70,    74,    27,    58,
       8,    44,     3,     3,    28,    22,    45,    20,    58,    59,
       3,    15,    16,    18,    19,    46,    47,    48,    49,    52,
      53,    61,    67,     9,     3,    71,    72,    26,    20,    29,
      20,    20,    20,     3,     5,     6,    20,    34,    36,    60,
      62,    63,    65,    66,    67,    23,    46,    26,    26,    26,
      28,    21,    27,    73,    57,    62,    68,    62,    62,    62,
       4,    50,    62,    62,    66,    66,    30,    31,    32,    33,
      34,    36,    64,    38,    40,    59,    22,    72,    27,    69,
      21,    26,    21,    21,    27,    51,    21,    65,    65,    63,
      66,    66,    56,    73,    62,    14,    45,    50,    21,    45,
      69,    45,    17,    54,    51,    23,    26,    45,    26,    26
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    42,    43,    44,    44,    45,    46,    46,    47,    47,
      47,    47,    47,    47,    48,    49,    50,    50,    51,    51,
      52,    53,    54,    54,    55,    56,    56,    57,    57,    58,
      58,    59,    59,    60,    60,    61,    62,    62,    63,    63,
      63,    64,    64,    64,    64,    65,    65,    65,    66,    66,
      66,    66,    66,    66,    67,    68,    68,    69,    69,    70,
      71,    71,    72,    73,    73,    74,    74
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     8,     2,     0,     3,     2,     0,     1,     1,
       1,     2,     2,     2,     2,     5,     1,     1,     3,     0,
       7,     7,     2,     0,     2,     1,     0,     6,     0,     3,
       0,     1,     1,     1,     1,     4,     1,     3,     1,     3,
       3,     1,     1,     1,     1,     1,     3,     3,     2,     2,
       3,     1,     1,     1,     4,     2,     0,     3,     0,    10,
       2,     0,     3,     3,     0,     1,     1
  };




#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   108,   108,   120,   125,   132,   138,   142,   149,   153,
     157,   161,   165,   169,   176,   183,   193,   197,   204,   209,
     216,   223,   230,   234,   241,   248,   252,   259,   266,   273,
     278,   285,   289,   296,   300,   308,   315,   319,   326,   330,
     334,   342,   346,   351,   356,   364,   368,   372,   380,   384,
     391,   395,   399,   403,   421,   428,   433,   440,   445,   452,
     459,   464,   471,   478,   483,   491,   495
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 2175 "parser.cc"

#line 501 "parser.yy"


void yy::parser::error(const location_type& l, const std::string& m) {
  std::cerr << l << ": " << m << '\n';
}

