#-------------------------------------------------
#
# Project created by QtCreator 2014-11-10T11:28:46
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = SearchEngine
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    word.cpp \
<<<<<<< HEAD
    document.cpp \
    parser.cpp \
    avltree.cpp
=======
    parser.cpp
>>>>>>> a4b30b808e9ebed28bca3691a110c700818663fc

HEADERS += \
    pugixml/src/pugixml.hpp \
    rapidxml-1.13/rapidxml.hpp \
    word.h \
    Stemmer.h \
    parser.h \
    avltree.h
