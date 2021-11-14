QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    StencilTester.cpp \
    actionstate.cpp \
    callbackoptions.cpp \
    main.cpp \
    pixelbrush.cpp \
    pixeleraser.cpp \
    pointer2darray.cpp \
				spriteeditorvc.cpp \
    softcirclestencilgenerator.cpp \
				spriteeditorvc.cpp \
				squarestencilgenerator.cpp \
				renderarea.cpp

HEADERS += \
    istencilgenerator.h \
    softcirclestencilgenerator.h \
    spriteeditorvc.h \
    squarestencilgenerator.h

HEADERS += \
    renderarea.h \
    actionstate.h \
    callbackoptions.h \
    itool.h \
    pixelbrush.h \
    pixeleraser.h \
    pointer2darray.h \
    spriteeditorvc.h

FORMS += \
    spriteeditorvc.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
