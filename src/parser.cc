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
#line 96 "parser.yy"

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
      case symbol_kind::S_signo: // signo
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

      case symbol_kind::S_estatuto: // estatuto
      case symbol_kind::S_imprime: // imprime
      case symbol_kind::S_ciclo: // ciclo
      case symbol_kind::S_asigna: // asigna
        value.YY_MOVE_OR_COPY< std::unique_ptr<StmntAST> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_list_id: // list_id
        value.YY_MOVE_OR_COPY< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_llamada_expresion: // llamada_expresion
      case symbol_kind::S_list_expresion: // list_expresion
      case symbol_kind::S_mas_expr: // mas_expr
        value.YY_MOVE_OR_COPY< std::vector<std::unique_ptr<ExprAST>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_43_funcs_opt: // funcs.opt
        value.YY_MOVE_OR_COPY< std::vector<std::unique_ptr<FuncDeclStmt>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parametros: // parametros
      case symbol_kind::S_list_params: // list_params
      case symbol_kind::S_mas_params: // mas_params
        value.YY_MOVE_OR_COPY< std::vector<std::unique_ptr<ParamVarDecl>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cuerpo: // cuerpo
      case symbol_kind::S_adentro: // adentro
      case symbol_kind::S_sino: // sino
        value.YY_MOVE_OR_COPY< std::vector<std::unique_ptr<StmntAST>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vars: // vars
      case symbol_kind::S_54_vars_opt: // vars.opt
      case symbol_kind::S_list_vars: // list_vars
      case symbol_kind::S_mas_vars: // mas_vars
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
      case symbol_kind::S_signo: // signo
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

      case symbol_kind::S_estatuto: // estatuto
      case symbol_kind::S_imprime: // imprime
      case symbol_kind::S_ciclo: // ciclo
      case symbol_kind::S_asigna: // asigna
        value.move< std::unique_ptr<StmntAST> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_list_id: // list_id
        value.move< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_llamada_expresion: // llamada_expresion
      case symbol_kind::S_list_expresion: // list_expresion
      case symbol_kind::S_mas_expr: // mas_expr
        value.move< std::vector<std::unique_ptr<ExprAST>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_43_funcs_opt: // funcs.opt
        value.move< std::vector<std::unique_ptr<FuncDeclStmt>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parametros: // parametros
      case symbol_kind::S_list_params: // list_params
      case symbol_kind::S_mas_params: // mas_params
        value.move< std::vector<std::unique_ptr<ParamVarDecl>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cuerpo: // cuerpo
      case symbol_kind::S_adentro: // adentro
      case symbol_kind::S_sino: // sino
        value.move< std::vector<std::unique_ptr<StmntAST>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vars: // vars
      case symbol_kind::S_54_vars_opt: // vars.opt
      case symbol_kind::S_list_vars: // list_vars
      case symbol_kind::S_mas_vars: // mas_vars
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
      case symbol_kind::S_signo: // signo
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

      case symbol_kind::S_estatuto: // estatuto
      case symbol_kind::S_imprime: // imprime
      case symbol_kind::S_ciclo: // ciclo
      case symbol_kind::S_asigna: // asigna
        value.copy< std::unique_ptr<StmntAST> > (that.value);
        break;

      case symbol_kind::S_list_id: // list_id
        value.copy< std::vector<std::string> > (that.value);
        break;

      case symbol_kind::S_llamada_expresion: // llamada_expresion
      case symbol_kind::S_list_expresion: // list_expresion
      case symbol_kind::S_mas_expr: // mas_expr
        value.copy< std::vector<std::unique_ptr<ExprAST>> > (that.value);
        break;

      case symbol_kind::S_43_funcs_opt: // funcs.opt
        value.copy< std::vector<std::unique_ptr<FuncDeclStmt>> > (that.value);
        break;

      case symbol_kind::S_parametros: // parametros
      case symbol_kind::S_list_params: // list_params
      case symbol_kind::S_mas_params: // mas_params
        value.copy< std::vector<std::unique_ptr<ParamVarDecl>> > (that.value);
        break;

      case symbol_kind::S_cuerpo: // cuerpo
      case symbol_kind::S_adentro: // adentro
      case symbol_kind::S_sino: // sino
        value.copy< std::vector<std::unique_ptr<StmntAST>> > (that.value);
        break;

      case symbol_kind::S_vars: // vars
      case symbol_kind::S_54_vars_opt: // vars.opt
      case symbol_kind::S_list_vars: // list_vars
      case symbol_kind::S_mas_vars: // mas_vars
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
      case symbol_kind::S_signo: // signo
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

      case symbol_kind::S_estatuto: // estatuto
      case symbol_kind::S_imprime: // imprime
      case symbol_kind::S_ciclo: // ciclo
      case symbol_kind::S_asigna: // asigna
        value.move< std::unique_ptr<StmntAST> > (that.value);
        break;

      case symbol_kind::S_list_id: // list_id
        value.move< std::vector<std::string> > (that.value);
        break;

      case symbol_kind::S_llamada_expresion: // llamada_expresion
      case symbol_kind::S_list_expresion: // list_expresion
      case symbol_kind::S_mas_expr: // mas_expr
        value.move< std::vector<std::unique_ptr<ExprAST>> > (that.value);
        break;

      case symbol_kind::S_43_funcs_opt: // funcs.opt
        value.move< std::vector<std::unique_ptr<FuncDeclStmt>> > (that.value);
        break;

      case symbol_kind::S_parametros: // parametros
      case symbol_kind::S_list_params: // list_params
      case symbol_kind::S_mas_params: // mas_params
        value.move< std::vector<std::unique_ptr<ParamVarDecl>> > (that.value);
        break;

      case symbol_kind::S_cuerpo: // cuerpo
      case symbol_kind::S_adentro: // adentro
      case symbol_kind::S_sino: // sino
        value.move< std::vector<std::unique_ptr<StmntAST>> > (that.value);
        break;

      case symbol_kind::S_vars: // vars
      case symbol_kind::S_54_vars_opt: // vars.opt
      case symbol_kind::S_list_vars: // list_vars
      case symbol_kind::S_mas_vars: // mas_vars
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
      case symbol_kind::S_signo: // signo
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

      case symbol_kind::S_estatuto: // estatuto
      case symbol_kind::S_imprime: // imprime
      case symbol_kind::S_ciclo: // ciclo
      case symbol_kind::S_asigna: // asigna
        yylhs.value.emplace< std::unique_ptr<StmntAST> > ();
        break;

      case symbol_kind::S_list_id: // list_id
        yylhs.value.emplace< std::vector<std::string> > ();
        break;

      case symbol_kind::S_llamada_expresion: // llamada_expresion
      case symbol_kind::S_list_expresion: // list_expresion
      case symbol_kind::S_mas_expr: // mas_expr
        yylhs.value.emplace< std::vector<std::unique_ptr<ExprAST>> > ();
        break;

      case symbol_kind::S_43_funcs_opt: // funcs.opt
        yylhs.value.emplace< std::vector<std::unique_ptr<FuncDeclStmt>> > ();
        break;

      case symbol_kind::S_parametros: // parametros
      case symbol_kind::S_list_params: // list_params
      case symbol_kind::S_mas_params: // mas_params
        yylhs.value.emplace< std::vector<std::unique_ptr<ParamVarDecl>> > ();
        break;

      case symbol_kind::S_cuerpo: // cuerpo
      case symbol_kind::S_adentro: // adentro
      case symbol_kind::S_sino: // sino
        yylhs.value.emplace< std::vector<std::unique_ptr<StmntAST>> > ();
        break;

      case symbol_kind::S_vars: // vars
      case symbol_kind::S_54_vars_opt: // vars.opt
      case symbol_kind::S_list_vars: // list_vars
      case symbol_kind::S_mas_vars: // mas_vars
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
#line 104 "parser.yy"
    {
        drv.ast = std::make_unique<ProgramAST>(
            yystack_[6].value.as < std::string > (),
            std::move(yystack_[4].value.as < std::vector<std::unique_ptr<VarDeclStmt>> > ()),
            std::move(yystack_[3].value.as < std::vector<std::unique_ptr<FuncDeclStmt>> > ()),
            std::move(yystack_[1].value.as < std::vector<std::unique_ptr<StmntAST>> > ())
        );
    }
