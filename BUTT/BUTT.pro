TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE *= -O3

SOURCES += main.cpp \
    TaxNode.cpp \
    TaxBuilder.cpp \
    SeqToKMers.cpp \
    Search/NameNode.cpp \
    Search/TaxSearch.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    TaxNode.h \
    Common.h \
    TaxBuilder.h \
    SeqToKMers.h \
    Search/NameNode.h \
    Search/TaxSearch.h

