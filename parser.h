#ifndef PARSER_H
#define PARSER_H
#include <QString>
#include "token.h"
#include "lexer.h"

class Parser
{
public:
        Token _currentToken;
        Lexer _lexer;
        Parser(QString sourceCode);
        bool Parse();
        bool Programa();
        bool Lista_Sentencias();
        bool Sentencia();
        bool E();
        bool Ep();
        bool T();
        bool Tp();
        bool F();
};

#endif // PARSER_H
