#ifndef TOKEN_H
#include <stdio.h>
#undef EOF

#define TOKEN_H

#define ILLEGAL "ILLEGAL"
#define EOF "EOF"

// Identifiers + literals
#define IDENT "IDENT"
#define INT "INT"

// Operators
#define ASSIGN "="
#define PLUS "+"
#define MINUS "-"
#define BANG "!"
#define ASTERISK "*"
#define SLASH "/"
#define LT "<"
#define GT ">"

// Delimiters
#define COMMA ","
#define SEMICOLON ";"

#define LPAREN "("
#define RPAREN ")"
#define LBRACE "{"
#define RBRACE "}"

// Keywords
#define FUNCTION "FUNCTION"
#define LET "LET"
#define IF "IF"
#define ELSE "ELSE"
#define RETURN "RETURN"
#define TRUE "TRUE"
#define FALSE "FALSE"


typedef char* TokenType;

typedef struct Token
{
  TokenType Type;
  char* Literal; 
}
Token;

#endif
