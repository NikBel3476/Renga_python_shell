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

# check if debug or release
CONFIG(debug, debug|release) {
  DEBUG_EXT = _d
} else {
  DEBUG_EXT =
}
PYTHON_PATH = C:/Users/Georg/AppData/Local/Programs/Python/Python310/
PYTHON_LIB =  C:/Users/Georg/AppData/Local/Programs/Python/Python310/libs/
RENGA_SDK = E:/30_Coding/SDK/RengaSDK/

win32:INCLUDEPATH += $${PYTHON_PATH}/include
win32:LIBS += $${PYTHON_LIB}/python310$${DEBUG_EXT}.lib

SOURCES += \
    renga_loader.cpp \
    shellwindow.cpp

INCLUDEPATH += \
    $$RENGA_SDK/Cpp/Include \
    $$RENGA_SDK/tlb \

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

RESOURCES += \
    qt_resources_data.qrc
