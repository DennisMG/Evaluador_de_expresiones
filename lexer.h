#ifndef LEXER_H
#define LEXER_H
#include "token.h"
#include <QMap>
#include <QString>

class Lexer
{
public:
    Lexer(QString inputBuffer);
        Lexer();
        QString _inputBuffer;
        int _currentPosition;
        char _currentSymbol;
        QMap<char, Token::TokenType> _symbolIndex;
        Token GetNextToken();
        char GetNextSymbol();
        QByteArray array;
        char* buffer;
};

#endif // LEXER_H
