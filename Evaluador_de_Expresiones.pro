#-------------------------------------------------
#
# Project created by QtCreator 2014-12-03T14:44:37
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Evaluador_de_Expresiones
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    lexer.cpp \
    parser.cpp \
    token.cpp

HEADERS += \
    lexer.h \
    parser.h \
    token.h
