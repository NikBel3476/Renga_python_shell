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
    Py_Initialize();

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


void ShellWindow::on_command_run_script_clicked()
{
    //execute scipt in code_space
    QString code_as_text = this->ui->code_space->toPlainText();

    char* argv[] = { (char*)"RengaPythonShell" };
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
       if (program == NULL) {
           fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
           exit(1);
       }
       Py_SetProgramName(program);  /* optional but recommended */
    Py_Initialize();
       PyRun_SimpleString(code_as_text.toStdString().c_str());
       if (Py_FinalizeEx() < 0) {
           exit(120);
       }
       PyMem_RawFree(program);
}

