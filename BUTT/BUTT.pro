TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

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

