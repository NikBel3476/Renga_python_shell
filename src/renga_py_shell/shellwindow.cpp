#include "shellwindow.h"
#include "ui_shellwindow.h"

ShellWindow::ShellWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ShellWindow)
{
    ui->setupUi(this);
}

ShellWindow::~ShellWindow()
{
    delete ui;
}

