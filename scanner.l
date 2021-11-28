%{
    #include <cerrno>
    #include <climits>
    #include <cstdlib>
    #include <cstring> // strerror
    #include <string>
    #include <iostream>
    #include "driver.hh"
    #include "parser.hh"
%}

%option noyywrap nounput noinput batch debug

%option c++
%option yyclass="Scanner"

%{
  // Code definitions at the end of scanner.cpp

  // A number symbol corresponding to the value in S.
  yy::parser::symbol_type make_NUMBER(
    const std::string &s,
    const yy::parser::location_type& loc
  );

  void Scanner::UpdateLocation() {
    if (driver.location_debug) {
        std::cerr << "Action called " << driver.location << std::endl;
    }
    driver.location.columns(yyleng);
  }
%}

id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
blank [ \t\r]

tag #[a-zA-Z_0-9]+
value $[a-zA-Z_0-9]+
ch '[^\"'\\]|(\\["'0n\\])'
str \"{ch}*\"


%{
  // Code run each time a pattern is matched.
  #define YY_USER_ACTION UpdateLocation();
%}

%%


%{
  // A handy shortcut to the location held by the driver.
  yy::location& loc = driver.location;
  if (driver.location_debug) {
  // Code run each time yylex is called.
    std::cerr << "BEFORE " << loc << std::endl;
  }
  // loc.step();
  if (driver.location_debug) {
    std::cerr << "AFTER " <<  loc << std::endl;
  }
%}

{blank}+   {
    if (driver.location_debug) {
        std::cerr << "Blank matched" << std::endl;
    }
    // loc.step();
}
\n+ {
    if (driver.location_debug) {
        std::cerr << "EOL called" << std::endl;
    }
    loc.lines(yyleng);
    loc.step();
}

"="        return yy::parser::make_ASSIGN(loc);

"-"        return yy::parser::make_MINUS(loc);
"+"        return yy::parser::make_PLUS(loc);
"*"        return yy::parser::make_STAR(loc);
"/"        return yy::parser::make_SLASH(loc);
"%"        return yy::parser::make_MOD(loc);

","        return yy::parser::make_COMMA(loc);

"=="       return yy::parser::make_EQUAL();
"!="       return yy::parser::make_NOT_EQUAL();

"!"        return yy::parser::make_NOT();
"&"        return yy::parser::make_AND();
"|"        return yy::parser::make_OR();

"("        return yy::parser::make_LPAREN(loc);
")"        return yy::parser::make_RPAREN(loc);
"["        return yy::parser::make_LBRACKET(loc);
"]"        return yy::parser::make_RBRACKET(loc);
"{"        return yy::parser::make_LBLOCK(loc);
"}"        return yy::parser::make_RBLOCK(loc);

":"        return yy::parser::make_COLON(loc); 
";"        return yy::parser::make_SEMICOLON(loc);
"?"        return yy::parser::make_CONDITION(loc);
"@"        return yy::parser::make_LOOP(loc);

{int}      return make_NUMBER(yytext, loc);
{id}       {
                if (driver.location_debug) {
                    std::cerr << "ID found " << yytext << std::endl;
                }
                return yy::parser::make_IDENTIFIER(yytext, loc);
           }
{tag}      return yy::parser::make_TAG(yytext, value);
{value}    {
                if (strcmp(yytext, "#true")) {
                    return yy::parser::make_LOGICAL_CONSTANT(true, loc);
                } else if (strcmp(yytext, "#false")) {
                    return yy::parser::make_LOGICAL_CONSTANT(false, loc);
                } else {
                    return yy::parser::make_VALUE(yytext, loc);
                }
           }
{ch}       return yy::parser::make_CHARACTER(yytext, loc);
{str}      return yy::parser::MAKE_STRING(yytext, loc);
.          {
                throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext));
           }
<<EOF>>    return yy::parser::make_END (loc);
%%

yy::parser::symbol_type make_NUMBER(
  const std::string &s,
  const yy::parser::location_type& loc
) {
  errno = 0;
  long n = strtol(s.c_str(), NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error(loc, "integer is out of range: " + s);
  return yy::parser::make_NUMBER((int) n, loc);
}