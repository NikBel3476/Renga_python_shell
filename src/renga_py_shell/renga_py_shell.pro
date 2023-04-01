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

# Установка формата библиотеки для Python
CONFIG(debug, debug|release) {
  DEBUG_EXT = _d
  DESTDIR = $$OUT_PWD/debug
} else {
  DEBUG_EXT =
  DESTDIR = $$OUT_PWD/release
}
PYTHON_PATH = C:/Users/Georg/AppData/Local/Programs/Python/Python310/
PYTHON_LIB =  C:/Users/Georg/AppData/Local/Programs/Python/Python310/libs/
RENGA_SDK = E:/30_Coding/SDK/RengaSDK/

LIBS += $${PYTHON_LIB}/python310$${DEBUG_EXT}.lib

SOURCES += \
    python_code_editor.cpp \
    python_code_handler.cpp \
    renga_loader.cpp \
    shellwindow.cpp

INCLUDEPATH += \
    $$RENGA_SDK/Cpp/Include \
    $$RENGA_SDK/tlb \
    $${PYTHON_PATH}/include

HEADERS += \
    python_code_editor.hpp \
    python_code_handler.hpp \
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
    renga_py_shell_d.rndesc \
    repa_logo.png \
    ui_form_run_script.png \
    rengacomapi.tlh

RESOURCES += \
    qt_resources_data.qrc

#События после сборки
copy_to_build.path = $$DESTDIR
copy_to_build.files = icons/*
copy_to_build2.path = $$DESTDIR
copy_to_build2.files = renga_py_shell.rndesc

INSTALLS += \
    copy_to_build \
    copy_to_build2
