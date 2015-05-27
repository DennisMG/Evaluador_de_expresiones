#include "parser.h"
#include "lexer.h"
#include "token.h"
#include <QString>
#include <iostream>
using namespace std;


Parser::Parser(QString sourceCode){
    _lexer = Lexer::Lexer(sourceCode);
    _currentToken = _lexer.GetNextToken();
}

bool Parser::Parse()
{
    return Programa();
    if (_currentToken.Type != Token::EndOfFile)
        return false;
}

bool Parser::Programa()
{
    return Lista_Sentencias();
}

bool Parser::Lista_Sentencias()
{

    if (_currentToken.Type == Token::Id || _currentToken.Type == Token::Print)
    {
        if (Sentencia())
                        {
                            if (!Lista_Sentencias())
                                return false;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    //este es el epsilon
                    else
                    {

                    }
                    return true;
 }

bool Parser::Sentencia()
{
    if (_currentToken.Type == Token::Id)
                {
                    _currentToken = _lexer.GetNextToken();
                    if (_currentToken.Type != Token::Equals)
                        return false;
                    _currentToken = _lexer.GetNextToken();
                    if (!E())
                        return false;
                    if (_currentToken.Type != Token::EndOfFile)
                        return false;
                    _currentToken = _lexer.GetNextToken();
                }
                else if (_currentToken.Type == Token::Print)
                {
                    _currentToken = _lexer.GetNextToken();
                    if(!E())
                        return false;
                    if (_currentToken.Type != Token::EndOfFile)
                        return false;
                    _currentToken = _lexer.GetNextToken();
                }
                else
                    return false;
                return true;
}

bool Parser::E()
{
    if (T())
                {
                    if (!Ep())
                        return false;
                }
                else
                {
                    return false;
                }

                return true;
}

bool Parser::Ep()
{
    if (_currentToken.Type == Token::Sum || _currentToken.Type == Token::Substract)
                {
                    _currentToken = _lexer.GetNextToken();
                    if (T())
                    {
                        if(!Ep())
                            return false;
                    }
                    else
                    {
                        return false;
                    }
                }
                //epsilon
                else
                {

                }
                return true;
}

bool Parser:: T()
{
    if (F())
                {
                    if (!Tp())
                        return false;
                }
                else
                {
                    return false;
                }

                return true;
}

bool Parser::Tp()
{
    if (_currentToken.Type == Token::Multiplication || _currentToken.Type == Token::Division)
                {
                    _currentToken = _lexer.GetNextToken();
                    if (F())
                    {
                        if (!Tp())
                            return false;
                    }
                    else
                    {
                        return false;
                    }
                }
                //epsilon
                else
                {

                }
                return true;
}

bool Parser::F()
{
    if (_currentToken.Type == Token::Id || _currentToken.Type == Token::Number)
                {
                    _currentToken = _lexer.GetNextToken();
                }
                else if (_currentToken.Type == Token::LeftParenthesis)
                {
                    _currentToken = _lexer.GetNextToken();
                    if (!E())
                        return false;
                    if (_currentToken.Type != Token::RightParenthesis)
                        return false;
                    _currentToken = _lexer.GetNextToken();
                }
                else
                {
                    return false;
                }
                return true;
}