#line 989 "parser.cc"
    break;

  case 3: // funcs.opt: funcs funcs.opt
#line 116 "parser.yy"
    {
        yystack_[0].value.as < std::vector<std::unique_ptr<FuncDeclStmt>> > ().insert(yystack_[0].value.as < std::vector<std::unique_ptr<FuncDeclStmt>> > ().begin(), std::move(yystack_[1].value.as < std::unique_ptr<FuncDeclStmt> > ()));
        yylhs.value.as < std::vector<std::unique_ptr<FuncDeclStmt>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<FuncDeclStmt>> > ());
    }
#line 998 "parser.cc"
    break;

  case 4: // funcs.opt: %empty
#line 121 "parser.yy"
    {
        yylhs.value.as < std::vector<std::unique_ptr<FuncDeclStmt>> > () = std::vector<std::unique_ptr<FuncDeclStmt>>();
    }
#line 1006 "parser.cc"
    break;

  case 5: // cuerpo: "{" adentro "}"
#line 127 "parser.yy"
                    {
        yylhs.value.as < std::vector<std::unique_ptr<StmntAST>> > () = std::move(yystack_[1].value.as < std::vector<std::unique_ptr<StmntAST>> > ());
    }
#line 1014 "parser.cc"
    break;

  case 6: // adentro: estatuto adentro
