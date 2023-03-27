#define PY_SSIZE_T_CLEAN
#include <Python.h>
#undef B0

#include "shellwindow.h"
#include "ui_shellwindow.h"



ShellWindow::ShellWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ShellWindow)
{
    ui->setupUi(this);
    //Проверить Python
}

ShellWindow::~ShellWindow()
{
    delete ui;
}


void ShellWindow::on_action_load_from_file_clicked()
{
 //load script from file
}


void ShellWindow::on_output_space_textChanged()
{
    //save to local file
}


void ShellWindow::on_code_space_textChanged()
{
    //save result to temp file
}


void ShellWindow::on_pushButton_clicked()
{
    //save to file
}

