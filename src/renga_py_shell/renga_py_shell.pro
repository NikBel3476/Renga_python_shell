QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    renga_loader.cpp \
    shellwindow.cpp

INCLUDEPATH += \
    "E:/30_Coding/SDK/RengaSDK/Cpp/Include" \
    "E:/30_Coding/SDK/RengaSDK/tlb" \

HEADERS += \
    renga_loader.hpp \
    shellwindow.h

FORMS += \
    shellwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    py_logo.png \
    renga_py_shell.rndesc \
    repa_logo.png \
    ui_form_run_script.png \
    rengacomapi.tlh