#line 133 "parser.yy"
                     {
        yystack_[0].value.as < std::vector<std::unique_ptr<StmntAST>> > ().insert(yystack_[0].value.as < std::vector<std::unique_ptr<StmntAST>> > ().begin(), std::move(yystack_[1].value.as < std::unique_ptr<StmntAST> > ()));
        yylhs.value.as < std::vector<std::unique_ptr<StmntAST>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<StmntAST>> > ());
    }
#line 1023 "parser.cc"
    break;

  case 7: // adentro: %empty
#line 138 "parser.yy"
  {
    yylhs.value.as < std::vector<std::unique_ptr<StmntAST>> > () = std::vector<std::unique_ptr<StmntAST>>();
  }
#line 1031 "parser.cc"
    break;

  case 8: // estatuto: asigna
#line 145 "parser.yy"
    {
    yylhs.value.as < std::unique_ptr<StmntAST> > () = std::move(yystack_[0].value.as < std::unique_ptr<StmntAST> > ());
    }
#line 1039 "parser.cc"
    break;

  case 9: // estatuto: condicion
#line 149 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<StmntAST> > () = std::move(yystack_[0].value.as < std::unique_ptr<IfStmnt> > ());
  }
#line 1047 "parser.cc"
    break;

  case 10: // estatuto: ciclo
#line 153 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<StmntAST> > () = std::move(yystack_[0].value.as < std::unique_ptr<StmntAST> > ());
  }
#line 1055 "parser.cc"
    break;

  case 11: // estatuto: llamada ";"
#line 157 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<StmntAST> > () = std::make_unique<CallStmt>(std::move(yystack_[1].value.as < std::unique_ptr<CallExpr> > ()));
  }
#line 1063 "parser.cc"
    break;

  case 12: // estatuto: imprime
#line 161 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<StmntAST> > () = std::move(yystack_[0].value.as < std::unique_ptr<StmntAST> > ());
  }
#line 1071 "parser.cc"
    break;

  case 13: // imprime: "escribe" "(" imprime_args imprime_mas ")" ";"
#line 168 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<StmntAST> > () = std::make_unique<PrintStmnt>(
            std::vector<std::unique_ptr<ExprAST>>{},
            std::vector<std::string>{}
        );
    }
#line 1082 "parser.cc"
    break;

  case 18: // ciclo: "mientras" "(" expresion ")" "haz" cuerpo ";"
#line 188 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<StmntAST> > () = std::make_unique<WhileStmnt>(std::move(yystack_[4].value.as < std::unique_ptr<ExprAST> > ()), std::move(yystack_[1].value.as < std::vector<std::unique_ptr<StmntAST>> > ()));
    }
#line 1090 "parser.cc"
    break;

  case 19: // condicion: "si" "(" expresion ")" cuerpo sino ";"
#line 195 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<IfStmnt> > () = std::make_unique<IfStmnt>(std::move(yystack_[4].value.as < std::unique_ptr<ExprAST> > ()), std::move(yystack_[2].value.as < std::vector<std::unique_ptr<StmntAST>> > ()), std::move(yystack_[1].value.as < std::vector<std::unique_ptr<StmntAST>> > ()));
    }
#line 1098 "parser.cc"
    break;

  case 20: // sino: "sino" cuerpo
#line 202 "parser.yy"
    {
        yylhs.value.as < std::vector<std::unique_ptr<StmntAST>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<StmntAST>> > ());
    }
#line 1106 "parser.cc"
    break;

  case 21: // sino: %empty
#line 206 "parser.yy"
  {
    yylhs.value.as < std::vector<std::unique_ptr<StmntAST>> > () = std::vector<std::unique_ptr<StmntAST>>();
  }
#line 1114 "parser.cc"
    break;

  case 22: // vars: "vars" list_vars
#line 213 "parser.yy"
    {
        yylhs.value.as < std::vector<std::unique_ptr<VarDeclStmt>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<VarDeclStmt>> > ());
    }
