TEMPLATE = lib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

#Вывод в консоль лога в верной кодировке
#https://blog.mgsxx.com/?p=2979
QMAKE_EXTRA_TARGETS += before_build makefilehook

makefilehook.target = $(MAKEFILE)
makefilehook.depends = .beforebuild

PRE_TARGETDEPS += .beforebuild

before_build.target = .beforebuild
before_build.depends = FORCE
before_build.commands = chcp 1251

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    renga_loader.cpp \
    shellwindow.cpp

INCLUDEPATH += \
    "E:/30_Coding/SDK/RengaSDK/Cpp/Include" \
    "E:/30_Coding/SDK/RengaSDK/tlb" \
    "C:/Users/Georg/AppData/Local/Programs/Python/Python310/Include"

HEADERS += \
    renga_loader.hpp \
    shellwindow.h

FORMS += \
    shellwindow.ui

LIBS += -L"C:/Users/Georg/AppData/Local/Programs/Python/Python310/libs/python310.lib"


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
