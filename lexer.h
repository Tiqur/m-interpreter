#ifndef LEXER_H
#define LEXER_H

#include "./token.h"

typedef struct Lexer
{
  char* input;
  int position;
  int readPosition;
  char ch;
}
Lexer;


Lexer CreateNewLexer(char* string);
void LexerReadChar(Lexer* lexer);
Token LexerNewToken(TokenType type, char literal);
Token LexerNextToken(Lexer* lexer);
#endif /* LEXER_H */
