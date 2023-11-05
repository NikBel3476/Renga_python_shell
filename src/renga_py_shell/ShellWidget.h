#ifndef SHELLWINDOW_H
#define SHELLWINDOW_H

#include "stdafx.h"

#include "PythonCodeEditor.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
    class ShellWidget;
}
QT_END_NAMESPACE

class ShellWidget : public QWidget
{
    Q_OBJECT

public:
    ShellWidget(Renga::IApplicationPtr rengaApp);
    ~ShellWidget();
    void insertPlainTextToOutput(QString *text);

private slots:
    void on_action_load_from_file_clicked();

    void on_output_space_textChanged();

    void on_code_space_textChanged();

    void on_pushButton_clicked();

    void on_command_run_script_clicked();

    void on_action_3_triggered();

    void on_action_5_triggered();

    void on_action_4_triggered();

    void on_action_6_triggered();

    void on_action_triggered();

    void on_action_Python_triggered();

    void on_action_Python_2_triggered();

    void on_command_run_script_triggered(QAction *arg1);

    void readStdOut();

private:
//    Ui::ShellWidget *ui;
    PythonCodeEditor* py_editor;
    // Inherited class for creating syntax highlighting logic
    Renga::IApplicationPtr rengaApp;
    std::unique_ptr<Ui::ShellWidget> ui;
    QProcess *proc;
};
#endif // SHELLWINDOW_H
