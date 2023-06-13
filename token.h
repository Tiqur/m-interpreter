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


typedef char* TokenType;

typedef struct Token
{
  TokenType Type;
  char* Literal; 
}
Token;

#endif
