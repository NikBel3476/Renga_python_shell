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

private:
    Ui::ShellWindow *ui;
};
#endif // SHELLWINDOW_H
