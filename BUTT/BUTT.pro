TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    TaxNode.cpp \
    TaxBuilder.cpp \
    SeqToKMers.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    TaxNode.h \
    Common.h \
    TaxBuilder.h \
    SeqToKMers.h

