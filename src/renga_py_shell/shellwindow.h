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

private:
    Ui::ShellWindow *ui;
};
#endif // SHELLWINDOW_H
