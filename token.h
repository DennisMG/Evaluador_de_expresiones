#ifndef TOKEN_H
#define TOKEN_H
#include <QString>

class Token
{
public:
    Token();

        enum TokenType{
                Sum,
                Substract,
                Multiplication,
                Division,
                SemiColon,
                LeftParenthesis,
                RightParenthesis,
                Id,
                Number,
                EndOfFile,
                Print,
                Equals
        };

        TokenType Type;
        QString Lexeme;
        Token(TokenType t,QString l);
        Token::TokenType getType();
        void setType(Token::TokenType type);
};

#endif // TOKEN_H
