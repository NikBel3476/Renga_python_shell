#include <QDesktopServices>
#include <QFileDialog>
#include <QStyle>

#include "ShellWidget.h"
#include "ui_shellwidget.h"
#include "python_code_handler.hpp"


ShellWidget::ShellWidget(Renga::IApplicationPtr rengaApplication) :
    QWidget(nullptr, Qt::Tool),
    rengaApp(rengaApplication)
//    ui(new Ui::ShellWidget)
{
    ui.reset(new Ui::ShellWidget());
    ui->setupUi(this);

//    this->py_editor = new PythonCodeEditor(this);
//    //QRect* reqt = new QRect(10, 40, 861, 341);
//    py_editor->setGeometry(10, 60, 861, 340);
//
//    // FIXME: remove hardcoded path
//    QFile inputFile("E:\\Temp\\test_1.py");
//    this->py_editor->insertPlainText("");
//    if (inputFile.open(QIODevice::ReadOnly))
//    {
//        QTextStream in(&inputFile);
//        while (!in.atEnd())
//        {
//            QString line = in.readLine();
//            this->py_editor->appendPlainText(line);
//        }
//        inputFile.close();
//    }
}

ShellWidget::~ShellWidget()
{

}


void ShellWidget::on_action_load_from_file_clicked()
{
 //load script from file
}


void ShellWidget::on_output_space_textChanged()
{
    //save to local file
}


void ShellWidget::on_code_space_textChanged()
{
    //save result to temp file
    //https://evileg.com/en/post/437/
    //colorzedata
    // We load the text for search in syntax highlighting
}


void ShellWidget::on_pushButton_clicked()
{
    //save to file
}


void ShellWidget::on_command_run_script_clicked()
{
    //execute scipt in code_space
    QString code_as_text = this->py_editor->toPlainText();
    python_run_code(&code_as_text, this->ui->output_space);
}

void ShellWidget::on_action_3_triggered()
{
    //перемещение в репозиторий с программой
    QDesktopServices::openUrl(QUrl("https://github.com/GeorgGrebenyuk/Renga_python_shell", QUrl::TolerantMode));
}


void ShellWidget::on_action_5_triggered()
{
    //= запуск кода
    this->ShellWidget::on_command_run_script_clicked();
}


void ShellWidget::on_action_4_triggered()
{
    //перемещение в ReadMe
    QDesktopServices::openUrl(QUrl("https://github.com/GeorgGrebenyuk/Renga_python_shell/blob/main/README.md", QUrl::TolerantMode));
}


void ShellWidget::on_action_6_triggered()
{
    //перемещение в Issues
    QDesktopServices::openUrl(QUrl("https://github.com/GeorgGrebenyuk/Renga_python_shell/issues", QUrl::TolerantMode));
}


void ShellWidget::on_action_triggered()
{
    //close form
    this->close();
}


void ShellWidget::on_action_Python_triggered()
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


void ShellWidget::on_action_Python_2_triggered()
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


void ShellWidget::on_command_run_script_triggered(QAction *arg1)
{
    this->on_command_run_script_clicked();
}