#line 1122 "parser.cc"
    break;

  case 23: // vars.opt: vars
#line 220 "parser.yy"
    {
        yylhs.value.as < std::vector<std::unique_ptr<VarDeclStmt>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<VarDeclStmt>> > ());
    }
#line 1130 "parser.cc"
    break;

  case 24: // vars.opt: %empty
#line 224 "parser.yy"
  {
    yylhs.value.as < std::vector<std::unique_ptr<VarDeclStmt>> > () = std::vector<std::unique_ptr<VarDeclStmt>>();
  }
#line 1138 "parser.cc"
    break;

  case 25: // list_vars: list_id ":" tipo ";" mas_vars
#line 231 "parser.yy"
    {
        yystack_[0].value.as < std::vector<std::unique_ptr<VarDeclStmt>> > ().insert(yystack_[0].value.as < std::vector<std::unique_ptr<VarDeclStmt>> > ().begin(), std::make_unique<VarDeclStmt>(yystack_[4].value.as < std::vector<std::string> > (), yystack_[2].value.as < Type > ()));
        yylhs.value.as < std::vector<std::unique_ptr<VarDeclStmt>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<VarDeclStmt>> > ());
    }
#line 1147 "parser.cc"
    break;

  case 26: // mas_vars: list_id ":" tipo ";" mas_vars
#line 239 "parser.yy"
    {
        yystack_[0].value.as < std::vector<std::unique_ptr<VarDeclStmt>> > ().insert(yystack_[0].value.as < std::vector<std::unique_ptr<VarDeclStmt>> > ().begin(), std::make_unique<VarDeclStmt>(yystack_[4].value.as < std::vector<std::string> > (), yystack_[2].value.as < Type > ()));
        yylhs.value.as < std::vector<std::unique_ptr<VarDeclStmt>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<VarDeclStmt>> > ());
    }
#line 1156 "parser.cc"
    break;

  case 27: // mas_vars: %empty
#line 244 "parser.yy"
  {
    yylhs.value.as < std::vector<std::unique_ptr<VarDeclStmt>> > () = std::vector<std::unique_ptr<VarDeclStmt>>();
  }
#line 1164 "parser.cc"
    break;

  case 28: // list_id: ID
#line 251 "parser.yy"
    {
        yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>();
        yylhs.value.as < std::vector<std::string> > ().push_back(yystack_[0].value.as < std::string > ());
    }
#line 1173 "parser.cc"
    break;

  case 29: // list_id: ID "," list_id
#line 256 "parser.yy"
    {
        yylhs.value.as < std::vector<std::string> > () = yystack_[0].value.as < std::vector<std::string> > ();
        yylhs.value.as < std::vector<std::string> > ().insert(yylhs.value.as < std::vector<std::string> > ().begin(), yystack_[2].value.as < std::string > ());
    }
#line 1182 "parser.cc"
    break;

  case 30: // tipo: "entero"
#line 264 "parser.yy"
    {
        yylhs.value.as < Type > () = Type::INT;
    }
#line 1190 "parser.cc"
    break;

  case 31: // tipo: "flotante"
#line 268 "parser.yy"
    {
        yylhs.value.as < Type > () = Type::FLOAT;
    }
#line 1198 "parser.cc"
    break;

  case 32: // cte: CTE_FLOT
#line 275 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<ExprAST> > () = std::make_unique<FloatingLiteral>(yystack_[0].value.as < double > ());
    }
#line 1206 "parser.cc"
    break;

  case 33: // cte: CTE_ENT
#line 279 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<ExprAST> > () = std::make_unique<IntegerLiteral>(yystack_[0].value.as < long > ());
    }
#line 1214 "parser.cc"
    break;

  case 34: // asigna: ID "=" expresion ";"
#line 287 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<StmntAST> > () = std::make_unique<AssignmentStmnt>(yystack_[3].value.as < std::string > (), std::move(yystack_[1].value.as < std::unique_ptr<ExprAST> > ()));
    }
#line 1222 "parser.cc"
    break;

  case 35: // expresion: exp
#line 294 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<ExprAST> > () = std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ());
    }
#line 1230 "parser.cc"
    break;

  case 36: // expresion: exp comp exp
#line 298 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<ExprAST> > () = std::make_unique<BinaryOpExpr>(yystack_[1].value.as < Operator > (), std::move(yystack_[2].value.as < std::unique_ptr<ExprAST> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ()));
  }
#line 1238 "parser.cc"
    break;

  case 37: // exp: termino
