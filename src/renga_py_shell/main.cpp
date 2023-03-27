#include "shellwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShellWindow w;
    w.show();
    return a.exec();
}
