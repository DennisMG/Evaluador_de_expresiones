#include "token.h"

Token::Token(TokenType t, QString l)
{
    this->Type=t;
    this->Lexeme=l;
}
Token::Token()
{

}

Token::TokenType Token::getType()
{
    return Type;
}

void Token::setType(Token::TokenType type)
{
    Type=type;

}