#line 305 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<ExprAST> > () = std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ());
    }
#line 1246 "parser.cc"
    break;

  case 38: // exp: exp PLUS termino
#line 309 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<ExprAST> > () = std::make_unique<BinaryOpExpr>(Operator::PLUS, std::move(yystack_[2].value.as < std::unique_ptr<ExprAST> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ()));
  }
#line 1254 "parser.cc"
    break;

  case 39: // exp: exp MINUS termino
#line 313 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<ExprAST> > () = std::make_unique<BinaryOpExpr>(Operator::MINUS, std::move(yystack_[2].value.as < std::unique_ptr<ExprAST> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ()));
  }
#line 1262 "parser.cc"
    break;

  case 40: // comp: ">"
#line 321 "parser.yy"
    {
        yylhs.value.as < Operator > () = Operator::GT;
    }
#line 1270 "parser.cc"
    break;

  case 41: // comp: "<"
#line 325 "parser.yy"
    {
        yylhs.value.as < Operator > () = Operator::LT;
    }
#line 1278 "parser.cc"
    break;

  case 42: // comp: "!="
#line 330 "parser.yy"
    {
        yylhs.value.as < Operator > () = Operator::NEQ;
    }
#line 1286 "parser.cc"
    break;

  case 43: // comp: "=="
#line 335 "parser.yy"
    {
        yylhs.value.as < Operator > () = Operator::EQ;
    }
#line 1294 "parser.cc"
    break;

  case 44: // termino: factor
#line 343 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<ExprAST> > () = std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ());
    }
#line 1302 "parser.cc"
    break;

  case 45: // termino: termino TIMES factor
#line 347 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<ExprAST> > () = std::make_unique<BinaryOpExpr>(Operator::TIMES, std::move(yystack_[2].value.as < std::unique_ptr<ExprAST> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ()));
  }
#line 1310 "parser.cc"
    break;

  case 46: // termino: termino DIV factor
#line 351 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<ExprAST> > () = std::make_unique<BinaryOpExpr>(Operator::DIV, std::move(yystack_[2].value.as < std::unique_ptr<ExprAST> > ()), std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ()));
  }
#line 1318 "parser.cc"
    break;

  case 47: // factor: "(" expresion ")"
#line 359 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<ExprAST> > () = std::move(yystack_[1].value.as < std::unique_ptr<ExprAST> > ());
    }
#line 1326 "parser.cc"
    break;

  case 48: // factor: ID
#line 363 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<ExprAST> > () = std::make_unique<ReferenceExpr>(yystack_[0].value.as < std::string > ());
  }
#line 1334 "parser.cc"
    break;

  case 49: // factor: cte
#line 367 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<ExprAST> > () = std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ());
  }
#line 1342 "parser.cc"
    break;

  case 50: // factor: signo ID
#line 371 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<ExprAST> > () = std::make_unique<UnaryOpExpr>(yystack_[1].value.as < Operator > (), std::make_unique<ReferenceExpr>(yystack_[0].value.as < std::string > ()));

  }
#line 1351 "parser.cc"
    break;

  case 51: // factor: signo cte
#line 376 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<ExprAST> > () = std::make_unique<UnaryOpExpr>(yystack_[1].value.as < Operator > (), std::move(yystack_[0].value.as < std::unique_ptr<ExprAST> > ()));
  }
#line 1359 "parser.cc"
    break;

  case 52: // factor: llamada
#line 380 "parser.yy"
  {
    yylhs.value.as < std::unique_ptr<ExprAST> > () = std::move(yystack_[0].value.as < std::unique_ptr<CallExpr> > ());
  }
#line 1367 "parser.cc"
    break;

  case 53: // signo: "+"
#line 387 "parser.yy"
    {
        yylhs.value.as < Operator > () = Operator::PLUS;
    }
#line 1375 "parser.cc"
    break;

  case 54: // signo: "-"
#line 391 "parser.yy"
  {
    yylhs.value.as < Operator > () = Operator::MINUS;
  }
#line 1383 "parser.cc"
    break;

  case 55: // llamada: ID "(" llamada_expresion ")"
#line 398 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<CallExpr> > () = std::make_unique<CallExpr>(yystack_[3].value.as < std::string > (), std::move(yystack_[1].value.as < std::vector<std::unique_ptr<ExprAST>> > ()));
    }
#line 1391 "parser.cc"
    break;

  case 56: // llamada_expresion: list_expresion
#line 404 "parser.yy"
                   { yylhs.value.as < std::vector<std::unique_ptr<ExprAST>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<ExprAST>> > ());}
