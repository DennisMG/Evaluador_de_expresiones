#include <QCoreApplication>
#include <QTextStream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "parser.cpp"
using namespace std;

const char * expressionToParse;

char peek()
{
    return *expressionToParse;
}

char get()
{
    return *expressionToParse++;
}

int expression();

int number()
{
    int result = get() - '0';
    while (peek() >= '0' && peek() <= '9')
    {
        result = 10*result + get() - '0';
    }
    return result;
}

int factor()
{
    if (peek() >= '0' && peek() <= '9')
        return number();
    else if (peek() == '(')
    {
        get(); // '('
        int result = expression();
        get(); // ')'
        return result;
    }
    else if (peek() == '-')
    {
        get();
        return -expression();
    }
    return 0; // error
}

int term()
{
    int result = factor();
    while (peek() == '*' || peek() == '/')
        if (get() == '*')
            result *= factor();
        else
            result /= factor();
    return result;
}

int expression()
{
    int result = term();
    while (peek() == '+' || peek() == '-')
        if (get() == '+')
            result += term();
        else
            result -= term();
    return result;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString input;
    QMap<QString, int> _resultList;

    do
    {
        cout << "Ingresar expresion a evaluar" << endl;
        QTextStream s(stdin);
        input = s.readLine();

        if(_resultList.contains(input))
        {
            cout << _resultList.value(input) << endl;
        }else
        {
            Parser parser = Parser::Parser(input);

            if(parser.Parse())
            {
                if(input.contains('='))
                {
                    int equalsPosition=input.indexOf('=');
                    QString variable = input.left(equalsPosition);
                    QString expresion = input.right(input.length()-equalsPosition-1);

                    foreach(QString key,_resultList.keys())
                    {
                        if(expresion.contains(key))
                        {
                            int value = _resultList[key];
                            expresion.replace(key,QString::number(value));
                        }
                    }

                    QByteArray ba = expresion.toLatin1();
                    const char *c_str2 = ba.data();

                    expressionToParse = c_str2;

                    int result = expression();

                    if(_resultList.contains(variable))
                    {
                        _resultList[variable]=result;

                    }else
                    {
                        _resultList.insert(variable,result);
                    }

                    cout << "Resultado: " << result << endl;
                }
            }
            else
            {
                cout << "Sentencia mal redactada" << endl;
            }
        }

    }while( input!="-1" );

    return a.exec();
}
