#define PY_SSIZE_T_CLEAN
#include <Python.h>
#undef B0

#include "shellwindow.h"
#include "ui_shellwindow.h"
#include <QDesktopServices>
#include <QFileDialog>
#include <QStyle>
#include "python_code_editor.hpp"


ShellWindow::ShellWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ShellWindow)
{
    ui->setupUi(this);
    this->py_editor = new python_code_editor(this);
    //QRect* reqt = new QRect(10, 40, 861, 341);
    py_editor->setGeometry(40, 60, 861, 321);

    //Проверить Python
    Py_Initialize();

    QFile inputFile("E:\\Temp\\py_test2.py");
    this->py_editor->insertPlainText("");
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            this->py_editor->appendPlainText(line);
        }
        inputFile.close();
    }


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
    //https://evileg.com/en/post/437/
    //colorzedata
    // We load the text for search in syntax highlighting
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

void ShellWindow::on_action_3_triggered()
{
    //перемещение в репозиторий с программой
    QDesktopServices::openUrl(QUrl("https://github.com/GeorgGrebenyuk/Renga_python_shell", QUrl::TolerantMode));
}


void ShellWindow::on_action_5_triggered()
{
    //= запуск кода
    this->ShellWindow::on_command_run_script_clicked();
}


void ShellWindow::on_action_4_triggered()
{
    //перемещение в ReadMe
    QDesktopServices::openUrl(QUrl("https://github.com/GeorgGrebenyuk/Renga_python_shell/blob/main/README.md", QUrl::TolerantMode));
}


void ShellWindow::on_action_6_triggered()
{
    //перемещение в Issues
    QDesktopServices::openUrl(QUrl("https://github.com/GeorgGrebenyuk/Renga_python_shell/issues", QUrl::TolerantMode));
}


void ShellWindow::on_action_triggered()
{
    //close form
    this->close();
}


void ShellWindow::on_action_Python_triggered()
{
    //open py script and loading them in code_space
    QString file1Name = QFileDialog::getOpenFileName(this,
             tr("Open Python-script"), "", tr("Python-scripts (*.py)"));
    QFile inputFile(file1Name);
    this->py_editor->insertPlainText("");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
            this->py_editor->appendPlainText(line);
       }
       inputFile.close();
    }
}


void ShellWindow::on_action_Python_2_triggered()
{
    //save inner of code_space to file
    QString code_string = this->py_editor->toPlainText();
    QString save_filename = QFileDialog::getSaveFileName(this,tr("Save Python scripts"), "",
        tr("Python-scripts (*.py)"));

    QFile file(save_filename);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << code_string;
    }
    file.close();
}


void ShellWindow::on_command_run_script_triggered(QAction *arg1)
{
    this->on_command_run_script_clicked();
}