#line 1397 "parser.cc"
    break;

  case 57: // llamada_expresion: %empty
#line 405 "parser.yy"
           { yylhs.value.as < std::vector<std::unique_ptr<ExprAST>> > () = std::vector<std::unique_ptr<ExprAST>>();}
#line 1403 "parser.cc"
    break;

  case 58: // list_expresion: expresion mas_expr
#line 410 "parser.yy"
    {
        yystack_[0].value.as < std::vector<std::unique_ptr<ExprAST>> > ().insert(yystack_[0].value.as < std::vector<std::unique_ptr<ExprAST>> > ().begin(), std::move(yystack_[1].value.as < std::unique_ptr<ExprAST> > ()));
        yylhs.value.as < std::vector<std::unique_ptr<ExprAST>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<ExprAST>> > ());
    }
#line 1412 "parser.cc"
    break;

  case 59: // mas_expr: "," expresion mas_expr
#line 418 "parser.yy"
    {
        yystack_[0].value.as < std::vector<std::unique_ptr<ExprAST>> > ().insert(yystack_[0].value.as < std::vector<std::unique_ptr<ExprAST>> > ().begin(), std::move(yystack_[1].value.as < std::unique_ptr<ExprAST> > ()));
        yylhs.value.as < std::vector<std::unique_ptr<ExprAST>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<ExprAST>> > ());
    }
#line 1421 "parser.cc"
    break;

  case 60: // mas_expr: %empty
#line 423 "parser.yy"
    {
        yylhs.value.as < std::vector<std::unique_ptr<ExprAST>> > () = std::vector<std::unique_ptr<ExprAST>>();
    }
#line 1429 "parser.cc"
    break;

  case 61: // funcs: tipo_func ID "(" parametros ")" "{" vars.opt cuerpo "}" ";"
#line 430 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<FuncDeclStmt> > () = std::make_unique<FuncDeclStmt>(std::move(yystack_[8].value.as < std::string > ()), std::move(yystack_[6].value.as < std::vector<std::unique_ptr<ParamVarDecl>> > ()), yystack_[9].value.as < Type > (), std::move(yystack_[2].value.as < std::vector<std::unique_ptr<StmntAST>> > ()));     
    }
#line 1437 "parser.cc"
    break;

  case 62: // parametros: list_params
#line 437 "parser.yy"
    {
        yylhs.value.as < std::vector<std::unique_ptr<ParamVarDecl>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<ParamVarDecl>> > ());
    }
#line 1445 "parser.cc"
    break;

  case 63: // parametros: %empty
#line 441 "parser.yy"
    {
        yylhs.value.as < std::vector<std::unique_ptr<ParamVarDecl>> > () = std::vector<std::unique_ptr<ParamVarDecl>>();
    }
#line 1453 "parser.cc"
    break;

  case 64: // list_params: param mas_params
#line 448 "parser.yy"
    {
        yystack_[0].value.as < std::vector<std::unique_ptr<ParamVarDecl>> > ().insert(yystack_[0].value.as < std::vector<std::unique_ptr<ParamVarDecl>> > ().begin(), std::move(yystack_[1].value.as < std::unique_ptr<ParamVarDecl> > ()));
        yylhs.value.as < std::vector<std::unique_ptr<ParamVarDecl>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<ParamVarDecl>> > ());
    }
#line 1462 "parser.cc"
    break;

  case 65: // mas_params: "," param mas_params
#line 456 "parser.yy"
    {
        yystack_[0].value.as < std::vector<std::unique_ptr<ParamVarDecl>> > ().insert(yystack_[0].value.as < std::vector<std::unique_ptr<ParamVarDecl>> > ().begin(), std::move(yystack_[1].value.as < std::unique_ptr<ParamVarDecl> > ()));
        yylhs.value.as < std::vector<std::unique_ptr<ParamVarDecl>> > () = std::move(yystack_[0].value.as < std::vector<std::unique_ptr<ParamVarDecl>> > ());
    }
#line 1471 "parser.cc"
    break;

  case 66: // mas_params: %empty
#line 461 "parser.yy"
    {
        yylhs.value.as < std::vector<std::unique_ptr<ParamVarDecl>> > () = std::vector<std::unique_ptr<ParamVarDecl>>();
    }
#line 1479 "parser.cc"
    break;

  case 67: // param: ID ":" tipo
#line 468 "parser.yy"
    {
        yylhs.value.as < std::unique_ptr<ParamVarDecl> > () = std::make_unique<ParamVarDecl>(yystack_[2].value.as < std::string > (), yystack_[0].value.as < Type > ());
    }
