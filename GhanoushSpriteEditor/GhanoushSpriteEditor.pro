QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    actionstate.cpp \
    callbackoptions.cpp \
    colorinverterbrush.cpp \
    hardcirclestencilgenerator.cpp \
    imagesizedialog.cpp \
    main.cpp \
    rainbowbrush.cpp \
    rainbowspraycanbrush.cpp \
    spraycanbrush.cpp \
    spriteeditormodel.cpp \
    pixelbrush.cpp \
    pixeleraser.cpp \
    pointer2darray.cpp \
    spriteeditorvc.cpp \
    softcirclestencilgenerator.cpp \
    squarestencilgenerator.cpp \
				renderarea.cpp \
				gaussianblurbrush.cpp \
				gaussianstencilgenerator.cpp

HEADERS += \
    brush.h \
    colorinverterbrush.h \
    hardcirclestencilgenerator.h \
    imagesizedialog.h \
    istencilgenerator.h \
    rainbowbrush.h \
    rainbowspraycanbrush.h \
    softcirclestencilgenerator.h \
    spraycanbrush.h \
    spriteeditorvc.h \
    squarestencilgenerator.h \
    renderarea.h \
    actionstate.h \
    callbackoptions.h \
    spriteeditormodel.h \
    spriteeditorvc.h \
    itool.h \
    pixelbrush.h \
    pixeleraser.h \
    pointer2darray.h \
				stencil.h \
				gaussianblurbrush.h \
				gaussianstencilgenerator.h


FORMS += \
    imagesizedialog.ui \
    spriteeditorvc.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    paint-brush.svg \
    pen.svg \
    res/paint-brush.svg \
    res/pen.svg

RESOURCES += \
    resources.qrc
