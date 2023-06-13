#include "./token.h"
#include "lexer.h"
#include <string.h>
#include <stdlib.h>

typedef struct {
  const char* keyword;
  TokenType tokenType;
} KeywordMapping;

// This should probably be a hashmap instead of an array
KeywordMapping keywords[] = {
  {"fn", FUNCTION},
  {"let", LET},
  {"if", IF},
  {"else", ELSE},
  {"return", RETURN},
  {"true", TRUE},
  {"false", FALSE}
};

TokenType LookupIdent(char* ident)
{
  for (int i = 0; i < sizeof(keywords) / sizeof(KeywordMapping); i++)
    if (strcmp(keywords[i].keyword, ident) == 0)
      return keywords[i].tokenType;
  return IDENT;
}

Lexer CreateNewLexer(char* string)
{
  Lexer l = {
    string,
    0,
    0,
    string[0]
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

Token LexerNewToken(TokenType type, char literal)
{
  Token tok;
  tok.Type = type;
  char* str = (char*)malloc(2 * sizeof(char));
  str[0] = literal;
  str[1] = '\0';
  tok.Literal = str;
  return tok;
}

int IsLetter(char ch) {
  return 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == '_';
}

char* LexerReadIdentifier(Lexer* lexer)
{
  int position = lexer->position;

  while(IsLetter(lexer->ch))
    LexerReadChar(lexer);

  int length = lexer->position - position;
  char* identifier = (char*)malloc((length+1) * sizeof(char));
  strncpy(identifier, lexer->input+position, length);

  identifier[length] = '\0';
  return identifier;
}

void LexerSkipWhitespace(Lexer* lexer)
{
  while (lexer->ch == ' ' || lexer->ch == '\t' || lexer->ch == '\n' || lexer->ch == '\r')
    LexerReadChar(lexer);
};

int IsDigit(char ch)
{
  return '0' <= ch && ch <= '9';
}

char* LexerReadNumber(Lexer* lexer)
{
  int position = lexer->position;

  while(IsDigit(lexer->ch))
    LexerReadChar(lexer);

  int length = lexer->position - position;
  char* number = (char*)malloc((length+1) * sizeof(char));
  strncpy(number, lexer->input+position, length);

  number[length] = '\0';
  return number;
}

Token LexerNextToken(Lexer* lexer)
{
  Token tok;
  
  LexerSkipWhitespace(lexer);

  switch (lexer->ch) {
    case '=':
      tok = LexerNewToken(ASSIGN, lexer->ch);
    break;
    case ';':
      tok = LexerNewToken(SEMICOLON, lexer->ch);
    break;
    case '(':
      tok = LexerNewToken(LPAREN, lexer->ch);
    break;
    case ')':
      tok = LexerNewToken(RPAREN, lexer->ch);
    break;
    case '{':
      tok = LexerNewToken(LBRACE, lexer->ch);
    break;
    case '}':
      tok = LexerNewToken(RBRACE, lexer->ch);
    break;
    case ',':
      tok = LexerNewToken(COMMA, lexer->ch);
    break;
    case '+':
      tok = LexerNewToken(PLUS, lexer->ch);
    break;
    case '-':
      tok = LexerNewToken(MINUS, lexer->ch);
    break;
    case '!':
      tok = LexerNewToken(BANG, lexer->ch);
    break;
    case '*':
      tok = LexerNewToken(ASTERISK, lexer->ch);
    break;
    case '/':
      tok = LexerNewToken(SLASH, lexer->ch);
    break;
    case '<':
      tok = LexerNewToken(LT, lexer->ch);
    break;
    case '>':
      tok = LexerNewToken(GT, lexer->ch);
    break;
    case 0:
      tok.Literal = "";
      tok.Type = EOF;
    break;
    default:
      if (IsLetter(lexer->ch))
      {
        tok.Literal = LexerReadIdentifier(lexer);
        tok.Type = LookupIdent(tok.Literal);
        return tok;
      }
      else if (IsDigit(lexer->ch))
      {
        tok.Literal = LexerReadNumber(lexer);
        tok.Type = INT;
        return tok;
      }
      else
      {
        tok = LexerNewToken(ILLEGAL, lexer->ch);
      }
    break;
  }

  LexerReadChar(lexer);

  return tok;
}

