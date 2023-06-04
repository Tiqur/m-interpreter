#include "./token.h"
#include "lexer.h"
#include <string.h>

Lexer CreateNewLexer(char* string)
{
  Lexer l = {
    string
  };
  return l;
};

void LexerReadChar(Lexer* lexer)
{
  if (lexer->readPosition >= strlen(lexer->input))
  {
    lexer->ch = 0;
  } 
  else
  {
    lexer->ch = lexer->input[lexer->readPosition];
  }
  lexer->position = lexer->readPosition;
  lexer->readPosition += 1;
}

Token LexerNewToken(TokenType type, char* literal) {
  Token tok;
  tok.Type = type;
  tok.Literal = literal;
  return tok;
}

Token LexerNextToken(Lexer* lexer)
{
  Token tok;
  
  LexerReadChar(lexer);

  switch (lexer->ch) {
    case '=':
      tok = LexerNewToken(ASSIGN, &lexer->ch);
    break;
    case ';':
      tok = LexerNewToken(SEMICOLON, &lexer->ch);
    break;
    case '(':
      tok = LexerNewToken(LPAREN, &lexer->ch);
    break;
    case ')':
      tok = LexerNewToken(RPAREN, &lexer->ch);
    break;
    case '{':
      tok = LexerNewToken(LBRACE, &lexer->ch);
    break;
    case '}':
      tok = LexerNewToken(RBRACE, &lexer->ch);
    break;
    case ',':
      tok = LexerNewToken(COMMA, &lexer->ch);
    break;
    case '+':
      tok = LexerNewToken(PLUS, &lexer->ch);
    break;
    case '0':
      tok.Literal = "";
      tok.Type = EOF;
    break;
  }

  return tok;
}

