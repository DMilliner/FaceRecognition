#-------------------------------------------------
#
# Project created by QtCreator 2013-02-06T10:45:51
#
#-------------------------------------------------

#QT       += multimedia

TARGET = detection_visage
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp

HEADERS  += dialog.h

FORMS    += dialog.ui

# pour openCV
CONFIG+=link_pkgconfig
PKGCONFIG+=opencv
