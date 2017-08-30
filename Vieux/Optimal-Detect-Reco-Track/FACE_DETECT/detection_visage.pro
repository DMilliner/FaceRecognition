#-------------------------------------------------
#
# Project created by QtCreator 2013-02-06T10:45:51
#
#-------------------------------------------------

#QT       += multimedia

TARGET = detection_visage
TEMPLATE = app



SOURCES += \
    mainwindow.cpp \
    main.cpp \
    facedetection.cpp \
    add_visage.cpp

HEADERS  += \
    facedetection.h \
    mainwindow.h \
    add_visage.h

FORMS    += \
    mainwindow.ui \
    add_visage.ui

# pour openCV
CONFIG+=link_pkgconfig
PKGCONFIG+=opencv

# pour OpenMP

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp
