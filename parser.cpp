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
#line 24 "parser.y"

    #include "driver.hh"
    #include "location.hh"

    /* Redefine parser to use our function from scanner */
    static yy::parser::symbol_type yylex(Scanner &scanner) {
        return scanner.ScanToken();
    }

#line 56 "/home/snail/Code/FormalLang/interpreter/parser.cpp"


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
#line 148 "/home/snail/Code/FormalLang/interpreter/parser.cpp"

  /// Build a parser object.
  parser::parser (Scanner &scanner_yyarg, Driver &driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
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
      case symbol_kind::S_assignment: // assignment
        value.YY_MOVE_OR_COPY< AssignmentNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_block: // block
        value.YY_MOVE_OR_COPY< BlockNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call_func: // call_func
        value.YY_MOVE_OR_COPY< CallFuncNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_condition: // condition
        value.YY_MOVE_OR_COPY< ConditionNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_create_var: // create_var
        value.YY_MOVE_OR_COPY< CreateVarNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.YY_MOVE_OR_COPY< ExprNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_logical_expr: // logical_expr
        value.YY_MOVE_OR_COPY< LogicalExprNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_loop: // loop
        value.YY_MOVE_OR_COPY< LoopNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_any_arg: // any_arg
        value.YY_MOVE_OR_COPY< Node* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LOGICAL_CONSTANT: // "logical_constant"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_TAG: // "tag"
      case symbol_kind::S_VALUE: // "value"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_CHARACTER: // "character"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_external_statements: // external_statements
      case symbol_kind::S_statements: // statements
      case symbol_kind::S_args_or_none: // args_or_none
      case symbol_kind::S_args: // args
        value.YY_MOVE_OR_COPY< std::vector<Node*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tags: // tags
        value.YY_MOVE_OR_COPY< std::vector<std::string> > (YY_MOVE (that.value));
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
      case symbol_kind::S_assignment: // assignment
        value.move< AssignmentNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_block: // block
        value.move< BlockNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_call_func: // call_func
        value.move< CallFuncNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_condition: // condition
        value.move< ConditionNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_create_var: // create_var
        value.move< CreateVarNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.move< ExprNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_logical_expr: // logical_expr
        value.move< LogicalExprNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_loop: // loop
        value.move< LoopNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_any_arg: // any_arg
        value.move< Node* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LOGICAL_CONSTANT: // "logical_constant"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_TAG: // "tag"
      case symbol_kind::S_VALUE: // "value"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_CHARACTER: // "character"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_external_statements: // external_statements
      case symbol_kind::S_statements: // statements
      case symbol_kind::S_args_or_none: // args_or_none
      case symbol_kind::S_args: // args
        value.move< std::vector<Node*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tags: // tags
        value.move< std::vector<std::string> > (YY_MOVE (that.value));
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
      case symbol_kind::S_assignment: // assignment
        value.copy< AssignmentNode* > (that.value);
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_block: // block
        value.copy< BlockNode* > (that.value);
        break;

      case symbol_kind::S_call_func: // call_func
        value.copy< CallFuncNode* > (that.value);
        break;

      case symbol_kind::S_condition: // condition
        value.copy< ConditionNode* > (that.value);
        break;

      case symbol_kind::S_create_var: // create_var
        value.copy< CreateVarNode* > (that.value);
        break;

      case symbol_kind::S_expr: // expr
        value.copy< ExprNode* > (that.value);
        break;

      case symbol_kind::S_logical_expr: // logical_expr
        value.copy< LogicalExprNode* > (that.value);
        break;

      case symbol_kind::S_loop: // loop
        value.copy< LoopNode* > (that.value);
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_any_arg: // any_arg
        value.copy< Node* > (that.value);
        break;

      case symbol_kind::S_LOGICAL_CONSTANT: // "logical_constant"
        value.copy< bool > (that.value);
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_TAG: // "tag"
      case symbol_kind::S_VALUE: // "value"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_CHARACTER: // "character"
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_external_statements: // external_statements
      case symbol_kind::S_statements: // statements
      case symbol_kind::S_args_or_none: // args_or_none
      case symbol_kind::S_args: // args
        value.copy< std::vector<Node*> > (that.value);
        break;

      case symbol_kind::S_tags: // tags
        value.copy< std::vector<std::string> > (that.value);
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
      case symbol_kind::S_assignment: // assignment
        value.move< AssignmentNode* > (that.value);
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_block: // block
        value.move< BlockNode* > (that.value);
        break;

      case symbol_kind::S_call_func: // call_func
        value.move< CallFuncNode* > (that.value);
        break;

      case symbol_kind::S_condition: // condition
        value.move< ConditionNode* > (that.value);
        break;

      case symbol_kind::S_create_var: // create_var
        value.move< CreateVarNode* > (that.value);
        break;

      case symbol_kind::S_expr: // expr
        value.move< ExprNode* > (that.value);
        break;

      case symbol_kind::S_logical_expr: // logical_expr
        value.move< LogicalExprNode* > (that.value);
        break;

      case symbol_kind::S_loop: // loop
        value.move< LoopNode* > (that.value);
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_any_arg: // any_arg
        value.move< Node* > (that.value);
        break;

      case symbol_kind::S_LOGICAL_CONSTANT: // "logical_constant"
        value.move< bool > (that.value);
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.move< int > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_TAG: // "tag"
      case symbol_kind::S_VALUE: // "value"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_CHARACTER: // "character"
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_external_statements: // external_statements
      case symbol_kind::S_statements: // statements
      case symbol_kind::S_args_or_none: // args_or_none
      case symbol_kind::S_args: // args
        value.move< std::vector<Node*> > (that.value);
        break;

      case symbol_kind::S_tags: // tags
        value.move< std::vector<std::string> > (that.value);
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
        switch (yykind)
    {
      case symbol_kind::S_IDENTIFIER: // "identifier"
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 560 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_TAG: // "tag"
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 566 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_VALUE: // "value"
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 572 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_STRING: // "string"
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 578 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_CHARACTER: // "character"
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 584 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_NUMBER: // "number"
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 590 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_LOGICAL_CONSTANT: // "logical_constant"
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 596 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_program: // program
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 602 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_block: // block
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 608 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_external_statements: // external_statements
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 614 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_statements: // statements
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 620 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_statement: // statement
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 626 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_create_var: // create_var
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 632 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_call_func: // call_func
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 638 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_args_or_none: // args_or_none
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 644 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_args: // args
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 650 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_any_arg: // any_arg
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 656 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_tags: // tags
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 662 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_assignment: // assignment
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 668 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_loop: // loop
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 674 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_condition: // condition
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 680 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_expr: // expr
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 686 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      case symbol_kind::S_logical_expr: // logical_expr
#line 103 "parser.y"
                 { /*yyo << $$;*/ }
#line 692 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
        break;

      default:
        break;
    }
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
            symbol_type yylookahead (yylex (scanner));
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
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
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
      case symbol_kind::S_assignment: // assignment
        yylhs.value.emplace< AssignmentNode* > ();
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_block: // block
        yylhs.value.emplace< BlockNode* > ();
        break;

      case symbol_kind::S_call_func: // call_func
        yylhs.value.emplace< CallFuncNode* > ();
        break;

      case symbol_kind::S_condition: // condition
        yylhs.value.emplace< ConditionNode* > ();
        break;

      case symbol_kind::S_create_var: // create_var
        yylhs.value.emplace< CreateVarNode* > ();
        break;

      case symbol_kind::S_expr: // expr
        yylhs.value.emplace< ExprNode* > ();
        break;

      case symbol_kind::S_logical_expr: // logical_expr
        yylhs.value.emplace< LogicalExprNode* > ();
        break;

      case symbol_kind::S_loop: // loop
        yylhs.value.emplace< LoopNode* > ();
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_any_arg: // any_arg
        yylhs.value.emplace< Node* > ();
        break;

      case symbol_kind::S_LOGICAL_CONSTANT: // "logical_constant"
        yylhs.value.emplace< bool > ();
        break;

      case symbol_kind::S_NUMBER: // "number"
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_TAG: // "tag"
      case symbol_kind::S_VALUE: // "value"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_CHARACTER: // "character"
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_external_statements: // external_statements
      case symbol_kind::S_statements: // statements
      case symbol_kind::S_args_or_none: // args_or_none
      case symbol_kind::S_args: // args
        yylhs.value.emplace< std::vector<Node*> > ();
        break;

      case symbol_kind::S_tags: // tags
        yylhs.value.emplace< std::vector<std::string> > ();
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
  case 2: // program: external_statements
#line 116 "parser.y"
                        {
        yylhs.value.as < BlockNode* > () = new BlockNode(yystack_[0].value.as < std::vector<Node*> > ());
        yylhs.value.as < BlockNode* > ()->execute();
    }
#line 1013 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 3: // block: "{" statements "}"
#line 122 "parser.y"
                       {
        yylhs.value.as < BlockNode* > () = new BlockNode(yystack_[1].value.as < std::vector<Node*> > ());
    }
#line 1021 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 4: // external_statements: %empty
#line 127 "parser.y"
           {}
#line 1027 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 5: // external_statements: external_statements statement
#line 128 "parser.y"
                                    {
        yylhs.value.as < std::vector<Node*> > () = yystack_[1].value.as < std::vector<Node*> > ();
        yylhs.value.as < std::vector<Node*> > ().push_back(yystack_[0].value.as < Node* > ());
    }
#line 1036 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 6: // external_statements: external_statements create_var ";"
#line 132 "parser.y"
                                         {
        yylhs.value.as < std::vector<Node*> > () = yystack_[2].value.as < std::vector<Node*> > ();
        yylhs.value.as < std::vector<Node*> > ().push_back(yystack_[1].value.as < CreateVarNode* > ());
    }
#line 1045 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 7: // statements: %empty
#line 138 "parser.y"
           {}
#line 1051 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 8: // statements: statements statement
#line 139 "parser.y"
                           {
        yylhs.value.as < std::vector<Node*> > () = yystack_[1].value.as < std::vector<Node*> > ();
        yylhs.value.as < std::vector<Node*> > ().push_back(yystack_[0].value.as < Node* > ());
    }
#line 1060 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 9: // statement: call_func ";"
#line 145 "parser.y"
                  {
        yylhs.value.as < Node* > () = yystack_[1].value.as < CallFuncNode* > ();
    }
#line 1068 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 10: // statement: assignment ";"
#line 148 "parser.y"
                     {
        yylhs.value.as < Node* > () = yystack_[1].value.as < AssignmentNode* > ();
    }
#line 1076 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 11: // statement: loop
#line 151 "parser.y"
           {
        yylhs.value.as < Node* > () = yystack_[0].value.as < LoopNode* > ();
    }
#line 1084 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 12: // statement: condition
#line 154 "parser.y"
                {
        yylhs.value.as < Node* > () = yystack_[0].value.as < ConditionNode* > ();
    }
#line 1092 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 13: // statement: block
#line 157 "parser.y"
            {
        yylhs.value.as < Node* > () = yystack_[0].value.as < BlockNode* > ();
    }
#line 1100 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 14: // create_var: "identifier" ":" tags
#line 162 "parser.y"
                          {
        yylhs.value.as < CreateVarNode* > () = new CreateVarNode(yystack_[2].value.as < std::string > (), yystack_[0].value.as < std::vector<std::string> > (), &(driver.storage));
    }
#line 1108 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 15: // call_func: "identifier" "(" args_or_none ")"
#line 167 "parser.y"
                                      {
        FuncType id = FuncType::NONE;
        if (yystack_[3].value.as < std::string > () == "print") {
            id = FuncType::PRINT;
        } else if (yystack_[3].value.as < std::string > () == "write") {
            id = FuncType::WRITE;
        } else if (yystack_[3].value.as < std::string > () == "scan") {
            id = FuncType::SCAN;
        } else {
            CallRuntimeError("RE: Unrecognized function name.");
        }
        // choose func type from $1
        if (id == FuncType::SCAN) {
            yylhs.value.as < CallFuncNode* > () = new CallTFuncNode(id, yystack_[1].value.as < std::vector<Node*> > ());
        } else {
            yylhs.value.as < CallFuncNode* > () = new CallFuncNode(id, yystack_[1].value.as < std::vector<Node*> > ());
        }
    }
#line 1131 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 16: // args_or_none: %empty
#line 187 "parser.y"
           {}
#line 1137 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 17: // args_or_none: args
#line 188 "parser.y"
           {
        yylhs.value.as < std::vector<Node*> > () = yystack_[0].value.as < std::vector<Node*> > ();
    }
#line 1145 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 18: // args: any_arg
#line 193 "parser.y"
            {
        yylhs.value.as < std::vector<Node*> > ().push_back(yystack_[0].value.as < Node* > ());
    }
#line 1153 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 19: // args: args "," any_arg
#line 196 "parser.y"
                       {
        yylhs.value.as < std::vector<Node*> > () = yystack_[2].value.as < std::vector<Node*> > ();
        yylhs.value.as < std::vector<Node*> > ().push_back(yystack_[0].value.as < Node* > ());
    }
#line 1162 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 20: // any_arg: expr
#line 202 "parser.y"
         {
        yylhs.value.as < Node* > () = yystack_[0].value.as < ExprNode* > ();
    }
#line 1170 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 21: // any_arg: "string"
#line 205 "parser.y"
               {
        yylhs.value.as < Node* > () = new StringNode(yystack_[0].value.as < std::string > ());
    }
#line 1178 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 22: // tags: "tag"
#line 210 "parser.y"
          { 
        yylhs.value.as < std::vector<std::string> > ().push_back(yystack_[0].value.as < std::string > ()); 
    }
#line 1186 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 23: // tags: "tag" tags
#line 213 "parser.y"
                 { 
        yylhs.value.as < std::vector<std::string> > () = yystack_[0].value.as < std::vector<std::string> > ();
        yylhs.value.as < std::vector<std::string> > ().push_back(yystack_[1].value.as < std::string > ());
    }
#line 1195 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 24: // assignment: "identifier" "=" expr
#line 219 "parser.y"
                          {
        yylhs.value.as < AssignmentNode* > () = new AssignmentNode(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ExprNode* > (), &(driver.storage));
        /*if (driver.location_debug) {
            std::cerr << driver.location << std::endl;
        }*/
    }
#line 1206 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 25: // loop: "@" "(" logical_expr ")" block
#line 232 "parser.y"
                                   {
        yylhs.value.as < LoopNode* > () = new LoopNode(yystack_[2].value.as < LogicalExprNode* > (), yystack_[0].value.as < BlockNode* > ());
    }
#line 1214 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 26: // condition: "?" "(" logical_expr ")" block ":" block
#line 237 "parser.y"
                                             {
        yylhs.value.as < ConditionNode* > () = new ConditionNode(yystack_[4].value.as < LogicalExprNode* > (), yystack_[2].value.as < BlockNode* > (), yystack_[0].value.as < BlockNode* > ());
    }
#line 1222 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 27: // expr: "number"
#line 242 "parser.y"
             { 
        yylhs.value.as < ExprNode* > () = new NumberExprNode(yystack_[0].value.as < int > ()); 
    }
#line 1230 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 28: // expr: "identifier"
#line 245 "parser.y"
                   { 
        yylhs.value.as < ExprNode* > () = new VarExprNode(yystack_[0].value.as < std::string > (), &(driver.storage));
        /*driver.variables[$1];*/
    }
#line 1239 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 29: // expr: call_func
#line 249 "parser.y"
                {
        yylhs.value.as < ExprNode* > () = yystack_[0].value.as < CallFuncNode* > ();
    }
#line 1247 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 30: // expr: "-" expr
#line 252 "parser.y"
               {
        yylhs.value.as < ExprNode* > () = new ExprNode(yystack_[0].value.as < ExprNode* > (), nullptr, Operator::NEGATIVE);
    }
#line 1255 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 31: // expr: expr "+" expr
#line 255 "parser.y"
                    { 
        yylhs.value.as < ExprNode* > () = new ExprNode(yystack_[2].value.as < ExprNode* > (), yystack_[0].value.as < ExprNode* > (), Operator::ADD); 
    }
#line 1263 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 32: // expr: expr "-" expr
#line 258 "parser.y"
                    { 
        yylhs.value.as < ExprNode* > () = new ExprNode(yystack_[2].value.as < ExprNode* > (), yystack_[0].value.as < ExprNode* > (), Operator::SUB); 
    }
#line 1271 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 33: // expr: expr "*" expr
#line 261 "parser.y"
                    { 
        yylhs.value.as < ExprNode* > () = new ExprNode(yystack_[2].value.as < ExprNode* > (), yystack_[0].value.as < ExprNode* > (), Operator::MULT); 
    }
#line 1279 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 34: // expr: expr "/" expr
#line 264 "parser.y"
                    { 
        yylhs.value.as < ExprNode* > () = new ExprNode(yystack_[2].value.as < ExprNode* > (), yystack_[0].value.as < ExprNode* > (), Operator::DIV); 
    }
#line 1287 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 35: // expr: expr "%" expr
#line 267 "parser.y"
                    { 
        yylhs.value.as < ExprNode* > () = new ExprNode(yystack_[2].value.as < ExprNode* > (), yystack_[0].value.as < ExprNode* > (), Operator::MOD); 
    }
#line 1295 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 36: // expr: "(" expr ")"
#line 270 "parser.y"
                   { 
        yylhs.value.as < ExprNode* > () = yystack_[1].value.as < ExprNode* > (); 
    }
#line 1303 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 37: // logical_expr: "logical_constant"
#line 275 "parser.y"
                       {
        yylhs.value.as < LogicalExprNode* > () = new LogicalConstantNode(yystack_[0].value.as < bool > ());
    }
#line 1311 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 38: // logical_expr: "!" logical_expr
#line 278 "parser.y"
                       { 
        yylhs.value.as < LogicalExprNode* > () = new LogicalExprNode(yystack_[0].value.as < LogicalExprNode* > (), nullptr, LogicalOperator::NOT);
    }
#line 1319 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 39: // logical_expr: logical_expr "&" logical_expr
#line 281 "parser.y"
                                    { 
        yylhs.value.as < LogicalExprNode* > () = new LogicalExprNode(yystack_[2].value.as < LogicalExprNode* > (), yystack_[0].value.as < LogicalExprNode* > (), LogicalOperator::AND);
    }
#line 1327 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 40: // logical_expr: logical_expr "|" logical_expr
#line 284 "parser.y"
                                    { 
        yylhs.value.as < LogicalExprNode* > () = new LogicalExprNode(yystack_[2].value.as < LogicalExprNode* > (), yystack_[0].value.as < LogicalExprNode* > (), LogicalOperator::OR); 
    }
#line 1335 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 41: // logical_expr: logical_expr "==" logical_expr
#line 287 "parser.y"
                                     {
        yylhs.value.as < LogicalExprNode* > () = new LogicalExprNode(yystack_[2].value.as < LogicalExprNode* > (), yystack_[0].value.as < LogicalExprNode* > (), LogicalOperator::EQUAL); 
    }
#line 1343 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 42: // logical_expr: logical_expr "!=" logical_expr
#line 290 "parser.y"
                                     {
        yylhs.value.as < LogicalExprNode* > () = new LogicalExprNode(yystack_[2].value.as < LogicalExprNode* > (), yystack_[0].value.as < LogicalExprNode* > (), LogicalOperator::NOT_EQUAL); 
    }
#line 1351 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 43: // logical_expr: "(" logical_expr ")"
#line 293 "parser.y"
                           { 
        yylhs.value.as < LogicalExprNode* > () = yystack_[1].value.as < LogicalExprNode* > (); 
    }
#line 1359 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 44: // logical_expr: expr "==" expr
#line 296 "parser.y"
                     {
        yylhs.value.as < LogicalExprNode* > () = new ComparasionNode(yystack_[2].value.as < ExprNode* > (), yystack_[0].value.as < ExprNode* > (), LogicalOperator::EQUAL); 
    }
#line 1367 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 45: // logical_expr: expr "!=" expr
#line 299 "parser.y"
                     {
        yylhs.value.as < LogicalExprNode* > () = new ComparasionNode(yystack_[2].value.as < ExprNode* > (), yystack_[0].value.as < ExprNode* > (), LogicalOperator::NOT_EQUAL); 
    }
#line 1375 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 46: // logical_expr: expr "<" expr
#line 302 "parser.y"
                    {
        yylhs.value.as < LogicalExprNode* > () = new ComparasionNode(yystack_[2].value.as < ExprNode* > (), yystack_[0].value.as < ExprNode* > (), LogicalOperator::LESS);
    }
#line 1383 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;

  case 47: // logical_expr: expr ">" expr
#line 305 "parser.y"
                    {
        yylhs.value.as < LogicalExprNode* > () = new ComparasionNode(yystack_[2].value.as < ExprNode* > (), yystack_[0].value.as < ExprNode* > (), LogicalOperator::GREATHER);
    }
#line 1391 "/home/snail/Code/FormalLang/interpreter/parser.cpp"
    break;


#line 1395 "/home/snail/Code/FormalLang/interpreter/parser.cpp"

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

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
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

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
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
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
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


  const signed char parser::yypact_ninf_ = -60;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
     -60,    12,    88,   -60,   -60,    -9,    -2,     4,   -60,   -60,
       0,     1,    18,   -60,   -60,    99,    37,    37,    26,    -1,
      -6,   -60,   -60,   -60,   -60,     3,   -60,    26,    37,    37,
      31,   -60,   -60,   -60,    79,    83,    92,    26,   125,   -60,
      32,    43,   -60,   125,    -6,   -60,    49,   112,    55,   101,
      26,    26,    26,    26,    26,    26,    26,    26,    26,    37,
      37,    37,    37,    50,    50,    70,   -60,    -1,   -60,   -60,
     -60,    49,    49,   -60,   -60,   -60,   125,   125,   125,   125,
     -60,   -60,     7,     7,    56,   -60,   -60,    50,   -60
  };

  const signed char
  parser::yydefact_[] =
  {
       4,     0,     2,     1,     7,     0,     0,     0,    13,     5,
       0,     0,     0,    11,    12,     0,     0,     0,     0,    16,
       0,     6,     9,    10,     3,     0,     8,     0,     0,     0,
      28,    27,    37,    29,     0,     0,     0,     0,    24,    21,
       0,    17,    18,    20,    22,    14,    30,    38,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    15,     0,    23,    36,
      43,    32,    31,    33,    34,    35,    44,    45,    46,    47,
      41,    42,    39,    40,     0,    25,    19,     0,    26
  };

  const signed char
  parser::yypgoto_[] =
  {
     -60,   -60,   -59,   -60,   -60,    57,   -60,     8,   -60,   -60,
      13,    38,   -60,   -60,   -60,   -18,   -15
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,     1,     8,     2,    15,     9,    10,    33,    40,    41,
      42,    45,    12,    13,    14,    34,    35
  };

  const signed char
  parser::yytable_[] =
  {
      38,    43,    36,    27,    84,    85,    18,    18,    16,    46,
      11,    48,     3,    47,    49,    17,    37,    59,    60,    65,
      19,    19,    44,    11,    21,    22,    30,    20,    88,    39,
      27,    31,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    27,    23,    37,    80,    81,    82,    83,    19,    43,
      66,    28,    67,    30,    29,    52,    53,    54,    31,    50,
      51,    52,    53,    54,    30,    55,    56,    57,    58,    31,
      32,     4,    26,    69,    50,    51,    52,    53,    54,    87,
      86,     0,    68,    50,    51,    52,    53,    54,    69,    55,
      56,    57,    58,    59,    60,     0,     0,     0,    61,    62,
       0,    63,    59,    60,     0,     0,     0,    61,    62,     4,
      64,    59,    60,     5,     6,     7,    61,    62,     0,    70,
       4,    24,    59,    60,     5,     6,    25,    61,    62,    50,
      51,    52,    53,    54
  };

  const signed char
  parser::yycheck_[] =
  {
      18,    19,    17,     4,    63,    64,     3,     3,    17,    27,
       2,    29,     0,    28,    29,    17,    17,    10,    11,    37,
      17,    17,    28,    15,    24,    24,    27,    23,    87,    30,
       4,    32,    50,    51,    52,    53,    54,    55,    56,    57,
      58,     4,    24,    17,    59,    60,    61,    62,    17,    67,
      18,    14,     9,    27,    17,     6,     7,     8,    32,     4,
       5,     6,     7,     8,    27,    10,    11,    12,    13,    32,
      33,    21,    15,    18,     4,     5,     6,     7,     8,    23,
      67,    -1,    44,     4,     5,     6,     7,     8,    18,    10,
      11,    12,    13,    10,    11,    -1,    -1,    -1,    15,    16,
      -1,    18,    10,    11,    -1,    -1,    -1,    15,    16,    21,
      18,    10,    11,    25,    26,    27,    15,    16,    -1,    18,
      21,    22,    10,    11,    25,    26,    27,    15,    16,     4,
       5,     6,     7,     8
  };

  const signed char
  parser::yystos_[] =
  {
       0,    36,    38,     0,    21,    25,    26,    27,    37,    40,
      41,    42,    47,    48,    49,    39,    17,    17,     3,    17,
      23,    24,    24,    24,    22,    27,    40,     4,    14,    17,
      27,    32,    33,    42,    50,    51,    51,    17,    50,    30,
      43,    44,    45,    50,    28,    46,    50,    51,    50,    51,
       4,     5,     6,     7,     8,    10,    11,    12,    13,    10,
      11,    15,    16,    18,    18,    50,    18,     9,    46,    18,
      18,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      51,    51,    51,    51,    37,    37,    45,    23,    37
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    35,    36,    37,    38,    38,    38,    39,    39,    40,
      40,    40,    40,    40,    41,    42,    43,    43,    44,    44,
      45,    45,    46,    46,    47,    48,    49,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     3,     0,     2,     3,     0,     2,     2,
       2,     1,     1,     1,     3,     4,     0,     1,     1,     3,
       1,     1,     1,     2,     3,     5,     7,     1,     1,     1,
       2,     3,     3,     3,     3,     3,     3,     1,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"=\"", "\"-\"",
  "\"+\"", "\"*\"", "\"/\"", "\"%\"", "\",\"", "\"==\"", "\"!=\"", "\"<\"",
  "\">\"", "\"!\"", "\"&\"", "\"|\"", "\"(\"", "\")\"", "\"[\"", "\"]\"",
  "\"{\"", "\"}\"", "\":\"", "\";\"", "\"?\"", "\"@\"", "\"identifier\"",
  "\"tag\"", "\"value\"", "\"string\"", "\"character\"", "\"number\"",
  "\"logical_constant\"", "\"^\"", "$accept", "program", "block",
  "external_statements", "statements", "statement", "create_var",
  "call_func", "args_or_none", "args", "any_arg", "tags", "assignment",
  "loop", "condition", "expr", "logical_expr", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   116,   116,   122,   127,   128,   132,   138,   139,   145,
     148,   151,   154,   157,   162,   167,   187,   188,   193,   196,
     202,   205,   210,   213,   219,   232,   237,   242,   245,   249,
     252,   255,   258,   261,   264,   267,   270,   275,   278,   281,
     284,   287,   290,   293,   296,   299,   302,   305
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
#line 1925 "/home/snail/Code/FormalLang/interpreter/parser.cpp"

#line 309 "parser.y"


void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
