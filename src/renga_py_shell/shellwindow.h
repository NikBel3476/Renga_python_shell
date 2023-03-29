#ifndef SHELLWINDOW_H
#define SHELLWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ShellWindow; }
QT_END_NAMESPACE

class ShellWindow : public QMainWindow
{
    Q_OBJECT

public:
    ShellWindow(QWidget *parent = nullptr);
    ~ShellWindow();

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

private:
    Ui::ShellWindow *ui;
};
#endif // SHELLWINDOW_H
