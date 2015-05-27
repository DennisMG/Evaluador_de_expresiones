#include "lexer.h"
#include "token.h"
#include <QString>
#include <iostream>

using namespace std;

Lexer::Lexer(QString inputBuffer)
{

    _symbolIndex.insert('+',Token::Sum);
    _symbolIndex.insert('-',Token::Substract);
    _symbolIndex.insert('*',Token::Multiplication);
    _symbolIndex.insert('/',Token::Division);
    _symbolIndex.insert(';',Token::SemiColon);
    _symbolIndex.insert('(',Token::LeftParenthesis);
    _symbolIndex.insert('=',Token::Equals);
    _symbolIndex.insert(')',Token::RightParenthesis);


     _inputBuffer = inputBuffer;
     _currentPosition = 0;
     _currentSymbol = GetNextSymbol();

}

Lexer::Lexer()
{

}

char Lexer::GetNextSymbol(){
     if (_currentPosition >= _inputBuffer.length())
         return '\0';
     return _inputBuffer.at(_currentPosition++).toLatin1();
        }

Token Lexer::GetNextToken()
        {
            int currentState = 0;
            QString lexeme = "";

            while (true)
            {
                switch (currentState)
                {
                    case 0:
                        if (_currentSymbol==' ')
                        {
                            _currentSymbol = GetNextSymbol();
                            currentState = 0;
                        }
                        else if (isalpha(_currentSymbol))
                        {
                            lexeme += _currentSymbol;
                            _currentSymbol = GetNextSymbol();
                            currentState = 1;
                        }
                        else if (isdigit(_currentSymbol))
                        {
                            lexeme += _currentSymbol;
                            _currentSymbol = GetNextSymbol();
                            currentState = 3;
                        }
                        else if (_symbolIndex.contains(_currentSymbol))
                        {
                            lexeme += _currentSymbol;
                            _currentSymbol = GetNextSymbol();
                            currentState =7;
                        }
                        else if (_currentSymbol=='\0')
                        {
                            lexeme += _currentSymbol;
                            currentState = 8;
                        }
                        else
                        {
                            cout<<"Simbolo no reconocido "+_currentSymbol;
                            //throw new LexicalException("Simbolo no reconocido "+_currentSymbol);
                        }
                        break;
                    case 1:
                        if (isalnum(_currentSymbol))
                        {
                            lexeme += _currentSymbol;
                            _currentSymbol = GetNextSymbol();
                            currentState = 1;
                        }
                        else
                        {
                            currentState = 2;
                        }
                        break;
                    case 2:
                    array = lexeme.toLocal8Bit();
                    buffer = array.data();

                       /* if (_reservedWordsIndex.contains(lexeme)
                            return Token::Token(_reservedWordsIndex[lexeme],lexeme);
                        else*/
                            return Token::Token(Token::TokenType::Id,lexeme);
                        break;
                    case 3:
                        if (isdigit(_currentSymbol))
                        {
                            lexeme += _currentSymbol;
                            _currentSymbol = GetNextSymbol();
                            currentState = 3;
                        }
                        else if (_currentSymbol=='.')
                        {
                            lexeme += _currentSymbol;
                            _currentSymbol = GetNextSymbol();
                            currentState = 4;
                        }
                        else
                        {
                            currentState = 6;
                        }
                        break;
                    case 4:
                        if (isdigit(_currentSymbol))
                        {
                            lexeme += _currentSymbol;
                            _currentSymbol = GetNextSymbol();
                            currentState = 5;
                        }
                        else
                        {
                            cout<<"Se esperaba digito en vez de "+_currentSymbol;
                            //throw new LexicalException("Se esperaba digito en vez de "+_currentSymbol);
                        }
                        break;
                    case 5:
                        if (isdigit(_currentSymbol))
                        {
                            lexeme += _currentSymbol;
                            _currentSymbol = GetNextSymbol();
                            currentState = 5;
                        }
                        else
                        {
                            currentState = 6;
                        }
                        break;
                    case 6:
                        return Token::Token(Token::TokenType::Number,lexeme);
                                //new Token { Type = TokenType.Number, Lexeme = lexeme };
                        break;
                    case 7:
                        array = lexeme.toLocal8Bit();
                        buffer = array.data();

                        return Token::Token(_symbolIndex[*buffer],lexeme);
                        //return new Token { Type = _symbolIndex[lexeme], Lexeme = lexeme };
                        break;
                    case 8:
                        return Token::Token(Token::EndOfFile,"$");
                        //return new Token { Type = TokenType.EndOfFile, Lexeme = "$" };
                        break;
                }
            }
        }



