QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    err.cpp \
    filtrinterface.cpp \
    fir_f.cpp \
    iir_f.cpp \
    main.cpp \
    mainwindow.cpp \
    myfiltrgui.cpp \
    myparamplot.cpp \
    qcustomplot.cpp \
    rangeslider.cpp \
    signal.cpp \
    signalinterface.cpp \
    signalwork.cpp

HEADERS += \
    err.h \
    filtrinterface.h \
    fir_f.h \
    iir_f.h \
    mainwindow.h \
    myfiltrgui.h \
    myparamplot.h \
    qcustomplot.h \
    rangeslider.h \
    signal.h \
    signalinterface.h \
    signalwork.h

FORMS += \
    mainwindow.ui

QMAKE_CXXFLAGS += -march=native -O0

QMAKE_CXXFLAGS_RELEASE += -O0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
