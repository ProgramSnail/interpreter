%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    #include <memory>
    #include <vector>
    /* Forward declaration of classes in order to disable cyclic dependencies */
    class Scanner;
    class Driver;

    #include "parse_tree.hh"
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
    LESS "<"
    GREATHER ">"

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

%nterm <BlockNode*> program
%nterm <BlockNode*> block
%nterm <std::vector<Node*>> external_statements
%nterm <std::vector<Node*>> statements
%nterm <Node*> statement
%nterm <CreateVarNode*> create_var
%nterm <CallFuncNode*> call_func
%nterm <std::vector<Node*>> args_or_none
%nterm <std::vector<Node*>> args
%nterm <Node*> any_arg
%nterm <LoopNode*> loop
%nterm <ConditionNode*> condition
%nterm <std::vector<std::string>> tags
%nterm <AssignmentNode*> assignment
%nterm <LogicalExprNode*> logical_expr
%nterm <ExprNode*> expr

// Prints output in parsing option for debugging location terminal
%printer { /*yyo << $$;*/ } <*>;

%%
%left "+" "-";
%left "*" "/" "%";

%left "!";
%left "&" "|" "^";
%left "==" "!=" "<" ">";
%left "=";

%start program;
program:
    external_statements {
        $$ = new BlockNode($1);
        $$->execute();
    };

block:
    "{" statements "}" {
        $$ = new BlockNode($2);
    };

external_statements:
    %empty {}
    | external_statements statement {
        $$ = $1;
        $$.push_back($2);
    }
    | external_statements create_var ";" {
        $$ = $1;
        $$.push_back($2);
    };

statements:
    %empty {}
    | statements statement {
        $$ = $1;
        $$.push_back($2);
    };

statement:
    call_func ";" {
        $$ = $1;
    }
    | assignment ";" {
        $$ = $1;
    }
    | loop {
        $$ = $1;
    }
    | condition {
        $$ = $1;
    }
    | block {
        $$ = $1;
    };

create_var: // todo: add initialization
    "identifier" ":" tags {
        $$ = new CreateVarNode($1, $3, &(driver.storage));
    };

call_func:
    "identifier" "(" args_or_none ")" {
        FuncType id = FuncType::NONE;
        if ($1 == "print") {
            id = FuncType::PRINT;
        } else if ($1 == "write") {
            id = FuncType::WRITE;
        } else if ($1 == "scan") {
            id = FuncType::SCAN;
        } else {
            CallRuntimeError("RE: Unrecognized function name.");
        }
        // choose func type from $1
        if (id == FuncType::SCAN) {
            $$ = new CallTFuncNode(id, $3);
        } else {
            $$ = new CallFuncNode(id, $3);
        }
    };

args_or_none:
    %empty {}
    | args {
        $$ = $1;
    };

args:
    any_arg {
        $$.push_back($1);
    }
    | args "," any_arg {
        $$ = $1;
        $$.push_back($3);
    };

any_arg:
    expr {
        $$ = $1;
    }
    | "string" {
        $$ = new StringNode($1);
    };

tags:
    "tag" { 
        $$.push_back($1); 
    }
    | "tag" tags { 
        $$ = $2;
        $$.push_back($1);
    };

assignment:
    "identifier" "=" expr {
        $$ = new AssignmentNode($1, $3, &(driver.storage));
        /*if (driver.location_debug) {
            std::cerr << driver.location << std::endl;
        }*/
    };
    /*| error ";" { // ??
    	// Hint for compilation error, resuming producing messages
    	std::cerr << "You should provide assignment in the form: variable := expression ; " << std::endl;
    };*/


loop:
    "@" "(" logical_expr ")" block {
        $$ = new LoopNode($3, $5);
    };

condition:
    "?" "(" logical_expr ")" block ":" block {
        $$ = new ConditionNode($3, $5, $7);
    };

expr:
    "number" { 
        $$ = new NumberExprNode($1); 
    }
    | "identifier" { 
        $$ = new VarExprNode($1, &(driver.storage));
        /*driver.variables[$1];*/
    }
    | call_func {
        $$ = $1;
    }
    | "-" expr {
        $$ = new ExprNode($2, nullptr, Operator::NEGATIVE);
    }
    | expr "+" expr { 
        $$ = new ExprNode($1, $3, Operator::ADD); 
    }
    | expr "-" expr { 
        $$ = new ExprNode($1, $3, Operator::SUB); 
    }
    | expr "*" expr { 
        $$ = new ExprNode($1, $3, Operator::MULT); 
    }
    | expr "/" expr { 
        $$ = new ExprNode($1, $3, Operator::DIV); 
    }
    | expr "%" expr { 
        $$ = new ExprNode($1, $3, Operator::MOD); 
    } 
    | "(" expr ")" { 
        $$ = $2; 
    };

logical_expr:
    "logical_constant" {
        $$ = new LogicalConstantNode($1);
    }
    | "!" logical_expr { 
        $$ = new LogicalExprNode($2, nullptr, LogicalOperator::NOT);
    }
    | logical_expr "&" logical_expr { 
        $$ = new LogicalExprNode($1, $3, LogicalOperator::AND);
    }
    | logical_expr "|" logical_expr { 
        $$ = new LogicalExprNode($1, $3, LogicalOperator::OR); 
    }
    | logical_expr "==" logical_expr {
        $$ = new LogicalExprNode($1, $3, LogicalOperator::EQUAL); 
    }
    | logical_expr "!=" logical_expr {
        $$ = new LogicalExprNode($1, $3, LogicalOperator::NOT_EQUAL); 
    }
    | "(" logical_expr ")" { 
        $$ = $2; 
    }
    | expr "==" expr {
        $$ = new ComparasionNode($1, $3, LogicalOperator::EQUAL); 
    }
    | expr "!=" expr {
        $$ = new ComparasionNode($1, $3, LogicalOperator::NOT_EQUAL); 
    }
    | expr "<" expr {
        $$ = new ComparasionNode($1, $3, LogicalOperator::LESS);
    }
    | expr ">" expr {
        $$ = new ComparasionNode($1, $3, LogicalOperator::GREATHER);
    };

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
