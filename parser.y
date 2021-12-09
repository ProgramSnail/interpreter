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

    class Node;
    class RootNode;
    class ExprNode;
    class NumberExprNode;
    class VarExprNode;
    class LogicalExprNode;
    class ComparasionNode;
    class LogicalConstantNode;
    class AssignmentNode;
    class CallFuncNode;
    class CallTFuncNode;
    class BlockNode;
    class ConditionNode;
    class LoopNode;
    class CreateVarNode;

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

%nterm <std::unique_ptr<BlockNode>> program
%nterm <std::unique_ptr<BlockNode>> block
%nterm <std::vector<std::unique_ptr<Node>>> statements
%nterm <std::unique_ptr<Node>> statement
%nterm <std::unique_ptr<CreateVarNode>> create_var
%nterm <std::unique_ptr<CallFuncNode>> call_func
%nterm <std::vector<std::unique_ptr<Node>>> args
%nterm <std::unique_ptr<LoopNode>> loop
%nterm <std::unique_ptr<ConditionNode>> condition
%nterm <std::vector<std::string>> tags
%nterm <std::unique_ptr<Node>> any_expr
%nterm <std::unique_ptr<AssignmentNode>> assignment
%nterm <std::unique_ptr<LogicalExprNode>> logical_expr
%nterm <std::unique_ptr<ExprNode>> expr

// Prints output in parsing option for debugging location terminal
%printer { yyo << $$; } <*>;

%%
%left "+" "-";
%left "*" "/" "%";

%left "!";
%left "&" "|" "^";

%start program;
program:
    statements {
        $$ = std::make_unique<BlockNode>(std::move($1));
    };

block:
    "{" statements "}" {
        $$ = std::make_unique<BlockNode>(std::move($2));
    };

statements:
    %empty {
        //$$ = vector<std::unique_ptr<Node>>();
    }
    | statements statement {
        $$ = std::move($1);
        $$.push_back(std::move(make_unique($2)));
    };

statement:
    assignment ";" {
        $$ = std::move($1);
    }
    | call_func ";" {
        $$ = std::move($1);
    }
    | create_var ";" {
        $$ = std::move($1);
    }
    | loop {
        $$ = std::move($1);
    }
    | condition {
        $$ = std::move($1);
    }
    | block {
        $$ = std::move($1);
    };

create_var: // todo: add initialization
    "identifier" ":" tags {
        $$ = make_unique<CreateVarNode>($1, $3);
        //driver.variables[$1] = 0;
    };

call_func:
    "identifier" "(" args ")" {
        FuncType id = FuncType::NONE;
        // choose func type from $1
        $$ = make_unique<CallFuncNode>(id, $3);
    };

args:
    %empty {
        // $$ = vector<std::unique_ptr<Node>>()
    }
    | args "," expr {
        $$ = std::move($1);
        $$.push_back(std::move($3));
    };

any_expr:
    expr {
        $$ = std::move($1);
    }
    | logical_expr {
        $$ = std::move($1);
    };

tags:
    "tag" { $$ = $1; }
    | "tag" tags { 
        $$ = $2;
        $$.push_back($1);
    };

assignment:
    "identifier" "=" expr {
        $$ = std::make_unique<AssignmentNode>($1, $3);
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
        $$ = make_unique<LoopNode>(std::move($3), std::move($5));
    };

condition:
    "?" "(" logical_expr ")" block {
        $$ = make_unique<ConditionNode>(std::move($3), std::move($5));
    };

expr:
    "number" { 
        $$ = std::make_unique<NumberExprNode>($1); 
    }
    | "identifier" { 
        $$ = std::make_unique<VarExprNode>($1);
        /*driver.variables[$1];*/
    }
    | call_func {
        $$ = std::move($1);
    }
    | "-" expr {
        $$ = std::make_unique<ExprNode>($2, nullptr, Operator::NEGATIVE);
    }
    | expr "+" expr { 
        $$ = std::make_unique<ExprNode>($1, $3, Operator::ADD); }
    | expr "-" expr { 
        $$ = std::make_unique<ExprNode>($1, $3, Operator::SUB); }
    | expr "*" expr { 
        $$ = std::make_unique<Expr_Node>($1, $3 Operator::MULT); }
    | expr "/" expr { 
        $$ = std::make_unique<ExprNode>($1, $3 Operator::DIV); }
    | expr "%" expr { 
        $$ = std::make_unique<ExprNode>($1, $3, Operator::MOD); } 
    | "(" expr ")" { 
        $$ = std::move($2); 
    };

logical_expr:
    "logical_constant" {
        $$ = std::make_unique<LogicalConstantNode>($1);
    }
    | "!" logical_expr { 
        $$ = std::make_unique<LogicalExprNode>($2, nullptr, LogicalOperator::NOT);
    }
    | logical_expr "&" logical_expr { 
        $$ = std::make_unique<LogicalExprNode>($1, $3, LogicalOperator::AND);
    }
    | logical_expr "|" logical_expr { 
        $$ = std::make_unique<LogicalExprNode>($1, $3, LogicalOperator::OR); 
    }
    | logical_expr "==" logical_expr {
        $$ = std::make_unique<LogicalExprNode>($1, $3, LogicalOperator::EQUAL); 
    }
    | logical_expr "!=" logical_expr {
        $$ = std::make_unique<LogicalExprNode>($1, $3, LogicalOperator::NOT_EQUAL); 
    }
    | "(" logical_expr ")" { 
        $$ = std::move($2); 
    }
    | expr "==" expr {
        $$ = std::make_unique<ComparasionNode>($1, $3, LogicalOperator::EQUAL); 
    }
    | expr "!=" expr {
        $$ = std::make_unique<ComparasionNode>($1, $3, LogicalOperator::NOT_EQUAL); 
    };

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