#line 1487 "parser.cc"
    break;

  case 68: // tipo_func: "nulo"
#line 475 "parser.yy"
    {
        yylhs.value.as < Type > () = Type::VOID;
    }
#line 1495 "parser.cc"
    break;

  case 69: // tipo_func: tipo
#line 479 "parser.yy"
    {
        yylhs.value.as < Type > () = yystack_[0].value.as < Type > ();
    }
#line 1503 "parser.cc"
    break;


#line 1507 "parser.cc"

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
  "nulo", "haz", "mientras", "si", "sino", "escribe", "(", ")", "{", "}",
  "[", "]", ";", ",", ":", "=", ">", "<", "!=", "==", "PLUS", "+", "MINUS",
  "-", "TIMES", "*", "DIV", "/", "$accept", "programa", "funcs.opt",
  "cuerpo", "adentro", "estatuto", "imprime", "imprime_args",
  "imprime_mas", "ciclo", "condicion", "sino", "vars", "vars.opt",
  "list_vars", "mas_vars", "list_id", "tipo", "cte", "asigna", "expresion",
  "exp", "comp", "termino", "factor", "signo", "llamada",
  "llamada_expresion", "list_expresion", "mas_expr", "funcs", "parametros",
  "list_params", "mas_params", "param", "tipo_func", YY_NULLPTR
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


  const signed char parser::yypact_ninf_ = -92;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
      -6,    21,    38,    25,   -92,    33,    60,   -92,    41,    39,
     -92,    37,   -92,   -92,   -92,    58,   -92,    41,    64,    60,
      48,    47,   -92,    50,   -92,    45,    13,    62,    69,    60,
      -2,    54,    55,    56,    57,    13,   -92,   -92,   -92,   -92,
      51,   -92,    53,    61,   -92,    52,   -92,    59,     8,     8,
       8,     8,     3,   -92,   -92,   -92,    48,    63,    69,   -92,
      48,    66,   -92,   -92,     8,   -92,   -92,   -92,    65,    16,
      18,   -92,    29,   -92,    67,   -92,    68,    70,    72,   -92,
      71,   -92,   -92,    33,    52,    73,    74,     8,   -92,   -92,
     -92,   -92,   -92,     8,     8,     8,     8,     8,   -92,   -92,
     -92,   -92,    75,    47,     3,    76,    47,   -92,    60,   -92,
      65,    18,    18,    23,   -92,   -92,    47,    78,    71,    77,
      79,   -92,   -92,    80,    47,    81,   -92,   -92,    82,   -92,
     -92,   -92,   -92
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     1,    24,     0,    23,     4,    28,
      22,     0,    30,    31,    68,     0,    69,     4,     0,     0,
       0,     0,     3,     0,    29,     0,     7,     0,    63,    27,
       0,     0,     0,     0,     0,     7,    12,    10,     9,     8,
       0,     2,     0,     0,    62,    66,    25,     0,    57,     0,
       0,     0,     0,     5,     6,    11,     0,     0,     0,    64,
       0,    48,    33,    32,     0,    53,    54,    49,    60,    35,
      37,    44,     0,    52,     0,    56,     0,     0,     0,    15,
      17,    14,    67,    24,    66,     0,     0,     0,    58,    40,
      41,    42,    43,     0,     0,     0,     0,     0,    50,    51,
      55,    34,     0,     0,     0,     0,     0,    65,    27,    47,
      60,    38,    39,    36,    45,    46,     0,    21,    17,     0,
       0,    26,    59,     0,     0,     0,    16,    13,     0,    18,
      20,    19,    61
  };

  const signed char
  parser::yypgoto_[] =
  {
     -92,   -92,    83,   -91,    42,   -92,   -92,   -22,   -30,   -92,
     -92,   -92,   -92,     0,   -92,    -9,     4,   -20,    31,   -92,
     -46,     9,   -92,   -74,   -35,   -92,    -5,   -92,   -92,    -1,
     -92,   -92,   -92,    24,    84,   -92
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,     2,    15,    27,    34,    35,    36,    80,   105,    37,
      38,   125,     7,     8,    10,    46,    47,    16,    67,    39,
      81,    69,    95,    70,    71,    72,    73,    74,    75,    88,
      17,    43,    44,    59,    45,    18
  };

  const unsigned char
  parser::yytable_[] =
  {
      25,     1,    68,    76,    77,    78,    61,    79,    62,    63,
      11,    61,   117,    62,    63,   120,    30,    48,    86,   111,
     112,    40,    64,    24,     3,   123,    49,    64,    31,    32,
      40,    33,    98,   130,    62,    63,    82,    65,     4,    66,
      85,   110,    65,     6,    66,    89,    90,    91,    92,    93,
       5,    94,    12,    13,    14,    96,    93,    97,    94,    12,
      13,   114,   115,     9,    20,    19,    21,    23,    26,    28,
      29,    41,    42,    50,    51,    52,    55,    54,    58,    53,
      56,    57,   118,   106,    83,    48,    60,   100,   126,   116,
     102,    87,   103,   101,   109,   124,   119,   104,   108,   121,
      22,   128,   127,    99,   113,   129,   131,   132,   107,   122,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    84
  };

  const signed char
  parser::yycheck_[] =
  {
      20,     7,    48,    49,    50,    51,     3,     4,     5,     6,
       6,     3,   103,     5,     6,   106,     3,    19,    64,    93,
      94,    26,    19,    19,     3,   116,    28,    19,    15,    16,
      35,    18,     3,   124,     5,     6,    56,    34,     0,    36,
      60,    87,    34,    10,    36,    29,    30,    31,    32,    33,
      25,    35,    11,    12,    13,    37,    33,    39,    35,    11,
      12,    96,    97,     3,    27,    26,     8,     3,    21,    19,
      25,     9,     3,    19,    19,    19,    25,    35,    26,    22,
      27,    20,   104,    83,    21,    19,    27,    20,   118,    14,
      20,    26,    20,    25,    20,    17,    20,    26,    25,   108,
      17,    22,    25,    72,    95,    25,    25,    25,    84,   110,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    58
  };

  const signed char
  parser::yystos_[] =
  {
       0,     7,    42,     3,     0,    25,    10,    53,    54,     3,
      55,    57,    11,    12,    13,    43,    58,    71,    76,    26,
      27,     8,    43,     3,    57,    58,    21,    44,    19,    25,
       3,    15,    16,    18,    45,    46,    47,    50,    51,    60,
      67,     9,     3,    72,    73,    75,    56,    57,    19,    28,
      19,    19,    19,    22,    45,    25,    27,    20,    26,    74,
      27,     3,     5,     6,    19,    34,    36,    59,    61,    62,
      64,    65,    66,    67,    68,    69,    61,    61,    61,     4,
      48,    61,    58,    21,    75,    58,    61,    26,    70,    29,
      30,    31,    32,    33,    35,    63,    37,    39,     3,    59,
      20,    25,    20,    20,    26,    49,    54,    74,    25,    20,
      61,    64,    64,    62,    65,    65,    14,    44,    48,    20,
      44,    56,    70,    44,    17,    52,    49,    25,    22,    25,
      44,    25,    25
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    41,    42,    43,    43,    44,    45,    45,    46,    46,
      46,    46,    46,    47,    48,    48,    49,    49,    50,    51,
      52,    52,    53,    54,    54,    55,    56,    56,    57,    57,
      58,    58,    59,    59,    60,    61,    61,    62,    62,    62,
      63,    63,    63,    63,    64,    64,    64,    65,    65,    65,
      65,    65,    65,    66,    66,    67,    68,    68,    69,    70,
      70,    71,    72,    72,    73,    74,    74,    75,    76,    76
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     8,     2,     0,     3,     2,     0,     1,     1,
       1,     2,     1,     6,     1,     1,     3,     0,     7,     7,
       2,     0,     2,     1,     0,     5,     5,     0,     1,     3,
       1,     1,     1,     1,     4,     1,     3,     1,     3,     3,
       1,     1,     1,     1,     1,     3,     3,     3,     1,     1,
       2,     2,     1,     1,     1,     4,     1,     0,     2,     3,
       0,    10,     1,     0,     2,     3,     0,     3,     1,     1
  };




#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   103,   103,   115,   120,   127,   133,   137,   144,   148,
     152,   156,   160,   167,   177,   178,   182,   183,   187,   194,
     201,   205,   212,   219,   223,   230,   238,   243,   250,   255,
     263,   267,   274,   278,   286,   293,   297,   304,   308,   312,
     320,   324,   329,   334,   342,   346,   350,   358,   362,   366,
     370,   375,   379,   386,   390,   397,   404,   405,   409,   417,
     422,   429,   436,   440,   447,   455,   460,   467,   474,   478
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
#line 2158 "parser.cc"

#line 484 "parser.yy"


void yy::parser::error(const location_type& l, const std::string& m) {
  std::cerr << l << ": " << m << '\n';
}

