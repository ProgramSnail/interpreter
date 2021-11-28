%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    #include <variant>
    /* Forward declaration of classes in order to disable cyclic dependencies */
    class Scanner;
    class Driver;
}


%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"

    /* Redefine parser to use our function from scanner */
    static yy::parser::symbol_type yylex(Scanner &scanner) {
        return scanner.ScanToken();
    }
}

%lex-param { Scanner &scanner }

%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%locations

%define api.token.prefix {TOK_}
// token name in variable
%token
    END 0 "end of file"
    ASSIGN "="
    
    MINUS "-"
    PLUS "+"
    STAR "*"
    SLASH "/"
    MOD "%"

    COMMA ","

    EQUAL "=="
    NOT_EQUAL "!="

    NOT "!"
    AND "&"
    OR "|"

    LPAREN "("
    RPAREN ")"
    RBRACKET "["
    LBRACKET "]"
    LBLOCK "{"
    RBLOCK "}"
    
    COLON ":"
    SEMICOLON ";"
    CONDITION "?"
    LOOP "@"
;

%token <std::string> IDENTIFIER "identifier"
%token <std::string> TAG "tag"
%token <std::string> VALUE "value"
%token <std::string> STRING "string"
%token <std::string> CHARACTER "character"
%token <int> NUMBER "number"
%token <bool> LOGICAL_CONSTANT "logical_constant"

%nterm <std::vector<std::string>> tags
%nterm <std::pair<int, bool>> any_expr // better have std::variant, but it requires c++17
%nterm <int> expr

// Prints output in parsing option for debugging location terminal
%printer { yyo << $$; } <*>;

%%
%left "+" "-";
%left "*" "/";

%left "!";
%left "&" "|" "^";

%start unit;
unit: assignments exp ";" { driver.result = $2; };

statements:
    %empty {}
    | statements statement {};

statement:
    assignment {}
    | create_var {}
    | loop {}
    | condition {};

create_var: // todo: add initialization
    "identifier" ":" tags {
        //
    }
    | "identifier" ":" tags {
        //
    };

call_func:
    "identifier" "(" args ")" ";" {};

args:
    %empty {
        //
    }
    | any_expr "," args {
        //
    };

any_expr:
    expr {
        //
    }
    | logical_expr {
        //
    };

tags:
    "tag" { $$ = $1; }
    | "tag" tags { 
        $$ = $2;
        $$.push_back($1);
    };

assignment:
    "identifier" "=" expr ";" {
        //
        driver.variables[$1] = $3;
        if (driver.location_debug) {
            std::cerr << driver.location << std::endl;
        }
    }
    | "identifier" "=" logical_expr ";" {
        //
    }
    | error ";" { // ??
    	// Hint for compilation error, resuming producing messages
    	std::cerr << "You should provide assignment in the form: variable := expression ; " << std::endl;
    };


loop:
    "@" "(" LOGICAL_EXPR ")" "{" statements "}" {
        //
    };

condition:
    "?" "(" LOGICAL_EXPR ")" "{" statements "}" {
        //
    };

expr:
    "number"
    | "identifier" { $$ = driver.variables[$1]; }
    | expr "+" expr { $$ = $1 + $3; }
    | expr "-" expr { $$ = $1 - $3; }
    | expr "*" expr { $$ = $1 * $3; }
    | expr "/" expr { $$ = $1 / $3; }
    | expr "%" expr { $$ = $1 % $3; }
    | "(" expr ")" { $$ = $2; };

logical_expr:
    "logical_constant"
    | "identifier" { $$ = driver.variables[$1]; }
    | "!" logical_expr { $$ = !$2; }
    | logical_expr "&" logical_expr { $$ = $1 && $3; }
    | logical_expr "|" logical_expr { $$ = $1 || $3; }
    | "(" logical_expr ")" { $$ = $2; }
    | any_expr "==" any_expr {$$ = ($1 == $3); }
    | any_expr "!=" any_expr {$$ = ($1 != $3); };

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
